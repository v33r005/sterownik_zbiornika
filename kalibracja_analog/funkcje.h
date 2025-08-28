#pragma once

void ObslugaPompy() {
  if (uruchomPompe->isOn() && aktualnyPoziom > minPompa) {
    pompa->turnOn();
  } 
  if (!uruchomPompe->isOn() && pompa->isOn()) {
    pompa->turnOff();
  } 
  if (uruchomPompe->isOn() && (aktualnyPoziom <= minPompa || zbiornik->isInvalidSensorStateActive())) {
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

void Obsluga_Status_LED_RGB(){
  if (digitalRead(STATUS_LED_GPIO) == true){
    dioda_statusu.setPixelColor(0, dioda_statusu.Color(0, 0, 0));
    dioda_statusu.show();
  }else{
    dioda_statusu.setPixelColor(0, dioda_statusu.Color(0, 50, 0));
    dioda_statusu.show();
  }
}

void Obsluga_Zaworu(){
  
  if (zaworReczny->isOn() && aktualnyPoziom < maxPoziom && !zbiornik->isInvalidSensorStateActive()) {
    zawor->turnOn();
  } 
  if (zaworReczny->isOn() && (aktualnyPoziom >= maxPoziom || zbiornik->isInvalidSensorStateActive())) {
    zawor->turnOff();
    zaworReczny->turnOff();
  }
  if (!zaworReczny->isOn() && !automatZawor->isOn()) {
    if (zawor->isOn()) {
      zawor->turnOff();
    }
  }
  if (automatZawor->isOn() && aktualnyPoziom <= minZawor && !zbiornik->isInvalidSensorStateActive() && aktualnyPoziom < maxZawor) {
    zawor->turnOn();
  } 
  if(automatZawor->isOn() && (aktualnyPoziom >= maxZawor || zbiornik->isInvalidSensorStateActive())) {
    zawor->turnOff();
  }
}

void Obsluga_Suwakow(){
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
}

void Obsluga_Bledow(){
  static uint32_t czasPowiadomienia1 = 0;
  if (Supla::Network::IsReady()) {
    if (Powiadomienia->isOn()){
      if (zbiornik->isInvalidSensorStateActive() && !wiadomosc1){
        if (!zabezpieczenie1){
          czas1 = millis() + 3000;
          zabezpieczenie1 = true;
        }
        if (zabezpieczenie1 && millis() > czas1){
          Supla::Notification::Send(-1, "Czujnik Poziomu", "Nieprawidłowy stan czujników");
          wiadomosc1 = true;
          czasPowiadomienia1 = millis();
        }
      }else{
        zabezpieczenie1 = false;
      }
      if (millis() - czasPowiadomienia1 > 120000  || millis() < czasPowiadomienia1){
        wiadomosc1 = false;
      }
    }
  }
}