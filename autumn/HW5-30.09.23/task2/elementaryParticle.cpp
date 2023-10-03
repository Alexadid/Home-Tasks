#include "elementaryParticle.hpp"
#include <iostream>

// Опредение констант для перевода единиц из одной системы измерения в другуж
const double ElementaryParticle::csgToSiMass = 1.0e-3;
const double ElementaryParticle::csgToSiLifetime = 1.0e-12;
const double ElementaryParticle::csgToSiCharge = 2997924580.0;
const double ElementaryParticle::csgToSiSpin = 6.626e-27;

// Опредение конструктора для СГС
ElementaryParticle::ElementaryParticle(double massCGS, double lifetimeCGS, double chargeCGS, double spinCGS, const std::string& name)
    : massCGS(massCGS), lifetimeCGS(lifetimeCGS), chargeCGS(chargeCGS), spinCGS(spinCGS),
      massSI(massCGS * csgToSiMass), lifetimeSI(lifetimeCGS * csgToSiLifetime),
      chargeSI(chargeCGS * csgToSiCharge), spinSI(spinCGS * csgToSiSpin), name(name) {}

// Опредение конструктора для СИ
ElementaryParticle::ElementaryParticle(double massSI, double lifetimeSI, double chargeSI, double spinSI, const std::string& name, MeasurementSystem units)
    : massSI(massSI), lifetimeSI(lifetimeSI), chargeSI(chargeSI), spinSI(spinSI), name(name)
{
    if (units == SI)
    {
        massCGS = massSI / csgToSiMass;
        lifetimeCGS = lifetimeSI / csgToSiLifetime;
        chargeCGS = chargeSI / csgToSiCharge;
        spinCGS = spinSI / csgToSiSpin;
    }
}

// Геттеры
double ElementaryParticle::getMass(MeasurementSystem units) const
{
    return (units == SI) ? massSI : massCGS;
}

double ElementaryParticle::getLifetime(MeasurementSystem units) const
{
    return (units == SI) ? lifetimeSI : lifetimeCGS;
}

double ElementaryParticle::getCharge(MeasurementSystem units) const
{
    return (units == SI) ? chargeSI : chargeCGS;
}

double ElementaryParticle::getSpin(MeasurementSystem units) const
{
    return (units == SI) ? spinSI : spinCGS;
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
        massSI = mass;
        massCGS = mass * csgToSiMass;
    } else
    {
        massCGS = mass;
        massSI = mass / csgToSiMass;
    }
}

void ElementaryParticle::setLifetime(double lifetime, MeasurementSystem units)
{
    if (units == SI)
    {
        lifetimeSI = lifetime;
        lifetimeCGS = lifetime * csgToSiLifetime;
    } else
    {
        lifetimeCGS = lifetime;
        lifetimeSI = lifetime / csgToSiLifetime;
    }
}

void ElementaryParticle::setCharge(double charge, MeasurementSystem units)
{
    if (units == SI)
    {
        chargeSI = charge;
        chargeCGS = charge * csgToSiCharge;
    } else
    {
        chargeCGS = charge;
        chargeSI = charge / csgToSiCharge;
    }
}

void ElementaryParticle::setSpin(double spin, MeasurementSystem units)
{
    if (units == SI)
    {
        spinSI = spin;
        spinCGS = spin * csgToSiSpin;
    } else
    {
        spinCGS = spin;
        spinSI = spin / csgToSiSpin;
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
