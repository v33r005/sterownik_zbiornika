#ifndef HTML_CLASSES_H_
#define HTML_CLASSES_H_

#include <supla/network/html_element.h>
#include <supla/network/web_sender.h>
#include <supla/storage/config.h>
#include <supla/storage/storage.h>
#include <string.h>

const char *required(bool isRequired) {
  return isRequired ? "required " : "";
}

const char *displayed(bool isDisplayed) {
  return isDisplayed ? "block\">" : "none\">";
}

#include "html/przycisk_update.h"
#include "html/readonly.h"
#include "html/standby_parameter.h"
#include "html/standby_parameter1.h"
#include "html/mode_parameter.h"
#include "html/mode_parameter_1.h"
#include "html/analog_sensors_.h"

#endif
