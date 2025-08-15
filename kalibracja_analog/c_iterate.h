#pragma once

class CustomIterate : public Supla::Element {
 public:
  CustomIterate() {}

  void iterateAlways() {
    Kalibracja();
    if (zaworReczny->isOn() && zbiornik->readNewValue() < sygnalAlarmu) {
      if (uruchomZawor->isOn()) {
        uruchomZawor->turnOff();
      }
      zawor->turnOn();
      ledZawor->turnOn();
    } else if (zaworReczny->isOn() && zbiornik->readNewValue() >= sygnalAlarmu) {
      zawor->turnOff();
      ledZawor->turnOff();
      zaworReczny->turnOff();
    }
    if (!zaworReczny->isOn() && !uruchomZawor->isOn()) {
      if (zawor->isOn()) {
        zawor->turnOff();
        ledZawor->turnOff();
      }
    }
    if (uruchomZawor->isOn() && zbiornik->readNewValue() <= minZawor) {
      zawor->turnOn();
      ledZawor->turnOn();
    } else if(uruchomZawor->isOn() && zbiornik->readNewValue() >= maxZawor) {
      zawor->turnOff();
      ledZawor->turnOn();
    }
    ObslugaPompy();
  }
};  //  CustomIterate

CustomIterate cIterate;
