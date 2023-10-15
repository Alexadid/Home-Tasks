#include "elementaryParticle.hpp"
#include <iostream>

// Опредение констант для перевода единиц из одной системы измерения в другуж
const double ElementaryParticle::csgToSiMass = 1000;
const double ElementaryParticle::csgToSiLifetime = 1;
const double ElementaryParticle::csgToSiCharge = 2997924580.0;
const double ElementaryParticle::csgToSiSpin = 1e7;

ElementaryParticle::ElementaryParticle(double mass, double lifetime, double charge, double spin, const std::string& name, MeasurementSystem units)
    : m_name{name}
{
    // Используем сеттеры для создания объекта класса
    setMass(mass, units);
    setLifetime(lifetime, units);
    setCharge(charge, units);
    setSpin(spin, units);
}

double ElementaryParticle::getMass(MeasurementSystem units) const
{
    return (units == SI) ? m_mass : m_mass * csgToSiMass;
}

double ElementaryParticle::getLifetime(MeasurementSystem units) const
{
    return (units == SI) ? m_lifetime : m_lifetime * csgToSiLifetime;
}

double ElementaryParticle::getCharge(MeasurementSystem units) const
{
    return (units == SI) ? m_charge : m_charge * csgToSiCharge;
}

double ElementaryParticle::getSpin(MeasurementSystem units) const
{
    return (units == SI) ? m_spin : m_spin * csgToSiSpin;
}

const std::string& ElementaryParticle::getName() const
{
    return m_name;
}

// Сеттеры
void ElementaryParticle::setMass(double mass, MeasurementSystem units)
{
    (units == SI) ? m_mass = mass : m_mass = mass / csgToSiMass;
}


void ElementaryParticle::setLifetime(double lifetime, MeasurementSystem units)
{
    (units == SI) ? m_lifetime = lifetime : m_lifetime = lifetime / csgToSiLifetime;
}

void ElementaryParticle::setCharge(double charge, MeasurementSystem units)
{
    (units == SI) ? m_charge = charge : m_charge = charge / csgToSiCharge;
}

void ElementaryParticle::setSpin(double spin, MeasurementSystem units)
{
    (units == SI) ? m_spin = spin : m_spin = spin / csgToSiSpin;
}

// Метод для печати всей информации о частице
void ElementaryParticle::printInformation(MeasurementSystem units) const
{
    std::cout << "Particle Information:\n";
    std::cout << "Name: " << m_name << "\n";
    std::cout << "Mass: " << getMass(units) << (units == SI ? " kg" : " g") << "\n";
    std::cout << "Lifetime: " << getLifetime(units) << (units == SI ? " s" : " s") << "\n";
    std::cout << "Charge: " << getCharge(units) << (units == SI ? " C" : " esu") << "\n";
    std::cout << "Spin: " << getSpin(units) << (units == SI ? " J*s" : " Erg*s") << "\n";
    std::cout << std::endl;
}
