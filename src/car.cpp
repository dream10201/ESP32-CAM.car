//
// Created by xl on 2020/4/18.
//

#include "car.h"

Car::Car() {
    pinMode(this->left_1,OUTPUT);
    pinMode(this->left_2,OUTPUT);
    pinMode(this->right_1,OUTPUT);
    pinMode(this->right_2,OUTPUT);
}
void Car::go() {
    this->stop();
    digitalWrite(this->left_1, LOW);
    digitalWrite(this->left_2, HIGH);
    digitalWrite(this->right_1, LOW);
    digitalWrite(this->right_2, HIGH);
    this->run_time = millis();
}
void Car::back() {
    this->stop();
    digitalWrite(this->left_1, HIGH);
    digitalWrite(this->left_2, LOW);
    digitalWrite(this->right_1, HIGH);
    digitalWrite(this->right_2, LOW);
    this->run_time = millis();
}
void Car::left() {
    this->stop();
    digitalWrite(this->left_1, HIGH);
    digitalWrite(this->left_2, LOW);
    digitalWrite(this->right_1, LOW);
    digitalWrite(this->right_2, HIGH);
    this->run_time = millis();
}
void Car::right() {
    this->stop();
    digitalWrite(this->left_1, LOW);
    digitalWrite(this->left_2, HIGH);
    digitalWrite(this->right_1, HIGH);
    digitalWrite(this->right_2, LOW);
    this->run_time = millis();
}
void Car::stop() {
    digitalWrite(this->left_1, LOW);
    digitalWrite(this->left_2, LOW);
    digitalWrite(this->right_1, LOW);
    digitalWrite(this->right_2, LOW);
    this->run_time = 0;
}
float Car::getMinBack() {return this->minBack;}
void Car::setMinBack(float v) {this->minBack=v;}
