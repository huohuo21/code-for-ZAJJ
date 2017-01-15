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
	EDBRHistoMaker(TTree *tree = 0, TFile *fileTMP = 0, TH1F* hR1 = 0);
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
	Double_t drj1a;
        Double_t drj2a;
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

	// List of branches
	TBranch *b_scalef;   //!
	TBranch *b_nVtx;   //!
	TBranch *b_theWeight;   //!
	TBranch *b_lumiWeight;   //!
	TBranch *b_pileupWeight;   //!
	TBranch *b_HLT_Ele1;   //!
	TBranch *b_HLT_Mu1;   //!
	TBranch *b_nump;   //!
	TBranch *b_numm;   //!
	TBranch *b_npT;   //!
	TBranch *b_lep;   //!
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
	TBranch *b_nlooseeles;   //!
	TBranch *b_nloosemus;   //!
	TBranch *b_MET_et;   //!
	TBranch *b_photonet;   //!
	TBranch *b_photoneta;   //!
	TBranch *b_photonsieie;   //!
	TBranch *b_photonphoiso;   //!
	TBranch *b_photonchiso;   //!
	TBranch *b_photonnhiso;   //!
	TBranch *b_isprompt;   //!
	TBranch *b_jet1pt;   //!
	TBranch *b_jet1eta;   //!
	TBranch *b_jet2pt;   //!
	TBranch *b_jet2eta;   //!
	TBranch *b_Mjj;    //!
	TBranch *b_zepp;
	TBranch *b_deltaeta;

	// Basic functions directly from MakeClass
	Int_t GetEntry(Long64_t entry);
	Long64_t LoadTree(Long64_t entry);
	void Init(TTree *tree);
	void Loop(std::string outFileName);
	void Loop_for_plj(std::string outFileName);

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

	fChain->SetBranchAddress("scalef", &scalef, &b_scalef);
	fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
	fChain->SetBranchAddress("theWeight", &theWeight, &b_theWeight);
	fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
	fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
	fChain->SetBranchAddress("HLT_Ele1", &HLT_Ele1, &b_HLT_Ele1);
	fChain->SetBranchAddress("HLT_Mu1", &HLT_Mu1, &b_HLT_Mu1);
	fChain->SetBranchAddress("nump", &nump, &b_nump);
	fChain->SetBranchAddress("numm", &numm, &b_numm);
	fChain->SetBranchAddress("npT", &npT, &b_npT);
	fChain->SetBranchAddress("lep", &lep, &b_lep);
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
	fChain->SetBranchAddress("nlooseeles", &nlooseeles, &b_nlooseeles);
	fChain->SetBranchAddress("nloosemus", &nloosemus, &b_nloosemus);
	fChain->SetBranchAddress("MET_et", &MET_et, &b_MET_et);
	fChain->SetBranchAddress("photonet", &photonet, &b_photonet);
	fChain->SetBranchAddress("photoneta", &photoneta, &b_photoneta);
	fChain->SetBranchAddress("photonsieie", &photonsieie, &b_photonsieie);
	fChain->SetBranchAddress("photonphoiso", &photonphoiso, &b_photonphoiso);
	fChain->SetBranchAddress("photonchiso", &photonchiso, &b_photonchiso);
	fChain->SetBranchAddress("photonnhiso", &photonnhiso, &b_photonnhiso);
	fChain->SetBranchAddress("isprompt", &isprompt, &b_isprompt);
	fChain->SetBranchAddress("jet1pt", &jet1pt, &b_jet1pt);
	fChain->SetBranchAddress("jet1eta", &jet1eta, &b_jet1eta);
	fChain->SetBranchAddress("jet2pt", &jet2pt, &b_jet2pt);
	fChain->SetBranchAddress("jet2eta", &jet2eta, &b_jet2eta);
	fChain->SetBranchAddress("Mjj", &Mjj, &b_Mjj);
	fChain->SetBranchAddress("zepp", &zepp, &b_zepp);
	fChain->SetBranchAddress("deltaeta", &deltaeta, &b_deltaeta);

}

