{
// To display entries, mean, RMS, integral, no of underflows, skewness and kurtosis
gStyle->SetOptStat(111111111);
    
    
TH1F h("Gaussian Histo","", 50,0.0,10.0);
TCanvas c("Exercise 3 Histo","Exercise 3 Histo",800,600);
    
TRandom rng;
    
for (int t=0;t<1e4;t++){
    h.Fill(rng.Gaus(5,2));
    
}
    
h.SetTitle("Exercise 3 Gaussian Histo");
h.Draw();
c.SaveAs("Ex3_histo.pdf");
}
