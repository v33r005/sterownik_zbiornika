#pragma once

class CustomIterate : public Supla::Element {
 public:
  CustomIterate() {}

  void iterateAlways() {

    if (millis() - lastReadTime_ > 2000) {
      lastReadTime_ = millis();
      aktualnyPoziom = map(analogRead(PIN_ANALOGOWY), 
                                           dolnaWartosc, gornaWartosc, 0 , 100);
      /*
      if (Aktualny_Poziom > 100) {
        zbiornik->setValue(100);
      } else if (Aktualny_Poziom < 0) {
        zbiornik->setValue(0);
      } else {
        zbiornik->setValue(Aktualny_Poziom);
      }
      */
      zbiornik->setValue(aktualnyPoziom);
    }
    Kalibracja();
    if (pominZabezpieczenia->isOn() && aktualnyPoziom < sygnalAlarmu) {
      if (uruchomZawor->isOn()) {
        uruchomZawor->turnOff();
      }
      zawor->turnOn();
    } else if (pominZabezpieczenia->isOn() && aktualnyPoziom >= sygnalAlarmu) {
      zawor->turnOff();
      pominZabezpieczenia->turnOff();
    }
    if (!pominZabezpieczenia->isOn() && !uruchomZawor->isOn()) {
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

 protected:
  uint32_t lastReadTime_ = 0;

};  //  CustomIterate

CustomIterate cIterate;
