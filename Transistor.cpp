#include "Transistor.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace std;

// ---------- Допоміжні функції введення ----------

static string trim(const string& s) {
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == string::npos) return "";
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

static string readLine(const string& prompt) {
    cout << prompt << ": ";
    string s;
    if (!getline(cin, s)) throw runtime_error("Введення перервано (кінець потоку).");
    return trim(s);
}

static double toNumber(string s) {
    for (char& c : s) if (c == ',') c = '.';   // дозволяємо кому як роздільник
    try {
        size_t pos = 0;
        double v = stod(s, &pos);
        if (pos == s.size()) return v;
    } catch (const exception&) {
    }
    throw invalid_argument("\"" + s + "\" не є числом.");
}

// ---------- Конструктори ----------

Transistor::Transistor() : type("Невідомо"), gain(1.0), maxCurrent(0.1) {}

Transistor::Transistor(const string& t, double g, double i) : Transistor() {
    setType(t);
    setGain(g);
    setMaxCurrent(i);
}

// ---------- Гетери ----------

const string& Transistor::getType() const { return type; }
double Transistor::getGain() const { return gain; }
double Transistor::getMaxCurrent() const { return maxCurrent; }

// ---------- Сетери з перевіркою ----------

void Transistor::setType(const string& value) {
    string v = trim(value);
    if (v.empty()) throw invalid_argument("Тип транзистора не може бути порожнім.");
    type = v;
}

void Transistor::setGain(double value) {
    if (value <= 0 || value > 10000) {
        ostringstream msg;
        msg << "Коефіцієнт підсилення " << value << " некоректний (має бути 0 < h <= 10000).";
        throw invalid_argument(msg.str());
    }
    gain = value;
}

void Transistor::setMaxCurrent(double value) {
    if (value <= 0 || value > 100) {
        ostringstream msg;
        msg << "Струм " << value << " А некоректний (має бути 0 < I <= 100).";
        throw invalid_argument(msg.str());
    }
    maxCurrent = value;
}

// ---------- Введення / виведення ----------

void Transistor::input() {
    while (true) {
        try { setType(readLine("  Тип (маркування)")); break; }
        catch (const invalid_argument& e) { cout << "  ! " << e.what() << " Спробуйте ще раз.\n"; }
    }
    while (true) {
        try { setGain(toNumber(readLine("  Коефіцієнт підсилення (0..10000]"))); break; }
        catch (const invalid_argument& e) { cout << "  ! " << e.what() << " Спробуйте ще раз.\n"; }
    }
    while (true) {
        try { setMaxCurrent(toNumber(readLine("  Максимальний струм, А (0..100]"))); break; }
        catch (const invalid_argument& e) { cout << "  ! " << e.what() << " Спробуйте ще раз.\n"; }
    }
}

void Transistor::print(ostream& os) const {
    os << left << setw(10) << type << right
       << " | h = " << setw(7) << fixed << setprecision(1) << gain
       << " | Imax = " << setw(6) << setprecision(2) << maxCurrent << " А";
}

bool Transistor::operator==(const Transistor& other) const {
    return type == other.type && gain == other.gain && maxCurrent == other.maxCurrent;
}

ostream& operator<<(ostream& os, const Transistor& t) {
    t.print(os);
    return os;
}
