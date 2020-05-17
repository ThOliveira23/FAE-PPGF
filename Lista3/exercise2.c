{
    
// Data values
std::vector<double> x {-0.22,0.05,0.25,0.35,0.5,0.61,0.7,0.85,0.89,0.95};
std::vector<double> y {1,2.9,5.6,7.4,9,9.6,8.7,6.3,4.5,1};
std::vector<double> ex {0.05,0.10,0.07,0.07,0.04,0.05,0.06,0.07,0.08,0.05};
std::vector<double> ey {0.8,0.7,0.6,0.5,0.4,0.4,0.5,0.6,0.7,0.8};
const Int_t n = x.size();
    
// For the simple graph
       
TGraph g(n,x.data(),y.data());
TCanvas c1("Exercise 2 Graph","Exercise 2 Graph",800,600);
g.SetTitle("Exercise 2 Graph");
g.SetMarkerStyle(21);
g.SetMarkerColor(kBlack);
g.Draw("AP"); // Points
c1.SaveAs("Ex2_graph_points.pdf");

TCanvas c2("Exercise 2 Graph - line","Exercise 2 Graph",800,600);
g.Draw("AL"); // Line
c2.SaveAs("Ex2_graph_line.pdf");
    
TCanvas c3("Exercise 2 Graph","Exercise 2 Graph",800,600);
g.Draw(); // Points + Line
c3.SaveAs("Ex2_graph_all.pdf");

    
// For the Graph with errors
    
TGraphErrors gr(n,x.data(),y.data(),ex.data(),ey.data());
gr.SetMarkerStyle(21);
gr.SetMarkerColor(kBlack);
gr.SetTitle("Exercise 2 GraphErrors");

TCanvas cr("Exercise 2 GraphErrors","",800,600);
gr.Draw();
cr.SaveAs("Ex2_graph_errors.pdf");
    
    
    
    
}

