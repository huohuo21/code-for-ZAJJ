#include "TGraphAsymmErrors.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TChain.h"
#include "math.h"
#include "TLorentzVector.h"
#define Pi 3.1415926
/// The large arrays that were here are now GONE.
/// Instead, we have this helper that holds the
/// information of all our histograms.

class HistoFactory {
	public:
		std::vector<std::string> vars;
		std::vector<int> nBins;
		std::vector<double> minBin;
		std::vector<double> maxBin;
		void setHisto(std::string s, int n, double min, double max) {
			vars.push_back(s);
			nBins.push_back(n);
			minBin.push_back(min);
			maxBin.push_back(max);
		}
};

class EDBRHistoMaker {
	public:
		EDBRHistoMaker(TTree *tree = 0, TFile *fileTMP = 0, TH1F* hR1 = 0, std::string out_name_="");
		virtual ~EDBRHistoMaker();

		/// This is the tree structure. This comes directly from MakeClass
		TTree* fChain;   //!pointer to the analyzed TTree or TChain
		TFile* fileTMP_;
		TH1F* hR1_;
		Int_t fCurrent; //!current Tree number in a TChain
		bool setUnitaryWeights_;

		// Declaration of leaf types
		Double_t scalef;
		Int_t nVtx;
		Double_t theWeight;
		Double_t lumiWeight;
		Double_t pileupWeight660;
		Double_t pileupWeight690;
		Double_t pileupWeight692;
		Int_t HLT_Ele1;
		Int_t HLT_Mu2;
		Int_t HLT_Mu5;
		Double_t nump;
		Double_t numm;
		Double_t npT;
		Int_t lep;
		Int_t run_period;
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
		Double_t drj1a;
		Double_t drj2a;
		Double_t drj1l;
		Double_t drj1l2;
		Double_t drj2l;
		Double_t drj2l2;
		Int_t nlooseeles;
		Int_t nloosemus;
		Double_t MET_et;
		Double_t photonet;
		Double_t photoneta;
		Double_t photonphi;
		Double_t photone;
		Double_t photonsieie;
		Double_t photonphoiso;
		Double_t photonchiso;
		Double_t photonnhiso;
		Int_t isprompt;
		Double_t jet1pt;
		Double_t jet1eta;
		Double_t jet1e;
		Double_t jet2e;
		Double_t jet2pt;
		Double_t jet2eta;
		Double_t jet1phi;
		Double_t jet2phi;
		Double_t Mjj;
		Double_t zepp;
		Double_t deltaeta;
		Double_t actualWeight;
		Double_t detajj;
		Double_t delta_phi;
		Double_t drjj;
		Double_t l1_weight;
		// List of branches
		TBranch *b_scalef;   //!
		TBranch *b_nVtx;   //!
		TBranch *b_theWeight;   //!
		TBranch *b_lumiWeight;   //!
		TBranch *b_pileupWeight660;   //!
		TBranch *b_pileupWeight690;   //!
		TBranch *b_pileupWeight692;   //!
		TBranch *b_HLT_Ele1;   //!
		TBranch *b_HLT_Mu2;   //!
		TBranch *b_HLT_Mu5;   //!
		TBranch *b_nump;   //!
		TBranch *b_numm;   //!
		TBranch *b_npT;   //!
		TBranch *b_lep;   //!
		TBranch *b_run_period;
		TBranch *b_ptVlep;   //!
		TBranch *b_yVlep;   //!
		TBranch *b_phiVlep;   //!
		TBranch *b_massVlep;   //!
		TBranch *b_ptlep1;   //!
		TBranch *b_etalep1;   //!
		TBranch *b_philep1;   //!
		TBranch *b_ptlep2;   //!
		TBranch *b_etalep2;   //!
		TBranch *b_philep2;   //!
		TBranch *b_drla;
		TBranch *b_drla2;
		TBranch *b_drj1a;
		TBranch *b_drj2a;
		TBranch *b_drj1l;
		TBranch *b_drj1l2;
		TBranch *b_drj2l;
		TBranch *b_drj2l2;
		TBranch *b_nlooseeles;   //!
		TBranch *b_nloosemus;   //!
		TBranch *b_MET_et;   //!
		TBranch *b_photonet;   //!
		TBranch *b_photoneta;   //!
		TBranch *b_photonphi;
		TBranch *b_photone;
		TBranch *b_photonsieie;   //!
		TBranch *b_photonphoiso;   //!
		TBranch *b_photonchiso;   //!
		TBranch *b_photonnhiso;   //!
		TBranch *b_isprompt;   //!
		TBranch *b_jet1pt;   //!
		TBranch *b_jet1eta;   //!
		TBranch *b_jet2pt;   //!
		TBranch *b_jet2eta;   //!
		TBranch *b_jet1phi;
		TBranch *b_jet2phi;
		TBranch *b_jet1e;
		TBranch *b_jet2e;
		TBranch *b_Mjj;    //!
		TBranch *b_zepp;
		TBranch *b_deltaeta;
		TBranch *b_l1_weight;

