/**
 * Project Name  : WiFi power extension board
 * Author Name	 : Ashish Kushwaha
 * Email	 : ashish.armofthings@gmail.com
 * Website	 : www.armofthings.com
 */

#define			debug		                 1	   	///< Debug option 1 enable 0 disable
#define			new_EEP_location	 	 0		///< For detecting the fresh ESP chip
#define			EEP_strings_start		 1		///< Starting location of the Network configuration String
#define			ON				 1		///< Defines ON for relays
#define			OFF				 0		///< Defines OFF for relays
#define			N_RELAY				 4		///< Numbers of relay supported in this firmware

const int RELAY[N_RELAY] = {5,13,14,16};		///< Relays and their respective gpio pin numbers
const char *DNSName	= "wifiext";			///< Host name on the network url

enum{							///< Representation of the states
	NONE,						///< None state
	AP_MODE,					///< Acting as a Access point
	STA_MODE					///< Acting as a Wifi station
};
int runMode = NONE;					///< Default running state variable, Initially NONE

/**
 * ESP8266 Header files
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <Ticker.h>

extern "C" {
#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"
#include "mem.h"
#include "user_interface.h"
#include "cont.h"
}

Ticker tick;						///< Timer object for creating the timer event
ESP8266WebServer server(80);				///< server at this port with IP 192.168.4.1
int16_t second = 0;               			///< variable for storing second count
String cli_MAC = WiFi.macAddress();			///< Mac address read for this device

struct EEP_strings {					///< Strings which have stored in eeprom
  char  Network_SSID[32];				///< Name of SSID to connect
  char  Network_password[32];				///< password of that network
};
struct EEP_strings network;				///< EEP_string instance for network configuration

struct states {						///< State Variable
	struct states *next;				///< State Variable pointer for holding the next state, Link list
	int(*stateFunc)();				///< State function pointer for hooking up the function
};
struct states STA_state,AP_state,*running;		///< Two states Station mode and AP mode

/**
 * Function For turning Relays ON and off
 * Arguments : Relay number
 * Returns 	 : void
 */
void relayTurn(int relay,int state){
	digitalWrite(RELAY[relay],state);
}

/**
 * Wrapper function For reading the relay status
 * Arguments : Relay number
 * Returns	 : State of the relay
 */
int relayRead(int relay){
	return digitalRead(RELAY[relay]);
}

/**
 * Function that takes structure and stores that into given location
 * Arguments : address where the data has to be stored, data structure pointer and size of that structure
 * Returns	 : void
 */
void EEPROM_write_obj(int addr,char * ptr,int siz){
  for(int i= addr;i<(siz + addr);i++){
    EEPROM.write(i,*(ptr));
    ptr++;
    EEPROM.commit();
  }
}

/**
 * Function for reading the data from eeprom
 * Arguments: address from the data has to be read, data structure pointer and size of that structure
 * returns void
 */
void EEPROM_read_obj(int addr, char * ptr, int siz){
  for(int i= addr;i<(siz + addr);i++){
    *(ptr) = EEPROM.read(i);
    ptr++;
  }
}

/**
 * Calling this function would restart the hardware from GPIO signal at 12th
 * Arguments : Void
 * Returns	 : void
 */
void system_restart_hard(void){
	EEPROM.end();					///< End the EEPROM
	delay(100);					///< Wait for buffer empty before restart
	pinMode(12,OUTPUT);				///< Make Reset pin output
	digitalWrite(12,LOW);				///< Set low to restart the system
}

/**
 * This function gets called every second as a callback
 * Arguments : Void
 * Returns	 : void
 */
void count_sec(void){
	digitalWrite(2,!digitalRead(2)); 	///< Toggle the ESP onboard LED
	second++;				///< Increment the second to count the second
#if debug
	Serial.print("Seconds=");		///< Print the debug information
	Serial.println(second);
	Serial.print("STA IP=");
	Serial.println(WiFi.localIP());
#endif
}

/**
 * This function reads the status of the relay, parses and returns the status
 * Arguments : Void
 * Returns	 : String, that has to be returned
 */
String getRelays(void){
	String retString = "Relay status:";					///< Initial Header String
	for(int i=0;i<N_RELAY;i++){
		retString += (" RELAY"+String(i)+"="+String(relayRead(i)));	///< Append the string with the status
	}
return retString;								///< Return that string
}

/**
 * This function takes the Payload string and returns that into the integer form
 * Arguments : String between '{' and '}' Ex: {1},{0},{100}
 * Returns	 : integer between those parenthesis
 */
uint32_t parseResponse(String serverArg){
	char *start,*end;						///< Pointers for holding the address of starting and ending
	String start_ind = "{";						///< Starting character
	String end_ind = "}";						///< Terminating character
	uint32_t ret_int=0;						///< Variable for holding return integer
	start = strstr(serverArg.c_str(),start_ind.c_str())+1;		///< find the version starting char pointer
	end	=	strstr(serverArg.c_str(),end_ind.c_str());	///< find the version ending char pointer
	for(;start<end;start++){					///< store the response between them in string
		ret_int = (ret_int*10)+((int)(*start)-48);		///< convert it to the 32 bit integer before storing
		}
	return ret_int;
}

