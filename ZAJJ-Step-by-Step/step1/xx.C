#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void xx::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   cout<<"Nevents="<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%100000==0) cout<<" "<<HLT_Ele1<<" "<<HLT_Mu1<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<endl;
	
	ExTree->Fill();	}
}
