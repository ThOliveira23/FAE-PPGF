#define Z_dimuon_cxx
#include "Z_dimuon.h"


// Exercise

// 1. Pick a peak
//   - you have several to choose from

// 2. Place selection cuts
//   - let's require a pt threshold on each muon at 10 GeV/c
//   - how are the signal yields affected?

// 3. Extract the fit result
//   - signal mass
//   - statistical uncertainties included


void Z_dimuon() {
    
    TChain *chain = new TChain("oniaTree","");
    chain->Add("Skim4.root");
    
    //chain->Show()
    //chan->Scan("*");
    
    dimuon a(chain);
    a._nevt = 100000;
    
    a.GetSpectrum();
    a.SelectPeak();
    a.FitPeak();
    
    
}

// Main processing function
void dimuon::GetSpectrum() {
    
    // Check tree
    if (fChain == 0) return;
    
    // Create and fill the mass histogram
    
    TH1F *hDiMuonMass_normal = new TH1F("hDiMuonMass_normal","hDiMuonMass_normal",10000,0.2,300);
    
    //Fill histo using virtual void FillHisto(TH1F* hist);
    FillHisto(hDiMuonMass_normal);
    
    // Save histo using  virtual void SaveHisto(TH1F* hist, Int_t log = 0);
    SaveHisto(hDiMuonMass_normal);
    
    // Set the log scales
    SaveHisto(hDiMuonMass_normal,kTRUE);

    // Define another (special) histogram: with variable (!) bin widths
    
    double xbins[100000];
    xbins[0] = 0.1;
    int nbins = 0;
    double binWidth = 0.005;
    
    for (int i=1; xbins[i-1] < 500; i++) {
        
        xbins[i] = xbins[i-1]*(1+binWidth);
        nbins++;
        
        }
    
    TH1F *hDiMuonMass = new TH1F("hDiMuonMass","hDiMuonMass",nbins,xbins);
    FillHisto(hDiMuonMass);
    SaveHisto(hDiMuonMass,kTRUE);
    
    
    // Normalize yields (to adapt to variable binning!)
    for (int i=1; i<=hDiMuonMass->GetNbinsX(); i++) {
        hDiMuonMass->SetBinContent(i,hDiMuonMass->GetBinContent(i)/hDiMuonMass->GetBinWidth(i));
        
    }
    
    SaveHisto(hDiMuonMass,kTRUE);

    
}

void dimuon::SaveHisto(TH1F* hist, Int_t log) {
    
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    
    hist->GetXaxis()->SetTitle("#mu^{+}#mu^{-} invariant mass [GeV]");
    hist->GetYaxis()->SetTitle("Events / GeV");
    
    TCanvas *c = new TCanvas("c","c",800,600);
    
    if(log) {
        c->SetLogx();
        c->SetLogy();
    }
    
    hist->Draw("HIST");
    
    TString hn ("");
    hn += "plots/";
    hn += hist->GetName();
    if(log) hn += "_log";
    hn += ".png";
    c->SaveAs(hn);
    delete c;
    
    _outputFile->cd();
    hist->Draw("HIST");
    hist->Write();
    _outputFile->Write();
    
}

void dimuon::FillHisto(TH1F* hist) {
    
    //  Loop over the tree and fill the histogram
    Long64_t nentries = fChain->GetEntriesFast();
    nentries = _nevt > 0 ? _nevt : nentries;
    // cout << "nentries: " << nentries << endl;
    
    Long64_t nbytes = 0, nb = 0;
    
    for (Long64_t jentry=0; jentry<nentries; jentry++) {
        
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry); nbytes += nb;
        
        if ( Cut(ientry) < 0) continue;
        
        double mass = dimuon_p4->M();
        
        hist->Fill(mass);
        
    }
    
}


void dimuon::SelectPeak() {
    
    Double_t min(80.9), max(99.3);
    _min = min; _max = max;
    
    // Create a histogram around a peak
    TH1F *hDiMuonMass_mypeak = new TH1F("hDiMuonMass_mypeak","hDiMuonMass_mypeak",100,min,max);
    FillHisto(hDiMuonMass_mypeak);
    SaveHisto(hDiMuonMass_mypeak);
}


