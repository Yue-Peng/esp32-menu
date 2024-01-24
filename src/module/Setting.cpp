//
// Created by user on 2024/1/23.
//

#include "Setting.h"
#include <unordered_map>
#include "SetName.h"
#include <EEPROM.h>


struct SettingItem {
private:
    int addr;
    int settingValue;
    int step;
    int min;
    int max;
    int defaultValue;
    bool needRestart;

public:
    SettingItem() {};

    SettingItem(int settingValue, int step, int min, int max, int defaultValue, bool needRestart) {
        this->settingValue = settingValue;
        this->step = step;
        this->min = min;
        this->max = max;
        this->defaultValue = defaultValue;
        this->needRestart = needRestart;
    }

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
            EEPROM.writeInt(addr, settingValue);
            flush();
        }
    }

    int getDefaultValue() { return defaultValue; }

    int getSettingValue() { return settingValue; }

    void resetting() {
        Serial.printf("flush value %d to address %d\r\n", defaultValue, addr);
        EEPROM.writeInt(addr, defaultValue);
    }

    void flush() { EEPROM.writeInt(addr, settingValue); }

    void add() { setSettingValue(settingValue + step); }

    void sub() { setSettingValue(settingValue - step); }
};

Setting *Setting::instance;

std::unordered_map<SetName, SettingItem> setMap;

Setting::~Setting() = default;

Setting::Setting() {
    // 配置项
    setMap = {
            {SET_BAUD_RATE, SettingItem(10, 1, 1, 1000, 1, false)},
            {SET_TEMP,      SettingItem(1234, 100, 1, 1000, 1, false)},
    };

    // 初始化内存
    Serial.println("init EEPROM");
    EEPROM.begin((SetName::SET_ITEM_COUNT + 1) * sizeof(int));
    Serial.println("EEPROM apply successful");

    // 给配置项分配内存地址
    Serial.println("init setting EEPROM address");
    int address = sizeof(int);
    for (auto &item: setMap) {
        item.second.setAddress(address);
        address += sizeof(int);
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

Setting *Setting::getInstance() {
    if (instance == nullptr) instance = new Setting();
    return instance;
}

int Setting::get(SetName name) {
    return setMap[name].getSettingValue();
}

void Setting::add(SetName name) { setMap[name].add(); }

void Setting::sub(SetName name) { setMap[name].sub(); }