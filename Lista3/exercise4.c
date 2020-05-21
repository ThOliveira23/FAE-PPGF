{
    TFile *f1 = new TFile("tree.root");
    TTree *mytree = (TTree *)f1->Get("tree1");
    mytree->Print();
    
    TCut* ebeam_h = new TCut("ebeam > 150.2");
    TCut* ebeam_l = new TCut("ebeam < 149.8");
    
    TCanvas *c1 = new TCanvas("c1","Tree canvas", 800, 600);
    gStyle->SetOptStat(0);
    mytree->Draw("(px**2 + py**2 + pz**2)**(1/2)",*ebeam_h);
    c1->SaveAs("Ex4_histo_high.pdf");
    
    TCanvas *c2 = new TCanvas("c2","Tree canvas", 800, 600);
    mytree->Draw("(px**2 + py**2 + pz**2)**(1/2)",*ebeam_l);
    c2->SaveAs("Ex4_histo_low.pdf");
    
    TCanvas *c3 = new TCanvas("c3","Tree canvas", 800, 600);
    mytree->Draw("(px**2 + py**2 + pz**2)**(1/2)",*ebeam_l || *ebeam_h);
    c3->SaveAs("Ex4_histo_both.pdf");

    
    
}
