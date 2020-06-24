  
#include "Pythia8/Pythia.h"
using namespace Pythia8;

int main()  {
    
    Pythia pythia;
    pythia.readString("Beams:eCM = 8000.");
    pythia.readString("Higgs:useBSM = on");         // Allow BSM
    pythia.readString("HiggsBSM:gg2A3 = on");       // Scattering gg → A^0(A_3^0) via loop contributions primarily from top
    pythia.readString("HiggsA3:parity = 2");        // A as a pure pseudoscalar with CP-odd
    pythia.readString("35:m0 = 300");              // mass
    pythia.readString("35:onMode = off");           // turn off decays
    pythia.readString("35:onIfMatch = 25 23");      // A -> Zh
    pythia.readString("25:onMode = off");
    pythia.readString("25:onIfMatch = 23 23");      // h -> ZZ
    pythia.readString("23:onMode = off");   // turn off all Z decays
    pythia.readString("23:onIfAny = 11 13 15");  // decays in leptons
    pythia.init();
    
    Hist mult("charged multiplicity", 100, -0.5, 799.5);

    for (int iEvent = 0; iEvent < 100; ++iEvent) {
      if (!pythia.next()) continue;
      // Find number of all final charged particles and fill histogram.
      int nCharged = 0;
      for (int i = 0; i < pythia.event.size(); ++i)
        if (pythia.event[i].isFinal() && pythia.event[i].isCharged())
          ++nCharged;
      mult.fill( nCharged );
    // End of event loop. Statistics. Histogram. Done.
    }
    pythia.stat();
    cout << mult;
    return 0;
    
    
   // mode  HiggsA3:parity   (default = 2; minimum = 0; maximum = 3)
   // possibility to modify angular decay correlations in the decay of a A^0(H_3) decay Z^0 Z^0 or W^+ W^- to four fermions. Currently it does not affect the partial width of the channels, which is only based on the above parameters.
   // option 0 : isotropic decays.
   // option 1 : assuming the A^0(H_3) is a pure scalar (CP-even).
   // option 2 : assuming the A^0(H_3) is a pure pseudoscalar (CP-odd), as in the MSSM.
   // option 3 : assuming the A^0(H_3) is a mixture of the two, including the CP-violating interference term. The parameter eta, see below, sets the strength of the CP-odd admixture, with the interference term being proportional to eta and the CP-odd one to eta^2.
}


// | g g -> A0(A3)                                 1042 |         384        100        100 |   7.424e-11  5.020e-12
