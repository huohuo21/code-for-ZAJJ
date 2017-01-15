#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
void scale(){
	const Int_t nbins = 7;
        const Int_t nfakerates = 6;
        Double_t ptbin[nbins] = { 25, 35, 45, 60, 80, 120, 400 };
        Double_t fakerate[nfakerates] = { 0.30, 0.25, 0.20, 0.13, 0.15, 0.11 };

	TFile* f1 = TFile::Open("fout.root");
	TH1D* hdata_ = (TH1D*)f1->Get("h_data");
	TH1D* hjet_ = (TH1D*)f1->Get("h_mc");

	TH1* hdata = hdata_->Rebin(nbins, "hdata", ptbin);
	TH1* hjet = hjet_->Rebin(nbins, "hjet", ptbin);
	
	Double_t scale[nfakerates];
	for (Int_t i=0; i<nfakerates; i++){
		std::cout<<"hdata bin "<<i<<" bin"<<hdata->GetBinContent(i+1)<<std::endl;
		std::cout<<"hjet bin "<<i<<" bin"<<hjet->GetBinContent(i+1)<<std::endl;
		scale[i] = fakerate[i]*hdata->GetBinContent(i+1)/hjet->GetBinContent(i+1);
		std::cout<<"scale bin "<<scale[i]<<std::endl;
	}
}


int main(){
	scale();
	return 1;
}
