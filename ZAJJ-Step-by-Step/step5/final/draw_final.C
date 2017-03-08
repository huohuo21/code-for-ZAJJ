#include "TCanvas.h"
#include "TH2.h"
#include <stdio.h>

void draw_final()
{
	double eff[4][4]={{0.89769, 0.92694, 0.90051, 0.79831},
			  {0.91126, 0.93383, 0.85536, 0.91347},
			  {0.90712, 0.83554, 0.92349, 0.90659},
			  {0.86068, 0.90411, 0.91615, 0.90592}};
	double eff_err[4][4]={{0.00958, 0.01253, 0.00898, 0.01495},
			      {0.00456, 0.00716, 0.00517, 0.01025},
			      {0.00638, 0.01017, 0.00725, 0.01524},
			      {0.00378, 0.00635, 0.00453, 0.01079}};
	double eff_lumi[4][4]={{0.91475,0.93714, 0.92164, 0.82913},
			       {0.92557,0.94285, 0.86979, 0.93144},
			       {0.91695,0.84456, 0.93603, 0.91482},
			       {0.87777,0.91841, 0.92818, 0.92402}};
	double eff_lumi_err[4][4]={{0.01021,0.01324, 0.00945,0.01552},
				   {0.00448,0.00732, 0.00513,0.00992},
				   {0.00664,0.01059, 0.00736,0.01526},
				   {0.00379,0.00660, 0.00446,0.01052}};
	TCanvas* c1 = new TCanvas("c1","c1",800,600);
	TCanvas* c2 = new TCanvas("c2","c2",800,600);
	double abseta1[5] = {0, 0.9, 1.2, 2.1, 2.4};
        double abseta2[5] = {0, 0.9, 1.2, 2.1, 2.4};
	TH2D *h2D = new TH2D("2Dh1","even average SFs",4,abseta1,4,abseta2);
	TH2D *h2Dlumi = new TH2D("2Dh2","lumi average SFs",4,abseta1,4,abseta2);
	for (int i=0; i<4; i++)
        {
                for (int j=0; j<4; j++)
                {
                        h2D->Fill(abseta1[i]+0.1, abseta2[j]+0.1, eff[3-j][i]);
			cout<<eff[3-j][i]<<endl;
                        h2D->SetBinError(i+1,j+1,eff_err[3-j][i]);
                }
        }
	for (int i=0; i<4; i++)
        {
                for (int j=0; j<4; j++)
                {
                        h2Dlumi->Fill(abseta1[i]+0.1, abseta2[j]+0.1, eff_lumi[3-j][i]);
                        h2Dlumi->SetBinError(i+1,j+1,eff_lumi_err[3-j][i]);
                }
        }
	h2D->SetMinimum(0.78);
        h2D->SetMaximum(0.96);
        h2D->SetStats(kFALSE);
        h2D->SetOption("colztexte");
        h2D->SetContour(19);
        h2D->SetContourLevel(0,0.78);
        h2D->SetContourLevel(1,0.79);
        h2D->SetContourLevel(2,0.80);
        h2D->SetContourLevel(3,0.81);
        h2D->SetContourLevel(4,0.82);
        h2D->SetContourLevel(5,0.83);
        h2D->SetContourLevel(6,0.84);
        h2D->SetContourLevel(7,0.85);
        h2D->SetContourLevel(8,0.86);
        h2D->SetContourLevel(9,0.87);
        h2D->SetContourLevel(10,0.88);
        h2D->SetContourLevel(11,0.89);
        h2D->SetContourLevel(12,0.90);
        h2D->SetContourLevel(13,0.91);
        h2D->SetContourLevel(14,0.92);
        h2D->SetContourLevel(15,0.93);
        h2D->SetContourLevel(16,0.94);
        h2D->SetContourLevel(17,0.95);
        h2D->SetContourLevel(18,0.96);
	c1->cd();
        h2D->Draw("");
	h2D->SetContourLevel(0,0);
        h2D->GetXaxis()->SetTitle("|#eta1|");
        h2D->GetYaxis()->SetTitle("|#eta2|");
        c1->SaveAs("even_average_SFs.png");

	h2Dlumi->SetMinimum(0.78);
        h2Dlumi->SetMaximum(0.96);
        h2Dlumi->SetStats(kFALSE);
	h2Dlumi->SetOption("colztexte");
	h2Dlumi->SetContour(19);
        h2Dlumi->SetContourLevel(0,0.78);
        h2Dlumi->SetContourLevel(1,0.79);
        h2Dlumi->SetContourLevel(2,0.80);
        h2Dlumi->SetContourLevel(3,0.81);
        h2Dlumi->SetContourLevel(4,0.82);
        h2Dlumi->SetContourLevel(5,0.83);
        h2Dlumi->SetContourLevel(6,0.84);
        h2Dlumi->SetContourLevel(7,0.85);
        h2Dlumi->SetContourLevel(8,0.86);
        h2Dlumi->SetContourLevel(9,0.87);
        h2Dlumi->SetContourLevel(10,0.88);
        h2Dlumi->SetContourLevel(11,0.89);
        h2Dlumi->SetContourLevel(12,0.90);
        h2Dlumi->SetContourLevel(13,0.91);
        h2Dlumi->SetContourLevel(14,0.92);
        h2Dlumi->SetContourLevel(15,0.93);
        h2Dlumi->SetContourLevel(16,0.94);
        h2Dlumi->SetContourLevel(17,0.95);
        h2Dlumi->SetContourLevel(18,0.96);
	c2->cd();
        h2Dlumi->Draw("");
	h2Dlumi->SetContourLevel(0,0);
        h2Dlumi->GetXaxis()->SetTitle("|#eta1|");
        h2Dlumi->GetYaxis()->SetTitle("|#eta2|");
        c2->SaveAs("lumi_average_SFs.png");
	TFile fout("di-lep_trigger.root", "RECREATE");
	fout.cd();
	h2D->Write();
	h2Dlumi->Write();
	fout.Close();
}
