#pragma once

inline constexpr char SOFT_VERSION[] = "5.08.2025 @veeroos";
constexpr uint8_t STATUS_LED_GPIO = 2;
constexpr uint8_t BUTTON_CFG_GPIO = 0;
constexpr uint8_t ON = 1;
constexpr uint8_t OFF = 0;
constexpr uint8_t ANALOG_GPIO = 10;
constexpr uint8_t PUMP_GPIO = 12;
constexpr uint8_t VALVE_GPIO = 13;
constexpr uint8_t PUMP_BTN_GPIO = 14;
constexpr uint8_t VALVE_BTN_GPIO = 15;
constexpr uint8_t SENSOR_MAX_GPIO = 3;
constexpr uint8_t SENSOR_MIN_GPIO = 4;
constexpr uint8_t LED_PUMP_GPIO = 5;
constexpr uint8_t LED_VALVE_GPIO = 6;

constexpr uint16_t DEFAULT_IN_MAX  = 4'095;
constexpr uint16_t DEFAULT_IN_MIN = 0;
constexpr int32_t DEFAULT_NAN_VALUE = -1;


