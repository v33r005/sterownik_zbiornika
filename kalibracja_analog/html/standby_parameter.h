#pragma once

namespace Supla {
namespace Html {

class StandByParameter : public Supla::HtmlElement {
 public:
  StandByParameter() : HtmlElement(HTML_SECTION_FORM) {}

  void send(Supla::WebSender* sender) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg) {
      uint8_t value = 0; // default value
      cfg->getUInt8(STANDBY_MODE, &value);
      // form-field BEGIN
      sender->send("<div class=\"form-field right-checkbox\">");
      sender->sendLabelFor(STANDBY_MODE, "Ustaw poziom minimalny");
      sender->send("<label>");
      sender->send("<span class=\"switch\">");
      sender->send("<input type=\"checkbox\" value=\"on\" ");
      cfg->getUInt8(STANDBY_MODE, &value);
      sender->send(checked(value));
      sender->sendNameAndId(STANDBY_MODE);
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
    return false;
  }
  
  void onProcessingEnd() {
    if (!checkboxFound_) {
      handleResponse(STANDBY_MODE, "off");
    }
    checkboxFound_ = false;
  }

 protected:
  bool checkboxFound_ = false;

};  // AverageParameter

};  // namespace Html
};  // namespace Supla
