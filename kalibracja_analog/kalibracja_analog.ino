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
#include "funkcje.h"
#include "c_iterate.h"

void setup() {
  Serial.begin(115200);

  #include "storage_init.h"

  pompa = new Supla::Control::InternalPinOutput(POMPA_GPIO);
  zawor = new Supla::Control::InternalPinOutput(ZAWOR_GPIO);

  zbiornik = new Supla::Sensor::Container();
  zbiornik->getChannel()->setDefault(SUPLA_CHANNELFNC_WATER_TANK);
  zbiornik->setInternalLevelReporting(true);

  auto cfgButton = new Supla::Control::Button(BUTTON_CFG_GPIO, true, true);
  cfgButton->configureAsConfigButton(&SuplaDevice);

  uruchomPompe = new Supla::Control::VirtualRelay();
  uruchomPompe->setInitialCaption("Pompa podlewania");
  uruchomPompe->getChannel()->setDefault(SUPLA_CHANNELFNC_POWERSWITCH);

  uruchomZawor = new Supla::Control::VirtualRelay();
  uruchomZawor->setInitialCaption("Automatyczne dolewanie wody");
  uruchomZawor->getChannel()->setDefault(SUPLA_CHANNELFNC_POWERSWITCH);
  uruchomZawor->setDefaultStateRestore();

  pominZabezpieczenia = new Supla::Control::VirtualRelay();
  pominZabezpieczenia->setInitialCaption("Załącz zawór ręcznie");
  pominZabezpieczenia->getChannel()->setDefault(SUPLA_CHANNELFNC_POWERSWITCH);

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
}


