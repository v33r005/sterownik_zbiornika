#pragma once

Supla::Storage::Init();
auto cfg = Supla::Storage::ConfigInstance();

if (Supla::Storage::ConfigInstance()->getString(DEV_NAME, devName, 30)) {
  SUPLA_LOG_DEBUG("# Param[%s]: %s", DEV_NAME, devName);
} else {
  Supla::Storage::ConfigInstance()->setString(DEV_NAME, "Supla-Sprzecik");
}
cfg->getUInt32(PARAM1, &maxZawor);
cfg->getUInt32(PARAM2, &minZawor);
cfg->getUInt32(PARAM3, &minPompa);
cfg->getUInt32(PARAM5, &gornaWartosc);
cfg->getUInt32(PARAM6, &dolnaWartosc);
cfg->getUInt32(PARAM8, &sygnalAlarmu);
cfg->getUInt8(STANDBY_MODE, &standbyMode);
cfg->getUInt8(STANDBY_MODE1, &standbyMode1);
cfg->getUInt32(NAN_VALUE, &nanValue);
