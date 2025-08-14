#pragma once

void ObslugaPompy() {
  if (uruchomPompe->isOn() && (aktualnyPoziom > minPompa)) {
    pompa->turnOn();
    ledPompa->turnOn();
  } else {
    if (uruchomPompe->isOn() && pompa->isOn()) {
      uruchomPompe->turnOff();
      pompa->turnOff();
      ledPompa->turnOff();
    } else if (!uruchomPompe->isOn() && pompa->isOn()) {
      pompa->turnOff();
      ledPompa->turnOFF();
    }
  }
}

void Kalibracja() {
   if (standbyMode) {
    Supla::Storage::ConfigInstance()->setUInt32(PARAM6, analogRead(ANALOG_GPIO));
    Supla::Storage::ConfigInstance()->setUInt8(STANDBY_MODE, 0);
    standbyMode = false;
  }
  if (standbyMode1) {
    Supla::Storage::ConfigInstance()->setUInt32(PARAM5, analogRead(ANALOG_GPIO));
    Supla::Storage::ConfigInstance()->setUInt8(STANDBY_MODE1, 0);
    standbyMode1 = false;
  } 
}