		// Basic functions directly from MakeClass
		Int_t GetEntry(Long64_t entry);
		Long64_t LoadTree(Long64_t entry);
		void Init(TTree *tree);
		void Loop(std::string outFileName);
		void Loop_SFs_mc(std::string outFileName, TH2F* ID_photon, TH2F* ID_BF, TH2F* ID_GH, TH2F* ISO_BF, TH2F* ISO_GH, TGraphAsymmErrors* track_SF, TH2D* di_lep_trigger);
		// Our added functions
		void createAllHistos();
		void printAllHistos();
		void saveAllHistos(std::string outFileName);
		void setUnitaryWeights(bool setuniw = false) {
			setUnitaryWeights_ = setuniw;
		}

		int check(double pt, std::vector<double> * ptZ) {
			int goodw = 1;
			for (unsigned int i = 0; i < ptZ->size(); i++) {
				if (pt == ptZ->at(i)) {
					goodw = 0;
					break;
				}
			}

			return goodw;
		}
		// Our added variables
		int nVars;
		bool debug_;

		///meng
		TTree *treename;
		TFile *fout;
		std::string out_name;
		void endjob(){
			fout->cd();
			treename->Write();
			fout->Write();
			fout->Close();
			delete fout;
		}
		///lu


		// The histograms
		HistoFactory hs;
		std::map<std::string, TH1D*> theHistograms;
		TH2D *hmjmzz;
		TH1D *hmzzNEW;
};

