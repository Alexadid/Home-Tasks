#include <iostream>
#include "elementaryParticle.hpp"

int main()
{
    // Параметры электрона в СИ
    const double massSIOfElectron = 9.10938356e-31;
    const double lifetimeSIOfElectorn = std::numeric_limits<double>::infinity();
    const double chargeSIOfElectorn = -1.60217663e-19;
    const double spinSIOfElectron = 5.2728590e-35;

    // Создаём электрон в единицах СИ
    ElementaryParticle electron_si(massSIOfElectron, lifetimeSIOfElectorn, chargeSIOfElectorn, spinSIOfElectron, "Electron", SI);

    // Параметры фотона в СГСЭ
    const double massCGSOfPhoton = 0;
    const double lifetimeCGSOfPhoton = std::numeric_limits<double>::infinity();
    const double chargeCGSOfPhoton = 0;
    const double spinCGSOfElectron = 1.054571800e-27;

    // Создём фотон в единицах СГС
    ElementaryParticle photon_cgs(massCGSOfPhoton, lifetimeCGSOfPhoton, chargeCGSOfPhoton, spinCGSOfElectron, "Photon", CGS);

    electron_si.printInformation(SI); // Печатаем информаицю в СИ
    electron_si.printInformation(CGS); // Печатаем информацию в СГС

    photon_cgs.printInformation(SI); // Печатаем информаицю в СИ
    photon_cgs.printInformation(CGS); // Печатаем информацию в СГС

    // Деонстрация работы констурктора по умолчанию...
    auto particle = ElementaryParticle();
    particle.printInformation(SI);
    
    return 0;
}
