#include <iostream>
#include <string>

using namespace std;


// Определение структуры Student
struct Student {
    string fio; // ФИО
    char gender; // Пол: 'M' - мужской, 'F' - женский
    int groupNumber; // Номер группы
    int listNumber; // Номер в списке группы
    int examGrades[3]; // Оценки за экзамены
    int diffGrades[5]; // Оценки за дифференцированные зачеты
};

// Функция для создания новой записи о студенте
void addStudent(Student& student) {
    cout << "Введите ФИО студента: ";
    getline(cin, student.fio);
    cout << "Введите пол студента (M/F): ";
    cin >> student.gender;
    cin.ignore(); // Очистка буфера ввода после ввода одного символа
    cout << "Введите номер группы: ";
    cin >> student.groupNumber;
    cout << "Введите номер студента в списке группы: ";
    cin >> student.listNumber;
    cout << "Введите оценки за экзамены (через пробел): ";
    for (int& grade : student.examGrades) {
        cin >> grade;
    }
    cin.ignore(); // Очистка буфера ввода после ввода чисел
    cout << "Введите оценки за дифференцированные зачеты (через пробел): ";
    for (int& grade : student.diffGrades) {
        cin >> grade;
    }
    cin.ignore(); // Очистка буфера ввода после ввода чисел
}

// Функция для изменения данных о студенте
void editStudent(Student& student) {
    int choice;
    cout << "Выберите данные для изменения:\n";
    cout << "1 - ФИО\n";
    cout << "2 - Пол\n";
    cout << "3 - Номер группы\n";
    cout << "4 - Номер в списке группы\n";
    cout << "5 - Оценки за экзамены\n";
    cout << "6 - Оценки за дифференцированные зачеты\n";
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Введите новое ФИО: ";
        cin.ignore(); // Игнорируем символ новой строки оставшийся в потоке
        getline(cin, student.fio);
        break;
    case 2:
        cout << "Введите новый пол (M/F): ";
        cin >> student.gender;
        break;
    case 3:
        cout << "Введите новый номер группы: ";
        cin >> student.groupNumber;
        break;
    case 4:
        cout << "Введите новый номер в списке группы: ";
        cin >> student.listNumber;
        break;
    case 5:
        cout << "Введите новые оценки за экзамены (через пробел): ";
        for (int& grade : student.examGrades) {
            cin >> grade;
        }
        break;
    case 6:
        cout << "Введите новые оценки за дифференцированные зачеты (через пробел): ";
        for (int& grade : student.diffGrades) {
            cin >> grade;
        }
        break;
    default:
        cout << "Неверный выбор.\n";
        break;
    }
}

// Функция для вывода информации о студенте
void printStudentInfo(Student& student) {
    cout << "ФИО: " << student.fio << "\n";
    cout << "Пол: " << student.gender << "\n";
    cout << "Номер группы: " << student.groupNumber << "\n";
    cout << "Номер в списке группы: " << student.listNumber << "\n";
    cout << "Оценки за экзамены: ";
    for (int grade : student.examGrades) {
        cout << grade << " ";
    }
    cout << "\nОценки за дифференцированные зачеты: ";
    for (int grade : student.diffGrades) {
        cout << grade << " ";
    }
    cout << "\n\n";
}

// Функция для вывода информации о всех студентах группы N
void printStudentsByGroup(Student students[], int numberOfStudents, int groupNumber) {
    for (int i = 0; i < numberOfStudents; ++i) {
        if (students[i].groupNumber == groupNumber) {
            printStudentInfo(students[i]);
        }
    }
}

// Функция для расчета среднего балла студента
double calculateAverageGrade(Student& student) {
    int sum = 0;
    for (int grade : student.examGrades) {
        sum += grade;
    }
    for (int grade : student.diffGrades) {
        sum += grade;
    }
    int totalGrades = sizeof(student.examGrades) / sizeof(student.examGrades[0]) + sizeof(student.diffGrades) / sizeof(student.diffGrades[0]);
    return static_cast<double>(sum) / totalGrades;
}

