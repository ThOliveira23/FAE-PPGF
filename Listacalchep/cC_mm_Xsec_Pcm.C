#include <string>
#include <fstream>
#include <iostream>
#include <TMath.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TLatex.h>
#include <TLine.h>
void cC_mm_Xsec_Pcm(void)
{
 TCanvas *Can = new TCanvas("c","c,C ->m,M",200,10,600,400);
 double xMin=1.000000E+02, xMax=6.500000E+03, yMin=4.268041E-07, yMax=2.674222E-01;
 char buff[2000];
 double  X0[100],dX0[100];
 for(int i=0;i<100;i++){ X0[i]=xMin+(i+0.5)*(xMax-xMin)/100; dX0[i]=(xMax-xMin)/3./100;}
 double Xtext = xMin+0.3*(xMax-xMin);
 double Ytext= yMax;
 Can->SetLogy();
 double dYtext=pow(yMax/yMin,0.055);
 TH1F *hr = Can->DrawFrame(xMin,yMin,xMax,yMax);
 hr->SetTitle("#sigma_{c,C #rightarrow m,M} x P_{CM}");
 hr->SetXTitle("Pcm");
 hr->SetYTitle("Cross Section [pb]");
 double  Y0[100];
 FILE*f=fopen("cC_mm_Xsec_Pcm.tab","r");
 for(int i=0;i<100;)
 {
  fscanf(f,"%[^\n]%*c",buff);
  if(buff[0]!='#') {  sscanf(buff," %lf"  ,Y0+i); i++;    }
 }
 fclose(f);
 TLatex ltx;
 ltx.SetTextFont(42);
 ltx.SetTextSize(0.04);
int i0,i1;
   for(i0=0;!isfinite(Y0[i0]);i0++);
   for(i1=99;!isfinite(Y0[i1]);i1--);
   TGraph *gr0 = new TGraph (1+i1-i0,X0+i0,Y0+i0);
   gr0->SetLineColor(1);
   gr0->Draw("L");
 Can->Print("cC_mm_Xsec_Pcm.pdf");
}
