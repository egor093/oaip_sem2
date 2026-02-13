#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

const int SIZE = 30;
int current_size = 0;

enum Faculties {
    FIT = 1,
    TOV,
    HTIT,
    PIM
};

struct EnterTime {
    unsigned day : 5;
    unsigned month : 4;
    unsigned year : 11;
};

struct Students {
    string surname;
    string name;
    string middlename;
    EnterTime enter_time;
    string specialty;
    int group;
    Faculties faculty;
    double average;
} students[SIZE];

Students empty_student = { "", "", "", {0, 0, 0}, "", 0, FIT, 0.0 };

bool contains_invalid_chars(const string& str) {
    return str.find_first_of("0123456789 ") != string::npos;
}

bool is_leap_year(int year);

bool is_valid_date(int day, int month, int year) {
    if (month < 1 || month > 12) return false;
    if (month == 2) return (day >= 1 && day <= (is_leap_year(year) ? 29 : 28));
    if (month == 4 || month == 6 || month == 9 || month == 11) return (day >= 1 && day <= 30);
    return (day >= 1 && day <= 31);
}

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void displayOneStructure(const Students& student) {
    cout << "\nФамилия: " << student.surname
        << "\nИмя: " << student.name
        << "\nОтчество: " << student.middlename
        << "\nДата поступления: " << student.enter_time.day << "." << student.enter_time.month << "." << student.enter_time.year
        << "\nСпециальность: " << student.specialty
        << "\nГруппа: " << student.group
        << "\nФакультет: " << (student.faculty == FIT ? "FIT" : student.faculty == TOV ? "TOV" : student.faculty == HTIT ? "HTIT" : "PIM")
        << "\nСредний балл: " << fixed << setprecision(2) << student.average << endl;
}

void addNew() {
    Students& new_student = students[current_size];

    auto input_field = [](const string& prompt) {
        string field;
        do {
            cout << prompt;
            getline(cin, field);
        } while (contains_invalid_chars(field));
        return field;
        };

    // Добавляем cin.ignore() перед вводом строки, чтобы очистить буфер после ввода чисел
    cin.ignore(); // Очистка буфера после предыдущих вводов (например, после cin >> choice)

    new_student.surname = input_field("Фамилия: ");
    new_student.name = input_field("Имя: ");
    new_student.middlename = input_field("Отчество: ");

    while (true) {
        int day, month, year;
        cout << "Введите дату поступления (день месяц год): ";
        cin >> day >> month >> year;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный ввод даты. Попробуйте снова." << endl;
            continue;
        }

        if (is_valid_date(day, month, year)) {
            new_student.enter_time.day = day;
            new_student.enter_time.month = month;
            new_student.enter_time.year = year;
            break;
        }
        else {
            cout << "Неверная дата. Попробуйте еще раз." << endl;
        }
    }

    cin.ignore(); // Очищаем буфер после ввода даты

    new_student.specialty = input_field("Специальность: ");

    while (true) {
        cout << "Группа: ";
        if (cin >> new_student.group) break;
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный ввод. Попробуйте еще раз." << endl;
        }
    }

    while (true) {
        cout << "Факультет (1 - FIT, 2 - TOV, 3 - HTIT, 4 - PIM): ";
        int fac;
        if (cin >> fac && fac >= 1 && fac <= 4) {
            new_student.faculty = static_cast<Faculties>(fac);
            break;
        }
        else {
            cout << "Некорректный ввод. Попробуйте снова." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true) {
        cout << "Средний балл: ";
        if (cin >> new_student.average && new_student.average >= 0 && new_student.average <= 10) break;
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный средний балл. Попробуйте еще раз." << endl;
        }
    }
    current_size++;
}


void deleteRecord() {
    int record;
    cout << "Введите номер записи для удаления (0 для удаления всех): ";
    cin >> record;

    if (record == 0) {
        fill(begin(students), end(students), empty_student);
        current_size = 0;
    }
    else if (record > 0 && record <= current_size) {
        for (int i = record - 1; i < current_size - 1; i++) {
            students[i] = students[i + 1];
        }
        current_size--;
    }
    else {
        cout << "Неверный номер записи." << endl;
    }
}

void display() {
    cout << "Все записи\n";
    for (int i = 0; i < current_size; i++) {
        displayOneStructure(students[i]);
    }
}


void search() {
    double avg;
    cout << "Введите средний балл для поиска: ";
    cin >> avg;

    bool found = false;
    for (int i = 0; i < current_size; i++) {
        if (abs(students[i].average - avg) < 0.0001) {
            displayOneStructure(students[i]);
            found = true;
        }
    }
    if (!found) cout << "Записи не найдены." << endl;
}

int main() {
    setlocale(LC_ALL, "rus");

    while (true) {
        int choice;
        cout << "\n1 - Ввести новую запись\n2 - Показать записи\n3 - Удалить запись\n4 - Поиск\n5 - Выход\n";
        cin >> choice;
        switch (choice) {
        case 1: addNew(); break;
        case 2: display(); break;
        case 3: deleteRecord(); break;
        case 4: search(); break;
        case 5: return 0;
        default: cout << "Некорректный ввод." << endl;
        }
    }
}