// Функция для сортировки студентов по среднему баллу (пузырьковая сортировка)
void sortStudentsByAverageGrade(Student students[], int numberOfStudents) {
    for (int i = 0; i < numberOfStudents - 1; ++i) {
        for (int j = 0; j < numberOfStudents - i - 1; ++j) {
            if (calculateAverageGrade(students[j]) < calculateAverageGrade(students[j + 1])) {
                // Обмен местами
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// Функция для вывода топа студентов по среднему баллу
void printTopStudents(Student students[], int numberOfStudents) {
    // Сортировка студентов по среднему баллу
    sortStudentsByAverageGrade(students, numberOfStudents);

    // Вывод топа студентов
    cout << "Топ студентов по среднему баллу:\n";
    for (int i = 0; i < numberOfStudents; ++i) {
        cout << students[i].fio << " - Средний балл: " << calculateAverageGrade(students[i]) << "\n";
    }
}

// Функция для подсчета количества студентов по полу
void countGender(Student students[], int numberOfStudents, int& maleCount, int& femaleCount) {
    maleCount = 0;
    femaleCount = 0;
    for (int i = 0; i < numberOfStudents; ++i) {
        if (students[i].gender == 'M') {
            ++maleCount;
        }
        else if (students[i].gender == 'F') {
            ++femaleCount;
        }
    }
}

// Функция для вывода данных о студентах по категориям
void printExcellentStudents(Student students[], int numberOfStudents) {
    for (int i = 0; i < numberOfStudents; ++i) {
        bool hasThree = false;
        bool isGoodAndExcellent = true;
        bool isOutstanding = true;
        for (int grade : students[i].examGrades) {
            if (grade == 3) {
                hasThree = true;
            }
            if (grade < 4) {
                isGoodAndExcellent = false;
                isOutstanding = false;
            }
            if (grade < 5) {
                isOutstanding = false;
            }
        }
        for (int grade : students[i].diffGrades) {
            if (grade == 3) {
                hasThree = true;
            }
            if (grade < 4) {
                isGoodAndExcellent = false;
                isOutstanding = false;
            }
            if (grade < 5) {
                isOutstanding = false;
            }
        }
        if (hasThree) {
            cout << students[i].fio << " - Имеет тройку\n";
        }
        if (isGoodAndExcellent && !hasThree) {
            cout << students[i].fio << " - Учится только на 4 и 5\n";
        }
        if (isOutstanding) {
            cout << students[i].fio << " - Учится только на 5\n";
        }
    }
}

// Функция для вывода данных о всех студентах с номером в списке k
void printStudentsByListNumber(Student students[], int numberOfStudents, int k) {
    bool found = false;
    for (int i = 0; i < numberOfStudents; ++i) {
        if (students[i].listNumber == k) {
            if (!found) {
                cout << "Студенты с номером в списке " << k << ":\n";
                found = true;
            }
            cout << "ФИО: " << students[i].fio << "\n";
            cout << "Пол: " << students[i].gender << "\n";
            cout << "Номер группы: " << students[i].groupNumber << "\n";
            cout << "Оценки за экзамены: ";
            for (int grade : students[i].examGrades) {
                cout << grade << " ";
            }
            cout << "\nОценки за дифференцированные зачеты: ";
            for (int grade : students[i].diffGrades) {
                cout << grade << " ";
            }
            cout << "\n\n";
        }
    }
    if (!found) {
        cout << "Студенты с номером в списке " << k << " не найдены.\n";
    }
}

int main() {
    setlocale(LC_ALL, "RUS");

    const int MAX_STUDENTS = 100; // Максимальное количество студентов
    Student students[MAX_STUDENTS]; // Статический массив структур
    int numberOfStudents; // Переменная для хранения фактического количества студентов

    /*
    const int numberOfStudents = 12; // Количество студентов
    
    // Создание массива структур Student
    Student students[numberOfStudents] = {
        {"Иванов Иван Иванович", 'M', 101, 1, {5, 4, 5}, {3, 4, 5, 4, 5}},
        {"Петрова Мария Ивановна", 'F', 101, 2, {4, 3, 4}, {5, 5, 4, 4, 3}},
        {"Смирнов Алексей Петрович", 'M', 101, 3, {3, 4, 5}, {4, 5, 4, 3, 5}},
        {"Кузнецова Анна Сергеевна", 'F', 102, 1, {5, 5, 5}, {5, 5, 5, 5, 5}},
        {"Соколов Илья Васильевич", 'M', 102, 2, {4, 4, 4}, {4, 4, 4, 4, 4}},
        {"Попова Ксения Андреевна", 'F', 102, 3, {3, 3, 3}, {3, 3, 3, 3, 3}},
        {"Лебедева Дарья Михайловна", 'F', 102, 4, {5, 4, 4}, {5, 4, 4, 5, 4}},
        {"Новиков Дмитрий Алексеевич", 'M', 103, 1, {4, 5, 4}, {4, 5, 4, 4, 5}},
        {"Морозова Елена Сергеевна", 'F', 103, 2, {5, 5, 5}, {5, 5, 5, 5, 5}},
        {"Петров Владимир Александрович", 'M', 103, 3, {3, 4, 3}, {3, 4, 3, 3, 4}},
        {"Волкова Алина Михайловна", 'F', 103, 4, {4, 4, 4}, {4, 4, 4, 4, 4}},
        {"Соловьёва Ольга Игоревна", 'F', 103, 5, {5, 4, 5}, {5, 4, 5, 5, 4}}
    };
    */

    while (true) {
        int choice;
        cout << "Выберите функцию:\n";
        cout << "1. Создание новой записи о студенте.\n";
        cout << "2. Внесение изменений в уже имеющуюся запись.\n";
        cout << "3. Вывод всех данных о студентах.\n";
        cout << "4. Вывод информации обо всех студентах группы N. N – инициализируется пользователем.\n";
        cout << "5. Вывод топа самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию.\n";
        cout << "6. Вывод количества студентов мужского и женского пола.\n";
        cout << "7. Вывод данных о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»;\n";
        cout << "8. Вывод данных о студентах, имеющих номер в списке – k.\n";
        cout << "9. Выход из программы.\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите количество студентов для добавления (не более " << MAX_STUDENTS << "): ";
            cin >> numberOfStudents;
            cin.ignore(); // Очистка буфера ввода после ввода числа

            if (numberOfStudents > MAX_STUDENTS) {
                cout << "Количество студентов не может превышать " << MAX_STUDENTS << "." << endl;
            }
            else {
                for (int i = 0; i < numberOfStudents; ++i) {
                    cout << "Студент " << (i + 1) << ":" << endl;
                    addStudent(students[i]);
                }
            }
            break;
        case 2:
            int studentIndex;
            cout << "Введите номер студента для изменения данных (0-" << numberOfStudents - 1 << "): ";
            cin >> studentIndex;
            if (studentIndex >= 0 && studentIndex < numberOfStudents) {
                editStudent(students[studentIndex]);
            }
            else {
                cout << "Неверный номер студента.\n";
            }
            break;
        case 3:
            for (int i = 0; i < numberOfStudents; ++i) {
                printStudentInfo(students[i]);
            }
            break;
        case 4:
            int groupNumber;
            cout << "Введите номер группы для вывода информации о студентах: ";
            cin >> groupNumber;
            printStudentsByGroup(students, numberOfStudents, groupNumber);
            break;
        case 5:
            printTopStudents(students, numberOfStudents);
            break;
        case 6:
            int maleCount, femaleCount;
            countGender(students, numberOfStudents, maleCount, femaleCount);
            cout << "Количество студентов мужского пола: " << maleCount << "\n";
            cout << "Количество студентов женского пола: " << femaleCount << "\n";
            break;
        case 7:
            printExcellentStudents(students, numberOfStudents);
            break;
        case 8:
            int k; // Укажите нужный номер в списке
            cout << "Введите номер в списке: ";
            cin >> k;
            printStudentsByListNumber(students, numberOfStudents, k);
            break;
        case 9:
            break;
        default:
            cout << "Неверный выбор.\n";
            break;
        }
    }

    return 0;
}
