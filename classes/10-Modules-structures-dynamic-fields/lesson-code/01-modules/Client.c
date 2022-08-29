#include "Client.h"

#include <string.h>

void initClient(struct Client* client, char* name, unsigned phone, struct Car* car) {
    client->phone = phone;
    initCar(&client->car, car->regNumber, car->color, car->power);
    strcpy_s(client->name, MAX_NAME_LENGTH, name);
}
