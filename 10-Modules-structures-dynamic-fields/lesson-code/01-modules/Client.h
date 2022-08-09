#pragma once

#include "Car.h"

#define MAX_NAME_LENGTH 15
#define NAME_BUF_SIZE MAX_NAME_LENGTH + 1

struct  Client {
    char name[NAME_BUF_SIZE];
    unsigned phone;
    struct Car car;
};

void initClient(struct Client* client, char* name, unsigned phone, struct Car* car);