#pragma once

Supla::Storage::Init();
auto cfg = Supla::Storage::ConfigInstance();

if (Supla::Storage::ConfigInstance()->getString(DEV_NAME, devName, 30)) {
  SUPLA_LOG_DEBUG("# Param[%s]: %s", DEV_NAME, devName);
} else {
  Supla::Storage::ConfigInstance()->setString(DEV_NAME, "Supla-Sprzecik");
}
cfg->getUInt32(MAX_ZAWOR, &maxZawor);
cfg->getUInt32(MIN_ZAWOR, &minZawor);
cfg->getUInt32(MIN_POMPA, &minPompa);
cfg->getUInt32(GORNA_WARTOSC, &gornaWartosc);
cfg->getUInt32(DOLNA_WARTOSC, &dolnaWartosc);
cfg->getUInt32(MAX_POZIOM, &maxPoziom);
cfg->getUInt8(USTAW_MINIMUM, &ustawMinimum);
cfg->getUInt8(USTAW_MAKSIMUM, &ustawMaksimum);
cfg->getInt32(NAN_VALUE, &nanValue);
cfg->getUInt8(KRANCOWKI, &Krancowki);
cfg->getUInt8(CZUJNIK_TEMPERATURY, &CzujnikTemperatury);