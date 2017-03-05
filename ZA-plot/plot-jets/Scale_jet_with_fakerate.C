//this function is used to scale the photon like jet to the data 
//according to the fakerate corresponding to different photon_pt bin
//by Meng Lu

#include "TH1.h"

void Scale_jet_with_fakerate(TTree *treeData, TTree *treeMC) {

// your fakerate with respect to pt bin
	const int nbins = 7;
	const int nfakerates = 6;
	Double_t ptbin[nbins] = { 25, 35, 45, 60, 80, 120, 400 };
	Double_t fakerate[nfakerates] = { 0.30, 0.25, 0.20, 0.13, 0.15, 0.11 };

	Double_t photon_pt_data;
	Int_t lep_data;
	Int_t HLT_Mu1_data;
	Double_t drla_data;
	Double_t drla2_data;
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

	Double_t photon_pt_jets;
	Int_t lep_jets;
	Int_t HLT_Mu1_jets;
	Double_t drla_jets;
	Double_t drla2_jets;
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

	treeData->SetBranchStatus("*", 0);
	treeData->SetBranchStatus("photonet", 1);
	treeData->SetBranchStatus("lep", 1);
	treeData->SetBranchStatus("HLT_Mu1", 1);
	treeData->SetBranchStatus("drla", 1);
	treeData->SetBranchStatus("drla2", 1);
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

	treeData->SetBranchAddress("photonet", &photon_pt_data);
	treeData->SetBranchAddress("lep", &lep_data);
	treeData->SetBranchAddress("HLT_Mu1", &HLT_Mu1_data);
	treeData->SetBranchAddress("drla", &drla_data);
	treeData->SetBranchAddress("drla2", &drla2_data);
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

	treeMC->SetBranchStatus("*", 1);
	treeMC->SetBranchStatus("scalef", 0);

	treeMC->SetBranchAddress("photonet", &photon_pt_jets);
	treeMC->SetBranchAddress("lep", &lep_jets);
	treeMC->SetBranchAddress("HLT_Mu1", &HLT_Mu1_jets);
	treeMC->SetBranchAddress("drla", &drla_jets);
	treeMC->SetBranchAddress("drla2", &drla2_jets);
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
	TBranch *scalef = treeMC->Branch("scalef", &scalef_jets, "scalef/D");

//bin data and mc to get the scale

	TH1D *h_data = new TH1D("h_data", "h_data", nbins, ptbin);
	TH1D *h_mc = new TH1D("h_mc", "h_mc", nbins, ptbin);

	Long64_t entries_data = treeData->GetEntriesFast();
	Long64_t entries_jets = treeMC->GetEntriesFast();

	for (Long64_t i = 0; i < entries_data; i++) {
		treeData->GetEntry(i);
		if (lep_data == 13 && photon_pt_data > 25. && photon_pt_data < 400.
				&& HLT_Mu1_data > 0 && drla_data > 0.7 && drla2_data > 0.7
				&& fabs(photoneta_data) < 1.4442 && ptlep1_data > 20.
				&& ptlep2_data > 20. && fabs(etalep1_data) < 2.4
				&& fabs(etalep2_data) < 2.4 && nlooseeles_data == 0
				&& nloosemus_data < 3 && Mjj_data > 150. && Mjj_data < 2000.
				&& jet1pt_data > 30. && jet2pt_data > 30. && jet1eta_data < 4.7
				&& jet2eta_data < 4.7 && massVlep_data > 70.
				&& massVlep_data < 110.) {
		}
		h_data->Fill(photon_pt_data);
	}

	for (Long64_t i = 0; i < entries_jets; i++) {
		treeMC->GetEntry(i);
		if (lep_jets == 13 && photon_pt_jets > 25. && photon_pt_jets < 400.
				&& HLT_Mu1_jets > 0 && drla_jets > 0.7 && drla2_jets > 0.7
				&& fabs(photoneta_jets) < 1.4442 && ptlep1_jets > 20.
				&& ptlep2_jets > 20. && fabs(etalep1_jets) < 2.4
				&& fabs(etalep2_jets) < 2.4 && nlooseeles_jets == 0
				&& nloosemus_jets < 3 && Mjj_jets > 150. && Mjj_jets < 2000.
				&& jet1pt_jets > 30. && jet2pt_jets > 30. && jet1eta_jets < 4.7
				&& jet2eta_jets < 4.7 && massVlep_jets > 70.
				&& massVlep_jets < 110.) {
		}
		h_mc->Fill(photon_pt_jets);
	}

	Double_t scale_value[nfakerates];
	for (int i = 0; i < nfakerates; i++) {
		scale_value[i] = (h_data->GetBinContent(i + 1) * fakerate[i])
				/ (h_mc->GetBinContent(i + 1));
	}

	for (Long64_t i = 0; i < entries_jets; i++) {

		treeMC->GetEntry(i);
		if (photon_pt_jets > 120.) {
			scalef_jets = scale_value[5];
		}
		if (photon_pt_jets > 80.) {
			scalef_jets = scale_value[4];
		}
		if (photon_pt_jets > 60.) {
			scalef_jets = scale_value[3];
		}
		if (photon_pt_jets > 45.) {
			scalef_jets = scale_value[2];
		}
		if (photon_pt_jets > 35.) {
			scalef_jets = scale_value[1];
		}
		if (photon_pt_jets > 25.) {
			scalef_jets = scale_value[0];
		}
		scalef->Fill();
	}
	treeMC->Write();
}
