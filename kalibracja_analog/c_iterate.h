#pragma once

class CustomIterate : public Supla::Element {
 public:
  CustomIterate() {}

  void iterateAlways() {

    if (millis() - lastReadTime_ > 2000) {
      lastReadTime_ = millis();
      Aktualny_Poziom = map(analogRead(PIN_ANALOGOWY), 
                                         Dolna_Wartosc, Gorna_Wartosc, 0 , 100);
      /*
      if (Aktualny_Poziom > 100) {
        zbiornik->setValue(100);
      } else if (Aktualny_Poziom < 0) {
        zbiornik->setValue(0);
      } else {
        zbiornik->setValue(Aktualny_Poziom);
      }
      */
      zbiornik->setValue(Aktualny_Poziom);
    }
    Kalibracja();
    odczyt = digitalRead(ZAWOR);
    if (pominZabezpieczenia->isOn() && Aktualny_Poziom < Sygnal_Alarmu) {
      if (uruchomZawor->isOn()) {
        uruchomZawor->turnOff();
      }
      digitalWrite(ZAWOR, true);
    } else if (pominZabezpieczenia->isOn() && Aktualny_Poziom >= Sygnal_Alarmu) {
      digitalWrite(ZAWOR, false);
      pominZabezpieczenia->turnOff();
    }
    if (pominZabezpieczenia->isOn() == false && uruchomZawor->isOn() == false) {
      if (digitalRead(ZAWOR) == true) {
        digitalWrite(ZAWOR, false);
      }
    }
    if (uruchomZawor->isOn() && Aktualny_Poziom <= min_zawor) {
      digitalWrite(ZAWOR, true);
    } else if(uruchomZawor->isOn() && Aktualny_Poziom >= max_zawor) {
      digitalWrite(ZAWOR, false);
    }
    ObslugaPompy();
  }

 protected:
  uint32_t lastReadTime_ = 0;

};  //  CustomIterate
