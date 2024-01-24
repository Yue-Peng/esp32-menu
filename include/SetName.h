//
// Created by user on 2024/1/23.
//

#ifndef ESP32_MENU_SETNAME_CPP
#define ESP32_MENU_SETNAME_CPP


enum SetName {
    SET_BAUD_RATE, // 波特率
    SET_TEMP_BASE, // 加热温度
    SET_TEMP_SLEEP, // 睡眠温度
    SET_POINT_TEMP_COUNT, // 温度曲线点数
    SET_POINT_POWER_COUNT, // 功率曲线点数
    SET_DISPLAY_REFRESH_RATE, // 屏幕刷新率，线程循环刷新率，这里是一个预估值，实际刷新率会受到线程中的延时影响
    SET_PROCESS_REFRESH_RATE, // 处理循环延时时间，实际延时会受到线程中的延时影响

    VAR_SCREEN_TYPE, // 判断屏幕类型，0：主屏幕  1：设置菜单  2：提示屏幕
};

#endif //ESP32_MENU_SETNAME_CPP






