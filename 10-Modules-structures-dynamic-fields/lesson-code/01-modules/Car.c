#include "Car.h"

void initCar(struct Car* car, int regNumber, char color, short power) {
    car->regNumber = regNumber;
    car->color = color;
    car->power = power;
}
