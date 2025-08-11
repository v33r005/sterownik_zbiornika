#ifndef BIBLIOTEKI_H_
#define BIBLIOTEKI_H

#include <FastLED.h>
#include <HardwareSerial.h>
#include <SuplaDevice.h>
#include <supla/network/esp_wifi.h>
#include <supla/control/relay.h>
#include <supla/control/button.h>
#include <supla/control/action_trigger.h>
#include <supla/device/status_led.h>
#include <supla/storage/littlefs_config.h>
#include <supla/network/html/div.h>
#include <supla/network/html/h3_tag.h>
#include <supla/network/html/device_info.h>
#include <supla/network/html/protocol_parameters.h>
#include <supla/network/html/status_led_parameters.h>
#include <supla/network/html/wifi_parameters.h>
#include <supla/device/supla_ca_cert.h>
#include <supla/events.h>
#include <supla/network/html/custom_parameter.h>
#include <supla/network/html/custom_text_parameter.h>
#include <supla/network/html/custom_checkbox_parameter.h>
#include <supla/network/html/text_cmd_input_parameter.h>
#include <supla/network/html/select_input_parameter.h>
#include <supla/network/html/select_cmd_input_parameter.h>
#include <supla/network/html/time_parameters.h>
#include <supla/control/virtual_relay.h>
#include <supla/sensor/general_purpose_measurement.h>
#include <supla/sensor/container.h>
#include <supla/network/html/container_parameters.h>
#include <supla/sensor/virtual_binary.h>
#include <supla/clock/clock.h>


Supla::Sensor::GeneralPurposeMeasurement *gpm = nullptr;
Supla::Sensor::Container *zbiornik = nullptr;

#include <HTTPUpdateServer.h>
HTTPUpdateServer httpUpdater;

#include <supla/network/esp_web_server.h>
#include <supla/network/client.h>
Supla::EspWebServer suplaServer;
#include <supla/storage/eeprom.h>
Supla::Eeprom eeprom;

Supla::ESPWifi wifi;
Supla::LittleFsConfig configSupla(2000);


Supla::Device::StatusLed statusLed(STATUS_LED_GPIO, true); // inverted state
Supla::Control::VirtualRelay *uruchom_pompe = nullptr;
Supla::Control::VirtualRelay *uruchom_zawor = nullptr;
Supla::Control::VirtualRelay *pomin_zabezpieczenia = nullptr;

CRGB leds[NUM_LEDS];


#endif

