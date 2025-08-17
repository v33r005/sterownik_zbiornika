#pragma once

namespace Supla {
namespace Html {

class ModeParameter : public Supla::HtmlElement {
 public:
  ModeParameter() : HtmlElement(HTML_SECTION_FORM) {}

  void send(Supla::WebSender* sender) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg) {
      uint32_t value = 0; // default value
    sender->send("<h2>Kalibracja czujnika poziomu</h2>");

    sender->send("<div class=\"form-field\">");
    sender->sendLabelFor("read_only", "Odczyt pinu analogowego");
    sender->send("<input type=\"text\" readonly");
    sender->sendNameAndId("read_only");
    sender->send("placeholder=\"");
    if (zbiornik != nullptr){
      sender->send(zbiornik->getRawValue());
    } 
    sender->send("\">");
    sender->send("</div>");

      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(PARAM6, "Minimalny poziom (wartość analogowa)");
      sender->send(
              "<input type=\"number\" min=\"0\" max=\"4095\" step=\"1\" ");
      sender->sendNameAndId(PARAM6);
      sender->send(" value=\"");
      inCfgValue = 0; // default value
      cfg->getUInt32(PARAM6, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>");

      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(PARAM5, "Maksymalny poziom (wartość analogowa)");
      sender->send("<input type=\"number\" min=\"0\" max=\"4095\" step=\"1\" ");
      sender->sendNameAndId(PARAM5);
      sender->send(" value=\"");
      inCfgValue = 4095; // default value
      cfg->getUInt32(PARAM5, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>");

      uint8_t value1 = 0; // default value
      cfg->getUInt8(STANDBY_MODE, &value1);
      // form-field BEGIN
      sender->send("<div class=\"form-field right-checkbox\">");
      sender->sendLabelFor(STANDBY_MODE, "Ustaw poziom minimalny");
      sender->send("<label>");
      sender->send("<span class=\"switch\">");
      sender->send("<input type=\"checkbox\" value=\"on\" ");
      cfg->getUInt8(STANDBY_MODE, &value1);
      sender->send(checked(value1));
      sender->sendNameAndId(STANDBY_MODE);
      sender->send(">");
      sender->send("<span class=\"slider\"></span>");
      sender->send("</span>");
      sender->send("</label>");
      sender->send("</div>");

      uint8_t value2 = 0; // default value

      cfg->getUInt8(STANDBY_MODE1, &value2);
        // form-field BEGIN
      sender->send("<div class=\"form-field right-checkbox\">");
      sender->sendLabelFor(STANDBY_MODE1, "Ustaw poziom maksymalny");
      sender->send("<label>");
      sender->send("<span class=\"switch\">");
      sender->send("<input type=\"checkbox\" value=\"on\" ");
      cfg->getUInt8(STANDBY_MODE1, &value2);
      sender->send(checked(value));
      sender->sendNameAndId(STANDBY_MODE1);
      sender->send(">");
      sender->send("<span class=\"slider\"></span>");
      sender->send("</span>");
      sender->send("</label>");
      sender->send("</div>");
      sender->send("</div>");
      
      sender->send("<div class=\"box\">");
      sender->send("<h2>Ustawienia urządzenia</h2>");

      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(PARAM1, "Poziom maksymalny dolewania w automacie [%]");
      sender->send(
              "<input type=\"number\" min=\"50\" max=\"98\" step=\"1\" ");
      sender->sendNameAndId(PARAM1);
      sender->send(" value=\"");
      inCfgValue = 60; // default value
      cfg->getUInt32(PARAM1, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>");

      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(PARAM2, "Poziom automatycznego dolewania [%]");
      sender->send("<input type=\"number\" min=\"10\" max=\"30\" step=\"1\" ");
      sender->sendNameAndId(PARAM2);
      sender->send(" value=\"");
      inCfgValue = 20; // default value
      cfg->getUInt32(PARAM2, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>");

      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(PARAM3, "Minimalny poziom pracy pompy [%]");
      sender->send("<input type=\"number\" min=\"0\" max=\"40\" step=\"1\" ");
      sender->sendNameAndId(PARAM3);
      sender->send(" value=\"");
      inCfgValue = 10; // default value
      cfg->getUInt32(PARAM3, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>");

      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(PARAM8, "Maksymalny poziom zbiornika do dolewania ręcznego [%]");
      sender->send("<input type=\"number\" min=\"50\" max=\"98\" step=\"1\" ");
      sender->sendNameAndId(PARAM8);
      sender->send(" value=\"");
      inCfgValue = 98; // default value
      cfg->getUInt32(PARAM8, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>"); 
    }
  }

  bool handleResponse(const char* key, const char* value) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg && strcmp(key, PARAM1) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 50 && inFormValue <= 98) {
        cfg->setUInt32(PARAM1, inFormValue);
        maxZawor = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, PARAM2) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 10 && inFormValue <= 40) {
        cfg->setUInt32(PARAM2, inFormValue);
        minZawor = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, PARAM3) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 0 && inFormValue <= 40) {
        cfg->setUInt32(PARAM3, inFormValue);
        minPompa = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, PARAM8) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 50 && inFormValue <= 98) {
        cfg->setUInt32(PARAM8, inFormValue);
        sygnalAlarmu = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, PARAM5) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 0 && inFormValue <= 4095) {
        cfg->setUInt32(PARAM5, inFormValue);
        gornaWartosc = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, PARAM6) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 0 && inFormValue <= 4095) {
        cfg->setUInt32(PARAM6, inFormValue);
        dolnaWartosc = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, STANDBY_MODE) == 0) {
      checkboxFound_ = true;
      uint8_t inCfgValue = 0;  // default value
      cfg->getUInt8(STANDBY_MODE, &inCfgValue);
      uint8_t inFormValue = (strcmp(value, "on") == 0 ? 1 : 0);
      if (inFormValue != inCfgValue) {
        standbyMode = inFormValue;
        cfg->setUInt8(STANDBY_MODE, inFormValue);
      }
      return true;
    }
    if (cfg && strcmp(key, STANDBY_MODE1) == 0) {
      checkboxFound_1 = true;
      uint8_t inCfgValue = 0;  // default value
      cfg->getUInt8(STANDBY_MODE1, &inCfgValue);
      uint8_t inFormValue = (strcmp(value, "on") == 0 ? 1 : 0);
      if (inFormValue != inCfgValue) {
        standbyMode1 = inFormValue;
        cfg->setUInt8(STANDBY_MODE1, inFormValue);
      }
      return true;
    }
    return false;    
  }
  void onProcessingEnd() {
    if (!checkboxFound_) {
      handleResponse(STANDBY_MODE, "off");
    }
    checkboxFound_ = false;
    if (!checkboxFound_1) {
      handleResponse(STANDBY_MODE1, "off");
    }
    checkboxFound_1 = false;
  }

 protected:  
  uint32_t inCfgValue;
  int32_t inCfgValue1;
  bool checkboxFound_ = false;
  bool checkboxFound_1 = false;

};  // ModeParameter

};  // namespace Html
};  // namespace Supla
