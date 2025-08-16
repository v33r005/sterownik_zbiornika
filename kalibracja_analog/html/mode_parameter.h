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

      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(NAN_VALUE, "Poziom wykrywania awarii czujnika [%]");
      sender->send("<input type=\"number\" min=\"-1\" max=\"98\" step=\"1\" ");
      sender->sendNameAndId(NAN_VALUE);
      sender->send(" value=\"");
      inCfgValue = -1; // default value
      cfg->getUInt32(NAN_VALUE, &inCfgValue);
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
    return false;    
  }

 protected:  
  uint32_t inCfgValue;

};  // ModeParameter

};  // namespace Html
};  // namespace Supla
