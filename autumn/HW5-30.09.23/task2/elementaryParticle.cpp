#include "elementaryParticle.hpp"
#include <iostream>

// Опредение констант для перевода единиц из одной системы измерения в другуж
const double ElementaryParticle::CGS_TO_SI_MASS = 1.0e-3;
const double ElementaryParticle::CGS_TO_SI_LIFETIME = 1.0e-12;
const double ElementaryParticle::CGS_TO_SI_CHARGE = 2997924580.0;
const double ElementaryParticle::CGS_TO_SI_SPIN = 6.626e-27;

// Опредение конструктора для СГС
ElementaryParticle::ElementaryParticle(double mass_cgs, double lifetime_cgs, double charge_cgs, double spin_cgs, const std::string& name)
    : mass_cgs(mass_cgs), lifetime_cgs(lifetime_cgs), charge_cgs(charge_cgs), spin_cgs(spin_cgs),
      mass_si(mass_cgs * CGS_TO_SI_MASS), lifetime_si(lifetime_cgs * CGS_TO_SI_LIFETIME),
      charge_si(charge_cgs * CGS_TO_SI_CHARGE), spin_si(spin_cgs * CGS_TO_SI_SPIN), name(name) {}

// Опредение конструктора для СИ
ElementaryParticle::ElementaryParticle(double mass_si, double lifetime_si, double charge_si, double spin_si, const std::string& name, MeasurementSystem units)
    : mass_si(mass_si), lifetime_si(lifetime_si), charge_si(charge_si), spin_si(spin_si), name(name)
{
    if (units == SI)
    {
        mass_cgs = mass_si / CGS_TO_SI_MASS;
        lifetime_cgs = lifetime_si / CGS_TO_SI_LIFETIME;
        charge_cgs = charge_si / CGS_TO_SI_CHARGE;
        spin_cgs = spin_si / CGS_TO_SI_SPIN;
    }
}

// Геттеры
double ElementaryParticle::getMass(MeasurementSystem units) const
{
    return (units == SI) ? mass_si : mass_cgs;
}

double ElementaryParticle::getLifetime(MeasurementSystem units) const
{
    return (units == SI) ? lifetime_si : lifetime_cgs;
}

double ElementaryParticle::getCharge(MeasurementSystem units) const
{
    return (units == SI) ? charge_si : charge_cgs;
}

double ElementaryParticle::getSpin(MeasurementSystem units) const
{
    return (units == SI) ? spin_si : spin_cgs;
}

const std::string& ElementaryParticle::getName() const
{
    return name;
}

// Сеттеры
void ElementaryParticle::setMass(double mass, MeasurementSystem units)
{
    if (units == SI)
    {
        mass_si = mass;
        mass_cgs = mass * CGS_TO_SI_MASS;
    } else
    {
        mass_cgs = mass;
        mass_si = mass / CGS_TO_SI_MASS;
    }
}

void ElementaryParticle::setLifetime(double lifetime, MeasurementSystem units)
{
    if (units == SI)
    {
        lifetime_si = lifetime;
        lifetime_cgs = lifetime * CGS_TO_SI_LIFETIME;
    } else
    {
        lifetime_cgs = lifetime;
        lifetime_si = lifetime / CGS_TO_SI_LIFETIME;
    }
}

void ElementaryParticle::setCharge(double charge, MeasurementSystem units)
{
    if (units == SI)
    {
        charge_si = charge;
        charge_cgs = charge * CGS_TO_SI_CHARGE;
    } else
    {
        charge_cgs = charge;
        charge_si = charge / CGS_TO_SI_CHARGE;
    }
}

void ElementaryParticle::setSpin(double spin, MeasurementSystem units)
{
    if (units == SI)
    {
        spin_si = spin;
        spin_cgs = spin * CGS_TO_SI_SPIN;
    } else
    {
        spin_cgs = spin;
        spin_si = spin / CGS_TO_SI_SPIN;
    }
}

// Функция для печати всей информации о частице
void ElementaryParticle::printInformation(MeasurementSystem units) const
{
    std::cout << "Particle Information:\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Mass: " << getMass(units) << (units == SI ? " kg" : " g") << "\n";
    std::cout << "Lifetime: " << getLifetime(units) << (units == SI ? " s" : " s") << "\n";
    std::cout << "Charge: " << getCharge(units) << (units == SI ? " C" : " esu") << "\n";
    std::cout << "Spin: " << getSpin(units) << (units == SI ? " h-bar" : " h-bar (CGS)") << "\n";
    std::cout << std::endl;
}
