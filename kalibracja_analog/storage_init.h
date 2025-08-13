#pragma once

Supla::Storage::Init();
auto cfg = Supla::Storage::ConfigInstance();

if (Supla::Storage::ConfigInstance()->getString(DEV_NAME, devName, 30)) {
  SUPLA_LOG_DEBUG("# Param[%s]: %s", DEV_NAME, devName);
} else {
  Supla::Storage::ConfigInstance()->setString(DEV_NAME, "Supla-Sprzecik");
}
cfg->getUInt32(PARAM1, &max_zawor);
cfg->getUInt32(PARAM2, &min_zawor);
cfg->getUInt32(PARAM3, &min_pompa);
cfg->getInt32(PARAM4, &Min_Analog_Odczyt);
cfg->getUInt32(PARAM5, &Gorna_Wartosc);
cfg->getUInt32(PARAM6, &Dolna_Wartosc);
cfg->getInt32(PARAM7, &Max_Analog_Odczyt);
cfg->getUInt32(PARAM8, &Sygnal_Alarmu);
cfg->getInt32(PARAM9, &Min_Wartosc);
cfg->getInt32(PARAM10, &Max_Wartosc);
cfg->getUInt8(PARAM11, &Zalacz_Analog);
cfg->getUInt8(STANDBY_MODE, &standby_mode);
cfg->getUInt8(STANDBY_MODE1, &standby_mode1);
