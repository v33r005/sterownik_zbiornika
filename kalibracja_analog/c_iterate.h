#pragma once

class CustomIterate : public Supla::Element {
 public:
  CustomIterate() {}

  void iterateAlways() {
    Kalibracja();
    if (zaworReczny->isOn() && aktualnyPoziom < sygnalAlarmu) {
      if (uruchomZawor->isOn()) {
        uruchomZawor->turnOff();
      }
      zawor->turnOn();
    } else if (zaworReczny->isOn() && aktualnyPoziom >= sygnalAlarmu) {
      zawor->turnOff();
      zaworReczny->turnOff();
    }
    if (!zaworReczny->isOn() && !uruchomZawor->isOn()) {
      if (zawor->isOn()) {
        zawor->turnOff();
      }
    }
    if (uruchomZawor->isOn() && aktualnyPoziom <= minZawor) {
      zawor->turnOn();
    } else if(uruchomZawor->isOn() && aktualnyPoziom >= maxZawor) {
      zawor->turnOff();
    }
    ObslugaPompy();
  }
};  //  CustomIterate

CustomIterate cIterate;
