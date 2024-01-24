#include "DisplayProcess.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "configuration.h"
#include "Variable.h"
#include "SetName.h"

Variable *var;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DisplayProcess::DisplayProcess() { var = Variable::getInstance(); }

DisplayProcess::~DisplayProcess() = default;

DisplayProcess *DisplayProcess::instance;

DisplayProcess *DisplayProcess::getInstance() {
    if (instance == nullptr) instance = new DisplayProcess();
    return instance;
}

struct Node {
    int value;
    Node *next;

    Node(int value, Node *next) {
        this->value = value;
        this->next = next;
    }

    Node(int value) {
        this->value = value;
        this->next = nullptr;
    }
};

Node *tempNode;

void DisplayProcess::setup() {
    Serial.println("DisplayProcess::setup");
    var->getInstance();
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR);
    display.setTextColor(SSD1306_WHITE);
    var->set(VAR_SCREEN_TYPE, 0);

    tempNode = new Node(1,
                        new Node(1,
                                 new Node(1,
                                          new Node(1,
                                                   new Node(1,
                                                            new Node(1,
                                                                     new Node(1,
                                                                              new Node(1,
                                                                                       new Node(1,
                                                                                                new Node(
                                                                                                        1,
                                                                                                        new Node(
                                                                                                                1,
                                                                                                                new Node(
                                                                                                                        1,
                                                                                                                        new Node(
                                                                                                                                1,
                                                                                                                                new Node(
                                                                                                                                        1,
                                                                                                                                        new Node(
                                                                                                                                                1,
                                                                                                                                                new Node(
                                                                                                                                                        1,
                                                                                                                                                        new Node(
                                                                                                                                                                1,
                                                                                                                                                                new Node(
                                                                                                                                                                        1,
                                                                                                                                                                        new Node(
                                                                                                                                                                                1,
                                                                                                                                                                                new Node(
                                                                                                                                                                                        1))))))))))))))))))));


    display.clearDisplay();
    Node *head = tempNode;
    while (head != nullptr) {
        head->value = random() % 400 + 50;
        head = head->next;
    }

    head = tempNode;
    while (head != nullptr) {
        display.print(head->value);
        display.print(" ");
        head = head->next;
    }
}

void DisplayProcess::begin() {

    display.clearDisplay();

    switch (var->get(VAR_SCREEN_TYPE)) {
        case 0: { // 主屏幕
            mainScreen();
            break;
        }
        case 1: { // 设置菜单
            settingScreen();
            break;
        }
        case 2: { // 提示屏幕
            break;
        }
    }

    display.display();


}

#define LEFT_BUNDLE 20
#define TOP_BUNDLE 32
#define WIDTH 80
#define HEIGHT 30

short targetTemp = 400;
short maxTemp = 450;
short minTemp = 50;

short yT(short temp) {
    return TOP_BUNDLE + HEIGHT - temp / ((maxTemp - minTemp) / WIDTH); // 400 / 30 = 13   200 / 13 = 15
}

//i=0 temp=383 x=0 y=36 x1=8 y1=74;
//i=1 temp=193 x=8 y=74 x1=16 y1=50;
//i=2 temp=312 x=16 y=50 x1=24 y1=37;
//i=3 temp=379 x=24 y=37 x1=32 y1=82;
//i=4 temp=150 x=32 y=82 x1=40 y1=41;
//i=5 temp=358 x=40 y=41 x1=48 y1=72;
//i=6 temp=202 x=48 y=72 x1=56 y1=91;
//i=7 temp=106 x=56 y=91 x1=64 y1=91;
//i=8 temp=106 x=64 y=91 x1=72 y1=79;

void DisplayProcess::mainScreen() {
    // 目标温度线
    for (int16_t i = 1; i < WIDTH; i += 2)
        display.drawPixel(LEFT_BUNDLE + i,
                          yT(targetTemp),
                          SSD1306_WHITE);
    // 图形框
    display.drawRect(LEFT_BUNDLE, TOP_BUNDLE, WIDTH, HEIGHT, SSD1306_WHITE);
    // temp坐标
    display.setCursor(1, 32);
    display.println(maxTemp);
    display.setCursor(1, 55);
    display.println(minTemp);
    // power坐标
    display.setCursor(102, 32);
    display.println("100%");
    display.setCursor(102, 55);
    display.println("0%");
    // 绘制折线图
    Node *head = tempNode;
    int p = var->get(SET_POINT_TEMP_COUNT);
    Serial.printf("begin display %d\r\n",p);
    for (int i = 0; i < p && head != nullptr && head->next != nullptr; i++) {
        int x = LEFT_BUNDLE + i * WIDTH / p;
        int x1 = LEFT_BUNDLE + (i + 1) * WIDTH / p;
        int y = yT(head->value);
        int y1 = yT(head->next->value);

        Serial.printf("WIDTH=%d SET_POINT_TEMP_COUNT=%d;\r\n", WIDTH, p);
        Serial.printf("i=%d temp=%d x=%d y=%d x1=%d y1=%d;\r\n", i, head->value, x, y, x1, y1);

        display.drawLine(x, y, x1, y1, SSD1306_WHITE);
        head = head->next;
    }
}

void DisplayProcess::settingScreen() {

}


