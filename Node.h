#ifndef NODE_H
#define NODE_H

#include "Transistor.h"

// Базовий клас елемента (вузла) двозв'язного списку.
// Кожен вузол зберігає дані та два вказівники: на попередній і на наступний вузол.
//
//   nullptr <- [prev | data | next] <-> [prev | data | next] -> nullptr
//               head                                tail
class Node {
private:
    Transistor data;   // дані елемента
    Node* prev;        // попередній вузол (nullptr у head)
    Node* next;        // наступний вузол (nullptr у tail)

    // Список має прямий доступ до prev/next, щоб перев'язувати вузли
    friend class DoublyLinkedList;

public:
    explicit Node(const Transistor& value) : data(value), prev(nullptr), next(nullptr) {}

    const Transistor& getData() const { return data; }
};

#endif
