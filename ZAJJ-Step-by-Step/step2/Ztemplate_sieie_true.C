#include <string>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
void Ztemplate_sieie_true(std::string filename, float lowpt, float highpt) {

	std::string pathToTrees = "./photon-rawsigmaetaeta-chiso4to10/";

	TFile* f1 = TFile::Open((pathToTrees + filename + "_for_fakerate_use_true.root").c_str());
	TTree* t1 = (TTree*) f1->Get("treeout");


	Double_t ptVlep;
	Double_t yVlep;
	Double_t phiVlep;
	Double_t massVlep;
	Double_t ptlep1;
	Double_t etalep1;
	Double_t philep1;
	Double_t ptlep2;
	Double_t etalep2;
	Double_t philep2;
	Double_t drla;
	Double_t drla2;
	Int_t nlooseeles;
	Int_t nloosemus;
	Int_t isprompt;
	Double_t jet1pt;
	Double_t jet1eta;
	Double_t jet2pt;
	Double_t jet2eta;
	Double_t Mjj;
	Double_t zepp;
	Double_t deltaeta;
	Double_t weight_lack_lumi;
	Double_t raw_sigmaetaeta;
	Double_t photonpt;

	t1->SetBranchAddress("ptVlep", &ptVlep);
	t1->SetBranchAddress("yVlep", &yVlep);
	t1->SetBranchAddress("phiVlep", &phiVlep);
	t1->SetBranchAddress("massVlep", &massVlep);
	t1->SetBranchAddress("ptlep1", &ptlep1);
	t1->SetBranchAddress("etalep1", &etalep1);
	t1->SetBranchAddress("philep1", &philep1);
	t1->SetBranchAddress("ptlep2", &ptlep2);
	t1->SetBranchAddress("etalep2", &etalep2);
	t1->SetBranchAddress("philep2", &philep2);
	t1->SetBranchAddress("drla", &drla);
	t1->SetBranchAddress("drla2", &drla2);
	t1->SetBranchAddress("nlooseeles", &nlooseeles);
	t1->SetBranchAddress("nloosemus", &nloosemus);
	t1->SetBranchAddress("isprompt", &isprompt);
	t1->SetBranchAddress("jet1pt", &jet1pt);
	t1->SetBranchAddress("jet1eta", &jet1eta);
	t1->SetBranchAddress("jet2pt", &jet2pt);
	t1->SetBranchAddress("jet2eta", &jet2eta);
	t1->SetBranchAddress("Mjj", &Mjj);
	t1->SetBranchAddress("zepp", &zepp);
	t1->SetBranchAddress("deltaeta", &deltaeta);
	t1->SetBranchAddress("weight_lack_lumi", &weight_lack_lumi);
	t1->SetBranchAddress("raw_sigmaetaeta", &raw_sigmaetaeta);
	t1->SetBranchAddress("photonpt", &photonpt);
	Double_t lumi = 36.749;
///////////////////    below is the variables you want to study      ///////////////////////

	Double_t drla_criti = 0.7;
	Double_t ptlep_criti = 20.;
	Double_t massVlep_low_criti = 70.;
	Double_t massVlep_high_criti = 110.;
////// begin processing photon candidates (medium photon)/////////
	Int_t entrynum = t1->GetEntries();
	std::cout << "open "<<pathToTrees<< filename << "_for_fakerate_use.root" <<std::endl;
	std::cout << "entrynum " << entrynum << std::endl;
	TH1F* histo = new TH1F("histo", "histo", 180, 0.0042, 0.0222);
	TFile fdata(Form("%s_%0.f_%0.f_true.root", filename.c_str(), lowpt, highpt),"RECREATE");

	for (Int_t i = 0; i < entrynum; i++) {
		t1->GetEntry(i);
		if (drla > drla_criti && drla2 > drla_criti && ptlep1 > ptlep_criti && photonpt> lowpt &&
			 photonpt<highpt && ptlep2 > ptlep_criti && massVlep > massVlep_low_criti && massVlep < massVlep_high_criti) {
			if (filename=="ZA_signal" && isprompt==1)histo->Fill(raw_sigmaetaeta, weight_lack_lumi*lumi);
			if(filename=="DMu") histo->Fill(raw_sigmaetaeta);
		}
	}
	fdata.cd();
	histo->Write();
	fdata.Close();
	std::cout<<"process finished "<<std::endl;
}