/**
 * This function gets called every time when new client gets connected for sensor configuration
 * Arguments : Nothing
 * Returns	 : Nothing
 */
void handleConfig(void) {
#if debug
	Serial.println("configuration handle");
	for(char i=0;i<server.args();i++){
		Serial.println(server.arg(i));				///< Print all the arguments send by the client
	}
#endif
	if(server.arg("ssid")!="")												///< If argument of ssid has value
		strcpy(network.Network_SSID,server.arg("ssid").c_str());	///< Store this value to the structure variable
	if(server.arg("pass")!="") 												///< If argument of password has value
		strcpy(network.Network_password,server.arg("pass").c_str());		///< Store this value to the structure variable
	EEPROM_write_obj(EEP_strings_start,						///< Store the whole structure into the EEPROM
					(char *)(&network),sizeof(struct EEP_strings));
	server.send(200, "text/html", "changed configuration to\nNetwork = "+	///< Send the settings to the client to reflect changes
								   String(network.Network_SSID) +
								   "\nPassword = "+
								   String(network.Network_password) +
								   "\nrebooting in 3 sec");
	tick.detach();															///< Stop the timer callback
	delay(1000);															///< Wait for one second
	system_restart_hard();													///< Restart the hardware
}

/**
 * This function gets called every time when new client gets connected for Relay configuration
 * Arguments : Nothing
 * Returns	 : Nothing
 */
void handleRelay(void){
#if debug
	Serial.println("handleRelay");							///< Print Serial information for debug
	for(char i=0;i<server.args();i++){
		Serial.println(server.arg(i));						///< Print each server argument
	}
#endif
	for(int i=0;i<N_RELAY;i++){
		String state = server.arg("RELAY"+String(i));				///< Parse the received comma
		if(state!="")													///< If state has non empty character
			relayTurn(i,parseResponse(server.arg("RELAY"+String(i))));	///< Turn the status accordingly
	}
	server.send(200, "text/html",getRelays());					///< Send the Relay status to the client as the acknowledge
}

/**
 * This function initializes the EEPROM when module gets woke up
 * Arguments: Nothing
 * Returns: Nothing
 */
void EEPROM_init(void){
	uint8_t new_byte = EEPROM.read(new_EEP_location);  			///< Look for new EEPROM location to detect if chip is new
#if debug
	Serial.println(new_byte);
#endif
	if(new_byte!=0){							///< If new ESP chip is detected
#if debug
		Serial.println("Initializing EEPROM first time");		///< Serial print the debug information
#endif
		strcpy(network.Network_SSID,"aasiyana s f");			///< Copy the default Network Name
		strcpy(network.Network_password,"9911775000");			///< Default password for that Network
		EEPROM_write_obj(EEP_strings_start,				///< Store into the EEPROM
				(char *)(&network),sizeof(struct EEP_strings));
		EEPROM.write(new_EEP_location,0);				///< Make the new byte old by writing it to zero
		EEPROM.commit();						///< commit this one byte changes
	}
	EEPROM_read_obj(EEP_strings_start,(char *)(&network),
			sizeof(struct EEP_strings)); 				///< Read the last saved values to the structure
#if debug
	Serial.println(network.Network_SSID);					///< Print the network information for debug purpose
	Serial.println(network.Network_password);
#endif
}

/**
 * This function starts the mDNS server and hooks up the server url callback function
 * Arguments: Nothing
 * Returns: Status 0 means fail, 1 means success
 */
int startServers(void){
	second=0;
#if debug
	Serial.println("Starting mDNS responder"); 		///< Print serial information for debugging
#endif
	while((!MDNS.begin(DNSName))&&(second<=10)) {		///< Start the mDNS server
		delay(100);
	}
	if(second>10){
#if debug							// Set for Station and Access point both
	Serial.println("FAILED!!!");				///< Print serial information for debugging
	return 0;
#endif
	}
#if debug
	Serial.println("started mDNS");				///< Print serial information for debugging
#endif
	server.on("/config", handleConfig);			///< set the http server at root
	server.on("/relays", handleRelay);			///< set the http server at root
	server.begin();						///< Start TCP (HTTP) server
#if debug
	Serial.println("TCP server started");			///< Print serial information for debugging
#endif
	MDNS.addService("http", "tcp", 80);			///< Add service to MDNS-SD
	return 1;						///< Return 1 in case of success
}

/**
 * This function puts the system into station mode by connecting it to the AP
 * and runs the Mdns server
 * Arguments: Nothing
 * Returns: Status STA_MODE if success, NONE if fail
 */
