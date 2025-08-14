#pragma once

namespace Supla {
namespace Html {

class AnalogSensorsParameters : public Supla::HtmlElement {
 public:
  AnalogSensorsParameters() : HtmlElement(HTML_SECTION_FORM) {}

  void send(Supla::WebSender* sender) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg) {
      sender->send("<h2>Ustawienia Czujnika Ciśnienia</h2>");
      
      // form-field BEGIN
      sender->send("<div class=\"form-field right-checkbox\">");
      char labelBuf[17];
      snprintf(labelBuf, sizeof(labelBuf), "Analog sensor S%d", 1);
      sender->sendLabelFor(PARAM11, labelBuf);
      sender->send("<label>");
      sender->send("<span class=\"switch\">");
      sender->send("<input type=\"checkbox\" value=\"on\" ");
      cfg->getUInt8(PARAM11, &value_);
      sender->send(checked(value_));
      sender->sendNameAndId(PARAM11);
      sender->send(" onclick=\"showHideAnalogSensor");
      sender->send(1);
      sender->send("DivToggle()\">");
      sender->send("<span class=\"slider\"></span>");
      sender->send("</span>");
      sender->send("</label>");
      sender->send("</div>");
      // form-field END

      // hidden div begin
      sender->send("<div id=\"as");
      sender->send(1);
      sender->send("_hidden_div\" style=\"display: ");
      sender->send(displayed(value_));

      // form-field BEGIN
      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(PARAM4, "IN minimum");
      sender->send("<input type=\"number\" min=\"0\" max=\"");
      sender->send(DEFAULT_IN_MAX);
      sender->send("\" step=\"1\" ");
      sender->sendNameAndId(PARAM4);
      sender->send(" value=\"");
      inCfgValue_ = DEFAULT_IN_MIN;
      cfg->getUInt32(PARAM4, &inCfgValue_);
      sender->send(inCfgValue_);
      sender->send("\">");
      sender->send("</div>");
      // form-field END

      // form-field BEGIN
      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(PARAM7, "IN maximum");
      sender->send("<input type=\"number\" min=\"0\" max=\"");
      sender->send(DEFAULT_IN_MAX);
      sender->send("\" step=\"1\" ");
      sender->sendNameAndId(PARAM7);
      sender->send(" value=\"");
      inCfgValue_ = DEFAULT_IN_MAX;
      cfg->getUInt32(PARAM7, &inCfgValue_);
      sender->send(inCfgValue_);
      sender->send("\">");
      sender->send("</div>");
      // form-field END
	  
	    // form-field BEGIN
      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(PARAM9, "OUT minimum");
      sender->send("<input type=\"number\" min=\"0\" step=\"0.001\" ");
      sender->sendNameAndId(PARAM9);
      sender->send(" value=\"");
      inCfgValue_ = DEFAULT_OUT_MIN;
      cfg->getUInt32(PARAM9, &inCfgValue_);
      sender->send(inCfgValue_, 4);
      sender->send("\">");
      sender->send("</div>");
      // form-field END
	  
	    // form-field BEGIN
      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(PARAM10, "OUT maximum");
      sender->send("<input type=\"number\" min=\"0\" step=\"0.001\" ");
      sender->sendNameAndId(PARAM10);
      sender->send(" value=\"");
      inCfgValue_ = DEFAULT_OUT_MAX;
      cfg->getUInt32(PARAM10, &inCfgValue_);
      sender->send(inCfgValue_, 4);
      sender->send("\">");
      sender->send("</div>");
      // form-field END
	  
	    // form-field BEGIN
      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(NAN_VALUE, "NaN value");
      sender->send("<input type=\"number\" min=\"-1\" step=\"1\" ");
      sender->sendNameAndId(NAN_VALUE);
      sender->send(" value=\"");
      inCfgIntValue_ = DEFAULT_NAN_VALUE;
      cfg->getInt32(NAN_VALUE, &inCfgIntValue_);
      sender->send(inCfgIntValue_);
      sender->send("\">");
      sender->send("</div>");
      // form-field END

      // form-field BEGIN
      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(RAW_VALUE, "RAW value");
      sender->send("<input type=\"text\" readonly");
      sender->sendNameAndId(RAW_VALUE);
      sender->send("placeholder=\"");
      if (zbiornik != nullptr) {
        sender->send(zbiornik->getRawValue());
      } else {
        sender->send("sensor is unavailable");
      }
      sender->send("\">");
      sender->send("</div>");
      // form-field END

      sender->send("</div>"); // hidden div end

      sender->send("<script>");
      sender->send("function showHideAnalogSensor");
      sender->send(1);
      sender->send("DivToggle() {"
          "var as");
      sender->send(1);
      sender->send("p_checkBox = document.getElementById(\"");
      sender->send(PARAM11);
      sender->send("\");"
          "var as");
      sender->send(1);
      sender->send("p_content = document.getElementById(\"as");
      sender->send(1);
      sender->send("_hidden_div\");"
          "if (as");
      sender->send(1);
      sender->send("p_checkBox.checked == true) {"
            "as");
      sender->send(1);
      sender->send("p_content.style.display = \"block\";"
          "} else {"
            "as");
      sender->send(1);
      sender->send("p_content.style.display = \"none\";"
          "}"
        "}");
      sender->send("</script>");
    } // cfg
  } // sender

