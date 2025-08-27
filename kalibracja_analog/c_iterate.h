#pragma once

class CustomIterate : public Supla::Element {
 public:
  CustomIterate() {}

  void iterateAlways() {
    Kalibracja();
    Obsluga_Suwakow();
    ObslugaPompy();
    Obsluga_Zaworu();
    Obsluga_Status_LED_RGB();
  }
};  // CustomIterate

CustomIterate cIterate;