void EDBRHistoMaker::Init(TTree *tree) {
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the branch addresses and branch
	// pointers of the tree will be set.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).

	// Set branch addresses and branch pointers
	if (!tree)
		return;
	fChain = tree;
	fCurrent = -1;
	fChain->SetMakeClass(1);

	fout = new TFile(out_name.c_str(), "RECREATE");
	treename = new TTree("outtree","outtree");
	cout<<"begin make outfile tree"<<endl;
	treename->Branch("scalef", &scalef, "scalef/D");
        treename->Branch("nVtx", &nVtx, "nVtx/I");
        treename->Branch("theWeight", &theWeight, "theWeight/D");
        treename->Branch("lumiWeight", &lumiWeight, "lumiWeight/D");
        treename->Branch("pileupWeight660", &pileupWeight660, "pileupWeight660/D");
	treename->Branch("pileupWeight690", &pileupWeight690, "pileupWeight690/D");
	treename->Branch("pileupWeight692", &pileupWeight692, "pileupWeight692/D");
        treename->Branch("HLT_Ele1", &HLT_Ele1, "HLT_Ele1/I");
        treename->Branch("HLT_Mu2", &HLT_Mu2, "HLT_Mu2/I");
        treename->Branch("HLT_Mu5", &HLT_Mu5, "HLT_Mu5/I");
        treename->Branch("nump", &nump, "nump/D");
        treename->Branch("numm", &numm, "numm/D");
        treename->Branch("npT", &npT, "npT/D");
        treename->Branch("lep", &lep, "lep/I");
	treename->Branch("run_period", &run_period, "run_period/I");
        treename->Branch("ptVlep", &ptVlep, "ptVlep/D");
        treename->Branch("yVlep", &yVlep, "yVlep/D");
        treename->Branch("phiVlep", &phiVlep, "phiVlep/D");
        treename->Branch("massVlep", &massVlep, "massVlep/D");
        treename->Branch("ptlep1", &ptlep1, "ptlep1/D");
        treename->Branch("etalep1", &etalep1, "etalep1/D");
        treename->Branch("philep1", &philep1, "philep1/D");
        treename->Branch("ptlep2", &ptlep2, "ptlep2/D");
        treename->Branch("etalep2", &etalep2, "etalep2/D");
        treename->Branch("philep2", &philep2, "philep2/D");
        treename->Branch("drla", &drla, "drla/D");
        treename->Branch("drla2", &drla2, "drla2/D");
        treename->Branch("drj1a", &drj1a, "drj1a/D");
        treename->Branch("drj2a", &drj2a, "drj2a/D");
        treename->Branch("drj1l", &drj1l, "drj1l/D");
        treename->Branch("drj2l", &drj2l, "drj2l/D");
        treename->Branch("drj1l2", &drj1l2, "drj1l2/D");
        treename->Branch("drj2l2", &drj2l2, "drj2l2/D");
        treename->Branch("nlooseeles", &nlooseeles, "nlooseeles/I");
	treename->Branch("nloosemus", &nloosemus, "nloosemus/I");
        treename->Branch("MET_et", &MET_et, "MET_et/D");
        treename->Branch("photonet", &photonet, "photonet/D");
        treename->Branch("photoneta", &photoneta, "photoneta/D");
        treename->Branch("photonphi", &photonphi, "photonphi/D");
        treename->Branch("photone", &photone, "photone/D");
        treename->Branch("photonsieie", &photonsieie, "photonsieie/D");
        treename->Branch("photonphoiso", &photonphoiso, "photonphoiso/D");
        treename->Branch("photonchiso", &photonchiso, "photonchiso/D");
        treename->Branch("photonnhiso", &photonnhiso, "photonnhiso/D");
        treename->Branch("isprompt", &isprompt, "isprompt/I");
        treename->Branch("jet1pt", &jet1pt, "jet1pt/D");
        treename->Branch("jet1eta", &jet1eta, "jet1eta/D");
        treename->Branch("jet1phi", &jet1phi, "jet1phi/D");
        treename->Branch("jet1e", &jet1e, "jet1e/D");
        treename->Branch("jet2pt", &jet2pt, "jet2pt/D");
        treename->Branch("jet2eta", &jet2eta, "jet2eta/D");
        treename->Branch("jet2phi", &jet2phi, "jet2phi/D");
        treename->Branch("jet2e", &jet2e, "jet2e/D");
        treename->Branch("Mjj", &Mjj, "Mjj/D");
        treename->Branch("zepp", &zepp, "zepp/D");
        treename->Branch("deltaeta", &deltaeta, "deltaeta/D");
        treename->Branch("l1_weight", &l1_weight, "l1_weight/D");
	cout<<"make outfile tree end"<<endl;

	fChain->SetBranchAddress("scalef", &scalef, &b_scalef);
	fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
	fChain->SetBranchAddress("theWeight", &theWeight, &b_theWeight);
	fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
	fChain->SetBranchAddress("pileupWeight660", &pileupWeight660, &b_pileupWeight660);
	fChain->SetBranchAddress("pileupWeight690", &pileupWeight690, &b_pileupWeight690);
	fChain->SetBranchAddress("pileupWeight692", &pileupWeight692, &b_pileupWeight692);
	fChain->SetBranchAddress("HLT_Ele1", &HLT_Ele1, &b_HLT_Ele1);
	fChain->SetBranchAddress("HLT_Mu2", &HLT_Mu2, &b_HLT_Mu2);
	fChain->SetBranchAddress("HLT_Mu5", &HLT_Mu5, &b_HLT_Mu5);
	fChain->SetBranchAddress("nump", &nump, &b_nump);
	fChain->SetBranchAddress("numm", &numm, &b_numm);
	fChain->SetBranchAddress("npT", &npT, &b_npT);
	fChain->SetBranchAddress("lep", &lep, &b_lep);
	fChain->SetBranchAddress("run_period", &run_period, &b_run_period);
	fChain->SetBranchAddress("ptVlep", &ptVlep, &b_ptVlep);
	fChain->SetBranchAddress("yVlep", &yVlep, &b_yVlep);
	fChain->SetBranchAddress("phiVlep", &phiVlep, &b_phiVlep);
	fChain->SetBranchAddress("massVlep", &massVlep, &b_massVlep);
	fChain->SetBranchAddress("ptlep1", &ptlep1, &b_ptlep1);
	fChain->SetBranchAddress("etalep1", &etalep1, &b_etalep1);
	fChain->SetBranchAddress("philep1", &philep1, &b_philep1);
	fChain->SetBranchAddress("ptlep2", &ptlep2, &b_ptlep2);
	fChain->SetBranchAddress("etalep2", &etalep2, &b_etalep2);
	fChain->SetBranchAddress("philep2", &philep2, &b_philep2);
	fChain->SetBranchAddress("drla", &drla, &b_drla);
	fChain->SetBranchAddress("drla2", &drla2, &b_drla2);
	fChain->SetBranchAddress("drj1a", &drj1a, &b_drj1a);
	fChain->SetBranchAddress("drj2a", &drj2a, &b_drj2a);
	fChain->SetBranchAddress("drj1l", &drj1l, &b_drj1l);
	fChain->SetBranchAddress("drj2l", &drj2l, &b_drj2l);
	fChain->SetBranchAddress("drj1l2", &drj1l2, &b_drj1l2);
	fChain->SetBranchAddress("drj2l2", &drj2l2, &b_drj2l2);
	fChain->SetBranchAddress("nlooseeles", &nlooseeles, &b_nlooseeles);
	fChain->SetBranchAddress("nloosemus", &nloosemus, &b_nloosemus);
	fChain->SetBranchAddress("MET_et", &MET_et, &b_MET_et);
	fChain->SetBranchAddress("photonet", &photonet, &b_photonet);
	fChain->SetBranchAddress("photoneta", &photoneta, &b_photoneta);
	fChain->SetBranchAddress("photonphi", &photonphi, &b_photonphi);
	fChain->SetBranchAddress("photone", &photone, &b_photone);
	fChain->SetBranchAddress("photonsieie", &photonsieie, &b_photonsieie);
	fChain->SetBranchAddress("photonphoiso", &photonphoiso, &b_photonphoiso);
	fChain->SetBranchAddress("photonchiso", &photonchiso, &b_photonchiso);
	fChain->SetBranchAddress("photonnhiso", &photonnhiso, &b_photonnhiso);
	fChain->SetBranchAddress("isprompt", &isprompt, &b_isprompt);
	fChain->SetBranchAddress("jet1pt", &jet1pt, &b_jet1pt);
	fChain->SetBranchAddress("jet1eta", &jet1eta, &b_jet1eta);
	fChain->SetBranchAddress("jet2pt", &jet2pt, &b_jet2pt);
	fChain->SetBranchAddress("jet2eta", &jet2eta, &b_jet2eta);
	fChain->SetBranchAddress("jet1phi", &jet1phi, &b_jet1phi);
	fChain->SetBranchAddress("jet2phi", &jet2phi, &b_jet2phi);
	fChain->SetBranchAddress("jet1e", &jet1e, &b_jet1e);
	fChain->SetBranchAddress("jet2e", &jet2e, &b_jet2e);
	fChain->SetBranchAddress("Mjj", &Mjj, &b_Mjj);
	fChain->SetBranchAddress("zepp", &zepp, &b_zepp);
	fChain->SetBranchAddress("deltaeta", &deltaeta, &b_deltaeta);
	fChain->SetBranchAddress("l1_weight", &l1_weight, &b_l1_weight);
}

