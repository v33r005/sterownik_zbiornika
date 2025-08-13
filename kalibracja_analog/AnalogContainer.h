#pragma once

#include <supla/sensor/container.h>

class Analog_Container : public Supla::Sensor::Container {
 public: Analog_Container(int pin, uint32_t in_min = 0,
  uint32_t in_max = 4095, double out_min = 0,
                                double out_max = 100, int32_t nanValue = -1)
    : pin(pin), in_min(in_min), in_max(in_max), out_min(out_min),
                                  out_max(out_max), nanValue(nanValue){
    setInternalLevelReporting(true);
    getChannel()->setDefault(SUPLA_CHANNELFNC_WATER_TANK);
  }

  void onInit() {
    channel.setNewValue(getValue());
  }

  void iterateAlways() override {
    if (millis() - lastReadTime > 2000) {
      lastReadTime = millis();
      getValue();
    }
  }

  double getRawValue() {
    _rawValue = analogRead(pin);
    return _rawValue;
  }
  
  double getValue() {
    double _raw = getRawValue();
    if (_raw < nanValue) {
      value = NAN;
    } else {
      value = map(_raw, in_min, in_max, out_min, out_max);
      value = (value < 0) ? 0 : value;
    }
    return value;
  }

 protected:
  int pin;
  int32_t _rawValue = 0;
  uint32_t in_min = 0;
  uint32_t in_max = 4095;
  int32_t nanValue = -1;
  double out_min = 0;
  double out_max = 100;
  double value = NAN;
  uint64_t lastReadTime = 0;
};
