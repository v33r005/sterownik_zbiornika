#pragma once

class CustomIterate : public Supla::Element {
 public:
  CustomIterate() {}

  void iterateAlways() {
    Kalibracja();
    if (zaworReczny->isOn() && ((aktualnyPoziom < maxPoziom) || (Krancowki == ON && czujnikMax->getValue() == false))) {
      if (automatZawor->isOn()) {
        automatZawor->turnOff();
      }
      zawor->turnOn();
    } else if (zaworReczny->isOn() && ((aktualnyPoziom >= maxPoziom) || (Krancowki == ON && czujnikMax->getValue() == true))) {
      zawor->turnOff();
      zaworReczny->turnOff();
    }
    if (!zaworReczny->isOn() && !automatZawor->isOn()) {
      if (zawor->isOn()) {
        zawor->turnOff();
      }
    }
    if (automatZawor->isOn() && aktualnyPoziom <= minZawor) {
      zawor->turnOn();
    } else if(automatZawor->isOn() && ((aktualnyPoziom >= maxZawor) || (Krancowki == ON && czujnikMax->getValue() == true))) {
      zawor->turnOff();
      automatZawor->turnOff();
    }
    ObslugaPompy();
  }
};  // CustomIterate

CustomIterate cIterate;