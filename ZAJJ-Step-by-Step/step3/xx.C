#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void xx::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L xx.C
//      Root > xx t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t npp = fChain->GetEntries("theWeight>0.");
   Long64_t nmm = fChain->GetEntries("theWeight<0.");
   std::cout<< "numberofnp:" << npp << "  numberofnm:" <<nmm << std::endl;
 
   TFile * input1 = new TFile ("puweight.root");
   TH1* h = NULL;
   input1->GetObject("h2",h);


   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   if(jentry%100000==0) cout<<" "<<HLT_Ele1<<" "<<HLT_Mu1<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<endl;

   if(m_dataset=="outDMuonB.root"){ scalef=1.0; }
   if(m_dataset=="outDMuonC.root"){ scalef=1.0; }
   if(m_dataset=="outDMuonD.root"){ scalef=1.0; }
   if(m_dataset=="outDMuonE.root"){ scalef=1.0; }
   if(m_dataset=="outDMuonF.root"){ scalef=1.0; }
   if(m_dataset=="outDMuonG.root"){ scalef=1.0; }
   if(m_dataset=="outDMuonH.root"){ scalef=1.0; }
   if(m_dataset=="outWA.root"){ scalef=1000.*489.0/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outWJets.root"){ scalef=1000.*61526.7/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outZJets.root"){ scalef=1000.*5765.4/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outZA.root"){ scalef=1000.*117.864/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outTTA.root"){ scalef=1000.*3.697/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outTTJets.root"){ scalef=1000.*831.76/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outSTs.root"){ scalef=1000.*3.36/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outSTbartW.root"){ scalef=1000.*35.85/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outSTtW.root"){ scalef=1000.*35.85/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outSTt.root"){ scalef=1000.*136.02/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outSTbart.root"){ scalef=1000.*80.95/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outWW.root"){ scalef=1000.*118.7/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outWZ.root"){ scalef=1000.*47.13/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outZZ.root"){ scalef=1000.*16.523/float(npp-nmm)*fabs(theWeight)/theWeight; }
   if(m_dataset=="outZA-EWK.root"){ scalef=1000.*0.1097/float(npp-nmm)*fabs(theWeight)/theWeight; }


   if(m_dataset !="outDMuonB.root" && m_dataset !="outDMuonC.root" && m_dataset !="outDMuonD.root" && m_dataset !="outDMuonE.root" && m_dataset !="outDMuonF.root" && m_dataset !="outDMuonG.root" && m_dataset !="outDMuonH.root" )  {
      pileupWeight=h->GetBinContent(h->GetXaxis()->FindBin(npT));
     // cout<<pileupWeight<<endl;
          }
   ExTree->Fill();
   }
   input1->Close();
}
