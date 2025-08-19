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
      sender->send("<div class=\"box\">"); //box begin
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
      sender->sendLabelFor(DOLNA_WARTOSC, "Minimalny poziom (wartość analogowa)");
      sender->send(
              "<input type=\"number\" min=\"0\" max=\"4095\" step=\"1\" ");
      sender->sendNameAndId(DOLNA_WARTOSC);
      sender->send(" value=\"");
      inCfgValue = 0; // default value
      cfg->getUInt32(DOLNA_WARTOSC, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>");

      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(GORNA_WARTOSC, "Maksymalny poziom (wartość analogowa)");
      sender->send("<input type=\"number\" min=\"0\" max=\"4095\" step=\"1\" ");
      sender->sendNameAndId(GORNA_WARTOSC);
      sender->send(" value=\"");
      inCfgValue = 4095; // default value
      cfg->getUInt32(GORNA_WARTOSC, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>");

      uint8_t value1 = 0; // default value
      cfg->getUInt8(USTAW_MINIMUM, &value1);
      // form-field BEGIN
      sender->send("<div class=\"form-field right-checkbox\">");
      sender->sendLabelFor(USTAW_MINIMUM, "Ustaw poziom minimalny");
      sender->send("<label>");
      sender->send("<span class=\"switch\">");
      sender->send("<input type=\"checkbox\" value=\"on\" ");
      cfg->getUInt8(USTAW_MINIMUM, &value1);
      sender->send(checked(value1));
      sender->sendNameAndId(USTAW_MINIMUM);
      sender->send(">");
      sender->send("<span class=\"slider\"></span>");
      sender->send("</span>");
      sender->send("</label>");
      sender->send("</div>");

      uint8_t value2 = 0; // default value

      cfg->getUInt8(USTAW_MAKSIMUM, &value2);
        // form-field BEGIN
      sender->send("<div class=\"form-field right-checkbox\">");
      sender->sendLabelFor(USTAW_MAKSIMUM, "Ustaw poziom maksymalny");
      sender->send("<label>");
      sender->send("<span class=\"switch\">");
      sender->send("<input type=\"checkbox\" value=\"on\" ");
      cfg->getUInt8(USTAW_MAKSIMUM, &value2);
      sender->send(checked(value));
      sender->sendNameAndId(USTAW_MAKSIMUM);
      sender->send(">");
      sender->send("<span class=\"slider\"></span>");
      sender->send("</span>");
      sender->send("</label>");
      sender->send("</div>");
      sender->send("</div>"); //box emd
      
      sender->send("<div class=\"box\">"); //box begin
      sender->send("<h2>Ustawienia urządzenia</h2>");

      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(MAX_ZAWOR, "Poziom maksymalny dolewania w automacie [%]");
      sender->send(
              "<input type=\"number\" min=\"50\" max=\"98\" step=\"1\" ");
      sender->sendNameAndId(MAX_ZAWOR);
      sender->send(" value=\"");
      inCfgValue = 60; // default value
      cfg->getUInt32(MAX_ZAWOR, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>");

      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(MIN_ZAWOR, "Poziom automatycznego dolewania [%]");
      sender->send("<input type=\"number\" min=\"10\" max=\"30\" step=\"1\" ");
      sender->sendNameAndId(MIN_ZAWOR);
      sender->send(" value=\"");
      inCfgValue = 20; // default value
      cfg->getUInt32(MIN_ZAWOR, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>");

      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(MIN_POMPA, "Minimalny poziom pracy pompy [%]");
      sender->send("<input type=\"number\" min=\"0\" max=\"40\" step=\"1\" ");
      sender->sendNameAndId(MIN_POMPA);
      sender->send(" value=\"");
      inCfgValue = 10; // default value
      cfg->getUInt32(MIN_POMPA, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>");

      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(MAX_POZIOM, "Maksymalny poziom zbiornika do dolewania ręcznego [%]");
      sender->send("<input type=\"number\" min=\"50\" max=\"98\" step=\"1\" ");
      sender->sendNameAndId(MAX_POZIOM);
      sender->send(" value=\"");
      inCfgValue = 98; // default value
      cfg->getUInt32(MAX_POZIOM, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>"); 

      sender->send("<div class=\"form-field\">");
        sender->sendLabelFor(NAN_VALUE, "NaN value");
        sender->send(
              "<input type=\"number\" min=\"-1\" step=\"1\" ");
        sender->sendNameAndId(NAN_VALUE);
        sender->send(" value=\"");
        inCfgIntValue = DEFAULT_NAN_VALUE;
        cfg->getInt32(NAN_VALUE, &inCfgIntValue);
        sender->send(inCfgIntValue);
        sender->send("\">");
        sender->send("</div>");
    }
  }

  bool handleResponse(const char* key, const char* value) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg && strcmp(key, MAX_ZAWOR) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 50 && inFormValue <= 98) {
        cfg->setUInt32(MAX_ZAWOR, inFormValue);
        maxZawor = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, MIN_ZAWOR) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 10 && inFormValue <= 40) {
        cfg->setUInt32(MIN_ZAWOR, inFormValue);
        minZawor = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, MIN_POMPA) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 0 && inFormValue <= 40) {
        cfg->setUInt32(MIN_POMPA, inFormValue);
        minPompa = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, MAX_POZIOM) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 50 && inFormValue <= 98) {
        cfg->setUInt32(MAX_POZIOM, inFormValue);
        maxPoziom = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, GORNA_WARTOSC) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 0 && inFormValue <= 4095) {
        cfg->setUInt32(GORNA_WARTOSC, inFormValue);
        gornaWartosc = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, DOLNA_WARTOSC) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 0 && inFormValue <= 4095) {
        cfg->setUInt32(DOLNA_WARTOSC, inFormValue);
        dolnaWartosc = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, USTAW_MINIMUM) == 0) {
      checkboxFound_ = true;
      uint8_t inCfgValue = 0;  // default value
      cfg->getUInt8(USTAW_MINIMUM, &inCfgValue);
      uint8_t inFormValue = (strcmp(value, "on") == 0 ? 1 : 0);
      if (inFormValue != inCfgValue) {
        ustawMinimum = inFormValue;
        cfg->setUInt8(USTAW_MINIMUM, inFormValue);
      }
      return true;
    }
    if (cfg && strcmp(key, USTAW_MAKSIMUM) == 0) {
      checkboxFound_1 = true;
      uint8_t inCfgValue = 0;  // default value
      cfg->getUInt8(USTAW_MAKSIMUM, &inCfgValue);
      uint8_t inFormValue = (strcmp(value, "on") == 0 ? 1 : 0);
      if (inFormValue != inCfgValue) {
        ustawMaksimum = inFormValue;
        cfg->setUInt8(USTAW_MAKSIMUM, inFormValue);
      }
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
      handleResponse(USTAW_MINIMUM, "off");
    }
    checkboxFound_ = false;
    if (!checkboxFound_1) {
      handleResponse(USTAW_MAKSIMUM, "off");
    }
    checkboxFound_1 = false;
  }

 protected:  
  uint32_t inCfgValue;
  int32_t inCfgValue1;
  int32_t inCfgIntValue = 0;
  bool checkboxFound_ = false;
  bool checkboxFound_1 = false;

};  // ModeParameter

};  // namespace Html
};  // namespace Supla
