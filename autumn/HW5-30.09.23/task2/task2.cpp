#include <iostream>
#include "elementaryParticle.hpp"

int main()
{
    // Create an electron in SI units
    ElementaryParticle electron_si(9.10938356e-31, 2.19703e-12, -1.60217663e-19, 0.5, "Electron", SI);

    // Create a photon in CGS units
    ElementaryParticle photon_cgs(0.0, 0.0, 0.0, 1.0, "Photon");

    electron_si.printInformation(SI); // Print information in SI units
    photon_cgs.printInformation(CGS); // Print information in CGS units
    

    return 0;
}
