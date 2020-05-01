//
// Created by xl on 2020/4/18.
//

#ifndef CARESP32CAM_ULTRASONICRANGING_H
#define CARESP32CAM_ULTRASONICRANGING_H
#include <Arduino.h>
class UltrasonicRanging {
public:
    UltrasonicRanging();
    float getDistance();
private:
    const int trigPin = 2;
    const int echoPin = 4;
    float duration;//持续时间
    float distance;//距离
};


#endif //CARESP32CAM_ULTRASONICRANGING_H
