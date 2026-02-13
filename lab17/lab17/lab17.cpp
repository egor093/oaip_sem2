#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct Train {
    string trainNumber, destination, travelDays, arrivalTime, departureTime;
};

void addTrain(Train trains[], int& count) {
    cout << "Введите номер поезда" << endl;
    cin.ignore();
    getline(cin, trains[count].trainNumber);
    cout << "Введите пункт назначения" << endl;
    getline(cin, trains[count].destination);
    cout << "Введите дни следования" << endl;
    getline(cin, trains[count].travelDays);
    cout << "Введите время прибытия" << endl;
    getline(cin, trains[count].arrivalTime);
    cout << "Введите время отправления" << endl;
    getline(cin, trains[count].departureTime);
    count++;
}

void displayTrains(const Train trains[], int count) {
    for (int i = 0; i < count; ++i)
        cout << "Номер поезда: " << trains[i].trainNumber << endl << "Пункт назначения : " << trains[i].destination << endl
        << "Дни следования: " << trains[i].travelDays << endl << "Время прибытия: " << trains[i].arrivalTime << endl
        << "Время отправления: " << trains[i].departureTime << endl << "-------------------" << endl;
}

void searchByDestination(const Train trains[], int count, const string& destination) {
    for (int i = 0; i < count; ++i)
        if (trains[i].destination == destination) {
            cout << "Найден поезд:" << endl << "Номер: " << trains[i].trainNumber << endl << "Дни следования: " << trains[i].travelDays << endl
                << "Время прибытия: " << trains[i].arrivalTime << endl << "Время отправления: " << trains[i].departureTime << endl;
            return;
        }
    cout << "Поезд не найден." << endl;
}

void deleteTrain(Train trains[], int& count, const string& trainNumber) {
    for (int i = 0; i < count; ++i) {
        if (trains[i].trainNumber == trainNumber) {
            trains[i] = trains[--count];
            cout << "Поезд удален." << endl;
            return;
        }
    }
    cout << "Поезд не найден." << endl;
}

void saveToFile(const Train trains[], int count, const string& filename) {
    ofstream file(filename);
    for (int i = 0; i < count; ++i)
        file << "Номер поезда: " << trains[i].trainNumber << "; " << "Пункт назначения: " << trains[i].destination << "; "
        << "Дни следования: " << trains[i].travelDays << "; " << "Время прибытия: " << trains[i].arrivalTime << "; "
        << "Время отправления: " << trains[i].departureTime << endl;
}

void loadFromFile(Train trains[], int& count, const string& filename) {
    ifstream file(filename);
    count = 0;
    while (getline(file, trains[count].trainNumber, ';') &&
        getline(file, trains[count].destination, ';') &&
        getline(file, trains[count].travelDays, ';') &&
        getline(file, trains[count].arrivalTime, ';') &&
        getline(file, trains[count].departureTime)) {
        count++;
    }
}


void deleteList(Train trains[], int& count) {
    count = 0;
    cout << "Список поездов очищен." << endl;
}

void countList(int count) {
    cout << "Количество поездов в списке: " << count << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int MAX_TRAINS = 100;
    Train trains[MAX_TRAINS];
    int count = 0, choice;
    string filename = "trains.txt", input;

    while (true) {
        cout << "1. Добавить поезд" << endl;
        cout << "2. Вывести список" << endl;
        cout << "3. Найти по пункту назначения" << endl;
        cout << "4. Удалить поезд" << endl;
        cout << "5. Сохранить в файл" << endl;
        cout << "6. Загрузить из файла" << endl;
        cout << "7. Удалить весь список" << endl;
        cout << "8. Подсчитать количество поездов" << endl;
        cout << "0. Выход" << endl;
        cin >> choice;
        if (choice == 0) break;
        switch (choice) {
        case 1: addTrain(trains, count); break;
        case 2: displayTrains(trains, count); break;
        case 3: cout << "Введите пункт назначения: "; cin.ignore(); getline(cin, input); searchByDestination(trains, count, input); break;
        case 4: cout << "Введите номер поезда: "; cin.ignore(); getline(cin, input); deleteTrain(trains, count, input); break;
        case 5: saveToFile(trains, count, filename); break;
        case 6: loadFromFile(trains, count, filename); break;
        case 7: deleteList(trains, count); break;
        case 8: countList(count); break;
        default: cout << "Неверный ввод. Попробуйте снова." << endl;
        }
    }

}