EDBRHistoMaker::EDBRHistoMaker(TTree* tree, TFile* fileTMP, TH1F* hR1) {
	fChain = 0;

	// Which category do we want to analyze?
	fileTMP_ = fileTMP;
	hR1_ = hR1;

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
	hs.setHisto("photonet", 25, 25, 400);
	hs.setHisto("Mjj", 15, 150, 2000);
	hs.setHisto("photoneta", 20, -1.5, 1.5);
	hs.setHisto("ptVlep", 50, 0, 1000);
	hs.setHisto("massVlep", 10, 60, 120);
	hs.setHisto("photonsieie", 10, 0, 0.012);
	hs.setHisto("photonphoiso", 10, 0, 2.5);
	hs.setHisto("ptlep1", 15, 20, 200);
	hs.setHisto("etalep1", 15, -2.5, 2.5);
	hs.setHisto("ptlep2", 15, 20, 200);
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
	double actualWeight;
	Long64_t nentries = fChain->GetEntriesFast();
	std::cout << "nentries" << nentries << std::endl;
	Long64_t npp = fChain->GetEntries("theWeight>0.");
	Long64_t nmm = fChain->GetEntries("theWeight<0.");
	Double_t nn;
	std::cout << "numberofnp:" << npp << "  numberofnm:" << nmm << std::endl;
	Long64_t nbytes = 0, nb = 0;

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

		actualWeight = lumiWeight * pileupWeight * scalef;

		if (setUnitaryWeights_) {
			if (jentry == 0)
				printf("Unitary weights set!\n");
			actualWeight = 1;
		}

		if (lep == 13 && photonet > 25. && photonet < 400. && HLT_Mu1 > 0
			&& drla2 >0.5 && drla > 0.5 && fabs(photoneta) < 1.4442 && ptlep1 > 20.
			&& zepp < 1. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4
				&& nlooseeles == 0 && nloosemus < 3 && Mjj>150. && Mjj<2000. && jet1pt >30. && jet2pt>30. 
				&& jet1eta < 4.7 && jet2eta < 4.7 && massVlep > 70. && massVlep < 110.) {
			numbe_out++;
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
	}     //end loop over entries
	cout << "after cut: " << numbe_out << "*actualweight" << actualWeight
	<< " result " << numbe_out * actualWeight << endl;
	this->saveAllHistos(outFileName);
}


///-----------------------------------------------------------------------
/// same function to Loop, but it is specially for photon like jet samples
/// you should already compute the scale factor by doing fakerate and bin's
/// number of data and plj both.
///-----------------------------------------------------------------------
void EDBRHistoMaker::Loop_for_plj(std::string outFileName) {

	std::cout<<"use photon like jet sample"<<std::endl;
	double scale_plj[6] = {0.0164217, 0.0158593, 0.0124016, 0.0126362, 0.0152482, 0.0128221};
	if (fChain == 0)
		return;
	int numbe_out = 0;
	double actualWeight;
	Long64_t nentries = fChain->GetEntriesFast();
	std::cout << "nentries" << nentries << std::endl;
	Long64_t npp = fChain->GetEntries("theWeight>0.");
	Long64_t nmm = fChain->GetEntries("theWeight<0.");
	Double_t nn;
	std::cout << "numberofnp:" << npp << "  numberofnm:" << nmm << std::endl;
	Long64_t nbytes = 0, nb = 0;

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


		if (lep == 13 && photonet > 25. && photonet < 400. && HLT_Mu1 > 0 && drj1a >0.7 && drj2a >0.7
			&& zepp < 1. && drla2 >0.7 && drla > 0.7 && fabs(photoneta) < 1.4442 && ptlep1 > 20.
				&& ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4
				&& nlooseeles == 0 && nloosemus < 3 && Mjj>150. && Mjj<2000. && jet1pt >30. && jet2pt>30. 
				&& jet1eta < 4.7 && jet2eta < 4.7 && massVlep > 70. && massVlep < 110.) {
			numbe_out++;
		}
		else
			continue;

		if(photonet>120.) actualWeight = scale_plj[5];
		if(photonet>80.) actualWeight = scale_plj[4];
		if(photonet>60.) actualWeight = scale_plj[3];
		if(photonet>45.) actualWeight = scale_plj[2];
		if(photonet>35.) actualWeight = scale_plj[1];
		if(photonet>25.) actualWeight = scale_plj[0];

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
	}     //end loop over entries
	cout << "after cut: " << numbe_out << "*actualweight" << actualWeight
	<< " result " << numbe_out * actualWeight << endl;
	this->saveAllHistos(outFileName);
}