int setStaMode(void){
	second=0;
#if debug
		Serial.println("Setting STA Mode");
#endif
	while((!WiFi.mode(WIFI_STA))&&(second<=10)){
		delay(100);					///< Set for Station Mode with 10 second of timeout
	}
	if(second>10){
#if debug
		Serial.println("FAILED!!!");			///< Print serial information for debugging
#endif
		return NONE;
	}
#if debug
	Serial.println("connecting to wifi network");		///< Print serial information for debugging
#endif
	second=0;
	while((!WiFi.begin(network.Network_SSID,			///< Start the connection to AP with EEPROM saved network with 20 seconds timeout
			network.Network_password))&&(second<=20)){
		delay(100);
	}
	if(second>20){
#if debug
		Serial.println("FAILED!!!");			///< Print serial information for debugging if failed to connect
#endif
		return NONE;					///< Return from here
	}
#if debug
		Serial.println("begun");			///< Print serial information for debugging
#endif
		if(startServers()) return STA_MODE;		///< If mDNS starts after dhcp means success in STA mode setup
		else return NONE;				///< Else return NONE
}

/**
 * This function puts the system into AP mode by
 * and runs the Mdns server
 * Arguments: Nothing
 * Returns: Status AP_MODE if success, NONE if fail
 */
int setApMode(void){
	second=0;
	while((!WiFi.mode(WIFI_AP))&&(second<=10)){		///< Switch the ESP wifi into AP mode with 10 seconds of timeout
	delay(100);
	}
#if debug
	Serial.println("Setting AP Mode done..");		///< Print serial information for debugging
#endif
	if(second>10) {						///< If Timeout occurred
#if debug
		Serial.println("FAILED!!!");			///< Serial print FAIL
#endif
		return NONE;					///< And return from here
	}
	second=0;
	while((!WiFi.softAP(("EXT_"+cli_MAC).c_str(),
			"wifiext123"))&&second<=10){		///< Start access point with "EXT_'(mac of device)'" string with 10 seconds of timeout
	delay(100);
	}
#if debug
	Serial.println("Started AP");				///< Print Serial Information for debugging
#endif
	if(second>10){						///< If Timeout occurred
#if debug
		Serial.println("FAILED!!!");			///< Serial print FAIL
#endif
		return NONE;					///< And return from here
	}
	if(startServers()) return AP_MODE;			///< If mDNS starts after AP setup, means success in STA mode setup
	else return NONE;					///< Else Return from here
}

/**
 * This function configures system initially for peripherals and Memory
 * Arguments: Nothing
 * Returns	: Nothing
 */
void setup() {
	pinMode(2,OUTPUT);					///< Indication LED
	digitalWrite(2,LOW);					///< Make LED ON
	for(int i=0;i<N_RELAY;i++){				///< Set all the relay pin OUTPUT
		pinMode(RELAY[i],OUTPUT);
	}
	delay(10);
	for(int i=0;i<N_RELAY;i++){				///< Set all the RELAY OFF at initial
		relayTurn(RELAY[i],OFF);
	}
	delay(5000); 						///< wait for 5 second while power becomes stable
	system_update_cpu_freq(160);				///< CPU frequency 160 MHz
	EEPROM.begin(4000);					///< allocate 4000 byte in EEPROM maximum is 4096
#if debug
	Serial.begin(115200);					///< begin the serial at 115200 baud rate
	Serial.println();
#endif
	EEPROM_init();						///< EEPROM initialize
	tick.attach(1,count_sec);				///< attach the function count_sec() for every one second

	STA_state.stateFunc = &setStaMode;			///< Hook up the SetStaMode function as STA_state function
	AP_state.stateFunc = &setApMode;			///< Hook up the SetAPMode function as AP_state function
														///< Create Link list
	STA_state.next = &AP_state;				///< Attach the AP state as the next state of STA state
	AP_state.next = &STA_state;				///< Attach the STA state as the next state of AP state
	running = &STA_state;					///< Current running state is being STA state for connection
	running->stateFunc();					///< Call the STA state function for STA mode setup
	digitalWrite(2,HIGH);					///< Turn off the Indication LED
}

/**
 * This function runs after the setup function and run forever in loop
 * Arguments: Nothing
 * Returns	: Nothing
 */
void loop() {
	if(second>=30){						///< Wait for 30 seconds
		if(!WiFi.isConnected()){			///< If wifi is not connected to the AP in STA mode
#if debug
			Serial.println("Toggling states");	///< Print the Debug information that state is being changed
#endif
			running = running->next;		///< Change the current state of the system
			runMode=running->stateFunc();		///< Call the state function
		}
		if(runMode==AP_MODE) second = -270;		///< If device has entered into the AP mode,
								///< Make the second delay 5 minutes to stay in this mode

		else second = 0;				///< else in STA mode check every 30 second
	}
	server.handleClient();					///< handle the client at server
}
