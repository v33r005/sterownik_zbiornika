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
    if (digitalRead(STATUS_LED_GPIO) == true){
    dioda_statusu.setPixelColor(0, dioda_statusu.Color(0, 0, 0));
    dioda_statusu.show();
  }else{
    dioda_statusu.setPixelColor(0, dioda_statusu.Color(0, 50, 0));
    dioda_statusu.show();
  }
  }
};  // CustomIterate

CustomIterate cIterate;