void dimuon::FitPeak() {
    
    if (!_outputFile) {cout << "Check input file." << endl; return;}
    
    // Retrieve histogram with selected peak
    TH1F *hpeak = 0;
    TString hname("hDiMuonMass_mypeak");
    _outputFile->GetObject(hname,hpeak);
    
    if (!hpeak) {
        
        cout << "Check input histogram." << hname << endl;
        return;
    }
    
    
    // Define fit function and fit the histogram
    const Int_t nfitpar(5);
    TF1* f = new TF1("f",fitfunction,_min,_max,nfitpar);
    //f->SetParameters(100,3.09,0.1,0,0);
    // BEST CONFIGURATION NOW
    f->SetParameters(100,91.0,2.5,0.0,0.0);
    hpeak->Fit("f");
    
    // Write fit results into an array
    Double_t par[nfitpar];
    f->GetParameters(par);
    
    printf("\nFitResults:\n\tResonance mass: %5.3f +/- %5.3f GeV/c^2.\n",
       par[1],f->GetParErrors()[1]);
    
    // return;   // comment for continuing
    
    // What follows is aesthetics, mostly ...
    
    gROOT->LoadMacro("tdrstyle.C");
    
    TCanvas *c0 = new TCanvas("peak","peak",800,600);
    //c0->SetFillColor(0);
    //c0->SetFrameFillColor(0);
    //c0->SetGrid();
    
    hpeak->GetXaxis()->SetTitle("#mu^{+}#mu^{-} invariant mass [GeV/c^{2}]");
    hpeak->GetYaxis()->SetTitle(Form("Events / %3.1f MeV/c^{2}",hpeak->GetBinWidth(1)*1000));
    hpeak->SetStats(0);
    hpeak->SetTitle("");
    hpeak->SetMarkerStyle(21);
    hpeak->SetMarkerSize(0.8);
    
    hpeak->Fit("f","V+","ep");
    
    // Get individual functions for separate representation
    TF1 *signalFunction = new TF1("signalFunction",signal,_min,_max,3);
    signalFunction->SetLineColor(kBlue);
    signalFunction->SetNpx(500);
    
    TF1 *backgroundFunction = new TF1("backgroundFunction",background,_min,_max,2);
    backgroundFunction->SetLineColor(kGray);
    backgroundFunction->SetLineStyle(2);
    
    //cout << "signal function parameters " << par << endl;
    signalFunction->SetParameters(par);
    signalFunction->Draw("same");
    
    //cout << "background function parameters " << &par[3] << endl;
    backgroundFunction->SetParameters(&par[3]);
    backgroundFunction->Draw("same");
    
    
    // draw the legend
    TLegend *legend=new TLegend(0.7,0.65,0.88,0.85);
    legend->SetBorderSize(0);
    legend->SetTextFont(40);
    legend->SetTextSize(0.03);
    legend->AddEntry(hpeak,"Data","lpe");
    legend->AddEntry(backgroundFunction,"Background fit","l");
    legend->AddEntry(signalFunction,"Signal fit","l");
    legend->AddEntry(f,"Global Fit","l");
    legend->Draw("same");
    
    // Display info + fit results
    TLatex L;
    L.SetNDC();
    L.SetTextSize(0.04);
    L.DrawLatex(0.15,0.8,"Dimuon Spectrum");
    L.SetTextSize(0.03);
    L.DrawLatex(0.15,0.75,"resonance: Z");
    L.DrawLatex(0.15,0.70,Form("mass: %5.3f #pm %5.3f GeV/c^{2}",
                   par[1], f->GetParErrors()[1]));
    L.DrawLatex(0.15,0.65,Form("width: %5.3f #pm %5.3f MeV/c^{2}",
                   par[2]*1000, f->GetParErrors()[2]*1000));

    // Save the fitted histogram
    c0->SaveAs("plots/myZpeak.png");
    
    
}







Double_t signal(Double_t *x, Double_t *par) {
  //a simple gaussian
  return par[0]*exp(-0.5*TMath::Power(((x[0]-par[1])/(par[2])),2));
}

//Breit-Wigner function
Double_t breitwigner(Double_t* x, Double_t* par)
{
  Double_t arg1 = 14.0/22.0; // 2 over pi
  Double_t arg2 = par[1]*par[1]*par[2]*par[2]; //Gamma=par[1]  M=par[2]
  Double_t arg3 = ((x[0]*x[0]) - (par[2]*par[2]))*((x[0]*x[0]) - (par[2]*par[2]));
  Double_t arg4 = x[0]*x[0]*x[0]*x[0]*((par[1]*par[1])/(par[2]*par[2]));
    //cout << "BW signal function parameters " << par[0] << endl;
  return par[0]*arg1*arg2/(arg3 + arg4);
}

Double_t background(Double_t *x, Double_t *par) {
  //a simple polynomial
    //cout << "background function parameters " << par[0] << endl;
  return par[0]+par[2]*x[0];
}

Double_t fitfunction(Double_t *x, Double_t *par) {
  //the total PDF function, sum of the above
  return signal(x,par) + background(x,&par[3]);
}



