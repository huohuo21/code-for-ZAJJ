import ROOT
import numpy as np
from ROOT import kBlue, kRed, kGreen, kPink, kCyan, kYellow
from optparse import OptionParser
from tdr_style import *
parser = OptionParser()

(options, args) = parser.parse_args()
print args

fit_result_file = ROOT.TFile.Open(args[0])

prefit_shapes = fit_result_file.Get('shapes_prefit')
postfit_shapes = fit_result_file.Get('shapes_fiti_s')

lumi = 35.9
ROOT.gROOT.LoadMacro('CMS_lumi.C')
ROOT.gROOT.LoadMacro('cmsLumi.C')
#ROOT.gROOT.LoadMacro('CMSTDRStyle.C')
#ROOT.CMSTDRStyle()
TDRStyle()

print 'start to make prefit plots'

pre_QCD = ROOT.TH1F('pre_qcd','pre_qcd',8,0,8)
pre_ST = ROOT.TH1F('pre_ST','pre_ST',8,0,8)
pre_WA = ROOT.TH1F('pre_ST','pre_ST',8,0,8)
pre_TTA = ROOT.TH1F('pre_TTA','pre_TTA',8,0,8)
pre_VBS = ROOT.TH1F('pre_VBS','pre_VBS',8,0,8)
pre_VV = ROOT.TH1F('pre_VV','pre_VV',8,0,8)
pre_non_prompt = ROOT.TH1F('pre_plj','pre_plj',8,0,8)
#pre_data = ROOT.TGraphAsymmErrors(8)
pre_data_x = [0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5]
pre_data_xel = [0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5]
pre_data_xer = [0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5]
pre_data_y = [0 for i in range(1,9)]
pre_data_yeh = [0 for i in range(1,9)]
pre_data_yel = [0 for i in range(1,9)]

pre_QCD.SetFillColor(kBlue-6);
pre_QCD.SetMarkerColor(kBlue-6);
pre_QCD.SetLineColor(kBlue-6);
pre_QCD.Scale(lumi);

pre_VBS.SetFillColor(kRed-9);
pre_VBS.SetMarkerColor(kRed-9);
pre_VBS.SetLineColor(kRed-9);
pre_VBS.Scale(lumi);
pre_VBS.SetMarkerStyle(21);

pre_WA.SetFillColor(kPink+8);
pre_WA.SetMarkerColor(kPink+8);
pre_WA.SetLineColor(kPink+8);
pre_WA.Scale(lumi);

pre_VV.SetFillColor(40);
pre_VV.SetMarkerColor(40);
pre_VV.SetLineColor(40);
pre_VV.Scale(lumi);

pre_TTA.SetFillColor(kCyan);
pre_TTA.SetMarkerColor(kCyan);
pre_TTA.SetLineColor(kCyan);
pre_TTA.Scale(lumi);

pre_ST.SetFillColor(kGreen+2);
pre_ST.SetMarkerColor(kGreen+2);
pre_ST.SetLineColor(kGreen+2);
pre_ST.Scale(lumi);

pre_non_prompt.SetFillColor(kYellow-7);
pre_non_prompt.SetMarkerColor(kYellow-7);
pre_non_prompt.SetLineColor(kYellow-7);


