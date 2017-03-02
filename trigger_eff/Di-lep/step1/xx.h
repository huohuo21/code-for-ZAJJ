//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 28 06:29:17 2016 by ROOT version 5.34/18
// from TTree ZPKUCandidates/ZPKU Candidates
// found on file: STt.root
//////////////////////////////////////////////////////////

#ifndef xx_h
#define xx_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxpassFilter_HBHE = 1;
const Int_t kMaxpassFilter_HBHEIso = 1;
const Int_t kMaxpassFilter_globalTightHalo = 1;
const Int_t kMaxpassFilter_ECALDeadCell = 1;
const Int_t kMaxpassFilter_GoodVtx = 1;
const Int_t kMaxpassFilter_EEBadSc = 1;
const Int_t kMaxpassFilter_badMuon = 1;
const Int_t kMaxpassFilter_badChargedHadron = 1;

class xx {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           event;
   Int_t           nVtx;
   Double_t        theWeight;
   Double_t        nump;
   Double_t        numm;
   Double_t        npT;
   Int_t           lep;
   Double_t        ptVlep;
   Double_t        yVlep;
   Double_t        phiVlep;
   Double_t        massVlep;
   Double_t        Mla;
   Double_t        Mla2;
   Double_t        Mva;
   Int_t           nlooseeles;
   Int_t           nloosemus;
   Bool_t          passEleVeto;
   Bool_t          passEleVetonew;
   Bool_t          passPixelSeedVeto;
   Double_t        photonet;
   Double_t        photoneta;
   Double_t        photonphi;
   Double_t        photone;
   Double_t        photonsieie;
   Double_t        photonphoiso;
   Double_t        photonchiso;
   Double_t        photonnhiso;
   Int_t           iphoton;
   Double_t        drla;
   Double_t        drla2;
   Int_t           isTrue;
   Int_t           isprompt;
   Double_t        jet1pt;
   Double_t        jet1eta;
   Double_t        jet1phi;
   Double_t        jet1e;
   Double_t        jet1csv;
   Double_t        jet1icsv;
   Double_t        jet2pt;
   Double_t        jet2eta;
   Double_t        jet2phi;
   Double_t        jet2e;
   Double_t        jet2csv;
   Double_t        jet2icsv;
   Double_t        drj1a;
   Double_t        drj2a;
   Double_t        drj1l;
   Double_t        drj2l;
   Double_t        drj1l2;
   Double_t        drj2l2;
   Double_t        Mjj;
   Double_t        deltaeta;
   Double_t        zepp;
   Double_t        ptlep1;
   Double_t        etalep1;
   Double_t        philep1;
   Double_t        ptlep2;
   Double_t        etalep2;
   Double_t        philep2;
   Double_t        j1metPhi;
   Double_t        j2metPhi;
   Double_t        MET_et;
   Double_t        MET_phi;
   Int_t           HLT_Ele1;
   Int_t           HLT_Mu1;
   Int_t           HLT_Mu2;
   Int_t           HLT_Mu3;
   Int_t           HLT_Mu4;
   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_theWeight;   //!
   TBranch        *b_nump;   //!
   TBranch        *b_numm;   //!
   TBranch        *b_npT;   //!
   TBranch        *b_lep;   //!
   TBranch        *b_ptVlep;   //!
   TBranch        *b_yVlep;   //!
   TBranch        *b_phiVlep;   //!
   TBranch        *b_massVlep;   //!
   TBranch        *b_Mla;   //!
   TBranch        *b_Mla2;   //!
   TBranch        *b_Mva;   //!
   TBranch        *b_nlooseeles;   //!
   TBranch        *b_nloosemus;   //!
   TBranch        *b_passEleVeto;   //!
   TBranch        *b_passEleVetonew;   //!
   TBranch        *b_passPixelSeedVeto;   //!
   TBranch        *b_photonet;   //!
   TBranch        *b_photoneta;   //!
   TBranch        *b_photonphi;   //!
   TBranch        *b_photone;   //!
   TBranch        *b_photonsieie;   //!
   TBranch        *b_photonphoiso;   //!
   TBranch        *b_photonchiso;   //!
   TBranch        *b_photonnhiso;   //!
   TBranch        *b_iphoton;   //!
   TBranch        *b_drla;   //!
   TBranch        *b_drla2;   //!
   TBranch        *b_isTrue;   //!
   TBranch        *b_isprompt;   //!
   TBranch        *b_jet1pt;   //!
   TBranch        *b_jet1eta;   //!
   TBranch        *b_jet1phi;   //!
   TBranch        *b_jet1e;   //!
   TBranch        *b_jet1csv;   //!
   TBranch        *b_jet1icsv;   //!
   TBranch        *b_jet2pt;   //!
   TBranch        *b_jet2eta;   //!
   TBranch        *b_jet2phi;   //!
   TBranch        *b_jet2e;   //!
   TBranch        *b_jet2csv;   //!
   TBranch        *b_jet2icsv;   //!
   TBranch        *b_drj1a;   //!
   TBranch        *b_drj2a;   //!
   TBranch        *b_drj1l;   //!
   TBranch        *b_drj2l;   //!
   TBranch        *b_drj1l2;   //!
   TBranch        *b_drj2l2;   //!
   TBranch        *b_Mjj;   //!
   TBranch        *b_deltaeta;   //!
   TBranch        *b_zepp;   //!
   TBranch        *b_ptlep1;   //!
   TBranch        *b_etalep1;   //!
   TBranch        *b_philep1;   //!
   TBranch        *b_ptlep2;   //!
   TBranch        *b_etalep2;   //!
   TBranch        *b_philep2;   //!
   TBranch        *b_j1metPhi;   //!
   TBranch        *b_j2metPhi;   //!
   TBranch        *b_MET_et;   //!
   TBranch        *b_MET_phi;   //!
   TBranch        *b_HLT_Ele1;   //!
   TBranch        *b_HLT_Mu1;   //!
   TBranch        *b_HLT_Mu2;   //!
   TBranch        *b_HLT_Mu3;   //!
   TBranch        *b_HLT_Mu4;

/// Meng
   TString m_dataset;
   xx(TTree *tree=0, TString dataset="");
///  Lu