EDBRHistoMaker::EDBRHistoMaker(TTree* tree, TFile* fileTMP, TH1F* hR1, std::string out_name_) {
	fChain = 0;

	// Which category do we want to analyze?
	fileTMP_ = fileTMP;
	hR1_ = hR1;
	out_name = out_name_;

	debug_ = true;
	Init(tree);
	createAllHistos();
	printAllHistos();
}

EDBRHistoMaker::~EDBRHistoMaker() {
	if (!fChain)
		return;
	delete fChain->GetCurrentFile();
}

Int_t EDBRHistoMaker::GetEntry(Long64_t entry) {
	// Read contents of entry.
	if (!fChain)
		return 0;
	return fChain->GetEntry(entry);
}

Long64_t EDBRHistoMaker::LoadTree(Long64_t entry) {
	// Set the environment to read one entry
	if (!fChain)
		return -5;
	Long64_t centry = fChain->LoadTree(entry);
	if (centry < 0)
		return centry;
	if (fChain->GetTreeNumber() != fCurrent) {
		fCurrent = fChain->GetTreeNumber();
	}
	return centry;
}

//-------------------------
// Infrastructure functions
//-------------------------

void EDBRHistoMaker::createAllHistos() {

	/// This part substitutes the big arrays that used to be 
	/// in the beginning of this file.
	/// Much simpler to create histos now: just add them to
	/// hs with hs.setHisto(name,nbins,min,max);
	hs.setHisto("nVtx", 20, -0.5, 35);
        hs.setHisto("photonet", 8, 25, 105);
        hs.setHisto("Mjj", 10, 150, 400);
        hs.setHisto("photoneta", 20, -1.5, 1.5);
        hs.setHisto("ptVlep", 25, 0, 1000);
        hs.setHisto("massVlep", 10, 70, 110);
        hs.setHisto("photonsieie", 10, 0, 0.012);
        hs.setHisto("photonphoiso", 10, 0, 2.5);
        hs.setHisto("ptlep1", 15, 20, 300);
        hs.setHisto("etalep1", 15, -2.5, 2.5);
        hs.setHisto("ptlep2", 15, 20, 300);
        hs.setHisto("etalep2", 15, -2.5, 2.5);
        hs.setHisto("zepp", 10, 0, 4);
	char buffer[256];
	char buffer2[256];

	nVars = hs.vars.size();

	for (int i = 0; i != nVars; ++i) {
		sprintf(buffer, "%s_mu", hs.vars[i].c_str());
		//    sprintf(buffer,"%s_el",hs.vars[i].c_str());
		sprintf(buffer2, "%s;%s;Number of events;", hs.vars[i].c_str(),
				hs.vars[i].c_str());
		TH1D* histogram = new TH1D(buffer, buffer2, hs.nBins[i], hs.minBin[i],
				hs.maxBin[i]);
		histogram->SetStats(kFALSE);
		histogram->SetDirectory(0);
		histogram->Sumw2();
		theHistograms[hs.vars[i]] = histogram;
	}

}

