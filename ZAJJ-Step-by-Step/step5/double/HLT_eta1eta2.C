#include <memory>
#include <fstream>
#include <ostream>
#include <iostream>
#include <stdio.h>
#include "TAxis.h"
#include <TH1.h>
#include <TH2.h>
#include <THStack.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TPaveStats.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TString.h"
#include "TVector2.h"
#include "TEfficiency.h"

void HLT_eta1eta2(std::string name)
{
	TFile* filein = TFile::Open(("../step1/out"+name+".root").c_str());
	TTree* demo = (TTree*)filein->Get("demo");
	Int_t _HLT_Mu2, _lep, _HLT_Mu4;
	Double_t _ptlep1, _ptlep2, _etalep1, _etalep2;
	demo->SetBranchAddress("HLT_Mu2",&_HLT_Mu2);
	demo->SetBranchAddress("HLT_Mu4",&_HLT_Mu4);
	demo->SetBranchAddress("lep",&_lep);
	demo->SetBranchAddress("ptlep1",&_ptlep1);
	demo->SetBranchAddress("etalep1",&_etalep1);
	demo->SetBranchAddress("ptlep2",&_ptlep2);
	demo->SetBranchAddress("etalep2",&_etalep2);

	TH2D* h11abseta = new TH2D("h11abseta", "h11abseta", 24, 0,2.4,24,0,2.4);
	TH2D* h12abseta = new TH2D("h12abseta", "h12abseta", 24, 0,2.4,24,0,2.4);

	for(int i=0;i<demo->GetEntriesFast();i++)
    	{
	if (i%1000000 ==0) std::cout<<"processing "<< name <<i<<std::endl;
        demo->GetEntry(i);
        if (_lep==13 && _ptlep1>20 && _ptlep2>20 && fabs(_etalep1)<2.4 && fabs(_etalep2)<2.4 &&  _HLT_Mu4>0)
        h11abseta->Fill(fabs(_etalep1), fabs(_etalep2));
    }

    for(int i=0;i<demo->GetEntriesFast();i++)
    {
	if (i%1000000 ==0) std::cout<<"processing "<<name <<i<<std::endl;
        demo->GetEntry(i);
        if (_lep==13 && _ptlep1>20 && _ptlep2>20 && fabs(_etalep1)<2.4 && fabs(_etalep2)<2.4 && _HLT_Mu4>0 && _HLT_Mu2>0)
        h12abseta->Fill(fabs(_etalep1), fabs(_etalep2));
    }

    TFile fileout(Form("fout_%s_histo.root", name.c_str()),"RECREATE");
    fileout.cd();
    h11abseta->Write();
    h12abseta->Write();
    fileout.Close();
}

Int_t main()
{
	HLT_eta1eta2("DMuB");
	HLT_eta1eta2("DMuC");
	HLT_eta1eta2("DMuD");
	HLT_eta1eta2("DMuE");
	HLT_eta1eta2("DMuF");
	HLT_eta1eta2("DMuG");
	HLT_eta1eta2("DMuH");
	HLT_eta1eta2("DY");
	return 1;	
}
