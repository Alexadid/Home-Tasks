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
    
    // Конструктор для СГС (или CGS, если по-английски)
    ElementaryParticle(double massCGS, double lifetimeCGS, double chargeCGS, double spinCGS, const std::string& name);
    
    // Конструктор для СИ
    ElementaryParticle(double massSI, double lifetimeSI, double chargeSI, double spinSI, const std::string& name, MeasurementSystem units);
    
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
    double massCGS;
    double lifetimeCGS;
    double chargeCGS;
    double spinCGS;
    
    double massSI;
    double lifetimeSI;
    double chargeSI;
    double spinSI;
    
    std::string name;
};

#endif
