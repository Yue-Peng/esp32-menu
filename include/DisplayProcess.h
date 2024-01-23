//
// Created by user on 2024/1/23.
//

#ifndef ESP32_MENU_DISPLAYPROCESS_H
#define ESP32_MENU_DISPLAYPROCESS_H

class DisplayProcess {
private:
    DisplayProcess();

    static DisplayProcess *instance;
public:
    ~DisplayProcess();

    static DisplayProcess *getInstance();

    void setup();
    void begin();
};

#endif //ESP32_MENU_DISPLAYPROCESS_H
