#ifndef Z_dimuon_h
#define Z_dimuon_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TLatex.h>
#include <TF1.h>
#include "TMath.h"
#include "TLegend.h"
#include "TLorentzVector.h"



// Defining auxiliary functions for fitting
Double_t signal(Double_t *x, Double_t *par);
Double_t background(Double_t *x, Double_t *par);
Double_t fitfunction(Double_t *x, Double_t *par);
Double_t breitwigner(Double_t *x, Double_t *par);


// Creating a class
class dimuon {
    
    public :

    TTree  *fChain;   // pointer to the TTree
    Int_t  fCurrent;
    TFile  *_outputFile;
    Double_t _nevt;
    Double_t _min;
    Double_t _max;
    
    // Fixed size dimensions of array or collections stored in the TTree if any.
       
    // Declaring the leaf types
    Int_t event;
    TLorentzVector *dimuon_p4;
    TLorentzVector *muonP_p4;
    TLorentzVector *muonN_p4;
    
    // Listing the branches
    TBranch  *b_event;
    TBranch  *b_dimuon_p4;
    TBranch  *b_muonP_p4;
    TBranch  *b_muonN_p4;
    
    // Declaring functions
    dimuon(TTree *tree=0);   // constructor
    virtual ~dimuon();       // destructor
    virtual Int_t  Cut(Long64_t entry);
    virtual Int_t  GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void Init(TTree *tree);
    virtual void GetSpectrum();
    virtual Bool_t Notify();
    virtual void Show(Long64_t entry =-1);
    virtual void FitPeak();
    virtual void FillHisto(TH1F* hist);
    virtual void SaveHisto(TH1F* hist, Int_t log = 0);
    virtual void SelectPeak();
    
};


#endif

#ifdef Z_dimuon_cxx
dimuon::dimuon(TTree *tree) : fChain(0)
 {
    
    // If tree parameter is not specified, connect the file
    // Used to generate this class and read the TTree
    
    if (tree == 0) {
        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("data.root");
        if (!f || !f->IsOpen()) {
            f = new TFile("data.root");
        }
        TDirectory *dir = (TDirectory*)f->Get("data.root:/");
        dir->GetObject("oniaTree",tree);
    }
    Init(tree);
    
    _outputFile = new TFile("plots/histos.root","update");
    
    
    
}
// Destructor
dimuon::~dimuon()
{
    if (!fChain) return;
    delete fChain->GetCurrentFile();
    _outputFile->Close();
    delete _outputFile;
}

// GetEntry function virtual Int_t  Cut(Long64_t entry); Read contents of entry
Int_t dimuon::GetEntry(Long64_t entry)
{
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}

// LoadTree function virtual Long64_t LoadTree(Long64_t entry); Set the environment to read opne entry
Long64_t dimuon::LoadTree(Long64_t entry)
{
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
        fCurrent = fChain->GetTreeNumber();
        Notify();
    }
    return centry;
}


// Init function virtual void Init(TTree *tree);
void dimuon::Init(TTree *tree)
{
    /* The Init() function is called when the selector needs to initialize
     a new tree or chain. Typically here the branch addresses and branch
     pointers of the tree will be set.
     
     It is normally not necessary to make changes to the generated code,
     but the routine can be extended by the user if needed.
     Init() will be called many times when running on PROOF
     once per file to be processed.
    */
    
    // Set object pointer
    dimuon_p4 = 0;
    muonN_p4 = 0;
    muonP_p4 = 0;
    
    // Set the branch address and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);
    
    fChain->SetBranchAddress("event",&event, &b_event);
    fChain->SetBranchAddress("dimuon_p4", &dimuon_p4, &b_dimuon_p4);
    fChain->SetBranchAddress("muonP_p4", &muonP_p4, &b_muonP_p4);
    fChain->SetBranchAddress("muonN_p4", &muonN_p4, &b_muonN_p4);
    
    Notify();
    
}

// Notify function  virtual Bool_t Notify();
Bool_t dimuon::Notify()
{
    /*
     The Notify() function is called when a new file is opened.
     This can be either for a new TTree in a TChain or when a new TTree is started
     using PROOF.
     It is normally not necessary to make changes to the generated code.
     but the routine can be extended by the user if needed.
     The return value is currently not used.
     
     */
    return kTRUE;
    
}

// Show function virtual void Show(Long64_t entry =-1);
void dimuon::Show(Long64_t entry)
{
    // Print contents of entry. If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);

}

// Cut function virtual Int_t  Cut(Long64_t entry);
Int_t dimuon::Cut(Long64_t entry)
{
    // This function may be called from Loop
    // returns 1 if entry is accepted
    // returns -1 otherwise
    
    double mass = dimuon_p4->M();
    double pt1 = muonN_p4->Pt();
    double pt2 = muonP_p4->Pt();
    //if (pt1 < 10 || pt2 < 10) return -1;
    //if (mass > 200) return -1;
    //cout << "Cut mass: " << mass << endl;
     
    return 1;
}

#endif  // #ifdef Z_dimuon_cxx