for i in range(1,9):
 if prefit_shapes.Get('ch{0}'.format(i)).FindObject('QCD'):
	(yields_QCD, error_QCD) = (prefit_shapes.Get('ch{0}'.format(i)).Get('QCD').GetBinContent(1), prefit_shapes.Get('ch{0}'.format(i)).Get('QCD').GetBinError(1))
	pre_QCD.SetBinContent(i, yields_QCD)
	pre_QCD.SetBinError(i, error_QCD)
 else:
	pre_QCD.SetBinContent(i, 0)
        pre_QCD.SetBinError(i, 0)

 if prefit_shapes.Get('ch{0}'.format(i)).FindObject('ST'):
	(yields_ST, error_ST) = (prefit_shapes.Get('ch{0}'.format(i)).Get('ST').GetBinContent(1), prefit_shapes.Get('ch{0}'.format(i)).Get('ST').GetBinError(1))
	pre_ST.SetBinContent(i, yields_ST)
	pre_ST.SetBinError(i, error_ST)
 else:
	pre_ST.SetBinContent(i, 0)
        pre_ST.SetBinError(i, 0)

 if prefit_shapes.Get('ch{0}'.format(i)).FindObject('TTA'):
	(yields_TTA, error_TTA) = (prefit_shapes.Get('ch{0}'.format(i)).Get('TTA').GetBinContent(1), prefit_shapes.Get('ch{0}'.format(i)).Get('TTA').GetBinError(1))
	pre_TTA.SetBinContent(i, yields_TTA)
	pre_TTA.SetBinError(i, error_TTA)
 else:
	pre_TTA.SetBinContent(i, 0)
        pre_TTA.SetBinError(i, 0)

 if prefit_shapes.Get('ch{0}'.format(i)).FindObject('WA'):
	(yields_WA, error_WA) = (prefit_shapes.Get('ch{0}'.format(i)).Get('WA').GetBinContent(1), prefit_shapes.Get('ch{0}'.format(i)).Get('WA').GetBinError(1))
	pre_WA.SetBinContent(i, yields_WA)
	pre_WA.SetBinError(i, error_WA)
 else:
	pre_WA.SetBinContent(i, 0)
        pre_WA.SetBinError(i, 0)


 if prefit_shapes.Get('ch{0}'.format(i)).FindObject('VBS'):
	(yields_VBS, error_VBS) = (prefit_shapes.Get('ch{0}'.format(i)).Get('VBS').GetBinContent(1), prefit_shapes.Get('ch{0}'.format(i)).Get('VBS').GetBinError(1))
	pre_VBS.SetBinContent(i, yields_VBS)
	pre_VBS.SetBinError(i, error_VBS)
 else:
	pre_VBS.SetBinContent(i, 0)
        pre_VBS.SetBinError(i, 0)

 if prefit_shapes.Get('ch{0}'.format(i)).FindObject('VV'):
	(yields_VV, error_VV) = (prefit_shapes.Get('ch{0}'.format(i)).Get('VV').GetBinContent(1), prefit_shapes.Get('ch{0}'.format(i)).Get('VV').GetBinError(1))
	pre_VV.SetBinContent(i, yields_VV)
	pre_VV.SetBinError(i, error_VV)
 else:
	pre_VV.SetBinContent(i, 0)
        pre_VV.SetBinError(i, 0)

 if prefit_shapes.Get('ch{0}'.format(i)).FindObject('non_prompt'):
	(yields_non_prompt, error_non_prompt) = (prefit_shapes.Get('ch{0}'.format(i)).Get('non_prompt').GetBinContent(1), prefit_shapes.Get('ch{0}'.format(i)).Get('non_prompt').GetBinError(1))
	pre_non_prompt.SetBinContent(i, yields_non_prompt)
	pre_non_prompt.SetBinError(i, error_non_prompt)
 else:
	pre_non_prompt.SetBinContent(i, 0)
        pre_non_prompt.SetBinError(i, 0)


 if prefit_shapes.Get('ch{0}'.format(i)).FindObject('data'):
	(yields_data, error_data_u, error_data_d) = (prefit_shapes.Get('ch{0}'.format(i)).Get('data').GetY(), prefit_shapes.Get('ch{0}'.format(i)).Get('data').GetErrorYhigh(1), prefit_shapes.Get('ch{0}'.format(i)).Get('data').GetErrorYlow(1))
	pre_data_y[i-1] = yields_data
	pre_data_yeh[i-1] = error_data_u
	pre_data_yel[i-1] = error_data_d
 else:
	pre_data_y[i-1] = 0
        pre_data_yeh[i-1] = 0
        pre_data_yel[i-1] = 0

pre_data = ROOT.TGraphAsymmErrors(8, np.array(pre_data_x), np.array(pre_data_y), np.array(pre_data_xel), np.array(pre_data_xer), np.array(pre_data_yel), np.array(pre_data_yeh))
pre_hstack = ROOT.THStack('hs','')
pre_hstack.SetMaximum(pre_QCD.GetBinContent(1)*2.5)
pre_hstack.Add(pre_ST)
pre_hstack.Add(pre_TTA)
pre_hstack.Add(pre_VV)
pre_hstack.Add(pre_WA)
pre_hstack.Add(pre_non_prompt)
pre_hstack.Add(pre_QCD)
pre_hstack.Add(pre_VBS)

c1 = ROOT.TCanvas('','',800,800)

ROOT.gStyle.SetPadBorderMode(0)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPadTickX(1)
ROOT.gStyle.SetPadTickY(1)
ROOT.gStyle.SetPadTickX(1)
ROOT.gStyle.SetPadTickY(1)
ROOT.gStyle.SetAxisColor(1, "XYZ")
ROOT.gStyle.SetStripDecimals(ROOT.kTRUE)
ROOT.gStyle.SetTickLength(0.03, "XYZ")
ROOT.gStyle.SetNdivisions(510, "XYZ")

c1.cd()
fPad1 = ROOT.TPad("pad1", "", 0.00, 0.00, 0.99, 0.99)
fPad1.Draw()
ROOT.CMS_lumi(fPad1, 4, 0, '35.9')

pre_hstack.Draw("HIST")
pre_hstack.GetYaxis().SetTitleOffset(0.95)
pre_hstack.GetYaxis().SetTitle("Events /bin")
pre_hstack.GetXaxis().SetTitle("m_{jj} (GeV)")
pre_hstack.GetXaxis().SetTitleOffset(1.3)
pre_hstack.GetXaxis().SetTitleSize(0.04)

pre_data.Draw("Same pe")

ROOT.cmsLumi(0);
c1.Update()
c1.Draw()
c1.SaveAs('aa.png')

fit_result_file.Close()
