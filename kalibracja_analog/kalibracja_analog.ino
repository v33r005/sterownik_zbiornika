/*
to do:
wejscie na czujnik plywakowy
przycisk zalaczenia pompy
wejscie analogowe pomiaru cisnienia
czujnik temperatury deszczówki
*/
#include "definicje.h"
#include "biblioteki.h"
#include "zmienne.h"
#include "html_classes.h"

void setup() {

  Serial.begin(115200);
  #include "storage_init.h"
  pinMode(POMPA, OUTPUT);
  pinMode(ZAWOR, OUTPUT);

  new Supla::Clock;

  zbiornik = new Supla::Sensor::Container();
  zbiornik->getChannel()->setDefault(SUPLA_CHANNELFNC_WATER_TANK);
  zbiornik->setInternalLevelReporting(true);

  auto buttonCfgRelay = new Supla::Control::Button(BUTTON_CFG_RELAY_GPIO, true, true);
  buttonCfgRelay->configureAsConfigButton(&SuplaDevice);

  uruchom_pompe = new Supla::Control::VirtualRelay();
  uruchom_pompe->setInitialCaption("Pompa podlewania");
  uruchom_pompe->getChannel()->setDefault(SUPLA_CHANNELFNC_POWERSWITCH);

  uruchom_zawor = new Supla::Control::VirtualRelay();
  uruchom_zawor->setInitialCaption("Automatyczne dolewanie wody");
  uruchom_zawor->getChannel()->setDefault(SUPLA_CHANNELFNC_POWERSWITCH);
  uruchom_zawor->setDefaultStateRestore();

  pomin_zabezpieczenia = new Supla::Control::VirtualRelay();
  pomin_zabezpieczenia->setInitialCaption("Załącz zawór ręcznie");
  pomin_zabezpieczenia->getChannel()->setDefault(SUPLA_CHANNELFNC_POWERSWITCH);

  FastLED.addLeds<CHIPSET, diodaPIN, COLOR_ORDER>(leds, NUM_LEDS);

  #include "html.h"
  httpUpdater.setup(suplaServer.getServerPtr(), "/update");
  SuplaDevice.setName(devName);
  SuplaDevice.setSwVersion(SOFT_VERSION);
  SuplaDevice.setSuplaCACert(suplaCACert);
  SuplaDevice.setSupla3rdPartyCACert(supla3rdCACert);
  SuplaDevice.setProtoVerboseLog(false);
  SuplaDevice.begin();
}

void loop() {
  SuplaDevice.iterate();

  static uint32_t lastTime = 0;
  if ((millis() - lastTime > 2000) || (lastTime > millis())) {
    Aktualny_Poziom = map(analogRead(PIN_ANALOGOWY), Dolna_Wartosc, Gorna_Wartosc, 0 , 100);
    lastTime = millis(); 
/*
    if (Aktualny_Poziom > 100){
      zbiornik->setValue(100);
    }else if (Aktualny_Poziom < 0){
      zbiornik->setValue(0);
    }else{
      zbiornik->setValue(Aktualny_Poziom);
    }
*/
  zbiornik->setValue(Aktualny_Poziom);
  }

  Kalibracja();
  odczyt = digitalRead(ZAWOR);

  if (pomin_zabezpieczenia->isOn() && Aktualny_Poziom < Sygnal_Alarmu){
    if (uruchom_zawor->isOn()){
      uruchom_zawor->turnOff();
    }
    digitalWrite(ZAWOR, true);
  }else if (pomin_zabezpieczenia->isOn() && Aktualny_Poziom >= Sygnal_Alarmu){
    digitalWrite(ZAWOR, false);
    pomin_zabezpieczenia->turnOff();
  }

  if (pomin_zabezpieczenia->isOn() == false && uruchom_zawor->isOn() == false){
    if (digitalRead(ZAWOR) == true){
      digitalWrite(ZAWOR, false);
    }
  }

  if (uruchom_zawor->isOn() && Aktualny_Poziom <= min_zawor){
    digitalWrite(ZAWOR, true);
  }else if(uruchom_zawor->isOn() && Aktualny_Poziom >= max_zawor){
    digitalWrite(ZAWOR, false);
  }

  Obsluga_Pompy();
  
}

void Kalibracja(){

   if (standby_mode){
    Supla::Storage::ConfigInstance()->setUInt32(PARAM6, analogRead(PIN_ANALOGOWY));
    Supla::Storage::ConfigInstance()->setUInt8(STANDBY_MODE, 0);
    standby_mode = 0;
  }

  if (standby_mode1){
    Supla::Storage::ConfigInstance()->setUInt32(PARAM5, analogRead(PIN_ANALOGOWY));
    Supla::Storage::ConfigInstance()->setUInt8(STANDBY_MODE1, 0);
    standby_mode1 = 0;
  } 
}

void Obsluga_Pompy(){
  if (uruchom_pompe->isOn() && (Aktualny_Poziom > min_pompa)){
    digitalWrite(POMPA, true);
  }else{
    if (uruchom_pompe->isOn() && digitalRead(POMPA == true)){
      digitalWrite(POMPA, false);
      uruchom_pompe->turnOff();
    }else if (uruchom_pompe->isOn() == false && digitalRead(POMPA == true)){
      digitalWrite(POMPA, false);
    }
  }
}
