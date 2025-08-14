#pragma once

class CustomIterate : public Supla::Element {
 public:
  CustomIterate() {}

  void iterateAlways() {
    Kalibracja();
    if (pominZabezpieczenia->isOn() && zbiornik->getValue() < sygnalAlarmu) {
      if (uruchomZawor->isOn()) {
        uruchomZawor->turnOff();
      }
      zawor->turnOn();
    } else if (pominZabezpieczenia->isOn() && zbiornik->getValue >= sygnalAlarmu) {
      zawor->turnOff();
      pominZabezpieczenia->turnOff();
    }
    if (!pominZabezpieczenia->isOn() && !uruchomZawor->isOn()) {
      if (zawor->isOn()) {
        zawor->turnOff();
      }
    }
    if (uruchomZawor->isOn() && zbiornik->getValue() <= minZawor) {
      zawor->turnOn();
    } else if(uruchomZawor->isOn() && zbiornik->getValue() >= maxZawor) {
      zawor->turnOff();
    }
    ObslugaPompy();
  }

 protected:

};  //  CustomIterate

CustomIterate cIterate;