void EDBRHistoMaker::printAllHistos() {
	printf("We have %i histograms \n", int(theHistograms.size()));
	typedef std::map<std::string, TH1D*>::iterator it_type;
	for (it_type iterator = theHistograms.begin();
			iterator != theHistograms.end(); iterator++) {
	}
}

void EDBRHistoMaker::saveAllHistos(std::string outFileName) {

	TFile* outFile = TFile::Open(outFileName.c_str(), "RECREATE");

	for (int i = 0; i != nVars; ++i) {
		std::string name = hs.vars[i];
		const TH1D* thisHisto = this->theHistograms[name];
		thisHisto->Write();
	}
	outFile->Close();
}

///----------------------------------------------------------------
/// This is the important function, the loop over all events.
/// Here we fill the histograms according to cuts, weights,
/// and can also filter out events on an individual basis.
///----------------------------------------------------------------
void EDBRHistoMaker::Loop(std::string outFileName) {

	if (fChain == 0)
		return;
	int numbe_out = 0;
	Long64_t nentries = fChain->GetEntriesFast();
	std::cout << "nentries" << nentries << std::endl;
	Long64_t npp = fChain->GetEntries("theWeight>0.");
	Long64_t nmm = fChain->GetEntries("theWeight<0.");
	Double_t nn;
	std::cout << "numberofnp:" << npp << "  numberofnm:" << nmm << std::endl;
	Long64_t nbytes = 0, nb = 0;
	TLorentzVector Zp4, photonp4, jet1p4, jet2p4;
	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;

		nb = fChain->GetEntry(jentry);
		nbytes += nb;

		if (jentry % 1000000 == 0)
			std::cout << "Entry num " << jentry << std::endl;

		if (theWeight > 0)
			nn = 1;
		else
			nn = -1;

		actualWeight = lumiWeight * pileupWeight692 * scalef;
		detajj = fabs(jet1eta - jet2eta);

		Zp4.SetPtEtaPhiE(ptVlep, yVlep, phiVlep, massVlep);
		photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
		jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
		jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
		delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
		if (delta_phi>Pi) delta_phi=2*Pi-delta_phi;

		if (setUnitaryWeights_) {
			if (jentry == 0)
				printf("Unitary weights set!\n");
			actualWeight = 1;
		}

		if (lep == 13 && photonet > 25. && ((run_period<7 && HLT_Mu5 > 0)|| (run_period==7 && HLT_Mu2 > 0)) && fabs(photoneta) < 1.4442 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4
				&& nlooseeles == 0 && nloosemus < 3  
				&& massVlep > 70. && massVlep < 110. && jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && Mjj > 150) {
			numbe_out++;
			treename->Fill();
		}
		else
			continue;

		int iswjets = 0;
		int isnotwets = 0;
		int iszjets = 0;
		int isttjets = 0;

		TString filename = fileTMP_->GetName();
		if (filename.Contains("WJets") && isprompt != 1) {
			iswjets = 1;
			//   std::cout<<"WJETs"<<iswjets<<std::endl;
		}
		if (filename.Contains("ZJets") && isprompt != 1) {
			iszjets = 1;
		}
		if (filename.Contains("TTJets") && isprompt != 1) {
			isttjets = 1;
		}
		if (!(filename.Contains("WJets")) && !(filename.Contains("ZJets"))
				&& !(filename.Contains("TTJets"))) {
			isnotwets = 1;
		}

		if (isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0) {

			(theHistograms["nVtx"])->Fill(nVtx, actualWeight);
			(theHistograms["photonet"])->Fill(photonet, actualWeight);
			if(Mjj<397)(theHistograms["Mjj"])->Fill(Mjj, actualWeight);
			(theHistograms["photoneta"])->Fill(photoneta, actualWeight);
			(theHistograms["ptVlep"])->Fill(ptVlep, actualWeight);
			(theHistograms["massVlep"])->Fill(massVlep, actualWeight);
			(theHistograms["photonsieie"])->Fill(photonsieie, actualWeight);
			(theHistograms["photonphoiso"])->Fill(photonphoiso, actualWeight);
			(theHistograms["ptlep1"])->Fill(ptlep1, actualWeight);
			(theHistograms["etalep1"])->Fill(etalep1, actualWeight);
			(theHistograms["ptlep2"])->Fill(ptlep2, actualWeight);
			(theHistograms["etalep2"])->Fill(etalep2, actualWeight);
			(theHistograms["zepp"])->Fill(zepp, actualWeight);

		}
	}     //end loop over entries
	cout << "after cut: " << numbe_out << "*actualweight" << actualWeight
		<< " result " << numbe_out * actualWeight << endl;
	this->saveAllHistos(outFileName);
}

