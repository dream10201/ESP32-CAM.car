//
// Created by xl on 2020/4/18.
//

#include "UltrasonicRanging.h"

UltrasonicRanging::UltrasonicRanging() {
    pinMode(this->trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(this->echoPin, INPUT); // Sets the echoPin as an Input
}

float UltrasonicRanging::getDistance() {
    // Clears the trigPin
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(this->trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    this->duration = pulseIn(this->echoPin, HIGH);
    // Calculating the distance
    this->distance = duration * 0.034 / 2.0;
    return this->distance;
    // Prints the distance on the Serial Monitor
}