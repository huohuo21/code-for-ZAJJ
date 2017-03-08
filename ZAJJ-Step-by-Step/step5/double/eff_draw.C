#include "TFile.h"
#include <string>
#include "TH2.h"
#include <fstream>
#include <ostream>
#include <iostream>
#include "TMath.h"
#include "TCanvas.h"

using namespace std;

Double_t delta_normal(Double_t a, Double_t b)
{
        Double_t c = sqrt((b/a)*(1-(b/a))/a);
        return c;
}

struct out_data
{
	Double_t eff[4][4];
	Double_t eff_err[4][4];
};

out_data eff_draw(std::string name)
{
	out_data mine_data;
	TFile* file = TFile::Open(("../step2/fout_" + name + "_histo.root").c_str());
	TH2D* t2d = (TH2D*)file->Get("h11abseta");
	TH2D* t2d_post = (TH2D*)file->Get("h12abseta");
	Double_t row[4][4]={0};
	Double_t eff[4][4]={0};
	Double_t eff_delta[4][4]={0};
	for (int i=1; i<25; i++)
	{
		for (int j=1; j<25;j++)
		{
			if(i<10)
			{
				if(j<10) row[3][0] += t2d->GetBinContent(i,j);
				else if(j<13) row[2][0] += t2d->GetBinContent(i,j);
				else if(j<22) row[1][0] += t2d->GetBinContent(i,j);
				else if(j<25) row[0][0] += t2d->GetBinContent(i,j);
			}
			else if(i<13)
			{
				if(j<10) row[3][1] += t2d->GetBinContent(i,j);
				else if(j<13) row[2][1] += t2d->GetBinContent(i,j);
				else if(j<22) row[1][1] += t2d->GetBinContent(i,j);
				else if(j<25) row[0][1] += t2d->GetBinContent(i,j);
			}
			else if(i<22)
			{
				if(j<10) row[3][2] += t2d->GetBinContent(i,j);
				else if(j<13) row[2][2] += t2d->GetBinContent(i,j);
				else if(j<22) row[1][2] += t2d->GetBinContent(i,j);
				else if(j<25) row[0][2] += t2d->GetBinContent(i,j);
			}
			else
			{
				if(j<10) row[3][3] += t2d->GetBinContent(i,j);
				else if(j<13) row[2][3] += t2d->GetBinContent(i,j);
				else if(j<22) row[1][3] += t2d->GetBinContent(i,j);
				else if(j<25) row[0][3] += t2d->GetBinContent(i,j);
			}
		}
	}
	int row_post[4][4]={0};
	for (int i=1; i<25; i++)
	{
		for (int j=1; j<25;j++)
		{
			if(i<10)
			{
				if(j<10) row_post[3][0] += t2d_post->GetBinContent(i,j);
				else if(j<13) row_post[2][0] += t2d_post->GetBinContent(i,j);
				else if(j<22) row_post[1][0] += t2d_post->GetBinContent(i,j);
				else if(j<25) row_post[0][0] += t2d_post->GetBinContent(i,j);
			}
			else if(i<13)
			{
				if(j<10) row_post[3][1] += t2d_post->GetBinContent(i,j);
				else if(j<13) row_post[2][1] += t2d_post->GetBinContent(i,j);
				else if(j<22) row_post[1][1] += t2d_post->GetBinContent(i,j);
				else if(j<25) row_post[0][1] += t2d_post->GetBinContent(i,j);
			}
			else if(i<22)
			{
				if(j<10) row_post[3][2] += t2d_post->GetBinContent(i,j);
				else if(j<13) row_post[2][2] += t2d_post->GetBinContent(i,j);
				else if(j<22) row_post[1][2] += t2d_post->GetBinContent(i,j);
				else if(j<25) row_post[0][2] += t2d_post->GetBinContent(i,j);
			}
			else
			{
				if(j<10) row_post[3][3] += t2d_post->GetBinContent(i,j);
				else if(j<13) row_post[2][3] += t2d_post->GetBinContent(i,j);
				else if(j<22) row_post[1][3] += t2d_post->GetBinContent(i,j);
				else if(j<25) row_post[0][3] += t2d_post->GetBinContent(i,j);
			}
		}
	}
	for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                	eff[i][j] = row_post[i][j]/row[i][j];
			eff_delta[i][j] = delta_normal(row[i][j], row_post[i][j]);
		}

        }
	char buffer[256];
        sprintf(buffer, "eff_%s.txt",name.c_str());
	ofstream myfile(TString(buffer),ios::out);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if (i==0 && j==0) myfile<<"events before HLT"<<std::endl;
			myfile << row[i][j] << " ";
			if (j==3) myfile<<std::endl;
		}
		
	}
	for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                        if (i==0 && j==0) myfile<<"events after HLT"<<std::endl;
                        myfile << row_post[i][j] << " ";
                        if (j==3) myfile<<std::endl;
                }

        }
	for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                        if (i==0 && j==0) myfile<<"eff"<<std::endl;
                        myfile << eff[i][j] << " ";
                        if (j==3) myfile<<std::endl;
                }

        }
	for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                        if (i==0 && j==0) myfile<<"eff uncertainty"<<std::endl;
                        myfile << eff_delta[i][j] << " ";
                        if (j==3) myfile<<std::endl;
                }

        }
	for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                        mine_data.eff[i][j] = eff[i][j];
			mine_data.eff_err[i][j] = eff_delta[i][j];
                }

        }
	return mine_data;
}

