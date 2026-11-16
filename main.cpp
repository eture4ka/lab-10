#include <iostream>
#include <stdexcept>
#include <string>
#include "DoublyLinkedList.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Зчитує ціле число в межах [minV, maxV]; повторює запит, поки введення некоректне
int readInt(const string& prompt, int minV, int maxV) {
    while (true) {
        cout << prompt;
        string s;
        if (!getline(cin, s)) throw runtime_error("Введення перервано (кінець потоку).");
        try {
            size_t pos = 0;
            int v = stoi(s, &pos);
            if (pos == s.size() && v >= minV && v <= maxV) return v;
        } catch (const exception&) {
        }
        cout << "  ! Введіть ціле число від " << minV << " до " << maxV << ".\n";
    }
}

string readText(const string& prompt) {
    cout << prompt;
    string s;
    if (!getline(cin, s)) throw runtime_error("Введення перервано (кінець потоку).");
    return s;
}

Transistor inputTransistor() {
    cout << "  Введіть дані транзистора:\n";
    Transistor t;
    t.input();
    return t;
}

void fillTestData(DoublyLinkedList& list) {
    list.pushBack(Transistor("KT315B", 200, 0.1));
    list.pushBack(Transistor("2N3055", 20, 15));
    list.pushBack(Transistor("IRF540N", 1500, 33));
    list.pushBack(Transistor("BC547", 110, 0.1));
    cout << "  Додано 4 тестові транзистори в кінець списку.\n";
}

void printMenu() {
    cout << "\n============ МЕНЮ ============\n"
         << "  1 - Додати на початок\n"
         << "  2 - Додати в кінець\n"
         << "  3 - Додати після вказаного елемента\n"
         << "  4 - Видалити з початку\n"
         << "  5 - Видалити з кінця\n"
         << "  6 - Видалити за значенням (типом)\n"
         << "  7 - Вивести від head до tail\n"
         << "  8 - Вивести від tail до head\n"
         << "  9 - Перевірити, чи список порожній\n"
         << " 10 - Додати тестові дані\n"
         << " 11 - Очистити список\n"
         << "  0 - Вихід\n";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    cout << "===== Лабораторна робота 14-15. Варіант 18 =====\n"
         << "Двозв'язний список транзисторів (тип, коеф. підсилення, макс. струм)\n";

    // Перевірка валідності: конструктор кидає виняток на некоректних даних
    try {
        Transistor bad("BAD", 100, -2);
    } catch (const invalid_argument& e) {
        cout << "\nПеревірка: створення транзистора зі струмом -2 А\n  ! " << e.what() << '\n';
    }

    DoublyLinkedList list;

    try {
        while (true) {
            printMenu();
            int choice = readInt("Ваш вибір: ", 0, 11);
            if (choice == 0) break;
            cout << '\n';

            switch (choice) {
            case 1:
                list.pushFront(inputTransistor());
                cout << "  Елемент додано на початок. Розмір: " << list.size() << '\n';
                break;
            case 2:
                list.pushBack(inputTransistor());
                cout << "  Елемент додано в кінець. Розмір: " << list.size() << '\n';
                break;
            case 3: {
                if (list.isEmpty()) {
                    cout << "  Список порожній: немає елемента, після якого вставляти.\n";
                    break;
                }
                list.printForward();
                int pos = readInt("  Після якого елемента вставити? ", 1, list.size());
                list.insertAfter(pos, inputTransistor());
                cout << "  Елемент вставлено на позицію " << pos + 1 << ". Розмір: " << list.size() << '\n';
                break;
            }
            case 4:
                if (list.popFront()) cout << "  Перший елемент видалено. Розмір: " << list.size() << '\n';
                else cout << "  Список порожній, видаляти нічого.\n";
                break;
            case 5:
                if (list.popBack()) cout << "  Останній елемент видалено. Розмір: " << list.size() << '\n';
                else cout << "  Список порожній, видаляти нічого.\n";
                break;
            case 6: {
                if (list.isEmpty()) {
                    cout << "  Список порожній, видаляти нічого.\n";
                    break;
                }
                string type = readText("  Тип транзистора для видалення: ");
                if (list.removeByValue(type)) cout << "  Елемент \"" << type << "\" видалено. Розмір: " << list.size() << '\n';
                else cout << "  ! Елемент з типом \"" << type << "\" не знайдено.\n";
                break;
            }
            case 7:
                cout << "--- Прямий вивід (head -> tail), елементів: " << list.size() << " ---\n";
                list.printForward();
                break;
            case 8:
                cout << "--- Зворотний вивід (tail -> head), елементів: " << list.size() << " ---\n";
                list.printBackward();
                break;
            case 9:
                cout << "  Список " << (list.isEmpty() ? "порожній." : "не порожній, елементів: " + to_string(list.size()) + ".") << '\n';
                break;
            case 10:
                fillTestData(list);
                break;
            case 11:
                list.clear();
                cout << "  Список очищено.\n";
                break;
            }
        }
    } catch (const exception& e) {
        cout << "\n  ! " << e.what() << '\n';
    }

    cout << "\nРоботу програми завершено.\n";
    return 0;   // тут спрацює деструктор list і звільнить усі вузли
}
