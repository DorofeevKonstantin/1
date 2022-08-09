#pragma once

#include "Car.h"
#include "Client.h"

#define MAX_CLIENTS_NUMBER 200
#define MAX_PLACES_NUMBER 100

struct Parking {
    struct Car* cars[MAX_PLACES_NUMBER];
    struct Client clients[MAX_CLIENTS_NUMBER];
    unsigned clientsNumber;
    unsigned freePlaces;
};

void initParking(struct Parking* parking);

struct Car** findCarOnParking(struct Parking* parking, unsigned regNumber);
struct Client* findClient(struct Parking* parking, unsigned phone);

void addClient(struct Parking* parking, struct Client* client);
void removeClient(struct Parking* parking, unsigned phone);

void addCar(struct Parking* parking, unsigned regNumber);
void removeCar(struct Parking* parking, unsigned regNumber);

void printClients(struct Parking* parking);
void printClientInfo(struct Client* client);

void printCars(struct Parking* parking);
void printCarInfo(struct Car* car);

