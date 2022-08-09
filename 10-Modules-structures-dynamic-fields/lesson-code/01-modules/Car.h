#pragma once

#define BLACK 'b'
#define GREEN 'g'
#define RED 'r'
#define YELLOW 'y'
#define WHITE 'w'
struct Car {
    unsigned regNumber;
    char color;
    short power;
};

void initCar(struct Car* car, int regNumber, char color, short power);
