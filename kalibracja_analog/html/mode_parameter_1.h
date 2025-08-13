#pragma once

namespace Supla {
namespace Html {

class ModeParameter1 : public Supla::HtmlElement {
 public:
  ModeParameter1() : HtmlElement(HTML_SECTION_FORM) {}

  void send(Supla::WebSender* sender) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg) {
      uint32_t value = 0; // default value
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
    }
  }

  bool handleResponse(const char* key, const char* value) {
    auto cfg = Supla::Storage::ConfigInstance();
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
    return false;    
  }
  
 protected:
  uint32_t inCfgValue;

};  // ModeParameter

};  // namespace Html
};  // namespace Supla
