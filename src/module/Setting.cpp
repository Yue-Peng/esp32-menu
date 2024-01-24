//
// Created by user on 2024/1/23.
//

#include "Variable.h"
#include <unordered_map>
#include "SetName.h"
#include <EEPROM.h>
#include "configuration.h"


struct VariableItem {
private:
    int addr;
    int settingValue;
    int defaultValue;
    int step;
    int min;
    int max;
    bool store;
    bool needRestart;
public:

    VariableItem() = default;

    VariableItem(int defaultValue, int step, int min, int max) {
        this->addr = 0;
        this->settingValue = defaultValue;
        this->defaultValue = defaultValue;
        this->step = step;
        this->min = min;
        this->max = max;
        this->store = true;
    }

    VariableItem(int settingValue) {
        this->addr = 0;
        this->settingValue = settingValue;
        this->defaultValue = settingValue;
        this->step = 1;
        this->min = -2000000000;
        this->max = 2000000000;
        this->store = false;
    }

    VariableItem(int settingValue, int defaultValue, int step, int min, int max, bool store) {
        this->addr = 0;
        this->settingValue = settingValue;
        this->defaultValue = defaultValue;
        this->step = step;
        this->min = min;
        this->max = max;
        this->store = store;
    }

//    VariableItem(int settingValue) {
//        VariableItem(settingValue, settingValue, 0, settingValue, settingValue, false, false);
//    }


    void setAddress(int address) { this->addr = address; }

    void readSetting() {
        Serial.printf("read value from %d\r\n", addr);
        settingValue = EEPROM.readInt(addr);
        Serial.printf("addr %d value is %d\r\n", addr, settingValue);
    }

    void setSettingValue(int value) {
        if (settingValue != value) {
            settingValue = value;
            settingValue = settingValue < min ? min : (settingValue > max ? max : settingValue);
            flush();
        }
    }

    int getDefaultValue() const { return defaultValue; }

    int getSettingValue() const { return settingValue; }

    void resetting() const {
        Serial.printf("flush value %d to address %d\r\n", defaultValue, addr);
        EEPROM.writeInt(addr, defaultValue);
    }

    void flush() const { if (store) EEPROM.writeInt(addr, settingValue); }

    void add() { setSettingValue(settingValue + step); }

    void sub() { setSettingValue(settingValue - step); }

    bool isStore() const { return store; }
};

Variable *Variable::instance;

std::unordered_map<SetName, VariableItem> setMap;

Variable::~Variable() = default;

Variable::Variable() {
    // 配置项
    setMap = {
            /*
             * 基础配置，需要写入存储持久化
             */
            {SET_TEMP_BASE,         VariableItem(100, 1, 1, 1)},
            {SET_TEMP_SLEEP,        VariableItem(50, 1, 1, 1)},
            {SET_POINT_TEMP_COUNT,  VariableItem(10, 1, 1, 20)},
            {SET_POINT_POWER_COUNT, VariableItem(10, 1, 1, 1)},

            /*
             * 运行变量，作为全局变量使用，不需要持久化到存储中
             */
            {VAR_SCREEN_TYPE,       VariableItem(0)},

    };

    // 初始化内存
    Serial.println("init EEPROM");
    EEPROM.begin((setMap.size() + 1) * sizeof(int));
    Serial.println("EEPROM apply successful");

    // 给配置项分配内存地址
    Serial.println("init setting EEPROM address");
    int address = sizeof(int);
    for (auto &item: setMap) {
        if (item.second.isStore()) {
            item.second.setAddress(address);
            address += sizeof(int);
        }
    }
    Serial.println("EEPROM address init successful");

    /*
     * 读取初始化位
     * 如果是0，说明是首次运行，需要将默认内容写入到内存中
     * 如果是1，说明非首次运行，从内存中读取配置信息
     */
    Serial.printf("EEPROM init flag is %d, will be init.\r\n", EEPROM.readInt(0));
    if (EEPROM.readInt(0) == -1) {
        Serial.println("first start, flush setting to EEPROM");
        for (auto &item: setMap) { item.second.resetting(); }
        EEPROM.writeInt(0, 1);
        Serial.println("EEPROM flush successfully");
    } else {
        Serial.println("read user setting from EEPROM");
        for (auto &item: setMap) { item.second.readSetting(); }
        Serial.println("read user setting successfully");
    }
}

Variable *Variable::getInstance() {
    if (instance == nullptr) instance = new Variable();
    return instance;
}

int Variable::get(SetName setName) {
    return setMap[setName].getSettingValue();
}

void Variable::set(SetName setName, int value) { setMap[setName].setSettingValue(value); }

void Variable::add(SetName setName) { setMap[setName].add(); }

void Variable::sub(SetName setName) { setMap[setName].sub(); }
