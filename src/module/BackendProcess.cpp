#include "BackendProcess.h"
#include <Arduino.h>
#include "Setting.h"
#include "SetName.h"

BackendProcess::BackendProcess() {}

BackendProcess::~BackendProcess() = default;

BackendProcess *BackendProcess::instance;

BackendProcess *BackendProcess::getInstance() {
    if (instance == nullptr) instance = new BackendProcess();
    return instance;
}

Setting *set;

void BackendProcess::setup() {
    set = Setting::getInstance();
}

void BackendProcess::begin() {
    Serial.println(set->get(SetName::SET_BAUD_RATE));
    Serial.println(set->get(SetName::SET_TEMP));
    set->add(SetName::SET_BAUD_RATE);
}