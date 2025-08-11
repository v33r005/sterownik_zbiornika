#ifndef ZMIENNE_H_
#define ZMIENNE_H_

const char DEV_NAME[] = "dev_name";
char devName[30] = {};
const char PARAM_CMD1[] = "cmd1";
const char PARAM1[] = "param1";
const char PARAM2[] = "param2";
const char PARAM3[] = "param3";
const char PARAM4[] = "param4";
const char PARAM5[] = "param5";
const char PARAM6[] = "param6";
const char PARAM7[] = "param7";
const char PARAM8[] = "param8";
const char PARAM9[] = "param8";
const char PARAM10[] = "param8";
const char PARAM11[] = "param8";
const char PARAM12[] = "param8";
uint32_t Gorna_Wartosc = 4095;
uint32_t Dolna_Wartosc = 0;
int32_t Dolewanie = 0;
uint32_t Sygnal_Alarmu = 95;
uint32_t max_zawor = 60;
uint32_t min_zawor = 20;
uint32_t min_pompa = 10;
int32_t Min_Analog_Odczyt = 0;
int32_t Max_Analog_Odczyt = 4095;
int32_t Min_Wartosc = 0;
int32_t Max_Wartosc = 100;
uint8_t Zalacz_Analog = OFF_;
const char STANDBY_MODE[] = "StandByMode";
uint8_t standby_mode = OFF_;
const char STANDBY_MODE1[] = "StandByMode1";
uint8_t standby_mode1 = OFF_;
bool dolej;
bool odczyt;
int32_t Aktualny_Poziom;
int32_t DEFAULT_IN_MAX = 4095;
int32_t DEFAULT_IN_MIN = 0;
int32_t DEFAULT_OUT_MIN = 0;
int32_t DEFAULT_OUT_MAX = 1000000;
int32_t DEFAULT_NAN_VALUE = -1;
const char NAN_VALUE[] = "nan_value";
int32_t nanValue = 100;
const char RAW_VALUE[] = "raw_value";


#endif

