#pragma once

class CustomIterate : public Supla::Element {
 public:
  CustomIterate() {}

  void iterateAlways() {
    Kalibracja();

    if (zaworReczny->isOn() && zmienna_bool_1 == false){
      zmienna_bool_1 = true;
      if (automatZawor->isOn()) automatZawor->turnOff();
    }
    if (!zaworReczny->isOn() && zmienna_bool_1 == true){
      zmienna_bool_1 = false;
    }
    
    if (automatZawor->isOn() && zmienna_bool_2 == false){
      zmienna_bool_2 = true;
      if (zaworReczny->isOn()) zaworReczny->turnOff();
    }
    if (!automatZawor->isOn() && zmienna_bool_2 == true){
      zmienna_bool_2 = false;
    } 
    
    if (zaworReczny->isOn() && aktualnyPoziom < maxPoziom) {
      zawor->turnOn();
    } else if (zaworReczny->isOn() && aktualnyPoziom >= maxPoziom) {
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
    } else if(automatZawor->isOn() && aktualnyPoziom >= maxZawor) {
      zawor->turnOff();
    }
    ObslugaPompy();
  }
};  // CustomIterate

CustomIterate cIterate;