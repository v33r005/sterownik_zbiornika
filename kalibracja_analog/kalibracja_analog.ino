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
#include "container_class.h"
#include "html_classes.h"
#include "funkcje.h"
#include "c_iterate.h"


void setup() {
  Serial.begin(115200);

  #include "storage_init.h"

  pompa = new Supla::Control::InternalPinOutput(PUMP_GPIO);
  zawor = new Supla::Control::InternalPinOutput(VALVE_GPIO);

  zbiornik = new AnalogContainer(
                      ANALOG_GPIO, minAnalogOdczyt, maxAnalogOdczyt,  nanValue);

  czujnikMin = new Supla::Sensor::Binery(SENSOR_MIN_GPIO, true, true);
  czujnikMax = new Supla::Sensor::Binary(SENSOR_MAX_GPIO, true, true);

  auto cfgButton = new Supla::Control::Button(BUTTON_CFG_GPIO, true, true);
  cfgButton->configureAsConfigButton(&SuplaDevice);

  zalaczReczniePompe = new Supla::Control::Button(PUMP_BTN_GPIO, true, true);
  zalaczRecznieZawor = new Supla::Control::Button(VALVE_BTN_GPIO, true, true);
  zalaczReczniePompe->setMulticlickTime(200);
  zalaczReczniePompe->setHoldTime(400);
  zalaczRecznieZawor->setMulticlickTime(200);
  zalaczRecznieZawor->setHoldTime(400);

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

  zalaczReczniePompe->addAction(Supla::TOGGLE, uruchomPompe, Supla::ON_PRESS);
  zalaczRecznieZawor->addAction(Supla::TOGGLE, pominZabezpieczenia, Supla::ON_PRESS);

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


