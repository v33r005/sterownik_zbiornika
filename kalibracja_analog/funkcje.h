#pragma once

void ObslugaPompy() {
  if (uruchomPompe->isOn() && ((aktualnyPoziom > minPompa)||(Krancowki == ON && czujnikMin->getValue() == true))) {
    pompa->turnOn();
  } else if (!uruchomPompe->isOn() && pompa->isOn()) {
      pompa->turnOff();
  } else if (uruchomPompe->isOn() && ((aktualnyPoziom < minPompa)||(Krancowki == ON && czujnikMin->getValue() == false))) {
    pompa->turnOff();
    uruchomPompe->turnOff();
  }
}

void Kalibracja() {
  auto cfg = Supla::Storage::ConfigInstance();
   if (ustawMinimum) {
    cfg->setUInt32(DOLNA_WARTOSC, zbiornik->getRawValue());
    cfg->setUInt8(USTAW_MINIMUM, OFF);
    ustawMinimum = false;
  }
  if (ustawMaksimum) {
    cfg->setUInt32(GORNA_WARTOSC, zbiornik->getRawValue());
    cfg->setUInt8(USTAW_MAKSIMUM, OFF);
    ustawMaksimum = false;
  } 
}