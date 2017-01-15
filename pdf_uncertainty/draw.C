void draw(){
	TCanvas *c1= new TCanvas("c1","test graph",800,800);
	double x_point1[2]={520.,1320.};
	double x_point2[2]={540.,1340.};
	double x_point3[2]={560.,1360.};
	double x_point4[2]={580.,1380.};
	double x_errorh[2]={140.,670.};
	double x_errorl[2]={140.,670.};
/*	double nnpdf_y[2]={3.84511e+06,2.68579e+06};
	double nnpdf_y_errorh[2]={0.14425e+06,0.105e+06};
	double nnpdf_y_errorl[2]={0.14425e+06,0.105e+06};
	double mmht_y[2]={3.51942e+06,2.4401e+06};
	double mmht_y_errorh[2]={0.0596e+06,0.0568e+06};
	double mmht_y_errorl[2]={0.0719e+06,0.0531e+06};
	double ct10_y[2]={4.00295e+06,2.65994e+06};
	double ct10_y_errorh[2]={0.0723e+06,0.0539e+06};
	double ct10_y_errorl[2]={0.074e+06,0.0537e+06};
	double scale_y[2]={3.84407e+06,2.68492e+06};
	double scale_y_errorh[2]={0.125e+06,0.228e+06};
	double scale_y_errorl[2]={0.128e+06,0.198e+06}; */


	double nnpdf_y[2]={3.08891e+06,3.44198e+06};
	double nnpdf_y_errorh[2]={0.117e+06,0.132e+06};
	double nnpdf_y_errorl[2]={0.117e+06,0.132e+06};
	double mmht_y[2]={2.82862e+06,3.1309e+06};
	double mmht_y_errorh[2]={0.047e+06,0.069e+06};
	double mmht_y_errorl[2]={0.058e+06,0.067e+06};
	double ct10_y[2]={3.22677e+06,3.43612e+06};
	double ct10_y_errorh[2]={0.059e+06,0.067e+06};
	double ct10_y_errorl[2]={0.06e+06,0.068e+06};
	double scale_y[2]={3.0881e+06,3.44089e+06};
	double scale_y_errorh[2]={0.09e+06,0.26e+06};
	double scale_y_errorl[2]={0.09e+06,0.23e+06};

	TGraphAsymmErrors* g_nnpdf=new TGraphAsymmErrors(2,x_point1,nnpdf_y,x_errorh,x_errorl,nnpdf_y_errorh,nnpdf_y_errorl);
	TGraphAsymmErrors* g_mmht=new TGraphAsymmErrors(2,x_point2,mmht_y,x_errorh,x_errorl,mmht_y_errorh,mmht_y_errorl);
	TGraphAsymmErrors* g_ct10=new TGraphAsymmErrors(2,x_point3,ct10_y,x_errorh,x_errorl,ct10_y_errorh,ct10_y_errorl);
	TGraphAsymmErrors* g_scale=new TGraphAsymmErrors(2,x_point4,scale_y,x_errorh,x_errorl,scale_y_errorh,scale_y_errorl);

	g_nnpdf->SetMarkerStyle(20);
	g_nnpdf->SetMarkerColor(2);
	g_nnpdf->SetLineColor(kRed);
	g_nnpdf->SetLineWidth(2);
	g_nnpdf->SetMarkerSize(1.2);
	g_nnpdf->SetTitle("PDF uncertainty");
	g_nnpdf->GetYaxis()->SetTitle("a.u.");
	g_nnpdf->GetXaxis()->SetTitle("gen_Mjj/GeV");
	g_nnpdf->GetXaxis()->CenterTitle();
	g_nnpdf->GetYaxis()->CenterTitle();
	g_nnpdf->GetYaxis()->SetRangeUser(2400000.,3800000.);
	TGaxis *myY = (TGaxis*)g_nnpdf->GetYaxis();
	myY->SetMaxDigits(2);
	TGaxis *myX = (TGaxis*)g_nnpdf->GetXaxis();
	myX->SetMaxDigits(4);
	g_nnpdf->GetYaxis()->SetTitleOffset(1.3);
	g_nnpdf->GetXaxis()->SetTitleOffset(1.1);
	g_nnpdf->Draw("AP");

	g_mmht->SetMarkerStyle(21);
	g_mmht->SetMarkerColor(3);
	g_mmht->SetLineColor(kGreen);
	g_mmht->SetLineWidth(2);
	g_mmht->SetMarkerSize(1.2);
	g_mmht->Draw("p same");

	g_ct10->SetMarkerStyle(34);
	g_ct10->SetMarkerColor(4);
	g_ct10->SetLineColor(kBlue);
	g_ct10->SetLineWidth(2);
	g_ct10->SetMarkerSize(1.2);
	g_ct10->Draw("p same");

	g_scale->SetMarkerStyle(23);
	g_scale->SetMarkerColor(1);
	g_scale->SetLineColor(kBlack);
	g_scale->SetLineWidth(2);
	g_scale->SetMarkerSize(1.2);
	g_scale->Draw("p same");

	TLegend *l1 = new TLegend(0.7799791,0.8080808,0.8998957,0.9);
	l1->SetBorderSize(1);
	l1->SetFillColor(0);
	l1->AddEntry(g_nnpdf,"nnpdf  ","lep");
	l1->AddEntry(g_mmht,"mmht ","lep");
	l1->AddEntry(g_ct10,"ct10 ", "lep");
	l1->AddEntry(g_scale,"scale ", "lep");
	l1->Draw();

	c1->SaveAs("PDF_uncertainty.png");
}

