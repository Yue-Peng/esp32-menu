#include "BackendProcess.h"
#include <Arduino.h>
#include "Variable.h"
#include "SetName.h"

Variable *BackendProcess::var;

BackendProcess::BackendProcess() {
    var = Variable::getInstance();
};

BackendProcess *BackendProcess::instance;

BackendProcess *BackendProcess::getInstance() {
    if (instance == nullptr) instance = new BackendProcess();
    return instance;
}

void BackendProcess::setup() {}

void BackendProcess::begin() {
//    var->get(SetName::VAR_SCREEN_TYPE) > 3 ?
//    var->set(SetName::VAR_SCREEN_TYPE, 0) : var->add(SetName::VAR_SCREEN_TYPE);
    delay(100000000);
}