void draw_eff(std::string name, out_data eff_data, out_data eff_mc)
{
	char buffer_1[256];
        sprintf(buffer_1, "eff_%s_MC.txt",name.c_str());
        ofstream myfile_1(TString(buffer_1),ios::out);
	TCanvas* c1 = new TCanvas("c","c",800,600);
        Double_t abseta1[5] = {0, 0.9, 1.2, 2.1, 2.4};
        Double_t abseta2[5] = {0, 0.9, 1.2, 2.1, 2.4};
        TH2D *h2D = new TH2D("2Dh","HLT_Mu17 behavior",4,abseta1,4,abseta2);
	Double_t SFs[4][4], SFs_err[4][4];
	for (Int_t i=0; i<4; i++)
	{
		for (Int_t j=0; j<4; j++)
		{
			SFs[i][j] = eff_data.eff[i][j]/eff_mc.eff[i][j];
			SFs_err[i][j] =  sqrt(eff_data.eff_err[i][j]*eff_data.eff_err[i][j]/(eff_mc.eff[i][j]*eff_mc.eff[i][j])+SFs[i][j]*SFs[i][j]*eff_mc.eff_err[i][j]*eff_mc.eff_err[i][j]/(eff_mc.eff[i][j]*eff_mc.eff[i][j]));
		}
	}
	for(Int_t i=0;i<4;i++)
        {
                for(Int_t j=0;j<4;j++)
                {
                        myfile_1 << SFs[i][j] << " ";
                        if (j==3) myfile_1<<std::endl;
                }

        }
	for(Int_t i=0;i<4;i++)
        {
                for(Int_t j=0;j<4;j++)
                {
                        myfile_1 << SFs_err[i][j] << " ";
                        if (j==3) myfile_1<<std::endl;
                }

        }
	for (int i=0; i<4; i++)
        {
                for (int j=0; j<4; j++)
                {
                        h2D->Fill(abseta1[j]+0.1, abseta2[i]+0.1, SFs[3-i][j]);
                        h2D->SetBinError(j+1,i+1,SFs_err[3-i][j]);
                }
        }
	h2D->SetMinimum(0.7);
        h2D->SetMaximum(1.0);
        h2D->SetStats(kFALSE);
        h2D->SetOption("colztexte");
        h2D->SetContour(20);
        h2D->SetContourLevel(0,0.7);
        h2D->SetContourLevel(1,0.715);
        h2D->SetContourLevel(2,0.73);
        h2D->SetContourLevel(3,0.745);
        h2D->SetContourLevel(4,0.76);
        h2D->SetContourLevel(5,0.775);
        h2D->SetContourLevel(6,0.79);
        h2D->SetContourLevel(7,0.805);
        h2D->SetContourLevel(8,0.82);
        h2D->SetContourLevel(9,0.835);
        h2D->SetContourLevel(10,0.85);
        h2D->SetContourLevel(11,0.865);
        h2D->SetContourLevel(12,0.88);
	h2D->SetContourLevel(13,0.895);
        h2D->SetContourLevel(14,0.91);
        h2D->SetContourLevel(15,0.925);
        h2D->SetContourLevel(16,0.94);
        h2D->SetContourLevel(17,0.955);
        h2D->SetContourLevel(18,0.97);
        h2D->SetContourLevel(19,0.985);
        h2D->SetContourLevel(20,1.);
        h2D->Draw("");
        h2D->SetContourLevel(0,0);
        h2D->GetXaxis()->SetTitle("|#eta1|");
        h2D->GetYaxis()->SetTitle("|#eta2|");
        char buffer[256];
        sprintf(buffer, "HLT_di-muon_%s.png", name.c_str());
        c1->SaveAs(buffer);
}


int main()
{
	out_data e_DY, e_B, e_C, e_D, e_E, e_F, e_G, e_H;
	e_DY =  eff_draw("DY");
	e_B  =	eff_draw("DMuB");
	e_C  =	eff_draw("DMuC");
	e_D  =	eff_draw("DMuD");
	e_E  =	eff_draw("DMuE");
	e_F  =	eff_draw("DMuF");
	e_G  =	eff_draw("DMuG");
	e_H  =	eff_draw("DMuH");
	draw_eff("B", e_B, e_DY);
	draw_eff("C", e_C, e_DY);
	draw_eff("D", e_D, e_DY);
	draw_eff("E", e_E, e_DY);
	draw_eff("F", e_F, e_DY);
	draw_eff("G", e_G, e_DY);
	draw_eff("H", e_H, e_DY);
	return 1;
}
