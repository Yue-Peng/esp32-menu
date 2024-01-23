#ifndef SETTING_H
#define SETTING_H

#include "SetName.h"

class Setting {
private:
    Setting();

    ~Setting();

    static Setting *instance;
public:
    static Setting *getInstance();

    int get(SetName name);

    void add(SetName name);
    void sub(SetName name);
};

#endif // SETTING_H
