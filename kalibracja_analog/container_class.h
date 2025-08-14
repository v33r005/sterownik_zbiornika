#pragma once

class Analog_Container_ : public Supla::Sensor::Container {
 public: Analog_Container_(int pin, uint32_t in_min = 0,
  uint32_t in_max = 4095, int out_min = 0,
                                int out_max = 100, int32_t nanValue = -1)
    : pin(pin), in_min(in_min), in_max(in_max), out_min(out_min),
                                  out_max(out_max), nanValue(nanValue){
    setInternalLevelReporting(true);
    getChannel()->setDefault(SUPLA_CHANNELFNC_WATER_TANK);
  }

  void onInit() {
    channel.setContainerFillValue(readNewValue());
  }

  void iterateAlways() override {
    if (millis() - lastReadTime > 2000) {
      lastReadTime = millis();
      channel.setContainerFillValue(readNewValue());
    }
  }

  double getRawValue() {
    _rawValue = analogRead(pin);
    return _rawValue;
  }
  

  int readNewValue() override{
    int _raw = getRawValue();
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
  uint32_t out_min = 0;
  uint32_t out_max = 100;
  int value = NAN;
  uint64_t lastReadTime = 0;
};
Analog_Container_ *zbiornik = nullptr;


