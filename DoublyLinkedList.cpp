#include "DoublyLinkedList.h"
#include <iostream>
#include <iomanip>

using namespace std;

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

DoublyLinkedList::~DoublyLinkedList() {
    int n = count;
    clear();
    cout << "[Деструктор] список знищено, звільнено вузлів: " << n << '\n';
}

// ---------- Додавання ----------

void DoublyLinkedList::pushFront(const Transistor& value) {
    Node* node = new Node(value);
    node->next = head;
    if (head) head->prev = node;   // старий перший тепер посилається назад на новий
    else tail = node;              // список був порожній: новий вузол і перший, і останній
    head = node;
    ++count;
}

void DoublyLinkedList::pushBack(const Transistor& value) {
    Node* node = new Node(value);
    node->prev = tail;
    if (tail) tail->next = node;
    else head = node;
    tail = node;
    ++count;
}

bool DoublyLinkedList::insertAfter(int position, const Transistor& value) {
    if (position < 1 || position > count) return false;

    Node* current = head;                         // шукаємо вузол № position
    for (int i = 1; i < position; ++i) current = current->next;

    if (current == tail) {                        // вставка після останнього = у кінець
        pushBack(value);
        return true;
    }
    Node* node = new Node(value);                 // current <-> node <-> current->next
    node->prev = current;
    node->next = current->next;
    current->next->prev = node;
    current->next = node;
    ++count;
    return true;
}

// ---------- Видалення ----------

void DoublyLinkedList::unlinkAndDelete(Node* node) {
    if (node->prev) node->prev->next = node->next;
    else head = node->next;                       // видаляли head

    if (node->next) node->next->prev = node->prev;
    else tail = node->prev;                       // видаляли tail

    delete node;
    --count;
}

bool DoublyLinkedList::popFront() {
    if (isEmpty()) return false;
    unlinkAndDelete(head);
    return true;
}

bool DoublyLinkedList::popBack() {
    if (isEmpty()) return false;
    unlinkAndDelete(tail);
    return true;
}

bool DoublyLinkedList::removeByValue(const string& type) {
    for (Node* cur = head; cur; cur = cur->next) {
        if (cur->data.getType() == type) {
            unlinkAndDelete(cur);
            return true;
        }
    }
    return false;
}

bool DoublyLinkedList::removeByValue(const Transistor& value) {
    for (Node* cur = head; cur; cur = cur->next) {
        if (cur->data == value) {
            unlinkAndDelete(cur);
            return true;
        }
    }
    return false;
}

void DoublyLinkedList::clear() {
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;   // запам'ятовуємо наступний ДО видалення поточного
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
    count = 0;
}

// ---------- Виведення ----------

void DoublyLinkedList::printForward() const {
    if (isEmpty()) {
        cout << "  (список порожній)\n";
        return;
    }
    cout << "  head\n";
    int i = 1;
    for (Node* cur = head; cur; cur = cur->next)
        cout << "  " << setw(2) << i++ << ". " << cur->data << '\n';
    cout << "  tail\n";
}

void DoublyLinkedList::printBackward() const {
    if (isEmpty()) {
        cout << "  (список порожній)\n";
        return;
    }
    cout << "  tail\n";
    int i = count;
    for (Node* cur = tail; cur; cur = cur->prev)   // рух назад по вказівниках prev
        cout << "  " << setw(2) << i-- << ". " << cur->data << '\n';
    cout << "  head\n";
}

// ---------- Стан ----------

bool DoublyLinkedList::isEmpty() const { return head == nullptr; }
int DoublyLinkedList::size() const { return count; }
