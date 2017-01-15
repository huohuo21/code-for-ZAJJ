#include "TFile.h"
#include "TTree.h"
using namespace std;

void aa(){


	int event;
	double pweight[446]={0.};
	double genjet_pt[6]={0.}, genjet_eta[6]={0.},genjet_phi[6]={0.},genjet_e[6]={0.};
	TFile *file = new TFile("treePKU_Z.root");

	TTree *ZPKUCandidates = (TTree*) file->Get("treeDumper/ZPKUCandidates");
//	if (!ZPKUCandidates) {cout<<"ERROR"<<endl;exit(1);}
	
	ZPKUCandidates->SetBranchAddress("event",&event);
	ZPKUCandidates->SetBranchAddress("pweight",pweight);
	ZPKUCandidates->SetBranchAddress("genjet_pt",genjet_pt);
	ZPKUCandidates->SetBranchAddress("genjet_eta",genjet_eta);
	ZPKUCandidates->SetBranchAddress("genjet_phi",genjet_phi);
	ZPKUCandidates->SetBranchAddress("genjet_e",genjet_e);
	int entries= ZPKUCandidates->GetEntries();
	cout<< entries<<endl;

	double weight[299995][446]={0.}, bincount_nnpdf[101][2]={0.}, bincount_mmht[51][2]={0.}, bincount_ct10[53][2]={0.};
	double scale[3][2]={0.};
	double Mjj=0.;
	double genjet1_pt=0.,genjet1_eta=0.,genjet1_phi=0.,genjet1_e=0.;
	double genjet2_pt=0.,genjet2_eta=0.,genjet2_phi=0.,genjet2_e=0.;
	for (int i=0;i<entries;i++){
		ZPKUCandidates->GetEntry(i);
		// ghit genjetphijj
		genjet1_pt=genjet_pt[0];
		genjet1_eta=genjet_eta[0];
		genjet1_phi=genjet_phi[0];
		genjet1_e=genjet_e[0];
		genjet2_pt=genjet_pt[1];
		genjet2_eta=genjet_eta[1];
		genjet2_phi=genjet_phi[1];
		genjet2_e=genjet_e[1];
		TLorentzVector J1, J2;
		J1.SetPtEtaPhiE(genjet1_pt,genjet1_eta,genjet1_phi,genjet1_e);
		J2.SetPtEtaPhiE(genjet2_pt,genjet2_eta,genjet2_phi,genjet2_e);
		Mjj=(J1+J2).M();
		// calculate weight uncertainty of defferent PDF set
		for(int j=0;j<446;j++){
			weight[i][j]=pweight[j];
			if (Mjj>=400 && Mjj<=680){
				for (int i_wgh=0;i_wgh<101;i_wgh++){
					if (i_wgh<3){
						scale[i_wgh][0] += pweight[i_wgh];
						bincount_nnpdf[i_wgh][0] += pweight[9+i_wgh];
						bincount_mmht[i_wgh][0] += pweight[315+i_wgh];
						bincount_ct10[i_wgh][0] += pweight[392+i_wgh];
					}
					else if (i_wgh<51){
						bincount_nnpdf[i_wgh][0] += pweight[9+i_wgh];
						bincount_mmht[i_wgh][0] += pweight[315+i_wgh];
						bincount_ct10[i_wgh][0] += pweight[392+i_wgh];
					}
					else if(i_wgh<53){
						bincount_nnpdf[i_wgh][0] += pweight[9+i_wgh];
						bincount_ct10[i_wgh][0] += pweight[392+i_wgh];
					}
					else {
						bincount_nnpdf[i_wgh][0] += pweight[9+i_wgh];
					}
				}
			}
			else if(Mjj>680){
				for (int i_wgh=0;i_wgh<101;i_wgh++){
					if (i_wgh<3){
						scale[i_wgh][1] += pweight[i_wgh];
						bincount_nnpdf[i_wgh][1] += pweight[9+i_wgh];
						bincount_mmht[i_wgh][1] += pweight[315+i_wgh];
						bincount_ct10[i_wgh][1] += pweight[392+i_wgh];
					}
					else if (i_wgh<51){
						bincount_nnpdf[i_wgh][1] += pweight[9+i_wgh];
						bincount_mmht[i_wgh][1] += pweight[315+i_wgh];
						bincount_ct10[i_wgh][1] += pweight[392+i_wgh];
					}
					else if(i_wgh<53){
						bincount_nnpdf[i_wgh][1] += pweight[9+i_wgh];
						bincount_ct10[i_wgh][1] += pweight[392+i_wgh];
					}
					else {
						bincount_nnpdf[i_wgh][1] += pweight[9+i_wgh];
					}
				}
			}
			else continue;
		}
	}


//////////////////////// nnpdf//////////////////////////

	double mean_nnpdf_[2]={0.}, mean_nnpdf[2]={0.};
	for(int ii=0;ii<101;ii++){
		mean_nnpdf_[0] +=bincount_nnpdf[ii][0];
		mean_nnpdf_[1] +=bincount_nnpdf[ii][1];
	}
	mean_nnpdf[0]=mean_nnpdf_[0]/101.;          //central value
	mean_nnpdf[1]=mean_nnpdf_[1]/101.;			//central value
	cout<<"nnpdf bin1 "<<mean_nnpdf[0]<<" nnpdf bin2 "<<mean_nnpdf[1]<<endl;
	double sigma_nnpdf_[2]={0.}, sigma_nnpdf[2]={0.};
	for(int ii=1;ii<101;ii++){
		sigma_nnpdf_[0] += ((bincount_nnpdf[ii][0]-mean_nnpdf[0])*(bincount_nnpdf[ii][0]-mean_nnpdf[0]));
		sigma_nnpdf_[1] += ((bincount_nnpdf[ii][1]-mean_nnpdf[0])*(bincount_nnpdf[ii][1]-mean_nnpdf[1]));
	}

	sigma_nnpdf[0] = sqrt(sigma_nnpdf_[0])/(mean_nnpdf[0]*10.);
	sigma_nnpdf[1] = sqrt(sigma_nnpdf_[1])/(mean_nnpdf[1]*10.);

//////////////////////// mmht//////////////////////////

// bincount_mmht[0][0] bincount_mmht[0][1]  are central value
	double sigma_mmht_p_[2]={0.}, sigma_mmht_p[2]={0.};
	double sigma_mmht_m_[2]={0.}, sigma_mmht_m[2]={0.};
	for (int ii=1;ii<26;ii++){
		sigma_mmht_p_[0] += TMath::Power(TMath::Max(0.,TMath::Max(bincount_mmht[2*ii-1][0]-bincount_mmht[0][0],bincount_mmht[2*ii][0]-bincount_mmht[0][0])),2.);
		sigma_mmht_p_[1] += TMath::Power(TMath::Max(0.,TMath::Max(bincount_mmht[2*ii-1][1]-bincount_mmht[0][1],bincount_mmht[2*ii][1]-bincount_mmht[0][1])),2.);	
		sigma_mmht_m_[0] += TMath::Power(TMath::Max(0.,TMath::Max(-bincount_mmht[2*ii-1][0]+bincount_mmht[0][0],-bincount_mmht[2*ii][0]+bincount_mmht[0][0])),2.);
		sigma_mmht_m_[1] += TMath::Power(TMath::Max(0.,TMath::Max(-bincount_mmht[2*ii-1][1]+bincount_mmht[0][1],-bincount_mmht[2*ii][1]+bincount_mmht[0][1])),2.);
	}
	sigma_mmht_p[0] = sqrt(sigma_mmht_p_[0])/bincount_mmht[0][0];
	sigma_mmht_p[1] = sqrt(sigma_mmht_p_[1])/bincount_mmht[0][1];
	sigma_mmht_m[0] = sqrt(sigma_mmht_m_[0])/bincount_mmht[0][0];
	sigma_mmht_m[1] = sqrt(sigma_mmht_m_[1])/bincount_mmht[0][1];

	cout<<"mmht bin1 "<<bincount_mmht[0][0]<<"mmht bin2 "<<bincount_mmht[0][1]<<endl;

//////////////////////// ct10//////////////////////////
	
//bincount_ct10[0][0] bincount_ct10[0][1]	are central value
	double sigma_ct10_p_[2]={0.}, sigma_ct10_p[2]={0.};
	double sigma_ct10_m_[2]={0.}, sigma_ct10_m[2]={0.};
	for (int ii=1;ii<27;ii++){
		sigma_ct10_p_[0] += TMath::Power(TMath::Max(0.,TMath::Max(bincount_ct10[2*ii-1][0]-bincount_ct10[0][0],bincount_ct10[2*ii][0]-bincount_ct10[0][0])),2.);
		sigma_ct10_p_[1] += TMath::Power(TMath::Max(0.,TMath::Max(bincount_ct10[2*ii-1][1]-bincount_ct10[0][1],bincount_ct10[2*ii][1]-bincount_ct10[0][1])),2.);	
		sigma_ct10_m_[0] += TMath::Power(TMath::Max(0.,TMath::Max(-bincount_ct10[2*ii-1][0]+bincount_ct10[0][0],-bincount_ct10[2*ii][0]+bincount_ct10[0][0])),2.);
		sigma_ct10_m_[1] += TMath::Power(TMath::Max(0.,TMath::Max(-bincount_ct10[2*ii-1][1]+bincount_ct10[0][1],-bincount_ct10[2*ii][1]+bincount_ct10[0][1])),2.);
	}
	sigma_ct10_p[0] = sqrt(sigma_ct10_p_[0])/(1.64485*bincount_ct10[0][0]);
	sigma_ct10_p[1] = sqrt(sigma_ct10_p_[1])/(1.64485*bincount_ct10[0][1]);
	sigma_ct10_m[0] = sqrt(sigma_ct10_m_[0])/(1.64485*bincount_ct10[0][0]);
	sigma_ct10_m[1] = sqrt(sigma_ct10_m_[1])/(1.64485*bincount_ct10[0][1]);

	cout<<"ct10 bin1 "<<bincount_ct10[0][0]<<"ct10 bin2 "<<bincount_ct10[0][1]<<endl;

///////////////////////scale////////////////////////////

	cout<< scale[0][0] << " scale_mean " << scale[0][1]<<endl;
	cout<< scale[1][0] << " scale_low " << scale[1][1]<<endl;
	cout<< scale[2][0] << " scale_high " << scale[2][1]<<endl;	 
	cout<< sigma_nnpdf[0] <<" nnpdf "<< sigma_nnpdf[1]<<endl;
	cout<< sigma_mmht_p[0] <<" mmht_p "<< sigma_mmht_p[1]<<endl;
	cout<< sigma_mmht_m[0] <<" mmht_m "<< sigma_mmht_m[1]<<endl;
	cout<< sigma_ct10_p[0] <<" ct10_p "<< sigma_ct10_p[1]<<endl;
	cout<< sigma_ct10_m[0] <<" ct10_m "<< sigma_ct10_m[1]<<endl;

/* output   boundary 800

nnpdf bin1 3.84511e+06 nnpdf bin2 2.68579e+06
mmht bin1 3.51942e+06mmht bin2 2.4401e+06
ct10 bin1 4.00295e+06ct10 bin2 2.65994e+06
3.84407e+06 scale_mean 2.68492e+06
3.71611e+06 scale_low 2.48666e+06
3.96857e+06 scale_high 2.91288e+06
0.0375139 nnpdf 0.0390164
0.0169451 mmht_p 0.0232755
0.0204188 mmht_m 0.021773
0.0180681 ct10_p 0.0202602
0.0184743 ct10_m 0.0202063

boundary  680
nnpdf bin1 3.08891e+06 nnpdf bin2 3.44198e+06
mmht bin1 2.82862e+06mmht bin2 3.1309e+06
ct10 bin1 3.22677e+06ct10 bin2 3.43612e+06
3.0881e+06 scale_mean 3.44089e+06
2.99428e+06 scale_low 3.20848e+06
3.17702e+06 scale_high 3.70443e+06
0.0377263 nnpdf 0.0384046
0.0166556 mmht_p 0.0220765
0.0203846 mmht_m 0.0214686
0.0182486 ct10_p 0.0194389
0.0185438 ct10_m 0.019647



*/
	
}
