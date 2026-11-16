#ifndef TRANSISTOR_H
#define TRANSISTOR_H

#include <iostream>
#include <string>

// Дані одного транзистора (варіант 18): тип, коефіцієнт підсилення, максимальний струм
class Transistor {
private:
    std::string type;     // тип (маркування), напр. "KT315B"
    double gain;          // коефіцієнт підсилення
    double maxCurrent;    // максимальний струм, А

public:
    Transistor();
    // Кидає std::invalid_argument, якщо дані некоректні
    Transistor(const std::string& type, double gain, double maxCurrent);

    // Гетери
    const std::string& getType() const;
    double getGain() const;
    double getMaxCurrent() const;

    // Сетери з перевіркою (кидають std::invalid_argument)
    void setType(const std::string& value);
    void setGain(double value);
    void setMaxCurrent(double value);

    // Введення з клавіатури (повторює запит, поки дані некоректні)
    void input();
    // Виведення в один рядок
    void print(std::ostream& os) const;

    // Два транзистори рівні, якщо збігаються всі три поля
    bool operator==(const Transistor& other) const;
};

std::ostream& operator<<(std::ostream& os, const Transistor& t);

#endif