  bool handleResponse(const char* key, const char* value) {
    auto cfg = Supla::Storage::ConfigInstance();
      if (cfg && strcmp(key, PARAM11) == 0) {
        checkboxFound_ = true;
        uint8_t inCfgValue = 0;  // default value
        cfg->getUInt8(PARAM11, &inCfgValue);
        uint8_t inFormValue = (strcmp(value, "on") == 0 ? 1 : 0);
        if (inFormValue != inCfgValue) {
          zalaczAnalog = inFormValue;
          cfg->setUInt8(PARAM11, inFormValue);
        }
        return true;
      }
      if (cfg && strcmp(key, PARAM4) == 0) {
        uint32_t inFormValue = stringToUInt(value);
        cfg->setUInt32(PARAM4, inFormValue);
        minAnalogOdczyt = inFormValue;
        return true;
      }
      if (cfg && strcmp(key, PARAM7) == 0) {
        uint32_t inFormValue = stringToUInt(value);
        cfg->setUInt32(PARAM7, inFormValue);
        maxAnalogOdczyt =
                (inFormValue < minAnalogOdczyt) ? minAnalogOdczyt : inFormValue;
        return true;
      }
      if (cfg && strcmp(key, PARAM9) == 0) {
        uint32_t inFormValue = floatStringToInt(value, 4);
        cfg->setUInt32(PARAM9, inFormValue);
        minWartosc = inFormValue;
        return true;
      }
      if (cfg && strcmp(key, PARAM10) == 0) {
        uint32_t inFormValue = floatStringToInt(value, 4);
        cfg->setUInt32(PARAM10, inFormValue);
        maxWartosc = (inFormValue < minWartosc) ? minWartosc : inFormValue;
        return true;
      }
      if (cfg && strcmp(key, NAN_VALUE) == 0) {
        int32_t inFormValue = stringToInt(value);
        cfg->setInt32(NAN_VALUE, inFormValue);
        nanValue = inFormValue;
        return true;
      }
    return false;
  }

  void onProcessingEnd() {
      if (!checkboxFound_) {
        handleResponse(PARAM11, "off");
      }
      checkboxFound_ = false;
  }

 protected:
  bool checkboxFound_ = false;
  uint8_t value_ = 0;
  uint32_t inCfgValue_ = 0;
  int32_t inCfgIntValue_ = 0;

}; // AnalogSensorsParameters

} // namespace Html
} // namespace Supla
