#pragma once

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

  uint16_t getRawValue() {
    return analogRead(pin_);
  }

  int readNewValue() override {
    uint16_t raw = getRawValue();
    if (raw < nanValue_) {
      value_ = NAN;
    } else {
      value_ = map(raw, inMin_, inMax_, 0, 100);
    }
    return value_;
  }

 protected:
  uint8_t pin_;
  uint16_t inMin_ = 0;
  uint16_t inMax_ = 4095;
  int16_t nanValue_ = -1;
  uint8_t value_ = NAN;
  uint64_t lastReadTime_ = 0;
};
