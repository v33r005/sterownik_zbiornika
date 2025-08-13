#pragma once

#include <HardwareSerial.h>
#include <SuplaDevice.h>
#include <supla/device/supla_ca_cert.h>
#include <supla/network/esp_wifi.h>
Supla::ESPWifi wifi;
#include <supla/device/status_led.h>
Supla::Device::StatusLed statusLed(STATUS_LED_GPIO, true); // inverted state
#include <supla/storage/littlefs_config.h>
Supla::LittleFsConfig configSupla(2000);
#include <supla/control/button.h>
Supla::Control::Button *cfgButton = nullptr;
#include <supla/control/virtual_relay.h>
Supla::Control::VirtualRelay *uruchomPompe = nullptr;
Supla::Control::VirtualRelay *uruchomZawor = nullptr;
Supla::Control::VirtualRelay *pominZabezpieczenia = nullptr;
#include <supla/sensor/general_purpose_measurement.h>
Supla::Sensor::GeneralPurposeMeasurement *gpm = nullptr;
#include <supla/sensor/container.h>
Supla::Sensor::Container *zbiornik = nullptr;
#include <HTTPUpdateServer.h>
HTTPUpdateServer httpUpdater;
#include <supla/network/esp_web_server.h>
Supla::EspWebServer suplaServer;
#include <supla/storage/eeprom.h>
Supla::Eeprom eeprom;

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
