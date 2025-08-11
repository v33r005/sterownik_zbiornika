#ifndef STORAGE_INIT_H_
#define STORAGE_INIT_H_

//******************własna nazwa*****************************
  Supla::Storage::Init();
  auto cfg = Supla::Storage::ConfigInstance();
  if (Supla::Storage::ConfigInstance()->getString(DEV_NAME, devName, 30)) {
    SUPLA_LOG_DEBUG("# Param[%s]: %s", DEV_NAME, devName);
  } else {
    Supla::Storage::ConfigInstance()->setString(DEV_NAME, "Supla-Sprzecik");
  }
//****************************************************************
  
  if (cfg->getInt32(PARAM1, &max_zawor)) {} else {}
  if (cfg->getInt32(PARAM2, &min_zawor)) {} else {}
  if (cfg->getInt32(PARAM3, &min_pompa)) {} else {}
  if (cfg->getInt32(PARAM4, &Min_Analog_Odczyt)) {} else {}
  if (cfg->getUInt32(PARAM5, &Gorna_Wartosc)) {} else {}
  if (cfg->getUInt32(PARAM6, &Dolna_Wartosc)) {} else {}
  if (cfg->getInt32(PARAM7, &Max_Analog_Odczyt)) {} else {}
  if (cfg->getInt32(PARAM8, &Sygnal_Alarmu)) {} else {}
  if (cfg->getInt32(PARAM9, &Min_Wartosc)) {} else {}
  if (cfg->getInt32(PARAM10, &Max_Wartosc)) {} else {}
  if (cfg->getUInt8(PARAM11, &Zalacz_Analog)) {} else {}
  if (cfg->getUInt8(STANDBY_MODE, &standby_mode)) {} else {}
  if (cfg->getUInt8(STANDBY_MODE1, &standby_mode1)) {} else {}

#endif

