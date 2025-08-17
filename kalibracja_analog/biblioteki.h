#pragma once

#include <HardwareSerial.h>
#include <SuplaDevice.h>
#include <supla/control/action_trigger.h>
#include <supla/device/supla_ca_cert.h>
#include <supla/network/esp_wifi.h>
Supla::ESPWifi wifi;
#include <supla/device/status_led.h>
Supla::Device::StatusLed statusLed(STATUS_LED_GPIO, true); // inverted state
#include <supla/storage/littlefs_config.h>
Supla::LittleFsConfig configSupla(2000);
#include <supla/control/button.h>
Supla::Control::Button *cfgButton = nullptr;
Supla::Control::Button *zalaczReczniePompe = nullptr;
Supla::Control::Button *zalaczRecznieZawor = nullptr;
#include <supla/control/virtual_relay.h>
Supla::Control::VirtualRelay *uruchomPompe = nullptr;
Supla::Control::VirtualRelay *automatZawor = nullptr;
Supla::Control::VirtualRelay *zaworReczny = nullptr;
#include <supla/control/internal_pin_output.h>
Supla::Control::InternalPinOutput *pompa = nullptr;
Supla::Control::InternalPinOutput *zawor = nullptr;
#include <supla/control/pin_status_led.h>
Supla::Control::PinStatusLed *ledPompa = nullptr;
Supla::Control::PinStatusLed *ledZawor = nullptr;
#include <supla/sensor/container.h>
#include <HTTPUpdateServer.h>
HTTPUpdateServer httpUpdater;
#include <supla/network/esp_web_server.h>
Supla::EspWebServer suplaServer;
#include <supla/storage/eeprom.h>
Supla::Eeprom eeprom;
#include <supla/sensor/binary.h>
Supla::Sensor::Binary *czujnikMax = nullptr;
Supla::Sensor::Binary *czujnikMin = nullptr;
#include <supla/sensor/DS18B20.h>
Supla::Sensor::DS18B20 *temperatureSensor = nullptr;

class AnalogContainer;
AnalogContainer *zbiornik = nullptr;

#include <supla/network/html/custom_parameter.h>
#include <supla/network/html/custom_text_parameter.h>
#include <supla/network/html/custom_checkbox_parameter.h>
#include <supla/network/html/text_cmd_input_parameter.h>
#include <supla/network/html/select_input_parameter.h>
#include <supla/network/html/select_cmd_input_parameter.h>
#include <supla/network/html/time_parameters.h>
#include <supla/network/html/container_parameters.h>
#include <supla/network/html/div.h>
#include <supla/network/html/h3_tag.h>
#include <supla/network/html/device_info.h>
#include <supla/network/html/protocol_parameters.h>
#include <supla/network/html/status_led_parameters.h>
#include <supla/network/html/wifi_parameters.h>

