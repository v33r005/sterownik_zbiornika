#pragma once

void ObslugaPompy() {
  if (uruchomPompe->isOn() && (aktualnyPoziom > minPompa)) {
    pompa->turnOn();
  } else {
    if (uruchomPompe->isOn() && pompa->isOn()) {
      uruchomPompe->turnOff();
      pompa->turnOff();
    } else if (!uruchomPompe->isOn() && pompa->isOn()) {
      pompa->turnOff();
    }
  }
}

void Kalibracja() {
   auto cfg = Supla::Storage::ConfigInstance();
   if (standbyMode) {
    cfg->setUInt32(PARAM6, zbiornik->getRawValue());
    cfg->setUInt8(STANDBY_MODE, 0);
    standbyMode = false;
  }
  if (standbyMode1) {
    cfg->setUInt32(PARAM5, zbiornik->getRawValue());
    cfg->setUInt8(STANDBY_MODE1, 0);
    standbyMode1 = false;
  } 
}
