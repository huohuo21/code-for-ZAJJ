#include <string>
#include <iostream>
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH2.h"
void check_data_relevant(){
	std::string pathToTree = "../../ZA_plot/outTree/";
	TFile* f = TFile::Open((pathToTree+"outDMu.root").c_str());
	TTree* t1 = (TTree*)f->Get("demo");

	Double_t scalef;
	Int_t nVtx;
	Double_t theWeight;
	Double_t lumiWeight;
	Double_t pileupWeight;
	Double_t photon_pt[6];
	Double_t photon_eta[6];
	Double_t photon_phi[6];
	Double_t photon_e[6];
	Bool_t photon_pev[6];
	Bool_t photon_pevnew[6];
	Bool_t photon_ppsv[6];
	Bool_t photon_iseb[6];
	Bool_t photon_isee[6];
	Double_t photon_hoe[6];
	Double_t photon_sieie[6];
	Double_t photon_sieie2[6];
	Double_t photon_chiso[6];
	Double_t photon_nhiso[6];
	Double_t photon_phoiso[6];
	Int_t photon_istrue[6];
	Int_t photon_isprompt[6];
	Double_t photon_drla[6];
	Double_t photon_drla2[6];
	Double_t photon_mla[6];
	Double_t photon_mla2[6];
	Double_t photon_mva[6]; 

	t1->SetBranchAddress("scalef", &scalef);
	t1->SetBranchAddress("nVtx", &nVtx);
	t1->SetBranchAddress("theWeight", &theWeight);
	t1->SetBranchAddress("lumiWeight", &lumiWeight);
	t1->SetBranchAddress("pileupWeight", &pileupWeight);
	t1->SetBranchAddress("photon_pt", photon_pt);
	t1->SetBranchAddress("photon_eta", photon_eta);
	t1->SetBranchAddress("photon_phi", photon_phi);
	t1->SetBranchAddress("photon_e", photon_e);
	t1->SetBranchAddress("photon_pev", photon_pev);
	t1->SetBranchAddress("photon_pevnew", photon_pevnew);
	t1->SetBranchAddress("photon_ppsv", photon_ppsv);
	t1->SetBranchAddress("photon_iseb", photon_iseb);
	t1->SetBranchAddress("photon_isee", photon_isee);
	t1->SetBranchAddress("photon_hoe", photon_hoe);
	t1->SetBranchAddress("photon_sieie", photon_sieie);
	t1->SetBranchAddress("photon_sieie2", photon_sieie2);
	t1->SetBranchAddress("photon_chiso", photon_chiso);
	t1->SetBranchAddress("photon_nhiso", photon_nhiso);
	t1->SetBranchAddress("photon_phoiso", photon_phoiso);
	t1->SetBranchAddress("photon_istrue", photon_istrue);
	t1->SetBranchAddress("photon_isprompt", photon_isprompt);
	t1->SetBranchAddress("photon_drla", photon_drla);
	t1->SetBranchAddress("photon_drla2", photon_drla2);
	t1->SetBranchAddress("photon_mla", photon_mla);
	t1->SetBranchAddress("photon_mla2", photon_mla2);
	t1->SetBranchAddress("photon_mva", photon_mva);

	Int_t total_pass = 0;
	Int_t entrynum = t1->GetEntries();
	std::cout << "entrynum " << entrynum << std::endl;
	Int_t igood_photon = 0;
	Double_t photon_pt_tempo = -99.;
	Double_t Sieie_data;
	Double_t chiso_data;
	TCanvas* c = new TCanvas("c","c",600,600);
	TH2D* h2 = new TH2D("h2","h2",50,0,0.025,50,0,20);
	for (Int_t i = 0; i < entrynum; i++) {
		t1->GetEntry(i);
		Int_t pass_photons = 0; // how many photon pass the cut among the six photons in every single entry
		if (i % 1000000 == 0)
			std::cout << "processing " << i << std::endl;
		for (Int_t iPhoton = 0; iPhoton < 6; iPhoton++) {
			Int_t pass_this = 0; // check iPhoton'th photon pass the cut or not
			if (photon_pev[iPhoton] == 1 && photon_hoe[iPhoton] < 0.05
					&& photon_nhiso[iPhoton] <(1.06 + 0.014*photon_pt[iPhoton]+0.000019*photon_pt[iPhoton]*photon_pt[iPhoton])
					&& photon_phoiso[iPhoton] <(0.28 + 0.0053*photon_pt[iPhoton])
					&& TMath::Abs(photon_eta[iPhoton]) < 1.4442
					&& photon_pt[iPhoton] > 25){
				pass_this = 1;
				pass_photons++;
			}
			if (pass_this > 0 && photon_pt[iPhoton] > photon_pt_tempo) {
				photon_pt_tempo = photon_pt[iPhoton];
				igood_photon = iPhoton;
			}
		}
		Double_t weight_tmp = pileupWeight * lumiWeight * scalef * 4.353;
		Sieie_data = photon_sieie[igood_photon];
		chiso_data = photon_chiso[igood_photon];
		h2->Fill(Sieie_data,chiso_data,weight_tmp);
	}
	h2->Draw();
	c->SaveAs("check_relevant.png");
}

int main(){
	check_relevant();
	return 0;
}
