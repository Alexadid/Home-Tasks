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
    static const double CGS_TO_SI_MASS;
    static const double CGS_TO_SI_LIFETIME;
    static const double CGS_TO_SI_CHARGE;
    static const double CGS_TO_SI_SPIN;
    
    // Конструктор для СГС (или CGS, если по-английски)
    ElementaryParticle(double mass_cgs, double lifetime_cgs, double charge_cgs, double spin_cgs, const std::string& name);
    
    // Конструктор для СИ
    ElementaryParticle(double mass_si, double lifetime_si, double charge_si, double spin_si, const std::string& name, MeasurementSystem units);
    
    // Геттеры
    double getMass(MeasurementSystem units) const; // масса
    double getLifetime(MeasurementSystem units) const; // средняя продолжительность жизни частицы
    double getCharge(MeasurementSystem units) const; // заряд
    double getSpin(MeasurementSystem units) const; // спин (здесь единицы, что в СГС, что в СИ одни и те же)
    const std::string& getName() const;

    // Сеттеры
    void setMass(double mass, MeasurementSystem units);
    void setLifetime(double lifetime, MeasurementSystem units);
    void setCharge(double charge, MeasurementSystem units);
    void setSpin(double spin, MeasurementSystem units);

    // Функция для печати всей информации о частице
    void printInformation(MeasurementSystem units) const;
    
private:
    // Приватные данные-члены для обеих сиситем измерений
    double mass_cgs;
    double lifetime_cgs;
    double charge_cgs;
    double spin_cgs;
    
    double mass_si;
    double lifetime_si;
    double charge_si;
    double spin_si;
    
    std::string name;
};

#endif
