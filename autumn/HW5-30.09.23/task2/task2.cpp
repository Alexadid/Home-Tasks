#include <iostream>
#include "elementaryParticle.hpp"

int main()
{
    // Создаём электрон в единицах СИ
    ElementaryParticle electron_si(9.10938356e-31, 2.19703e-12, -1.60217663e-19, 0.5, "Electron", SI);

    // Создём фотон в единицах СГС
    ElementaryParticle photon_cgs(0.0, 0.0, 0.0, 1.0, "Photon");

    electron_si.printInformation(SI); // Печатаем информаицю в СИ
    electron_si.printInformation(CGS); // Печатаем информацию в СГС

    photon_cgs.printInformation(SI); // Печатаем информаицю в СИ
    photon_cgs.printInformation(CGS); // Печатаем информацию в СГС
    
    return 0;
}
