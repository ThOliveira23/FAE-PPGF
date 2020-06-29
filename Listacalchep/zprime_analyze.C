  
#include "TLorentzVector.h"

void zprime_analyze()
{


   TFile *f1 = new TFile("zprime_mm_MZp1000.root");
   TTree *t1 = (TTree*)f1->Get("h10");

   
   // Declaration of leaf types
   Int_t           Nprt;
   Int_t           Ikf[100];   //[Nprt]
   Int_t           Ipar[100];   //[Nprt]
   Int_t           Ista[100];   //[Nprt]
   Float_t         Cs;
   Float_t         Xpup[100];   //[Nprt]
   Float_t         Ypup[100];   //[Nprt]
   Float_t         Zpup[100];   //[Nprt]
   Float_t         Epup[100];   //[Nprt]

   TLorentzVector t2;
   TLorentzVector t3;
   TLorentzVector muon_pair;
   int nbins = 50;
   TH1F *hMuonPt    = new TH1F("hMuonPt","",nbins,0,600);
   TH1F *hInvMass   = new TH1F("InvMass","",nbins,800,1200);
   

   t1->SetBranchAddress("Nprt", &Nprt);
   t1->SetBranchAddress("Ikf", Ikf);
   t1->SetBranchAddress("Ipar", Ipar);
   t1->SetBranchAddress("Ista", Ista); //initial state
   t1->SetBranchAddress("Cs", &Cs);  //cross-section
   t1->SetBranchAddress("Xpup", &Xpup); //p_x component of ALL  particles
   t1->SetBranchAddress("Ypup", &Ypup); //p_y component of ALL  particles
   t1->SetBranchAddress("Zpup", &Zpup);    //p_z component of ALL  particles
   t1->SetBranchAddress("Epup", &Epup); //energy  of ALL particles

     Long64_t nentries1 = t1->GetEntries();
     for (Long64_t i=0;i<nentries1;i++) {
     t2.Clear();
     t3.Clear();
     muon_pair.Clear();
     t1->GetEntry(i);
     t2.SetPxPyPzE(Xpup[2],Ypup[2],Zpup[2],Epup[2]);
     t3.SetPxPyPzE(Xpup[3],Ypup[3],Zpup[3],Epup[3]);
     muon_pair = t2 + t3;
     hInvMass->Fill(muon_pair.M());
     hMuonPt->Fill(t2.Pt());
  }

     TCanvas *c1 = new TCanvas("c1", "c1", 800,450);
     c1->Divide(2,1);
     hInvMass->GetXaxis()->SetTitle("M_{#mu#mu}");
     hMuonPt->GetXaxis()->SetTitle("P_{T}^{#mu}");
     c1->cd(1); hInvMass->Draw();
     c1->cd(2); hMuonPt->Draw();
      
}
