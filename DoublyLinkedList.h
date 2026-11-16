#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <string>
#include "Node.h"

// Двозв'язний лінійний список транзисторів (варіант 18)
class DoublyLinkedList {
private:
    Node* head;   // перший вузол
    Node* tail;   // останній вузол
    int count;    // кількість вузлів

    // Від'єднує вузол від сусідів і звільняє пам'ять
    void unlinkAndDelete(Node* node);

public:
    DoublyLinkedList();
    ~DoublyLinkedList();   // видаляє всі вузли

    // Копіювання заборонене: інакше два списки ділили б одні вузли
    // і деструктор звільнив би ту саму пам'ять двічі
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    // ---- Додавання ----
    void pushFront(const Transistor& value);                // на початок
    void pushBack(const Transistor& value);                 // у кінець
    bool insertAfter(int position, const Transistor& value); // після елемента № position (1..size)

    // ---- Видалення ----
    bool popFront();                                  // з початку
    bool popBack();                                   // з кінця
    bool removeByValue(const std::string& type);      // перший елемент із заданим типом
    bool removeByValue(const Transistor& value);      // перший елемент, рівний value (operator==)
    void clear();                                     // усі вузли

    // ---- Виведення ----
    void printForward() const;    // від head до tail
    void printBackward() const;   // від tail до head

    // ---- Стан ----
    bool isEmpty() const;
    int size() const;
};

#endif
