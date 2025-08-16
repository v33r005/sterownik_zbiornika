#pragma once

const char DEV_NAME[] = "dev_name";
char devName[30] = {};
const char PARAM_CMD1[] = "cmd1";
const char PARAM1[] = "param1";
const char PARAM2[] = "param2";
const char PARAM3[] = "param3";
const char PARAM5[] = "param5";
const char PARAM6[] = "param6";
const char PARAM8[] = "param8";
uint32_t gornaWartosc = 4095;
uint32_t dolnaWartosc = 0;
uint32_t sygnalAlarmu = 95;
uint32_t maxZawor = 60;
uint32_t minZawor = 20;
uint32_t minPompa = 10;
const char STANDBY_MODE[] = "StandByMode";
uint8_t standbyMode = OFF;
const char STANDBY_MODE1[] = "StandByMode1";
uint8_t standbyMode1 = OFF;
bool dolej = false;
bool odczyt = false;
int32_t aktualnyPoziom;
const char NAN_VALUE[] = "nan_value";
uint32_t nanValue = DEFAULT_NAN_VALUE;
const char RAW_VALUE[] = "raw_value";



