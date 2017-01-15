#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
using namespace std;

void mjj_draw(){

	stringstream ss;
	string num1;
	int event;
	double pweight[703]={0.};
	double genjet_pt[6]={0.}, genjet_eta[6]={0.},genjet_phi[6]={0.},genjet_e[6]={0.};
	TFile *file = new TFile("AQGC.root");
	TTree *ZPKUCandidates = (TTree*) file->Get("treeDumper/ZPKUCandidates");
	TCanvas* c[16];

	ZPKUCandidates->SetBranchAddress("event",&event);
	ZPKUCandidates->SetBranchAddress("pweight",pweight);
	ZPKUCandidates->SetBranchAddress("genjet_pt",genjet_pt);
	ZPKUCandidates->SetBranchAddress("genjet_eta",genjet_eta);
	ZPKUCandidates->SetBranchAddress("genjet_phi",genjet_phi);
	ZPKUCandidates->SetBranchAddress("genjet_e",genjet_e);

	int entries= ZPKUCandidates->GetEntries();

	TH1D* AQGC[16][16];
	double binmin=0., binmax=4.;
	double nbin= 20.0;
	char Tname[20], Hname[20],title[20],pngname[20];

	TH1D* AQGC_sm = new TH1D("AQGC_sm","AQGC_sm",nbin,binmin,binmax);
	AQGC_sm->Sumw2();
	for(int j=0;j<16;j++){
		if(j<8) sprintf(Tname,"AQGC_FM%d",j);
		else if(j<11) sprintf(Tname,"AQGC_FT%d",j-8);
		else sprintf(Tname,"AQGC_FT%d",j-6);
		c[j] = new TCanvas(Tname, "AQGC",1000,1000);
		for (int i=0;i<16;i++)
			{
				if(i<8) sprintf(Hname,"AQGC_FM%d",i);
				else if(i<11) sprintf(Hname,"AQGC_FT%d",i-8);
				else sprintf(Hname,"AQGC_FT%d",i-6);
				AQGC[j][i]=new TH1D(Hname, "AQGC", nbin,binmin,binmax);
				AQGC[j][i]->Sumw2();
			}
	}

	double Mjj=0.;
	double genjet1_pt=0.,genjet1_eta=0.,genjet1_phi=0.,genjet1_e=0.;
	double genjet2_pt=0.,genjet2_eta=0.,genjet2_phi=0.,genjet2_e=0.;
	for (int i=0;i<entries;i++){
		ZPKUCandidates->GetEntry(i);
		genjet1_pt=genjet_pt[0];
		genjet1_eta=genjet_eta[0];
		genjet1_phi=genjet_phi[0];
		genjet1_e=genjet_e[0];
		genjet2_pt=genjet_pt[1];
		genjet2_eta=genjet_eta[1];
		genjet2_phi=genjet_phi[1];
		genjet2_e=genjet_e[1];
		TLorentzVector J1, J2;
		J1.SetPtEtaPhiE(genjet1_pt,genjet1_eta,genjet1_phi,genjet1_e);
		J2.SetPtEtaPhiE(genjet2_pt,genjet2_eta,genjet2_phi,genjet2_e);
		Mjj=(J1+J2).M()/1000.;
		AQGC_sm->Fill(Mjj,pweight[446]);
		for (int jj=0;jj<16;jj++){
			for(int j=0;j<16;j++){
				AQGC[jj][j]->Fill(Mjj,pweight[446+j+jj*16+1]);
			}
		}
	}

	for(int i=0;i<16;i++)
	{
		c[i]->cd();
		c[i]->SetGrid();
		c[i]->SetTicks(1,1);
		c[i]->SetLogy();
		if(i<8) sprintf(title,"AQGC_FM%d",i);
		else if(i<11) sprintf(title,"AQGC_FT%d",i-8);
		else sprintf(title,"AQGC_FT%d",i-6);
		AQGC[i][0]->SetTitle(title);
		AQGC[i][0]->GetYaxis()->SetTitle("a.u.");
		AQGC[i][0]->GetYaxis()->CenterTitle();
		AQGC[i][0]->GetXaxis()->SetTitle("Mjj [TeV] ");
		AQGC[i][0]->GetXaxis()->CenterTitle();
		AQGC[i][0]->GetXaxis()->SetTitleOffset(1.);
		AQGC[i][0]->GetYaxis()->SetTitleOffset(1.2);
		AQGC[i][0]->SetStats(0);
		AQGC[i][0]->SetLineColor(2);
		AQGC[i][0]->GetYaxis()->SetRangeUser(0.0001,4000);
		AQGC[i][0]->Draw("HIST");

		AQGC_sm->SetLineColor(1);
		AQGC_sm->Draw("HIST same");
		for(int ii=1;ii<9;ii++){
			AQGC[i][ii]->SetLineColor(ii+1);
			AQGC[i][ii]->Draw("HIST same");
		}

		TLegend *l1 = new TLegend(0.14,0.14,0.32,0.45);
		l1->SetBorderSize(1);
		l1->SetFillColor(0);	
		l1->AddEntry(AQGC[i][0],title);
		l1->AddEntry(AQGC[i][1],title);
		l1->AddEntry(AQGC[i][2],title);
		l1->AddEntry(AQGC[i][3],title);
		l1->AddEntry(AQGC[i][4],title);
		l1->AddEntry(AQGC[i][5],title);
		l1->AddEntry(AQGC[i][6],title);
		l1->AddEntry(AQGC[i][7],title);
		l1->AddEntry(AQGC_sm,"SM");
		l1->Draw();
		if(i<8) sprintf(pngname,"AQGC_mjj_FM%d.png",i);
		else if(i<11) sprintf(pngname,"AQGC_mjj_FT%d.png",i-8);
		else sprintf(pngname,"AQGC_mjj_FT%d.png",i-6);
		c[i]->Update();
    	c[i]->SaveAs(pngname);
	}

}
