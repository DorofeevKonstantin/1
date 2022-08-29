#include <stdio.h>
#include <stdlib.h>

#include "Parking.h"

void initParking(struct Parking* parking) {
    parking->clientsNumber = 0;
    parking->freePlaces = MAX_PLACES_NUMBER;
}

void addClient(struct Parking* parking, struct Client* client) {
    initClient(&parking->clients[parking->clientsNumber],
        client->name, client->phone, &client->car);
    ++parking->clientsNumber;
}

struct Client* findClient(struct Parking* parking, unsigned phone) {
    struct Client* client = parking->clients;
    for (unsigned i = 0; i < parking->clientsNumber; ++i) {
        if (client[i].phone == phone) return client;
        ++client;
    }
    return 0;
}

void removeClient(struct Parking* parking, unsigned phone) {
    struct Client* clientPtr = findClient(parking, phone);
    if (clientPtr == NULL) return;
    --parking->clientsNumber;
    unsigned shiftsCount = (unsigned)(parking->clientsNumber - (clientPtr - parking->clients));
    // кошмар по производительности, так делать не нужно никогда:
    for (unsigned i = 0; i < shiftsCount; ++i) {
        initClient(clientPtr, (clientPtr + 1)->name, (clientPtr + 1)->phone, &(clientPtr + 1)->car);
        ++clientPtr;
    }
}

void addCar(struct Parking* parking, unsigned regNumber) {
    if (parking->freePlaces == 0 || findCarOnParking(parking, regNumber)) return;
    for (unsigned i = 0; i < parking->clientsNumber; ++i) {
        if (parking->clients[i].car.regNumber == regNumber) {
            parking->cars[MAX_PLACES_NUMBER - parking->freePlaces] = &parking->clients[i].car;
            --parking->freePlaces;
            break;
        }
    }
}

void removeCar(struct Parking* parking, unsigned regNumber) {
    struct Car** car = findCarOnParking(parking, regNumber);
    if (car == NULL) return;
    ++parking->freePlaces;
    // сдвинем часть массива, которая правее удаляемой машины, на одну ячейку влево
    unsigned shiftsCount = (unsigned)(MAX_PLACES_NUMBER - parking->freePlaces - (car - parking->cars));
    for (unsigned i = 0; i < shiftsCount; ++i) {
        *car = car[1];
        ++car;
    }
}

struct Car** findCarOnParking(struct Parking* parking, unsigned regNumber) {
    struct Car** carPtr = parking->cars;
    unsigned carsNumber = MAX_PLACES_NUMBER - parking->freePlaces;
    for (unsigned i = 0; i < carsNumber; ++i) {
        if ((*carPtr)->regNumber == regNumber) return carPtr;
        ++carPtr;
    }
    return NULL;
}

void printClients(struct Parking* parking) {
    printf_s("%15s\t%11s\t%11s\n", "Name", "Phone", "Car number");
    for (unsigned i = 0; i < parking->clientsNumber; ++i) printClientInfo(parking->clients + i);
    system("pause");
}

void printClientInfo(struct Client* client) {
    printf_s("%15s\t%11u\t%11u\n", client->name, client->phone, client->car.regNumber);
}

void printCars(struct Parking* parking) {
    printf_s("%11s\t%5s\t%5s\n", "Reg. number", "Color", "Power");
    unsigned carsNumber = MAX_PLACES_NUMBER - parking->freePlaces;
    for (unsigned i = 0; i < carsNumber; ++i) printCarInfo(*(parking->cars + i));
    system("pause");
}

void printCarInfo(struct Car* car) {
    printf_s("%11u\t%5c\t%5hu\n", car->regNumber, car->color, car->power);
}
