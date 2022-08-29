/*
Предположим, что мы владеем парковкой и хотим
написать программу, которая поможет нам в бизнесе.
*/
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// давайте опишем сущность "автомобиль"
// предположим, что для нас важны:
// регистрационный номер авто, его цвет и мощность двигателя в л.с.
// номер опишем типом unsigned, поскольку он может хранить более 10 числовых знаков
// и этого будет точно достаточно
// цвет опишем символом и, для нашего удобства, объявим константы
// мощность двигателя опишем типом short, поскольку его будет достаточно
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
// теперь мы сможем хранить список автомобилей, находящийся на стоянке в виде
// массива объектов типа Car, подумайте как именно это сделать, создайте проект
// и самостоятельно напишите соответствующий код с использованием данной структуры

// теперь давайте пойдем немного дальше и подумаем о том, что было бы неплохо
// иметь список своих клиентов с некоторой информацией о них, как минимум
// телефонный номер, чтобы можно было позвонить им, если с их автомобилем
// что-нибудь произошло
// т.е. нам нужна сущность "клиент", у которой будут следующие поля:
// имя, телефонный номер, автомобиль
// условимся, что максимальная длина имени 15 символов
#define MAX_NAME_LENGTH 15
#define NAME_BUF_SIZE MAX_NAME_LENGTH + 1

struct  Client {
    char name[NAME_BUF_SIZE];
    unsigned phone;
    // наша структура Car - тип данных, поэтому мы можем использовать её
    // как тип поля другой структуры:
    struct Car car;
};

// а теперь давайте создадим структуру, которая будет описывать целую парковку
// условимся, что максимальный размер парковки и максимальное число клиентов
// ограничены и задаются статически, а также что у каждого клиента ровно 1 автомобиль
#define MAX_CLIENTS_NUMBER 200
#define MAX_PLACES_NUMBER 100
// будем хранить в структуре список клиентов, список авто на парковке,
// количество свободных мест, и количество клиентов
struct Parking {
    // хранить список машин, стоящих на парковке будем в виде
    // массива указателей на эти машины, далее станет ясно
    // для чего мы это делаем
    struct Car* cars[MAX_PLACES_NUMBER];
    struct Client clients[MAX_CLIENTS_NUMBER];
    unsigned clientsNumber;
    unsigned freePlaces;
};
// все необходимые типы данных имеются, осталось написать необходимые функции
// по работе с ними

// инициализация парковки начальными значениями (будем использовать эту функцию
// при объявлении новой переменной типа struct Parking
// в данном случае необходимо передавать указатель на структуру, поскольку
// мы собираемся внутри функции изменять её поля
// однако, рационально передавать структуры по адресу всегда (подумайте почему)
// так мы и будем далее делать
void initParking(struct Parking* parking);
// прочие инициализации структур:
void initCar(struct Car* car, int regNumber, char color, short power);
void initClient(struct Client* client, char* name, unsigned phone, struct Car* car);

// вспомогательные функции
// поиск машины на парковке
struct Car** findCarOnParking(struct Parking* parking, unsigned regNumber);
// поиск клиента в базе клиентов
struct Client* findClient(struct Parking* parking, unsigned phone);

// добавление клиента в список
void addClient(struct Parking* parking, struct Client* client);
// удаление клиента из списка (по номеру телефона, т.к. они уникальны)
void removeClient(struct Parking* parking, unsigned phone);

// добавление машины на парковку (по владельцу)
void addCar(struct Parking* parking, unsigned regNumber);
// удаление машины с парковки (по номеру)
void removeCar(struct Parking* parking, unsigned regNumber);

// вывод информации о клиентах
void printClients(struct Parking* parking);
void printClientInfo(struct Client* client);

// вывод информации о машинах
void printCars(struct Parking* parking);
void printCarInfo(struct Car* car);

// интерактивное меню нашей программы:
int mainMenu(struct Parking* parking);
void addCarMenu(struct Parking* parking);
void addClientMenu(struct Parking* parking);
void removeCarMenu(struct Parking* parking);
void removeClientMenu(struct Parking* parking);


int main(void) {
    struct Parking myParking;
    initParking(&myParking);
    while (mainMenu(&myParking));

    return 0;
}

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
    getchar(); // перенос строки остался на вводе
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

void initParking(struct Parking* parking) {
    parking->clientsNumber = 0;
    parking->freePlaces = MAX_PLACES_NUMBER;
}

void initCar(struct Car* car, int regNumber, char color, short power) {
    car->regNumber = regNumber;
    car->color = color;
    car->power = power;
}

void initClient(struct Client* client, char* name, unsigned phone, struct Car* car) {
    client->phone = phone;
    initCar(&client->car, car->regNumber, car->color, car->power);
    strcpy_s(client->name, MAX_NAME_LENGTH, name);
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
