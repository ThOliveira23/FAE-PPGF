#include "Pythia8/Pythia.h"
using namespace Pythia8;

int main()  {
    
    Pythia pythia;
    pythia.readString("Beams:eCM = 8000.");
    pythia.readString("Higgs:useBSM = on");
    pythia.readString("HiggsBSM:gg2H1 = on");
    pythia.readString("HiggsH1:parity = 3");
    pythia.readString("HiggsH1:etaParity = 0.5");
    pythia.readString("25:m0 = 125.0");
    pythia.readString("25:onMode = off ");
    pythia.readString("25:onIfMatch = 23 23");
    pythia.readString("23:onMode = off");
    pythia.readString("23:onIfAny = 11 13 15");
    //pythia.readFile("list_of_pythia_parameters.txt");
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
    
    
    
}


/*
 
 
 *-------  PYTHIA Event and Cross Section Statistics  -------------------------------------------------------------*
 |                                                                                                                 |
 | Subprocess                                    Code |            Number of events       |      sigma +- delta    |
 |                                                    |       Tried   Selected   Accepted |     (estimated) (mb)   |
 |                                                    |                                   |                        |
 |-----------------------------------------------------------------------------------------------------------------|
 |                                                    |                                   |                        |
 | g g -> h0(H1)                                 1002 |        1022        100        100 |   1.810e-12  1.304e-13 |
 |                                                    |                                   |                        |
 | sum                                                |        1022        100        100 |   1.810e-12  1.304e-13 |
 |                                                                                                                 |
 *-------  End PYTHIA Event and Cross Section Statistics ----------------------------------------------------------*
 
 */
