#include "TH1.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include "TLegend.h"
#include "THStack.h"
#include "CMSTDRStyle.h"
#include "CMS_lumi.C"
#include "TArrow.h"
#include "TLatex.h"
using namespace std;

void cmsLumi(bool channel) 
{
        TLatex latex;
        latex.SetNDC();
        latex.SetTextSize(0.04);
        latex.SetLineWidth(2);
        float lumiel=35.8;
        float lumimu=35.8;
        int beamcomenergytev=13;
        latex.SetTextAlign(31); 
        latex.SetTextAlign(11);
        latex.DrawLatex(0.18,0.82,"Preliminary");
        latex.DrawLatex(0.18,0.86,"CMS");
        latex.SetTextSize(0.03);
        latex.DrawLatex(0.76,0.92,Form("35.9 fb^{-1} (%d TeV)", (beamcomenergytev)));
}

TH1F* construct_th(std::string str, TDirectoryFile* fout){
	TDirectoryFile* d1 = (TDirectoryFile*)fout->Get("ch1");
	TDirectoryFile* d2 = (TDirectoryFile*)fout->Get("ch2");
	TDirectoryFile* d3 = (TDirectoryFile*)fout->Get("ch3");
	TDirectoryFile* d4 = (TDirectoryFile*)fout->Get("ch4");
	TDirectoryFile* d5 = (TDirectoryFile*)fout->Get("ch5");
	TDirectoryFile* d6 = (TDirectoryFile*)fout->Get("ch6");
	TDirectoryFile* d7 = (TDirectoryFile*)fout->Get("ch7");
	TDirectoryFile* d8 = (TDirectoryFile*)fout->Get("ch8");
	TH1F* t_temp = new TH1F(str.c_str(),str.c_str(),8,0,8);
//	t_temp->Sumw2();
	TH1F* tp;
	if(d1->GetObjectChecked(str.c_str(),"TH1F")!=0){
		tp = (TH1F*)d1->Get(str.c_str());
		t_temp->SetBinContent(1, tp->GetBinContent(1));
	        t_temp->SetBinError(1, tp->GetBinError(1));
	}
	else{
		t_temp->SetBinContent(1, 0);
        	t_temp->SetBinError(1, 0);
	}


	if(d2->GetObjectChecked(str.c_str(),"TH1F")!=0){
		tp = (TH1F*)d2->Get(str.c_str());
		t_temp->SetBinContent(2, tp->GetBinContent(1));
	        t_temp->SetBinError(2, tp->GetBinError(1));
	}
	else{
		t_temp->SetBinContent(2, 0);
        	t_temp->SetBinError(2, 0);
	}

	if(d3->GetObjectChecked(str.c_str(),"TH1F")!=0){
		tp = (TH1F*)d3->Get(str.c_str());
		t_temp->SetBinContent(3, tp->GetBinContent(1));
	        t_temp->SetBinError(3, tp->GetBinError(1));
	}
	else{
		t_temp->SetBinContent(3, 0);
        	t_temp->SetBinError(3, 0);
	}

	if(d4->GetObjectChecked(str.c_str(),"TH1F")!=0){
		tp = (TH1F*)d4->Get(str.c_str());
		t_temp->SetBinContent(4, tp->GetBinContent(1));
	        t_temp->SetBinError(4, tp->GetBinError(1));
	}
	else{
		t_temp->SetBinContent(4, 0);
        	t_temp->SetBinError(4, 0);
	}

	if(d5->GetObjectChecked(str.c_str(),"TH1F")!=0){
		tp = (TH1F*)d5->Get(str.c_str());
		t_temp->SetBinContent(5, tp->GetBinContent(1));
	        t_temp->SetBinError(5, tp->GetBinError(1));
	}
	else{
		t_temp->SetBinContent(5, 0);
        	t_temp->SetBinError(5, 0);
	}

	if(d6->GetObjectChecked(str.c_str(),"TH1F")!=0){
		tp = (TH1F*)d6->Get(str.c_str());
		t_temp->SetBinContent(6, tp->GetBinContent(1));
	        t_temp->SetBinError(6, tp->GetBinError(1));
	}
	else{
		t_temp->SetBinContent(6, 0);
        	t_temp->SetBinError(6, 0);
	}

	if(d7->GetObjectChecked(str.c_str(),"TH1F")!=0){
		tp = (TH1F*)d7->Get(str.c_str());
		t_temp->SetBinContent(7, tp->GetBinContent(1));
	        t_temp->SetBinError(7, tp->GetBinError(1));
	}
	else{
		t_temp->SetBinContent(7, 0);
        	t_temp->SetBinError(7, 0);
	}

	if(d8->GetObjectChecked(str.c_str(),"TH1F")!=0){
		tp = (TH1F*)d8->Get(str.c_str());
		t_temp->SetBinContent(8, tp->GetBinContent(1));
	        t_temp->SetBinError(8, tp->GetBinError(1));
	}
	else{
		t_temp->SetBinContent(8, 0);
        	t_temp->SetBinError(8, 0);
	}

	return t_temp;
	
}

