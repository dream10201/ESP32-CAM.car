//
// Created by xl on 2020/4/18.
//

#ifndef CARESP32CAM_CAR_H
#define CARESP32CAM_CAR_H

#include <Arduino.h>

class Car {
public:
    Car();
    long run_time = 0;
    uint timeout = 250;//run timeout todo 需要根据实际情况调整

    void left();

    void right();

    void go();

    void back();

    void stop();

    float getMinBack();


    void setMinBack(float v);

private:
    const int left_1 = 14;
    const int left_2 = 15;
    const int right_1 = 13;
    const int right_2 = 12;
    float minBack = 20.0;
};


#endif //CARESP32CAM_CAR_H
