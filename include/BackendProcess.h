//
// Created by user on 2024/1/23.
//

#ifndef ESP32_MENU_BACKENDPROCESS_H
#define ESP32_MENU_BACKENDPROCESS_H


class BackendProcess {
private:
    BackendProcess();

    static BackendProcess *instance;
public:
    ~BackendProcess();

    static BackendProcess *getInstance();

    void setup();
    void begin();
};


#endif //ESP32_MENU_BACKENDPROCESS_H
