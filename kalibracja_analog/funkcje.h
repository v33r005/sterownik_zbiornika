#pragma once

void ObslugaPompy() {
  if (uruchomPompe->isOn() && (Aktualny_Poziom > min_pompa)) {
    digitalWrite(POMPA, true);
  } else {
    if (uruchomPompe->isOn() && digitalRead(POMPA == true)) {
      digitalWrite(POMPA, false);
      uruchomPompe->turnOff();
    } else if (uruchomPompe->isOn() == false && digitalRead(POMPA == true)) {
      digitalWrite(POMPA, false);
    }
  }
}

void Kalibracja() {
   if (standby_mode) {
    Supla::Storage::ConfigInstance()->setUInt32(PARAM6, analogRead(PIN_ANALOGOWY));
    Supla::Storage::ConfigInstance()->setUInt8(STANDBY_MODE, 0);
    standby_mode = 0;
  }
  if (standby_mode1) {
    Supla::Storage::ConfigInstance()->setUInt32(PARAM5, analogRead(PIN_ANALOGOWY));
    Supla::Storage::ConfigInstance()->setUInt8(STANDBY_MODE1, 0);
    standby_mode1 = 0;
  } 
}