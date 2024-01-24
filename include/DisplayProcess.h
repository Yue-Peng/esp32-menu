//
// Created by user on 2024/1/23.
//

#ifndef ESP32_MENU_DISPLAYPROCESS_H
#define ESP32_MENU_DISPLAYPROCESS_H

#include "Setting.h"

class DisplayProcess {
private:
    DisplayProcess();

    Setting *set;

    static DisplayProcess *instance;
public:
    ~DisplayProcess();

    static DisplayProcess *getInstance();

    void setup();

    void begin();
};

#endif //ESP32_MENU_DISPLAYPROCESS_H
