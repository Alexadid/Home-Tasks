#ifndef ELEMENTARY_PARTICLE_HPP
#define ELEMENTARY_PARTICLE_HPP

#include <string>

// Enum для указания системы единиц измерения
enum MeasurementSystem
{
    SI,
    CGS
};

class ElementaryParticle
{
public:
    // Константы для перевода деиниц измерений
    static const double csgToSiMass;
    static const double csgToSiLifetime;
    static const double csgToSiCharge;
    static const double csgToSiSpin;

    // Конструктор по умолчанию
    ElementaryParticle() = default;

    // Параметризованный констурктор
    ElementaryParticle(double mass, double lifetime, double charge, double spin, const std::string& name, MeasurementSystem units);

    // Геттеры
    double getMass(MeasurementSystem units) const; // масса
    double getLifetime(MeasurementSystem units) const; // средняя продолжительность жизни частицы
    double getCharge(MeasurementSystem units) const; // заряд
    double getSpin(MeasurementSystem units) const; // спин (в Дж*с в СИ и в Эрг*с в СГСЭ)
    const std::string& getName() const;

    // Сеттеры
    void setMass(double mass, MeasurementSystem units);
    void setLifetime(double lifetime, MeasurementSystem units);
    void setCharge(double charge, MeasurementSystem units);
    void setSpin(double spin, MeasurementSystem units);

    // Метод для печати всей информации о частице
    void printInformation(MeasurementSystem units) const;

private:
    // Приватные данные-члены, всё хранится в СИ
    // Значения по умолчанию
    double m_mass{0};
    double m_lifetime{0};
    double m_charge{0};
    double m_spin{0};
    std::string m_name{"Particle Name"};

    static double convertToCGS(double value, MeasurementSystem units);
};

#endif
