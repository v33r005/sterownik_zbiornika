#pragma once

class CustomIterate : public Supla::Element {
 public:
  CustomIterate() {}

  void iterateAlways() {
    Kalibracja();
    if (pominZabezpieczenia->isOn() && zbiornik->readNewValue() < sygnalAlarmu) {
      if (uruchomZawor->isOn()) {
        uruchomZawor->turnOff();
      }
      zawor->turnOn();
    } else if (pominZabezpieczenia->isOn() && zbiornik->readNewValue() >= sygnalAlarmu) {
      zawor->turnOff();
      pominZabezpieczenia->turnOff();
    }
    if (!pominZabezpieczenia->isOn() && !uruchomZawor->isOn()) {
      if (zawor->isOn()) {
        zawor->turnOff();
      }
    }
    if (uruchomZawor->isOn() && zbiornik->readNewValue() <= minZawor) {
      zawor->turnOn();
    } else if(uruchomZawor->isOn() && zbiornik->readNewValue() >= maxZawor) {
      zawor->turnOff();
    }
    ObslugaPompy();
  }
};  //  CustomIterate

CustomIterate cIterate;