   virtual ~xx();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

///Meng
private:
    TTree *ExTree;
    TFile *fout;
    double scalef;
///Lu
};

#endif

#ifdef xx_cxx
xx::xx(TTree *tree,TString dataset) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("STt.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("STt.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("STt.root:/treeDumper");
      dir->GetObject("ZPKUCandidates",tree);

   }
///Meng
	m_dataset=dataset;
///Lu
   Init(tree);
}

xx::~xx()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t xx::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t xx::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void xx::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fout = new TFile(m_dataset, "RECREATE");
   ExTree = new TTree("demo","demo");
   ExTree->Branch("scalef",&scalef,"scalef/D");
   ExTree->Branch("nVtx", &nVtx, "nVtx/I");
   ExTree->Branch("HLT_Ele1", &HLT_Ele1, "HLT_Ele1/I");
   ExTree->Branch("HLT_Mu1", &HLT_Mu1, "HLT_Mu1/I");
   ExTree->Branch("HLT_Mu2", &HLT_Mu2, "HLT_Mu2/I");
   ExTree->Branch("HLT_Mu3", &HLT_Mu3, "HLT_Mu3/I");
   ExTree->Branch("HLT_Mu4", &HLT_Mu4, "HLT_Mu4/I");
   ExTree->Branch("nump", &nump, "nump/D");
   ExTree->Branch("numm", &numm, "numm/D");
   ExTree->Branch("npT", &npT, "npT/D");
   ExTree->Branch("lep", &lep, "lep/I");
   ExTree->Branch("ptVlep", &ptVlep, "ptVlep/D");
   ExTree->Branch("yVlep", &yVlep, "yVlep/D");
   ExTree->Branch("phiVlep", &phiVlep, "phiVlep/D");
   ExTree->Branch("massVlep", &massVlep, "massVlep/D");
   ExTree->Branch("ptlep1", &ptlep1, "ptlep1/D");
   ExTree->Branch("etalep1", &etalep1, "etalep1/D");
   ExTree->Branch("philep1", &philep1, "philep1/D");
   ExTree->Branch("ptlep2", &ptlep2, "ptlep2/D");
   ExTree->Branch("etalep2", &etalep2, "etalep2/D");
   ExTree->Branch("philep2", &philep2, "philep2/D");
   ExTree->Branch("drla", &drla, "drla/D");
   ExTree->Branch("drla2", &drla2, "drla2/D");
   ExTree->Branch("nlooseeles", &nlooseeles, "nlooseeles/I");
   ExTree->Branch("drj1a", &drj1a, "drj1a/D");
   ExTree->Branch("drj2a", &drj2a, "drj2a/D");
   ExTree->Branch("drj1l", &drj1l, "drj1l/D");
   ExTree->Branch("drj2l", &drj2l, "drj2l/D");
   ExTree->Branch("drj1l2", &drj1l2, "drj1l2/D");
   ExTree->Branch("drj2l2", &drj2l2, "drj2l2/D");
   ExTree->Branch("nloosemus", &nloosemus, "nloosemus/I");
   ExTree->Branch("MET_et", &MET_et, "MET_et/D");
   ExTree->Branch("photonet", &photonet, "photonet/D");
   ExTree->Branch("photoneta", &photoneta, "photoneta/D");
   ExTree->Branch("photonsieie", &photonsieie, "photonsieie/D");
   ExTree->Branch("photonphoiso", &photonphoiso, "photonphoiso/D");
   ExTree->Branch("photonchiso", &photonchiso, "photonchiso/D");
   ExTree->Branch("photonnhiso", &photonnhiso, "photonnhiso/D");
   ExTree->Branch("isprompt", &isprompt, "isprompt/I");
   ExTree->Branch("jet1pt", &jet1pt, "jet1pt/D");
   ExTree->Branch("jet1eta", &jet1eta, "jet1eta/D");
   ExTree->Branch("jet2pt", &jet2pt, "jet2pt/D");
   ExTree->Branch("jet2eta", &jet2eta, "jet2eta/D");
   ExTree->Branch("Mjj", &Mjj, "Mjj/D");
   ExTree->Branch("zepp", &zepp, "zepp/D");
   ExTree->Branch("deltaeta", &deltaeta, "deltaeta/D");   

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("theWeight", &theWeight, &b_theWeight);
   fChain->SetBranchAddress("nump", &nump, &b_nump);
   fChain->SetBranchAddress("numm", &numm, &b_numm);
   fChain->SetBranchAddress("npT", &npT, &b_npT);
   fChain->SetBranchAddress("lep", &lep, &b_lep);
   fChain->SetBranchAddress("ptVlep", &ptVlep, &b_ptVlep);
   fChain->SetBranchAddress("yVlep", &yVlep, &b_yVlep);
   fChain->SetBranchAddress("phiVlep", &phiVlep, &b_phiVlep);
   fChain->SetBranchAddress("massVlep", &massVlep, &b_massVlep);
   fChain->SetBranchAddress("Mla", &Mla, &b_Mla);
   fChain->SetBranchAddress("Mla2", &Mla2, &b_Mla2);
   fChain->SetBranchAddress("Mva", &Mva, &b_Mva);
   fChain->SetBranchAddress("nlooseeles", &nlooseeles, &b_nlooseeles);
   fChain->SetBranchAddress("nloosemus", &nloosemus, &b_nloosemus);
   fChain->SetBranchAddress("passEleVeto", &passEleVeto, &b_passEleVeto);
   fChain->SetBranchAddress("passEleVetonew", &passEleVetonew, &b_passEleVetonew);
   fChain->SetBranchAddress("passPixelSeedVeto", &passPixelSeedVeto, &b_passPixelSeedVeto);
   fChain->SetBranchAddress("photonet", &photonet, &b_photonet);
   fChain->SetBranchAddress("photoneta", &photoneta, &b_photoneta);
   fChain->SetBranchAddress("photonphi", &photonphi, &b_photonphi);
   fChain->SetBranchAddress("photone", &photone, &b_photone);
   fChain->SetBranchAddress("photonsieie", &photonsieie, &b_photonsieie);
   fChain->SetBranchAddress("photonphoiso", &photonphoiso, &b_photonphoiso);
   fChain->SetBranchAddress("photonchiso", &photonchiso, &b_photonchiso);
   fChain->SetBranchAddress("photonnhiso", &photonnhiso, &b_photonnhiso);
   fChain->SetBranchAddress("iphoton", &iphoton, &b_iphoton);
   fChain->SetBranchAddress("drla", &drla, &b_drla);
   fChain->SetBranchAddress("drla2", &drla2, &b_drla2);
   fChain->SetBranchAddress("isTrue", &isTrue, &b_isTrue);
   fChain->SetBranchAddress("isprompt", &isprompt, &b_isprompt);
   fChain->SetBranchAddress("jet1pt", &jet1pt, &b_jet1pt);
   fChain->SetBranchAddress("jet1eta", &jet1eta, &b_jet1eta);
   fChain->SetBranchAddress("jet1phi", &jet1phi, &b_jet1phi);
   fChain->SetBranchAddress("jet1e", &jet1e, &b_jet1e);
   fChain->SetBranchAddress("jet1csv", &jet1csv, &b_jet1csv);
   fChain->SetBranchAddress("jet1icsv", &jet1icsv, &b_jet1icsv);
   fChain->SetBranchAddress("jet2pt", &jet2pt, &b_jet2pt);
   fChain->SetBranchAddress("jet2eta", &jet2eta, &b_jet2eta);
   fChain->SetBranchAddress("jet2phi", &jet2phi, &b_jet2phi);
   fChain->SetBranchAddress("jet2e", &jet2e, &b_jet2e);
   fChain->SetBranchAddress("jet2csv", &jet2csv, &b_jet2csv);
   fChain->SetBranchAddress("jet2icsv", &jet2icsv, &b_jet2icsv);
   fChain->SetBranchAddress("drj1a", &drj1a, &b_drj1a);
   fChain->SetBranchAddress("drj2a", &drj2a, &b_drj2a);
   fChain->SetBranchAddress("drj1l", &drj1l, &b_drj1l);
   fChain->SetBranchAddress("drj2l", &drj2l, &b_drj2l);
   fChain->SetBranchAddress("drj1l2", &drj1l2, &b_drj1l2);
   fChain->SetBranchAddress("drj2l2", &drj2l2, &b_drj2l2);
   fChain->SetBranchAddress("Mjj", &Mjj, &b_Mjj);
   fChain->SetBranchAddress("deltaeta", &deltaeta, &b_deltaeta);
   fChain->SetBranchAddress("zepp", &zepp, &b_zepp);
   fChain->SetBranchAddress("ptlep1", &ptlep1, &b_ptlep1);
   fChain->SetBranchAddress("etalep1", &etalep1, &b_etalep1);
   fChain->SetBranchAddress("philep1", &philep1, &b_philep1);
   fChain->SetBranchAddress("ptlep2", &ptlep2, &b_ptlep2);
   fChain->SetBranchAddress("etalep2", &etalep2, &b_etalep2);
   fChain->SetBranchAddress("philep2", &philep2, &b_philep2);
   fChain->SetBranchAddress("j1metPhi", &j1metPhi, &b_j1metPhi);
   fChain->SetBranchAddress("j2metPhi", &j2metPhi, &b_j2metPhi);
   fChain->SetBranchAddress("MET_et", &MET_et, &b_MET_et);
   fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
   fChain->SetBranchAddress("HLT_Ele1", &HLT_Ele1, &b_HLT_Ele1);
   fChain->SetBranchAddress("HLT_Mu1", &HLT_Mu1, &b_HLT_Mu1);
   fChain->SetBranchAddress("HLT_Mu2", &HLT_Mu2, &b_HLT_Mu2);
   fChain->SetBranchAddress("HLT_Mu3", &HLT_Mu3, &b_HLT_Mu3);
   fChain->SetBranchAddress("HLT_Mu4", &HLT_Mu4, &b_HLT_Mu4);
   Notify();
}

Bool_t xx::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void xx::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
///Meng
void xx::endJob() {
    fout->cd();
    ExTree->Write();
    fout->Write();
    fout->Close();
    delete fout;
 }
///Lu


Int_t xx::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef xx_cxx
