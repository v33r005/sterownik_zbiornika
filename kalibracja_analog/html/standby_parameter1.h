#ifndef STANDBY_PARAMETER_1_H_
#define STANDBY_PARAMETER_1_H_

namespace Supla {
namespace Html {

class StandByParameter1 : public Supla::HtmlElement {
 public:
  StandByParameter1() : HtmlElement(HTML_SECTION_FORM) {}

  void send(Supla::WebSender* sender) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg) {
      uint8_t value = 0; // default value

        cfg->getUInt8(STANDBY_MODE1, &value);
        // form-field BEGIN
        sender->send("<div class=\"form-field right-checkbox\">");
        sender->sendLabelFor(STANDBY_MODE1, "Ustaw poziom maksymalny");
        sender->send("<label>");
        sender->send("<span class=\"switch\">");
        sender->send("<input type=\"checkbox\" value=\"on\" ");
        cfg->getUInt8(STANDBY_MODE1, &value);
        sender->send(checked(value));
        sender->sendNameAndId(STANDBY_MODE1);
        sender->send(">");
        sender->send("<span class=\"slider\"></span>");
        sender->send("</span>");
        sender->send("</label>");
        sender->send("</div>");
        // form-field END
        
     
    } // cfg

  }; // sender

  bool handleResponse(const char* key, const char* value) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg && strcmp(key, STANDBY_MODE1) == 0) {
      checkboxFound = true;
      uint8_t inCfgValue = 0;  // default value
      cfg->getUInt8(STANDBY_MODE1, &inCfgValue);
      uint8_t inFormValue = (strcmp(value, "on") == 0 ? 1 : 0);
      if (inFormValue != inCfgValue) {
        standby_mode1 = inFormValue;
        cfg->setUInt8(STANDBY_MODE1, inFormValue);
      }
      return true;
    }

    return false;
  };
  
  void onProcessingEnd() {
    if (!checkboxFound) {
      handleResponse(STANDBY_MODE1, "off");
    }
    checkboxFound = false;

  };

 protected:
  bool checkboxFound = false;
  uint32_t inCfgValue;

}; // AverageParameter

}; // namespace Html
}; // namespace Supla

#endif