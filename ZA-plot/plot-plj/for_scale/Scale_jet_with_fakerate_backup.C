//this function is used to scale the photon like jet to the data 
//according to the fakerate corresponding to different photon_pt bin
//by Meng Lu
#include <iostream>
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "math.h"
void Scale_jet_with_fakerate() {

// your fakerate with respect to pt bin
	const int nbins = 7;
	const int nfakerates = 6;
	Double_t ptbin[nbins] = { 25, 35, 45, 60, 80, 120, 400 };
	Double_t fakerate[nfakerates] = { 0.30, 0.25, 0.20, 0.13, 0.15, 0.11 };
	std::string pathToTree = "../../../small-ntuple-maker/outTree-new-pu/";	
	TFile* fdata = TFile::Open((pathToTree+"outDMu.root").c_str());
	TTree* treeData = (TTree*)fdata->Get("demo");
	TFile* fjet = TFile::Open((pathToTree+"outphotonlikejet.root").c_str());
	TTree* treeMC = (TTree*)fjet->Get("demo");
	TFile fout("fout.root","RECREATE");

	Double_t photon_pt_data;
	Int_t lep_data;
	Int_t HLT_Mu1_data;
	Double_t drla_data;
	Double_t drla2_data;
	Double_t drj1a_data;
	Double_t drj2a_data;
	Double_t photoneta_data;
	Double_t ptlep1_data;
	Double_t ptlep2_data;
	Double_t etalep1_data;
	Double_t etalep2_data;
	Int_t nlooseeles_data;
	Int_t nloosemus_data;
	Double_t Mjj_data;
	Double_t jet1pt_data;
	Double_t jet2pt_data;
	Double_t jet1eta_data;
	Double_t jet2eta_data;
	Double_t massVlep_data;
	Double_t zepp_data;

	Double_t photon_pt_jets;
	Int_t lep_jets;
	Int_t HLT_Mu1_jets;
	Double_t drla_jets;
	Double_t drla2_jets;
	Double_t drj1a_jets;
	Double_t drj2a_jets;
	Double_t photoneta_jets;
	Double_t ptlep1_jets;
	Double_t ptlep2_jets;
	Double_t etalep1_jets;
	Double_t etalep2_jets;
	Int_t nlooseeles_jets;
	Int_t nloosemus_jets;
	Double_t Mjj_jets;
	Double_t jet1pt_jets;
	Double_t jet2pt_jets;
	Double_t jet1eta_jets;
	Double_t jet2eta_jets;
	Double_t massVlep_jets;
	Double_t scalef_jets;
	Double_t zepp_jets;	

	treeData->SetBranchStatus("*", 0);
	treeData->SetBranchStatus("photonet", 1);
	treeData->SetBranchStatus("lep", 1);
	treeData->SetBranchStatus("HLT_Mu1", 1);
	treeData->SetBranchStatus("drla", 1);
	treeData->SetBranchStatus("drla2", 1);
	treeData->SetBranchStatus("drj1a", 1);
	treeData->SetBranchStatus("drj2a", 1);
	treeData->SetBranchStatus("photoneta", 1);
	treeData->SetBranchStatus("ptlep1", 1);
	treeData->SetBranchStatus("ptlep2", 1);
	treeData->SetBranchStatus("etalep1", 1);
	treeData->SetBranchStatus("etalep2", 1);
	treeData->SetBranchStatus("nlooseeles", 1);
	treeData->SetBranchStatus("nloosemus", 1);
	treeData->SetBranchStatus("Mjj", 1);
	treeData->SetBranchStatus("jet1pt", 1);
	treeData->SetBranchStatus("jet2pt", 1);
	treeData->SetBranchStatus("jet1eta", 1);
	treeData->SetBranchStatus("jet2eta", 1);
	treeData->SetBranchStatus("massVlep", 1);
	treeData->SetBranchStatus("zepp", 1);

	treeData->SetBranchAddress("photonet", &photon_pt_data);
	treeData->SetBranchAddress("lep", &lep_data);
	treeData->SetBranchAddress("HLT_Mu1", &HLT_Mu1_data);
	treeData->SetBranchAddress("drla", &drla_data);
	treeData->SetBranchAddress("drla2", &drla2_data);
	treeData->SetBranchAddress("drj1a", &drj1a_data);
	treeData->SetBranchAddress("drj2a", &drj2a_data);
	treeData->SetBranchAddress("photoneta", &photoneta_data);
	treeData->SetBranchAddress("ptlep1", &ptlep1_data);
	treeData->SetBranchAddress("ptlep2", &ptlep2_data);
	treeData->SetBranchAddress("etalep1", &etalep1_data);
	treeData->SetBranchAddress("etalep2", &etalep2_data);
	treeData->SetBranchAddress("nlooseeles", &nlooseeles_data);
	treeData->SetBranchAddress("nloosemus", &nloosemus_data);
	treeData->SetBranchAddress("Mjj", &Mjj_data);
	treeData->SetBranchAddress("jet1pt", &jet1pt_data);
	treeData->SetBranchAddress("jet2pt", &jet2pt_data);
	treeData->SetBranchAddress("jet1eta", &jet1eta_data);
	treeData->SetBranchAddress("jet2eta", &jet2eta_data);
	treeData->SetBranchAddress("massVlep", &massVlep_data);
	treeData->SetBranchAddress("zepp", &zepp_data);

	treeMC->SetBranchStatus("*", 1);
	treeMC->SetBranchStatus("scalef", 0);

	treeMC->SetBranchAddress("photonet", &photon_pt_jets);
	treeMC->SetBranchAddress("lep", &lep_jets);
	treeMC->SetBranchAddress("HLT_Mu1", &HLT_Mu1_jets);
	treeMC->SetBranchAddress("drla", &drla_jets);
	treeMC->SetBranchAddress("drla2", &drla2_jets);
	treeMC->SetBranchAddress("drj1a", &drj1a_jets);
	treeMC->SetBranchAddress("drj2a", &drj2a_jets);
	treeMC->SetBranchAddress("photoneta", &photoneta_jets);
	treeMC->SetBranchAddress("ptlep1", &ptlep1_jets);
	treeMC->SetBranchAddress("ptlep2", &ptlep2_jets);
	treeMC->SetBranchAddress("etalep1", &etalep1_jets);
	treeMC->SetBranchAddress("etalep2", &etalep2_jets);
	treeMC->SetBranchAddress("nlooseeles", &nlooseeles_jets);
	treeMC->SetBranchAddress("nloosemus", &nloosemus_jets);
	treeMC->SetBranchAddress("Mjj", &Mjj_jets);
	treeMC->SetBranchAddress("jet1pt", &jet1pt_jets);
	treeMC->SetBranchAddress("jet2pt", &jet2pt_jets);
	treeMC->SetBranchAddress("jet1eta", &jet1eta_jets);
	treeMC->SetBranchAddress("jet2eta", &jet2eta_jets);
	treeMC->SetBranchAddress("massVlep", &massVlep_jets);
	treeMC->SetBranchAddress("zepp", &zepp_jets);
	TBranch *scalef = treeMC->Branch("scalef", &scalef_jets, "scalef/D");

//bin data and mc to get the scale

	TH1D *h_data_drja04_jetpt15_massV50130 = new TH1D("h_data_drja04_jetpt15_massV50130", "h_data_drja04_jetpt15_massV50130", 100,25,400);
	TH1D *h_data_drja04_jetpt15 = new TH1D("h_data_drja04_jetpt15", "h_data_drja04_jetpt15", 100,25,400);
	TH1D *h_data_drja04_massV50130 = new TH1D("h_data_drja04_massV50130", "h_data_drja04_massV50130", 100,25,400);
	TH1D *h_data_drja04 = new TH1D("h_data_drja04", "h_data_drja04", 100,25,400);
	TH1D *h_data_jetpt15_massV50130 = new TH1D("h_data_jetpt15_massV50130", "h_data_jetpt15_massV50130", 100,25,400);
    TH1D *h_data_jetpt15 = new TH1D("h_data_jetpt15", "h_data_jetpt15", 100,25,400);
    TH1D *h_data_massV50130 = new TH1D("h_data_massV50130", "h_data_massV50130", 100,25,400);
    TH1D *h_data = new TH1D("h_data", "h_data", 100,25,400);

	TH1D *h_mc_drja04_jetpt15_massV50130 = new TH1D("h_mc_drja04_jetpt15_massV50130", "h_mc_drja04_jetpt15_massV50130", 100,25,400);
	TH1D *h_mc_drja04_jetpt15 = new TH1D("h_mc_drja04_jetpt15", "h_mc_drja04_jetpt15", 100,25,400);
	TH1D *h_mc_drja04_massV50130 = new TH1D("h_mc_drja04_massV50130", "h_mc_drja04_massV50130", 100,25,400);
	TH1D *h_mc_drja04 = new TH1D("h_mc_drja04", "h_mc_drja04", 100,25,400);
	TH1D *h_mc_jetpt15_massV50130 = new TH1D("h_mc_jetpt15_massV50130", "h_mc_jetpt15_massV50130", 100,25,400);
    TH1D *h_mc_jetpt15 = new TH1D("h_mc_jetpt15", "h_mc_jetpt15", 100,25,400);
    TH1D *h_mc_massV50130 = new TH1D("h_mc_massV50130", "h_mc_massV50130", 100,25,400);
    TH1D *h_mc = new TH1D("h_mc", "h_mc", 100,25,400);

	Long64_t entries_data = treeData->GetEntriesFast();
	Long64_t entries_jets = treeMC->GetEntriesFast();

	for (Long64_t i = 0; i < entries_data; i++) {
		if(i%1000000==0) std::cout<<"processing data  "<<i<<std::endl;
		treeData->GetEntry(i);
		if (lep_data == 13 && photon_pt_data > 25. && photon_pt_data < 400.
				&& HLT_Mu1_data > 0  
				&& fabs(photoneta_data) < 1.4442
				&& nlooseeles_data == 0
				&& nloosemus_data < 3)
				{
					if(drj1a_data>0.4 && drj2a_data>0.4 && jet1pt_data>15 && jet2pt_data>15 && massVlep_data>50 && massVlep_data<130) h_data_drja04_jetpt15_massV50130->Fill(photon_pt_data);
					if(drj1a_data>0.4 && drj2a_data>0.4 && jet1pt_data>15 && jet2pt_data>15) h_data_drja04_jetpt15->Fill(photon_pt_data);
					if(drj1a_data>0.4 && drj2a_data>0.4 && massVlep_data>50 && massVlep_data<130) h_data_drja04_massV50130->Fill(photon_pt_data);
					if(drj1a_data>0.4 && drj2a_data>0.4) h_data_drja04->Fill(photon_pt_data);
					if(jet1pt_data>15 && jet2pt_data>15 && massVlep_data>50 && massVlep_data<130) h_data_jetpt15_massV50130->Fill(photon_pt_data);
					if(jet1pt_data>15 && jet2pt_data>15) h_data_jetpt15->Fill(photon_pt_data);
					if(massVlep_data>50 && massVlep_data<130) h_data_massV50130->Fill(photon_pt_data);
					if(1) h_data->Fill(photon_pt_data);
				}
	}

	for (Long64_t i = 0; i < entries_jets; i++) {
		if(i%1000000==0) std::cout<<"processing jets  "<<i<<std::endl;
		treeMC->GetEntry(i);
		if (lep_jets == 13 && photon_pt_jets > 25. && photon_pt_jets < 400.
				&& HLT_Mu1_jets > 0  
				&& fabs(photoneta_jets) < 1.4442
				&& nlooseeles_jets == 0
				&& nloosemus_jets < 3)
				{
					if(drj1a_jets>0.4 && drj2a_jets>0.4 && jet1pt_jets>15 && jet2pt_jets>15 && massVlep_jets>50 && massVlep_jets<130) h_mc_drja04_jetpt15_massV50130->Fill(photon_pt_jets);
					if(drj1a_jets>0.4 && drj2a_jets>0.4 && jet1pt_jets>15 && jet2pt_jets>15) h_mc_drja04_jetpt15->Fill(photon_pt_jets);
					if(drj1a_jets>0.4 && drj2a_jets>0.4 && massVlep_jets>50 && massVlep_jets<130) h_mc_drja04_massV50130->Fill(photon_pt_jets);
					if(drj1a_jets>0.4 && drj2a_jets>0.4) h_mc_drja04->Fill(photon_pt_jets);
					if(jet1pt_jets>15 && jet2pt_jets>15 && massVlep_jets>50 && massVlep_jets<130) h_mc_jetpt15_massV50130->Fill(photon_pt_jets);
					if(jet1pt_jets>15 && jet2pt_jets>15) h_mc_jetpt15->Fill(photon_pt_jets);
					if(massVlep_jets>50 && massVlep_jets<130) h_mc_massV50130->Fill(photon_pt_jets);
					if(1) h_mc->Fill(photon_pt_jets);
				}
	}
	fout.cd();
	h_data_drja04_jetpt15_massV50130->Write();
	h_data_drja04_jetpt15->Write();
	h_data_drja04_massV50130->Write();
	h_data_drja04->Write();
	h_data_jetpt15_massV50130->Write();
	h_data_jetpt15->Write();
	h_data_massV50130->Write();
	h_data->Write();
	h_mc_drja04_jetpt15_massV50130->Write();
	h_mc_drja04_jetpt15->Write();
	h_mc_drja04_massV50130->Write();
	h_mc_drja04->Write();
	h_mc_jetpt15_massV50130->Write();
	h_mc_jetpt15->Write();
	h_mc_massV50130->Write();
	h_mc->Write();
	fout.Close();	
}

int main(){
	Scale_jet_with_fakerate();
	return 1;
}
