//
// Created by user on 2024/1/23.
//

#ifndef ESP32_MENU_DISPLAYPROCESS_H
#define ESP32_MENU_DISPLAYPROCESS_H

#include "Variable.h"

class DisplayProcess {
private:
    DisplayProcess();

    Variable *var;

    static DisplayProcess *instance;

    void mainScreen();

    void settingScreen();
public:
    ~DisplayProcess();

    static DisplayProcess *getInstance();

    void setup();

    void begin();
};

#endif //ESP32_MENU_DISPLAYPROCESS_H
