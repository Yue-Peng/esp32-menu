#include "DisplayProcess.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include "configuration.h"
#include "Setting.h"
#include "SetName.h"

Setting *set;

DisplayProcess::DisplayProcess() {
    set = Setting::getInstance();
}

DisplayProcess::~DisplayProcess() = default;

DisplayProcess *DisplayProcess::instance;

DisplayProcess *DisplayProcess::getInstance() {
    if (instance == nullptr) instance = new DisplayProcess();
    return instance;
}

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void DisplayProcess::setup() {
    Serial.println("DisplayProcess::setup");
    set->getInstance();
    u8g2.begin();
}


void drawJX() {
    // u8g2.drawRFrame(10, set->get(SetName::SET_BAUD_RATE), 50, 30, 5);
    for (int i = 0; i < 20; i++) {
        u8g2.drawLine(20 + i, 20, 20 + i, 40);
    }
}


int i = 0;

void DisplayProcess::begin() {
    u8g2.firstPage();
    i += 3;
    if (i > 60) i = 0;
    do {
        u8g2.drawRFrame(10, 10, 50 + i, 30, 5);
    } while (u8g2.nextPage());
}