void EDBRHistoMaker::Loop_SFs_mc(std::string outFileName, TH2F* ID_photon, TH2F* ID_BF, TH2F* ID_GH, TH2F* ISO_BF, TH2F* ISO_GH, TGraphAsymmErrors* track_SF, TH2D* di_lep_trigger){

	if (fChain == 0)
		return;
	int numbe_out = 0;
	Long64_t nentries = fChain->GetEntriesFast();
	std::cout << "nentries" << nentries << std::endl;
	Long64_t npp = fChain->GetEntries("theWeight>0.");
	Long64_t nmm = fChain->GetEntries("theWeight<0.");
	Double_t nn;
	std::cout << "numberofnp:" << npp << "  numberofnm:" << nmm << std::endl;
	Long64_t nbytes = 0, nb = 0;

	TLorentzVector Zp4, photonp4, jet1p4, jet2p4;

	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;

		nb = fChain->GetEntry(jentry);
		nbytes += nb;

		if (jentry % 1000000 == 0)
			std::cout << "Entry num " << jentry << std::endl;

		if (theWeight > 0)
			nn = 1;
		else
			nn = -1;
		actualWeight = lumiWeight * pileupWeight692 * scalef;
		detajj = fabs(jet1eta - jet2eta);

		jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
		jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
		Zp4.SetPtEtaPhiE(ptVlep, yVlep, phiVlep, massVlep);
		photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
		delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
		if (delta_phi>Pi) delta_phi=2*Pi-delta_phi;

		if (setUnitaryWeights_) {
			if (jentry == 0)
				printf("Unitary weights set!\n");
			actualWeight = 1;
		}

		if (lep == 13 && photonet > 25. && HLT_Mu2 > 0
				&& fabs(photoneta) < 1.4442 && ptlep1 > 20.
				&& ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4
				&& nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && Mjj > 150) {
			numbe_out++;
			treename->Fill();
		}
		else
			continue;

		Double_t photon_ID_scale, ID_lep1, ID_lep2, ISO_lep1, ISO_lep2, Track_lep1, Track_lep2, trigger_SF, photon_ID, photon_eveto, ptlep1_tmp, ptlep2_tmp;;
		ptlep1_tmp=ptlep1;
                ptlep2_tmp=ptlep2;
		if(ptlep1>110) ptlep1_tmp=110.;
                if(ptlep2>110) ptlep2_tmp=110.;
		ID_lep1=0.55*ID_BF->GetBinContent(ID_BF->FindBin(fabs(etalep1),ptlep1_tmp))+0.45*ID_GH->GetBinContent(ID_GH->FindBin(fabs(etalep1),ptlep1_tmp));
		ID_lep2=0.55*ID_BF->GetBinContent(ID_BF->FindBin(fabs(etalep2),ptlep2_tmp))+0.45*ID_GH->GetBinContent(ID_GH->FindBin(fabs(etalep2),ptlep2_tmp));
		ISO_lep1=0.55*ISO_BF->GetBinContent(ISO_BF->FindBin(fabs(etalep1),ptlep1_tmp))+0.45*ISO_GH->GetBinContent(ISO_GH->FindBin(fabs(etalep1),ptlep1_tmp));
		ISO_lep2=0.55*ISO_BF->GetBinContent(ISO_BF->FindBin(fabs(etalep2),ptlep2_tmp))+0.45*ISO_GH->GetBinContent(ISO_GH->FindBin(fabs(etalep2),ptlep2_tmp));
		Track_lep1=track_SF->Eval(0.1+0.2*int(fabs(etalep1)/0.2));
		Track_lep2=track_SF->Eval(0.1+0.2*int(fabs(etalep2)/0.2));
		trigger_SF=di_lep_trigger->GetBinContent(di_lep_trigger->FindBin(fabs(etalep1),fabs(etalep2)));
		photon_ID_scale=ID_photon->GetBinContent(ID_photon->FindBin(photoneta,photonet));
		photon_eveto=0.9938;//barrel
		//photon_eveto=0.9875;//endcap
		actualWeight = actualWeight*ID_lep1*ID_lep2*ISO_lep1*ISO_lep2*Track_lep1*Track_lep2*trigger_SF*photon_ID_scale*photon_eveto;
		int iswjets = 0;
		int isnotwets = 0;
		int iszjets = 0;
		int isttjets = 0;

		TString filename = fileTMP_->GetName();
		if (filename.Contains("WJets") && isprompt != 1) {
			iswjets = 1;
		}
		if (filename.Contains("ZJets") && isprompt != 1) {
			iszjets = 1;
		}
		if (filename.Contains("TTJets") && isprompt != 1) {
			isttjets = 1;
		}
		if (!(filename.Contains("WJets")) && !(filename.Contains("ZJets"))
				&& !(filename.Contains("TTJets"))) {
			isnotwets = 1;
		}

		if (isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0) {

			(theHistograms["nVtx"])->Fill(nVtx, actualWeight);
			(theHistograms["photonet"])->Fill(photonet, actualWeight);
			(theHistograms["Mjj"])->Fill(Mjj, actualWeight);
			(theHistograms["photoneta"])->Fill(photoneta, actualWeight);
			(theHistograms["ptVlep"])->Fill(ptVlep, actualWeight);
			(theHistograms["massVlep"])->Fill(massVlep, actualWeight);
			(theHistograms["photonsieie"])->Fill(photonsieie, actualWeight);
			(theHistograms["photonphoiso"])->Fill(photonphoiso, actualWeight);
			(theHistograms["ptlep1"])->Fill(ptlep1, actualWeight);
			(theHistograms["etalep1"])->Fill(etalep1, actualWeight);
			(theHistograms["ptlep2"])->Fill(ptlep2, actualWeight);
			(theHistograms["etalep2"])->Fill(etalep2, actualWeight);
			(theHistograms["zepp"])->Fill(zepp, actualWeight);

		}
	}
	cout << "after cut: " << numbe_out << "*actualweight" << actualWeight
		<< " result " << numbe_out * actualWeight << endl;
	this->saveAllHistos(outFileName);
}
