#pragma once

new Supla::Html::DeviceInfo(&SuplaDevice);
new Supla::Html::WifiParameters;
new Supla::Html::ProtocolParameters(false, false);
new Supla::Html::StatusLedParameters;
new Supla::Html::TimeParameters(&SuplaDevice);
new Supla::Html::CustomTextParameter(DEV_NAME, "Nazwa Urządzenia", 30);
new Supla::Html::DivEnd();
new Supla::Html::DivBegin("box");
new Supla::Html::ModeParameter;
auto selectCmd = new Supla::Html::SelectCmdInputParameter(PARAM_CMD1, "Reset do ustawień fabrycznych");
selectCmd->registerCmd("RESET", Supla::ON_EVENT_1);
selectCmd->addAction(Supla::RESET_TO_FACTORY_SETTINGS, SuplaDevice, Supla::ON_EVENT_1, true);
new Supla::Html::UpdateParameter;
