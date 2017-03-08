#include <iostream>
#include "TFile.h"
#include "TH1.h"

void ZA_scale(){
	std::string path = "./";
	Double_t lumi = 35.862;

	TFile* fDMu = TFile::Open(( path + "histos_outDMu.root").c_str());
	TFile* fZA = TFile::Open(( path +"histos_ZA.root").c_str());
	TFile* fplj = TFile::Open(( path +"histos_photonlikejet.root").c_str());
	TFile* fST = TFile::Open(( path +"histos_ST.root").c_str());
	TFile* fTTA = TFile::Open(( path +"histos_TTA.root").c_str());
	TFile* fVV = TFile::Open(( path +"histos_VV.root").c_str());
	TFile* fZA_EWK = TFile::Open(( path +"histos_outZA_signal.root").c_str());
	TFile* fWA = TFile::Open(( path +"histos_WA.root").c_str());

	TH1D* hDMu = (TH1D*)(fDMu->Get("Mjj_mu")->Clone("clone"));
	TH1D* hZA = (TH1D*)(fZA->Get("Mjj_mu")->Clone("clone"));
	TH1D* hplj = (TH1D*)(fplj->Get("Mjj_mu")->Clone("clone"));
	TH1D* hST = (TH1D*)(fST->Get("Mjj_mu")->Clone("clone"));
	TH1D* hTTA = (TH1D*)(fTTA->Get("Mjj_mu")->Clone("clone"));
	TH1D* hVV = (TH1D*)(fVV->Get("Mjj_mu")->Clone("clone"));
	TH1D* hZA_EWK = (TH1D*)(fZA_EWK->Get("Mjj_mu")->Clone("clone"));
	TH1D* hWA = (TH1D*)(fWA->Get("Mjj_mu")->Clone("clone"));

	Double_t nDMu = hDMu->GetBinContent(1) + hDMu->GetBinContent(2);
	Double_t nZA = hZA->GetBinContent(1) + hZA->GetBinContent(2);
	Double_t nplj = hplj->GetBinContent(1) + hplj->GetBinContent(2);
	Double_t nST = hST->GetBinContent(1) + hST->GetBinContent(2);
	Double_t nTTA = hTTA->GetBinContent(1) + hTTA->GetBinContent(2);
	Double_t nVV = hVV->GetBinContent(1) + hVV->GetBinContent(2);
	Double_t nZA_EWK = hZA_EWK->GetBinContent(1) + hZA_EWK->GetBinContent(2);
	Double_t nWA = hWA->GetBinContent(1) + hWA->GetBinContent(2);

	Double_t nMC = (nZA + nST + nTTA + nVV + nZA_EWK + nWA) * lumi + nplj;
	Double_t scale = (nDMu - nMC + nZA*lumi)/(nZA*lumi);

	std::cout<<"scale of ZA "<<scale<<std::endl; ///  0.89
	std::cout<<"nMC "<<nMC<<std::endl;  ///  264.668
	std::cout<<"nDMu "<<nDMu<<std::endl; /// 246
	std::cout<<"nZA "<<nZA*lumi<<std::endl; /// 169.42
	std::cout<<"signal contribution in control region "<<nZA_EWK*lumi/nDMu<<std::endl;/// 0.028

	Double_t nDMu_s=0, nZA_s=0, nplj_s=0, nST_s=0, nTTA_s=0, nVV_s=0, nZA_EWK_s=0, nWA_s=0;
	for (Int_t i=3; i<16; i++){
		nDMu_s += hDMu->GetBinContent(i);
		nZA_s += hZA->GetBinContent(i);
		nplj_s += hplj->GetBinContent(i);
		nST_s += hST->GetBinContent(i);
		nTTA_s += hTTA->GetBinContent(i);
		nVV_s += hVV->GetBinContent(i);
		nZA_EWK_s += hZA_EWK->GetBinContent(i);
		nWA_s += hWA->GetBinContent(i);
	}
	Double_t nbkg = (nZA_s*scale + nST_s + nTTA_s + nVV_s + nWA_s)*lumi + nplj_s;
	Double_t sigma = (nZA_EWK_s*lumi)/sqrt(nbkg);
	std::cout<<"signal strenth sigma is "<<sigma<<std::endl;
	std::cout<<"signal yields is "<<nZA_EWK_s*lumi<<std::endl;
	std::cout<<"bkg yields is "<<nbkg<<std::endl;

}

int main(){

		ZA_scale();
		return 1;
}
