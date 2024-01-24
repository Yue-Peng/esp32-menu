#include "BackendProcess.h"
#include <Arduino.h>
#include "Setting.h"
#include "SetName.h"

Setting *BackendProcess::set;

BackendProcess::BackendProcess() {
    set = Setting::getInstance();
};

BackendProcess *BackendProcess::instance;

BackendProcess *BackendProcess::getInstance() {
    if (instance == nullptr) instance = new BackendProcess();
    return instance;
}

void BackendProcess::setup() {}

void BackendProcess::begin() {
    Serial.println(set->get(SetName::SET_BAUD_RATE));
    Serial.println(set->get(SetName::SET_TEMP));
    set->add(SetName::SET_BAUD_RATE);
}