################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries/Ticker/examples/TickerParameter/subdir.mk
-include libraries/Ticker/examples/TickerBasic/subdir.mk
-include libraries/Ticker/subdir.mk
-include libraries/SPI/subdir.mk
-include libraries/SD/src/utility/subdir.mk
-include libraries/SD/src/subdir.mk
-include libraries/SD/examples/listfiles/subdir.mk
-include libraries/SD/examples/ReadWrite/subdir.mk
-include libraries/SD/examples/Files/subdir.mk
-include libraries/SD/examples/DumpFile/subdir.mk
-include libraries/SD/examples/Datalogger/subdir.mk
-include libraries/SD/examples/CardInfo/subdir.mk
-include libraries/OneWire/examples/DS250x_PROM/subdir.mk
-include libraries/OneWire/examples/DS2408_Switch/subdir.mk
-include libraries/OneWire/examples/DS18x20_Temperature/subdir.mk
-include libraries/OneWire/subdir.mk
-include libraries/ESP8266mDNS/examples/mDNS_Web_Server/subdir.mk
-include libraries/ESP8266mDNS/examples/mDNS-SD_Extended/subdir.mk
-include libraries/ESP8266mDNS/examples/OTA-mDNS-SPIFFS/subdir.mk
-include libraries/ESP8266mDNS/subdir.mk
-include libraries/ESP8266httpUpdate/src/subdir.mk
-include libraries/ESP8266httpUpdate/examples/httpUpdateSPIFFS/subdir.mk
-include libraries/ESP8266httpUpdate/examples/httpUpdate/subdir.mk
-include libraries/ESP8266WiFi/src/subdir.mk
-include libraries/ESP8266WiFi/examples/WiFiWebServer/subdir.mk
-include libraries/ESP8266WiFi/examples/WiFiTelnetToSerial/subdir.mk
-include libraries/ESP8266WiFi/examples/WiFiScan/subdir.mk
-include libraries/ESP8266WiFi/examples/WiFiMulti/subdir.mk
-include libraries/ESP8266WiFi/examples/WiFiClientEvents/subdir.mk
-include libraries/ESP8266WiFi/examples/WiFiClientBasic/subdir.mk
-include libraries/ESP8266WiFi/examples/WiFiClient/subdir.mk
-include libraries/ESP8266WiFi/examples/WiFiAccessPoint/subdir.mk
-include libraries/ESP8266WiFi/examples/NTPClient/subdir.mk
-include libraries/ESP8266WiFi/examples/HTTPSRequest/subdir.mk
-include libraries/ESP8266WebServer/src/subdir.mk
-include libraries/ESP8266WebServer/examples/WebUpdate/subdir.mk
-include libraries/ESP8266WebServer/examples/SimpleAuthentification/subdir.mk
-include libraries/ESP8266WebServer/examples/SDWebServer/subdir.mk
-include libraries/ESP8266WebServer/examples/HttpBasicAuth/subdir.mk
-include libraries/ESP8266WebServer/examples/HelloServer/subdir.mk
-include libraries/ESP8266WebServer/examples/FSBrowser/subdir.mk
-include libraries/ESP8266WebServer/examples/AdvancedWebServer/subdir.mk
-include libraries/ESP8266HTTPClient/src/subdir.mk
-include libraries/ESP8266HTTPClient/examples/StreamHttpClient/subdir.mk
-include libraries/ESP8266HTTPClient/examples/ReuseConnection/subdir.mk
-include libraries/ESP8266HTTPClient/examples/BasicHttpClient/subdir.mk
-include libraries/ESP8266HTTPClient/examples/Authorization/subdir.mk
-include libraries/EEPROM/examples/eeprom_write/subdir.mk
-include libraries/EEPROM/examples/eeprom_read/subdir.mk
-include libraries/EEPROM/examples/eeprom_clear/subdir.mk
-include libraries/EEPROM/subdir.mk
-include libraries/DallasTemperature/examples/setUserData/subdir.mk
-include libraries/DallasTemperature/examples/oneWireSearch/subdir.mk
-include libraries/DallasTemperature/examples/WaitForConversion2/subdir.mk
-include libraries/DallasTemperature/examples/WaitForConversion/subdir.mk
-include libraries/DallasTemperature/examples/TwoPin_DS18B20/subdir.mk
-include libraries/DallasTemperature/examples/Tester/subdir.mk
-include libraries/DallasTemperature/examples/Single/subdir.mk
-include libraries/DallasTemperature/examples/Simple/subdir.mk
-include libraries/DallasTemperature/examples/Multiple/subdir.mk
-include libraries/DallasTemperature/examples/Multibus_simple/subdir.mk
-include libraries/DallasTemperature/examples/AlarmHandler/subdir.mk
-include libraries/DallasTemperature/examples/Alarm/subdir.mk
-include libraries/DallasTemperature/subdir.mk
-include libraries/ArduinoOTA/examples/OTALeds/subdir.mk
-include libraries/ArduinoOTA/examples/BasicOTA/subdir.mk
-include libraries/ArduinoOTA/subdir.mk
-include core/core/umm_malloc/subdir.mk
-include core/core/spiffs/subdir.mk
-include core/core/libb64/subdir.mk
-include core/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
arduino.ar \

ELF += \
WiFiEXT.elf \

HEX += \
WiFiEXT.hex \


# All Target
all: WiFiEXT

# Tool invocations
WiFiEXT: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/../../../tools/xtensa-lx106-elf-gcc/2.0-26-gb404fb9/bin/xtensa-lx106-elf-size" -A "/home/ashish/workspace_neon/WiFiEXT/Release/WiFiEXT.elf"
	@echo 'Finished building target: $@'
	@echo ' '

arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/../../../tools/xtensa-lx106-elf-gcc/2.0-26-gb404fb9/bin/xtensa-lx106-elf-ar" cru "/home/ashish/workspace_neon/WiFiEXT/Release/arduino.ar"  arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

WiFiEXT.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/../../../tools/xtensa-lx106-elf-gcc/2.0-26-gb404fb9/bin/xtensa-lx106-elf-gcc" -g -Os -nostdlib -Wl,--no-check-sections -u call_user_start -Wl,-static "-L/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/tools/sdk/lib" "-L/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/tools/sdk/ld" "-Teagle.flash.4m1m.ld" -Wl,--gc-sections -Wl,-wrap,system_restart_local -Wl,-wrap,register_chipv6_phy -o "/home/ashish/workspace_neon/WiFiEXT/Release/WiFiEXT.elf" -Wl,--start-group  $(LINK_OBJ) $(AR) "/home/ashish/workspace_neon/WiFiEXT/Release/arduino.ar" -lm -lgcc -lhal -lphy -lpp -lnet80211 -lwpa -lcrypto -lmain -lwps -laxtls -lsmartconfig -lmesh -lwpa2 -llwip_gcc -lstdc++ -Wl,--end-group "-L/home/ashish/workspace_neon/WiFiEXT/Release"
	@echo 'Finished building: $@'
	@echo ' '

WiFiEXT.hex: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
