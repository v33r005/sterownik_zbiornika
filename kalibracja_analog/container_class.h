#pragma once

#include <algorithm>
#include <supla/sensor/container.h>

class AnalogContainer : public Supla::Sensor::Container {
 public:
  AnalogContainer(uint8_t pin, 
                  uint16_t inMin = 0,
                  uint16_t inMax = 4095,
                  int16_t nanValue = -1)
    : pin_(pin),
      inMin_(inMin),
      inMax_(inMax),
      nanValue_(nanValue) {

    setInternalLevelReporting(true);
    getChannel()->setDefault(SUPLA_CHANNELFNC_WATER_TANK);
  }

  int16_t getRawValue() {
    return analogRead(pin_);
  }

  int readNewValue() override {
    value_ = (raw_ < nanValue_) ? NAN
                      : std::clamp(map(raw_, inMin_, inMax_, 0, 100), 0L, 100L);
    return value_;
  }

  int16_t rawAverage(uint8_t samples) {
    int32_t sum = 0;
    for (int i = 0; i < samples; i++) {
      sum += getRawValue();
      delayMicroseconds(200);
    }
    return sum / samples;
  }

  void iterateAlways() override {
    if (millis() - lastReadTime_ > 5'000) {
      raw_ = rawAverage(20);
    }
    Supla::Sensor::Container::iterateAlways();
  }

 protected:
  uint8_t pin_;
  uint16_t inMin_ = 0;
  uint16_t inMax_ = 4095;
  int16_t nanValue_ = -1;
  int16_t raw_ = 0;
  int8_t value_ = NAN;
  uint64_t lastReadTime_ = 0;
};