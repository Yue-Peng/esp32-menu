#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "configuration.h"
#include "DisplayProcess.h"
#include "BackendProcess.h"
#include "Setting.h"

TaskHandle_t displayTask;
TaskHandle_t processTask;

bool taskDelay(int refreshRate);

[[noreturn]] void displayCode(void *pvParameters);

[[noreturn]] void processCode(void *pvParameters);

void setup() {
    Serial.begin(BAUD_RATE);
    Serial.println("System starting");

    xTaskCreatePinnedToCore(
            displayCode,             // pxTaskCode：指向任务函数的指针，任务函数是你自定义的函数，用于执行任务的功能。
            "displayLoop",           // pcName：任务的名称，为一个字符串。
            DISPLAY_TASK_STACK_SIZE, // usStackDepth：任务堆栈的大小，以字节为单位。
            nullptr,                 // pvParameters：传递给任务函数的参数，可以是任何类型的指针。
            10,                       // uxPriority：任务的优先级，数值越高优先级越高。
            &displayTask,            // pxCreatedTask：可选参数，指向用于保存新任务句柄的指针。如果不需要保存任务句柄，则可以传入NULL。
            0);                      // xCoreID：指定任务要运行的核心编号，可以是0或1。
    delay(100);

    xTaskCreatePinnedToCore(
            processCode,             /* Task function. */
            "processLoop",           /* name of task. */
            PROCESS_TASK_STACK_SIZE, /* Stack size of task */
            nullptr,                 /* parameter of the task */
            1,                       /* priority of the task */
            &processTask,            /* Task handle to keep track of created task */
            1);                      /* pin task to core 1 */
}

void loop() { /* 不需要这个循环 */ }

bool taskDelay(int refreshRate) {
    delay(1000 / refreshRate);
    return true;
}

void displayCode(void *pvParameters) {
    Serial.printf("displayLoop running on core: %d\r\n", xPortGetCoreID());
    DisplayProcess::getInstance()->setup();
    while (true) {
        DisplayProcess::getInstance()->begin();
        taskDelay(DISPLAY_REFRESH_RATE);
    }
}

void processCode(void *pvParameters) {
    Serial.printf("processLoop running on core: %d\r\n", xPortGetCoreID());
    BackendProcess::getInstance()->setup();
    while (true) {
        BackendProcess::getInstance()->begin();
        taskDelay(PROCESS_REFRESH_RATE);
    }
}
