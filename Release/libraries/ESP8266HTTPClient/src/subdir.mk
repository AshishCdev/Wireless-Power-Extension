################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.cpp 

LINK_OBJ += \
./libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.cpp.o 

CPP_DEPS += \
./libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.cpp.o: /home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/../../../tools/xtensa-lx106-elf-gcc/2.0-26-gb404fb9/bin/xtensa-lx106-elf-g++" -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ "-I/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/tools/sdk/include" "-I/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/tools/sdk/lwip/include" "-I/home/ashish/workspace_neon/WiFiEXT/Release/core" -c -Os -g -mlongcalls -mtext-section-literals -fno-exceptions -fno-rtti -falign-functions=4 -std=c++11 -MMD -ffunction-sections -fdata-sections -DF_CPU=160000000L -DLWIP_OPEN_SRC  -DARDUINO=10609 -DARDUINO_ESP8266_ESP12 -DARDUINO_ARCH_ESP8266 '-DARDUINO_BOARD="ESP8266_ESP12"' -DESP8266  -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/cores/esp8266" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/variants/espino" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/SPI" -I"/home/ashish/arduino-1.6.9/libraries/OneWire" -I"/home/ashish/arduino-1.6.9/libraries/DallasTemperature" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266WiFi" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266WiFi/src" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266HTTPClient" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266HTTPClient/src" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/EEPROM" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266httpUpdate" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266httpUpdate/src" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266WebServer" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266WebServer/src" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/SD" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/SD/src" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/Ticker" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266mDNS" -I"/home/ashish/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ArduinoOTA" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '


