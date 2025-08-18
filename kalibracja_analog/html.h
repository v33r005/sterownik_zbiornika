#pragma once

new Supla::Html::DeviceInfo(&SuplaDevice);
new Supla::Html::WifiParameters;
new Supla::Html::ProtocolParameters(false, false);
new Supla::Html::StatusLedParameters;
new Supla::Html::CustomTextParameter(DEV_NAME, "Nazwa Urządzenia", 30);
new Supla::Html::DivEnd();
new Supla::Html::ModeParameter;
new Supla::Html::DivEnd();
new Supla::Html::AdditionalOptions;
auto selectCmd = new Supla::Html::SelectCmdInputParameter(PARAM_CMD1, "Reset do ustawień fabrycznych");
selectCmd->registerCmd("RESET", Supla::ON_EVENT_1);
selectCmd->addAction(Supla::RESET_TO_FACTORY_SETTINGS, SuplaDevice, Supla::ON_EVENT_1, true);
new Supla::Html::UpdateParameter;