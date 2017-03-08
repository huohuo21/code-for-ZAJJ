#include <string>
#include "TFile.h"
#include "TDirectoryFile.h" 
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TH2.h"
#include "math.h"
#include <fstream>
#include <ostream>
#include <iostream>

using namespace std;

struct eff_error
{
	double eff_x[4];
	double eff_y[4];
	double error_l[4];
	double error_h[4];
	double error[4];
};

eff_error read(std::string name)
{
	TFile* _file0 = TFile::Open(("TnP_MuonTrigger_noptbin_"+name+".root").c_str());
//	TFile* _file0 = TFile::Open("TnP_MuonTrigger_noptbin_B.root");
	TDirectoryFile*dir0=(TDirectoryFile*)_file0->Get("tpTree");
	TDirectoryFile*dir1=(TDirectoryFile*)dir0->Get("trigger_pt_eta");
	TDirectoryFile*dir2=(TDirectoryFile*)dir1->Get("fit_eff_plots");
	TCanvas*can=(TCanvas*)dir2->Get("abseta_PLOT_Tight2012_pass_&_tag_Mu17_pass");
	TGraphAsymmErrors*gra=(TGraphAsymmErrors*)can->GetPrimitive("hxy_fit_eff");
	double xx[4], yy[4], err_l[4], err_h[4];
	eff_error err_out;
	for (int i=0; i<4; i++)
	{
		gra->GetPoint(i, xx[i], yy[i]);
		err_out.eff_x[i] = xx[i];
		err_out.eff_y[i] = yy[i];
		err_out.error_l[i] = gra->GetErrorYlow(i);
		err_out.error_h[i] = gra->GetErrorYhigh(i);
		err_out.error[i] =(err_out.error_l[i]+err_out.error_h[i])/2;		
	}
	return err_out;
}


void draw_eff(std::string name, eff_error eff_data, eff_error eff_mc)
{
	TCanvas* c1 = new TCanvas("c","c",800,600);
	char buffer_1[256];
        sprintf(buffer_1, "eff_%s_MC.txt",name.c_str());
        ofstream myfile_1(TString(buffer_1),ios::out);
	double abseta1[5] = {0, 0.9, 1.2, 2.1, 2.4};
	double abseta2[5] = {0, 0.9, 1.2, 2.1, 2.4};
	TH2D *h2D = new TH2D("2Dh","HLT_Mu17 behavior",4,abseta1,4,abseta2);
	double SFs[4], SFs_err[4];
	double SFs_eff[4][4]={0,},SFs_eff_err[4][4]={0};
	for(int i=0; i<4; i++)
	{
		SFs[i] = eff_data.eff_y[i]/eff_mc.eff_y[i];
		SFs_err[i] = sqrt(eff_data.error[i]*eff_data.error[i]/(eff_mc.eff_y[i]*eff_mc.eff_y[i])+SFs[i]*SFs[i]*eff_mc.error[i]*eff_mc.error[i]/(eff_mc.eff_y[i]*eff_mc.eff_y[i]));
	}
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			h2D->Fill(abseta1[i]+0.1, abseta2[j]+0.1, SFs[i]+SFs[j]-SFs[i]*SFs[j]);
			SFs_eff[i][j]= SFs[i]+SFs[j]-SFs[i]*SFs[j];
			SFs_eff_err[i][j]=sqrt((1+SFs[i]*SFs[i])*SFs_err[j]*SFs_err[j]+(1+SFs[j]*SFs[j])*SFs_err[i]*SFs_err[i]);
			h2D->SetBinError(i+1,j+1,sqrt((1+SFs[i]*SFs[i])*SFs_err[j]*SFs_err[j]+(1+SFs[j]*SFs[j])*SFs_err[i]*SFs_err[i]));
		}
	}
	for(Int_t i=0;i<4;i++)
        {
                for(Int_t j=0;j<4;j++)
                {
                        myfile_1 << SFs_eff[3-i][j] << " ";
                        if (j==3) myfile_1<<std::endl;
                }

        }
        for(Int_t i=0;i<4;i++)
        {
                for(Int_t j=0;j<4;j++)
                {
                        myfile_1 << SFs_eff_err[3-i][j] << " ";
                        if (j==3) myfile_1<<std::endl;
                }

        }
	h2D->SetMinimum(0.965);
	h2D->SetMaximum(1.0);
	h2D->SetStats(kFALSE);
	h2D->SetOption("colztexte");
	h2D->SetContour(21);
	h2D->SetContourLevel(0,0.97);
	h2D->SetContourLevel(1,0.9715);
	h2D->SetContourLevel(2,0.973);
	h2D->SetContourLevel(3,0.9745);
	h2D->SetContourLevel(4,0.976);
	h2D->SetContourLevel(5,0.9775);
	h2D->SetContourLevel(6,0.979);
	h2D->SetContourLevel(7,0.9805);
	h2D->SetContourLevel(8,0.982);
	h2D->SetContourLevel(9,0.9835);
	h2D->SetContourLevel(10,0.985);
	h2D->SetContourLevel(11,0.9865);
	h2D->SetContourLevel(12,0.988);
	h2D->SetContourLevel(13,0.9895);
	h2D->SetContourLevel(14,0.991);
	h2D->SetContourLevel(15,0.9925);
	h2D->SetContourLevel(16,0.994);
	h2D->SetContourLevel(17,0.9955);
	h2D->SetContourLevel(18,0.997);
	h2D->SetContourLevel(19,0.9985);
	h2D->SetContourLevel(20,1.);
	h2D->Draw("");
	h2D->SetContourLevel(0,0);
	h2D->GetXaxis()->SetTitle("|#eta1|");
	h2D->GetYaxis()->SetTitle("|#eta2|");
	char buffer[256];
	sprintf(buffer, "HLT_Mu17_%s.png", name.c_str());
	c1->SaveAs(buffer);

}


int main()
{
	eff_error eff_B, eff_C, eff_D, eff_E,eff_F, eff_G, eff_H, eff_MC;
	eff_B = read("B");
	eff_C = read("C");
	eff_D = read("D");
	eff_E = read("E");
	eff_F = read("F");
	eff_G = read("G");
	eff_H = read("H");
	eff_MC = read("MC");
	draw_eff("B", eff_B, eff_MC);
	draw_eff("C", eff_C, eff_MC);
	draw_eff("D", eff_D, eff_MC);
	draw_eff("E", eff_E, eff_MC);
	draw_eff("F", eff_F, eff_MC);
	draw_eff("G", eff_G, eff_MC);
	draw_eff("H", eff_H, eff_MC);
	return 1;
}
