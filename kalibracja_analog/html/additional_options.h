#pragma once

namespace Supla {
namespace Html {

class AdditionalOptions : public Supla::HtmlElement {
 public:
  AdditionalOptions() : HtmlElement(HTML_SECTION_FORM) {}

  void send(Supla::WebSender* sender) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg) {
      uint8_t value = 0; // default 
      sender->send("<div class=\"box\">"); //box begin
      sender->send("<h2>Ustawienia dodatkowe</h2>");
      cfg->getUInt8(KRANCOWKI, &value);
      // form-field BEGIN
      sender->send("<div class=\"form-field right-checkbox\">");
      sender->sendLabelFor(KRANCOWKI, "Czujniki poziomu binarne");
      sender->send("<label>");
      sender->send("<span class=\"switch\">");
      sender->send("<input type=\"checkbox\" value=\"on\" ");
      cfg->getUInt8(KRANCOWKI, &value);
      sender->send(checked(value));
      sender->sendNameAndId(KRANCOWKI);
      sender->send(">");
      sender->send("<span class=\"slider\"></span>");
      sender->send("</span>");
      sender->send("</label>");
      sender->send("</div>");

      uint8_t value1 = 0; // default 
      cfg->getUInt8(CZUJNIK_TEMPERATURY, &value1);
      // form-field BEGIN
      sender->send("<div class=\"form-field right-checkbox\">");
      sender->sendLabelFor(CZUJNIK_TEMPERATURY, "Czujnik Temperatury deszczówki");
      sender->send("<label>");
      sender->send("<span class=\"switch\">");
      sender->send("<input type=\"checkbox\" value=\"on\" ");
      cfg->getUInt8(CZUJNIK_TEMPERATURY, &value1);
      sender->send(checked(value1));
      sender->sendNameAndId(CZUJNIK_TEMPERATURY);
      sender->send(">");
      sender->send("<span class=\"slider\"></span>");
      sender->send("</span>");
      sender->send("</label>");
      sender->send("</div>");
      // form-field END
    }  // cfg
  }  // sender

  bool handleResponse(const char* key, const char* value) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg && strcmp(key, KRANCOWKI) == 0) {
      checkboxFound_ = true;
      uint8_t inCfgValue = 0;  // default value
      cfg->getUInt8(KRANCOWKI, &inCfgValue);
      uint8_t inFormValue = (strcmp(value, "on") == 0 ? 1 : 0);
      if (inFormValue != inCfgValue) {
        Krancowki = inFormValue;
        cfg->setUInt8(KRANCOWKI, inFormValue);
      }
      return true;
    }

    if (cfg && strcmp(key, CZUJNIK_TEMPERATURY) == 0) {
      checkboxFound_1 = true;
      uint8_t inCfgValue = 0;  // default value
      cfg->getUInt8(CZUJNIK_TEMPERATURY, &inCfgValue);
      uint8_t inFormValue = (strcmp(value, "on") == 0 ? 1 : 0);
      if (inFormValue != inCfgValue) {
        CzujnikTemperatury = inFormValue;
        cfg->setUInt8(CZUJNIK_TEMPERATURY, inFormValue);
      }
      return true;
    }
    return false;
  }
  
  void onProcessingEnd() {
    if (!checkboxFound_) {
      handleResponse(KRANCOWKI, "off");
    }
    checkboxFound_1 = false;
    if (!checkboxFound_) {
      handleResponse(CZUJNIK_TEMPERATURY, "off");
    }
    checkboxFound_1 = false;
  }

 protected:
  bool checkboxFound_ = false;
  bool checkboxFound_1 = false;

};  // AverageParameter

};  // namespace Html
};  // namespace Supla
