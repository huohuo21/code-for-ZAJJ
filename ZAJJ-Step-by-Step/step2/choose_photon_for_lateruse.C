#include <string>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
// this code is for the jet_fake_photon fakerate uncertainty study and it will choose the photon meeting the following requirements from six photons that from our ntuple code: 
//			pass electron_veto;
//			medium photon ID removing sigmaetaeta;
// 			barrel region, TMath::Abs(photon_eta) < 1.4442
//			photon pt region, (lowpt,highpt)
//			&& lep == 13 && TMath::Abs(etalep1) < 2.4
//			&& TMath::Abs(etalep2) < 2.4 && nlooseeles == 0
//			&& nloosemus < 3

void choose_photon_for_lateruse(std::string filename, bool isfake, std::string tailname) {

	std::string pathToTrees = "../../ZA_plot/outTree/";

	TFile* f1 = TFile::Open((pathToTrees + "out" + filename + ".root").c_str());
	TTree* t1 = (TTree*) f1->Get("demo");
////////// for t1
	Double_t scalef;
	Int_t nVtx;
	Double_t theWeight;
	Double_t lumiWeight;
	Double_t pileupWeight;
	Int_t HLT_Ele1;
	Int_t HLT_Mu1;
	Double_t nump;
	Double_t numm;
	Double_t npT;
	Int_t lep;
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
	Double_t MET_et;
	Double_t photonet;
	Double_t photoneta;
	Double_t photonsieie;
	Double_t photonphoiso;
	Double_t photonchiso;
	Double_t photonnhiso;
	Int_t isprompt;
	Double_t jet1pt;
	Double_t jet1eta;
	Double_t jet2pt;
	Double_t jet2eta;
	Double_t Mjj;
	Double_t zepp;
	Double_t deltaeta;
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

//////////////// for treeout

	Double_t ptVlep_o;
	Double_t yVlep_o;
	Double_t phiVlep_o;
	Double_t massVlep_o;
	Double_t ptlep1_o;
	Double_t etalep1_o;
	Double_t philep1_o;
	Double_t ptlep2_o;
	Double_t etalep2_o;
	Double_t philep2_o;
	Double_t drla_o;
	Double_t drla2_o;
	Int_t nlooseeles_o;
	Int_t nloosemus_o;
	Int_t isprompt_o;
	Double_t jet1pt_o;
	Double_t jet1eta_o;
	Double_t jet2pt_o;
	Double_t jet2eta_o;
	Double_t Mjj_o;
	Double_t zepp_o;
	Double_t deltaeta_o;
	Double_t weight_lack_lumi;
	Double_t raw_sigmaetaeta;
	Double_t photonpt_o;

	TFile fdata(Form("%s_for_fakerate_use_%s.root", filename.c_str(), tailname.c_str()), "RECREATE");
	TTree* treeout = new TTree("treeout", "tree for fakerate use");
	treeout->Branch("ptVlep", &ptVlep_o, "ptVlep/D");
	treeout->Branch("photonpt", &photonpt_o, "photonpt/D");
	treeout->Branch("yVlep", &yVlep_o, "yVlep/D");
	treeout->Branch("phiVlep", &phiVlep_o, "phiVlep/D");
	treeout->Branch("massVlep", &massVlep_o, "massVlep/D");
	treeout->Branch("ptlep1", &ptlep1_o, "ptlep1/D");
	treeout->Branch("etalep1", &etalep1_o, "etalep1/D");
	treeout->Branch("philep1", &philep1_o, "philep1/D");
	treeout->Branch("ptlep2", &ptlep2_o, "ptlep2/D");
	treeout->Branch("etalep2", &etalep2_o, "etalep2/D");
	treeout->Branch("philep2", &philep2_o, "philep2/D");
	treeout->Branch("drla", &drla_o, "drla/D");
	treeout->Branch("drla2", &drla2_o, "drla2/D");
	treeout->Branch("nlooseeles", &nlooseeles_o, "nlooseeles/I");
	treeout->Branch("nloosemus", &nloosemus_o, "nloosemus/I");
	treeout->Branch("isprompt", &isprompt_o, "isprompt/I");
	treeout->Branch("jet1pt", &jet1pt_o, "jet1pt/D");
	treeout->Branch("jet1eta", &jet1eta_o, "jet1eta/D");
	treeout->Branch("jet2pt", &jet2pt_o, "jet2pt/D");
	treeout->Branch("jet2eta", &jet2eta_o, "jet2eta/D");
	treeout->Branch("Mjj", &Mjj_o, "Mjj/D");
	treeout->Branch("zepp", &zepp_o, "zepp/D");
	treeout->Branch("deltaeta", &deltaeta_o, "deltaeta/D");
	treeout->Branch("weight_lack_lumi", &weight_lack_lumi,
			"weight_lack_lumi/D");
	treeout->Branch("raw_sigmaetaeta", &raw_sigmaetaeta, "raw_sigmaetaeta/D");

	t1->SetBranchAddress("scalef", &scalef);
	t1->SetBranchAddress("nVtx", &nVtx);
	t1->SetBranchAddress("theWeight", &theWeight);
	t1->SetBranchAddress("lumiWeight", &lumiWeight);
	t1->SetBranchAddress("pileupWeight", &pileupWeight);
	t1->SetBranchAddress("HLT_Ele1", &HLT_Ele1);
	t1->SetBranchAddress("HLT_Mu1", &HLT_Mu1);
	t1->SetBranchAddress("nump", &nump);
	t1->SetBranchAddress("numm", &numm);
	t1->SetBranchAddress("npT", &npT);
	t1->SetBranchAddress("lep", &lep);
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
	t1->SetBranchAddress("nlooseeles", &nlooseeles);
	t1->SetBranchAddress("nloosemus", &nloosemus);
	t1->SetBranchAddress("MET_et", &MET_et);
	t1->SetBranchAddress("photonet", &photonet);
	t1->SetBranchAddress("photoneta", &photoneta);
	t1->SetBranchAddress("photonsieie", &photonsieie);
	t1->SetBranchAddress("photonphoiso", &photonphoiso);
	t1->SetBranchAddress("photonchiso", &photonchiso);
	t1->SetBranchAddress("photonnhiso", &photonnhiso);
	t1->SetBranchAddress("isprompt", &isprompt);
	t1->SetBranchAddress("jet1pt", &jet1pt);
	t1->SetBranchAddress("jet1eta", &jet1eta);
	t1->SetBranchAddress("jet2pt", &jet2pt);
	t1->SetBranchAddress("jet2eta", &jet2eta);
	t1->SetBranchAddress("Mjj", &Mjj);
	t1->SetBranchAddress("zepp", &zepp);
	t1->SetBranchAddress("deltaeta", &deltaeta);
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

	if (isfake) {
		Int_t entrynum = t1->GetEntries();
		Double_t chiso_low = 4., chiso_high = 12.;
		std::cout << "open " << pathToTrees << "out" << filename << ".root"
				<< std::endl;
		std::cout << "entrynum " << entrynum << std::endl;
		Int_t igood_photon = 0;
		Double_t photon_pt_tempo = -99.;
		Double_t lowpt = 25.;
		Double_t highpt = 200.;
		for (Int_t i = 0; i < entrynum; i++) {
			t1->GetEntry(i);
			Int_t pass_photons = 0; // how many photon pass the cut among the six photons in every single entry
			if (i % 1000000 == 0)
				std::cout << "processing " << i << std::endl;
			for (Int_t iPhoton = 0; iPhoton < 6; iPhoton++) {
				Int_t pass_this = 0; // check iPhoton'th photon pass the cut or not
				if (photon_pev[iPhoton] == 1 && photon_hoe[iPhoton] < 0.05
						&& photon_chiso[iPhoton] > chiso_low
						&& photon_chiso[iPhoton] < chiso_high
						&& photon_nhiso[iPhoton]
								< (1.06 + 0.014 * photon_pt[iPhoton]
										+ 0.000019 * photon_pt[iPhoton]
												* photon_pt[iPhoton])
						&& photon_phoiso[iPhoton]
								< (0.28 + 0.0053 * photon_pt[iPhoton])
						&& TMath::Abs(photon_eta[iPhoton]) < 1.4442
						&& photon_pt[iPhoton] > lowpt
						&& photon_pt[iPhoton] < highpt) {
					pass_this = 1;
					pass_photons++;
				}
				if (pass_this > 0 && photon_pt[iPhoton] > photon_pt_tempo) {
					photon_pt_tempo = photon_pt[iPhoton];
					igood_photon = iPhoton;
				}
			}

			weight_lack_lumi = pileupWeight * lumiWeight * scalef;
			ptVlep_o = ptVlep;
			yVlep_o = yVlep;
			phiVlep_o = phiVlep;
			massVlep_o = massVlep;
			ptlep1_o = ptlep1;
			etalep1_o = etalep1;
			philep1_o = philep1;
			ptlep2_o = ptlep2;
			etalep2_o = etalep2;
			philep2_o = philep2;
			drla_o = photon_drla[igood_photon];
			drla2_o = photon_drla2[igood_photon];
			nlooseeles_o = nlooseeles;
			nloosemus_o = nloosemus;
			isprompt_o = photon_isprompt[igood_photon];
			jet1pt_o = jet1pt;
			jet1eta_o = jet1eta;
			jet2pt_o = jet2pt;
			jet2eta_o = jet2eta;
			Mjj_o = Mjj;
			zepp_o = zepp;
			deltaeta_o = deltaeta;
			raw_sigmaetaeta = photon_sieie[igood_photon];
			photonpt_o = photon_pt[igood_photon];
			if (pass_photons > 0 && lep == 13 && TMath::Abs(etalep1) < 2.4
					&& TMath::Abs(etalep2) < 2.4 && nlooseeles == 0
					&& nloosemus < 3 && raw_sigmaetaeta > (-10.)) {
				treeout->Fill();
			}
		}
	} else {
		Int_t entrynum = t1->GetEntries();
		std::cout << "open " << pathToTrees << "out" << filename << ".root"
				<< std::endl;
		std::cout << "entrynum " << entrynum << std::endl;
		Int_t igood_photon = 0;
		Double_t photon_pt_tempo = -99.;
		Double_t lowpt = 25.;
		Double_t highpt = 200.;
		for (Int_t i = 0; i < entrynum; i++) {
			t1->GetEntry(i);
			Int_t pass_photons = 0; // how many photon pass the cut among the six photons in every single entry
			if (i % 1000000 == 0)
				std::cout << "processing " << i << std::endl;
			for (Int_t iPhoton = 0; iPhoton < 6; iPhoton++) {
				Int_t pass_this = 0; // check iPhoton'th photon pass the cut or not
				if (photon_pev[iPhoton] == 1 && photon_hoe[iPhoton] < 0.05
						&& photon_chiso[iPhoton] < 1.37
						&& photon_nhiso[iPhoton]
								< (1.06 + 0.014 * photon_pt[iPhoton]
										+ 0.000019 * photon_pt[iPhoton]
												* photon_pt[iPhoton])
						&& photon_phoiso[iPhoton]
								< (0.28 + 0.0053 * photon_pt[iPhoton])
						&& TMath::Abs(photon_eta[iPhoton]) < 1.4442
						&& photon_pt[iPhoton] > lowpt
						&& photon_pt[iPhoton] < highpt) {
					pass_this = 1;
					pass_photons++;
				}
				if (pass_this > 0 && photon_pt[iPhoton] > photon_pt_tempo) {
					photon_pt_tempo = photon_pt[iPhoton];
					igood_photon = iPhoton;
				}
			}

			weight_lack_lumi = pileupWeight * lumiWeight * scalef;
			ptVlep_o = ptVlep;
			yVlep_o = yVlep;
			phiVlep_o = phiVlep;
			massVlep_o = massVlep;
			ptlep1_o = ptlep1;
			etalep1_o = etalep1;
			philep1_o = philep1;
			ptlep2_o = ptlep2;
			etalep2_o = etalep2;
			philep2_o = philep2;
			drla_o = photon_drla[igood_photon];
			drla2_o = photon_drla2[igood_photon];
			nlooseeles_o = nlooseeles;
			nloosemus_o = nloosemus;
			isprompt_o = photon_isprompt[igood_photon];
			jet1pt_o = jet1pt;
			jet1eta_o = jet1eta;
			jet2pt_o = jet2pt;
			jet2eta_o = jet2eta;
			Mjj_o = Mjj;
			zepp_o = zepp;
			deltaeta_o = deltaeta;
			raw_sigmaetaeta = photon_sieie[igood_photon];
			photonpt_o = photon_pt[igood_photon];
			if (pass_photons > 0 && lep == 13 && TMath::Abs(etalep1) < 2.4
					&& TMath::Abs(etalep2) < 2.4 && nlooseeles == 0
					&& nloosemus < 3 && raw_sigmaetaeta > (-10.)) {
				treeout->Fill();
			}
		}
	}

fdata.cd();
treeout->Write();
fdata.Close();
std::cout<<"process finished "<<std::endl;

}

int main() {

choose_photon_for_lateruse("DMu",false,"true");
choose_photon_for_lateruse("ZA_signal",false,"true");
choose_photon_for_lateruse("DMu",true,"fake");
choose_photon_for_lateruse("ZJets",true,"fake");
return 0;
}