int main(){
	setTDRStyle();
	TFile* fout = TFile::Open("../fitDiagnostics.root");
//	TDirectoryFile* ds = (TDirectoryFile*)fout->Get("shapes_prefit");
	TDirectoryFile* ds = (TDirectoryFile*)fout->Get("shapes_fit_s");
	const char *name[8]={"500~800","800~1200","1200~2000","500~800","800~1200","1200~2000","500~1200","1200~2000"};

	TH1F* t_ZA = construct_th("QCD", ds);
	t_ZA->SetFillColor(kBlue-6);
        t_ZA->SetMarkerColor(kBlue-6);
        t_ZA->SetLineColor(kBlue-6);

	TH1F* t_VBS = construct_th("VBS", ds);
	t_VBS->SetFillColor(kRed-9);
        t_VBS->SetMarkerColor(kRed-9);
        t_VBS->SetLineColor(kRed-9);
        t_VBS->SetMarkerStyle(21);

	TH1F* t_VV = construct_th("VV", ds);
	t_VV->SetFillColor(40);
        t_VV->SetMarkerColor(40);
        t_VV->SetLineColor(40);

	TH1F* t_TTA = construct_th("TTA", ds);
	t_TTA->SetFillColor(kCyan);
        t_TTA->SetMarkerColor(kCyan);
        t_TTA->SetLineColor(kCyan);

	TH1F* t_WA= construct_th("WA", ds);
	t_WA->SetFillColor(kPink+8);
        t_WA->SetMarkerColor(kPink+8);
        t_WA->SetLineColor(kPink+8);

	TH1F* t_ST = construct_th("ST", ds);
	t_ST->SetFillColor(kGreen+2);
        t_ST->SetMarkerColor(kGreen+2);
        t_ST->SetLineColor(kGreen+2);
	for(Int_t i=1;i<=9;i++){ t_ST->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TH1F* t_plj = construct_th("non_prompt", ds);
	t_plj->SetFillColor(kYellow-7);
        t_plj->SetMarkerColor(kYellow-7);
        t_plj->SetLineColor(kYellow-7);

	TH1F* t_data = new TH1F("data","data",8,0,8);
	t_data->SetBinContent(1,19);
	t_data->SetBinContent(2,10);
	t_data->SetBinContent(3,2);
	t_data->SetBinContent(4,20);
	t_data->SetBinContent(5,5);
	t_data->SetBinContent(6,4);
	t_data->SetBinContent(7,6);
	t_data->SetBinContent(8,3);

	THStack* hs = new THStack("hs", "");
        hs->SetMaximum(t_ZA->GetBinContent(1)*2.5);
        hs->Add(t_ST);
        hs->Add(t_TTA);
        hs->Add(t_VV);
        hs->Add(t_WA);
        hs->Add(t_plj);
        hs->Add(t_ZA);
        hs->Add(t_VBS);

        gStyle->SetPadBorderMode(0);
        gStyle->SetOptStat(0);
        gStyle->SetPadTickX(1);
        gStyle->SetPadTickY(1);
        gStyle->SetPadTickX(1);
        gStyle->SetPadTickY(1);
        gStyle->SetAxisColor(1, "XYZ");
        gStyle->SetStripDecimals(kTRUE);
        gStyle->SetTickLength(0.03, "XYZ");
        gStyle->SetNdivisions(510, "XYZ");

	TCanvas* c1=new TCanvas("","",800,800);
        c1->cd();
        TPad* fPad1 = new TPad("pad1", "", 0.00, 0.00, 0.99, 0.99);
        fPad1->Draw();
        CMS_lumi(fPad1, 4, 0, "35.9");
        hs->Draw("HIST");
        hs->GetYaxis()->SetTitleOffset(0.95);
        hs->GetYaxis()->SetTitle("Events /bin");
        hs->GetXaxis()->SetTitle("m_{jj} (GeV)");
        hs->GetXaxis()->SetTitleOffset(1.3);
        hs->GetXaxis()->SetTitleSize(0.04);

	t_data->Draw("SAME pe");	

	TH1D* htemp = (TH1D*)(hs->GetStack()->Last());
        htemp->SetBinErrorOption(TH1::kPoisson);
        const int binsize = htemp->GetSize()-2;
        Double_t x[binsize];
        Double_t y[binsize];
        Double_t xerror[binsize];
        Double_t yerror[binsize];
        for(int i=0;i<binsize;i++)
        {
                x[i]=htemp->GetBinCenter(i+1);
                y[i]=htemp->GetBinContent(i+1);
                xerror[i]=0.5*htemp->GetBinWidth(i+1);
                yerror[i]=htemp->GetBinError(i+1);
                if(htemp->GetBinContent(i+1)==0)
                {yerror[i]=0.;}
        }
        TGraphErrors* gr = new TGraphErrors(binsize, x, y, xerror, yerror);
        gr->SetFillColor(1);
        gr->SetFillStyle(3005);
        gr->Draw("SAME 2");

        TLegend* leg1 = new TLegend(0.74, 0.72, 0.94, 0.88);
        TLegend* leg2 = new TLegend(0.54, 0.72, 0.74, 0.88);
        leg1->SetMargin(0.4);
        leg2->SetMargin(0.4);
        leg1->AddEntry(gr,"Stat. Unc.", "f");
        leg1->AddEntry(t_ST, "ST", "f");
        leg1->AddEntry(t_TTA, "TT#gamma", "f");
        leg1->AddEntry(t_VV, "VV", "f");
        leg2->AddEntry(t_WA, "QCD W#gamma", "f");
        leg2->AddEntry(t_plj, "Fake Photon", "f");
        leg2->AddEntry(t_ZA, "QCD Z#gamma", "f");
	leg2->AddEntry(t_VBS, "EWK Z#gamma");
        leg1->SetFillColor(kWhite);
        leg1->Draw();
        leg2->SetFillColor(kWhite);
        leg2->Draw();

        TLatex latex1;
        latex1.SetTextAlign(12);
        latex1.SetTextSize(0.04);
        TArrow* line1 = new TArrow(t_ZA->GetBinLowEdge(4),0,t_ZA->GetBinLowEdge(4),2.5*t_ZA->GetMaximum(),0.07,"") ;
        TArrow* line2 = new TArrow(t_ZA->GetBinLowEdge(7),0,t_ZA->GetBinLowEdge(7),2.*t_ZA->GetMaximum(),0.07,"") ;
        line1->SetLineColor(1);
        line1->SetLineWidth(3);
        line1->SetLineStyle(7);
        line2->SetLineColor(1);
        line2->SetLineWidth(3);
        line2->SetLineStyle(7);

        cmsLumi(0);

        latex1.DrawLatexNDC(0.15,0.5,"#font[12]{#Delta#eta_{jj} #in (2.5, 4.5)}");
        latex1.DrawLatexNDC(0.45,0.5,"#font[12]{#Delta#eta_{jj} #in (4.5, 6)}");
        latex1.DrawLatexNDC(0.75,0.5,"#font[12]{#Delta#eta_{jj} > 6}");

        line1->Draw();
        line2->Draw();

//        c1->SaveAs("eb.png");
        c1->SaveAs("eb_post.png");

	
	return 1;
}
