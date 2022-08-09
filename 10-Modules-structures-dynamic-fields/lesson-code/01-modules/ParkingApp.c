#include "ParkingApp.h"

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

int mainMenu(struct Parking* parking) {
    system("cls");
    printf_s("Choose action:\n"
        "1) Show cars on parking\n"
        "2) Add car on parking\n"
        "3) Remove car from parking\n"
        "4) Add new client\n"
        "5) Show clients\n"
        "6) Remove client\n"
        "0) Exit\n");
    while (!_kbhit());
    char action = _getch();
    system("cls");
    switch (action) {
    case '1':
        printCars(parking);
        break;
    case '2':
        addCarMenu(parking);
        break;
    case '3':
        removeCarMenu(parking);
        break;
    case '4':
        addClientMenu(parking);
        break;
    case '5':
        printClients(parking);
        break;
    case '6':
        removeClientMenu(parking);
        break;
    case '0':
        return 0;
    default:
        break;
    }
    return 1;
}

void addCarMenu(struct Parking* parking) {
    printf_s("Enter the registration number of car: ");
    unsigned regNumber = 0;
    scanf_s("%u", &regNumber);
    addCar(parking, regNumber);
}

void addClientMenu(struct Parking* parking) {
    struct Client newClient;
    struct Car newClientCar;
    char clientName[NAME_BUF_SIZE];
    unsigned clientPhone = 0, carRegNumber = 0;
    short carPower = 0;
    char carColor = 'w';
    printf_s("Enter the client name: ");
    scanf_s("%s", clientName, NAME_BUF_SIZE);
    printf_s("Enter the phone number: ");
    scanf_s("%u", &clientPhone);
    printf_s("Enter the registration number of car: ");
    scanf_s("%u", &carRegNumber);
    printf_s("Enter the power of car: ");
    scanf_s("%hu", &carPower);
    printf_s("Enter the color of car (%c, %c, %c, %c, %c): ", BLACK, GREEN, RED, YELLOW, WHITE);
    getchar();
    scanf_s("%c", &carColor, 1);
    initCar(&newClientCar, carRegNumber, carColor, carPower);
    initClient(&newClient, clientName, clientPhone, &newClientCar);
    addClient(parking, &newClient);
}

void removeCarMenu(struct Parking* parking) {
    printf_s("Enter the registration number of car: ");
    unsigned regNumber = 0;
    scanf_s("%u", &regNumber);
    removeCar(parking, regNumber);
}

void removeClientMenu(struct Parking* parking) {
    printf_s("Enter the phone number of client: ");
    unsigned phone;
    scanf_s("%u", &phone);
    removeClient(parking, phone);
}
