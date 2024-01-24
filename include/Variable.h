#ifndef SETTING_H
#define SETTING_H

#include "SetName.h"

class Variable {
private:
    ~Variable();

    Variable();

    static Variable *instance;
public:
    static Variable *getInstance();

    int get(SetName setName);

    void set(SetName setName, int value);

    void add(SetName setName);

    void sub(SetName setName);
};

#endif // SETTING_H
