# import ROOT in batch mode
import sys
oldargv = sys.argv[:]
sys.argv = [ '-b-' ]
import ROOT
from ROOT import kBlack, kBlue, kRed, kGreen
ROOT.gROOT.SetBatch(True)
sys.argv = oldargv

ROOT.gROOT.SetStyle('Plain')
c1 = ROOT.TCanvas('c1','Example',200,10,700,500)
h_pfiso_wo = ROOT.TH1F('pfiso_wo','pfiso_wo',100,-0.01,0.4)
h_trackiso_wo = ROOT.TH1F('trackiso_wo','trackiso_wo',100,-0.01,0.4)
h_pfiso_wi = ROOT.TH1F('pfiso_wi','pfiso_wi',100,-0.01,0.4)
h_trackiso_wi = ROOT.TH1F('trackiso_wi','trackiso_wi',100,-0.01,0.4)

# load FWLite C++ libraries
ROOT.gSystem.Load("libFWCoreFWLite.so");
ROOT.gSystem.Load("libDataFormatsFWLite.so");

# load FWlite python libraries
from DataFormats.FWLite import Handle, Events
import math

triggerBits, triggerBitLabel = Handle("edm::TriggerResults"), ("TriggerResults","","HLT")
eles, eleLabel = Handle('std::vector<pat::Electron>'), ('slimmedElectrons')
rho, rhoLabel = Handle('double'),('fixedGridRhoFastjetAll')
vtex, vtexLabel = Handle('std::vector<reco::Vertex>'), ('offlineSlimmedPrimaryVertices')
redirector = 'root://cms-xrd-global.cern.ch'
files = ['{0}/{1}'.format(redirector ,f) if f.startswith('/store') else f for f in sys.argv[1:]]
#events = Events(sys.argv[1:])
events = Events(files)


def getEffectiveArea(num):
	if math.fabs(num)<1: effective_area = 0.1703
	elif math.fabs(num)<1.479: effective_area = 0.1715
	elif math.fabs(num)<2: effective_area =  0.1213
	elif math.fabs(num)<2.2: effective_area =  0.1230
	elif math.fabs(num)<2.3: effective_area =  0.1635
	elif math.fabs(num)<2.4: effective_area =  0.1937
	elif math.fabs(num)<5: effective_area = 0.2393
	else : effective_area = 0
	return effective_area


for iev,event in enumerate(events):
    event.getByLabel(triggerBitLabel, triggerBits)
    names = event.object().triggerNames(triggerBits.product())
    if iev%1000==0: print "processing ", iev
    event.getByLabel(vtexLabel, vtex)
    event.getByLabel(eleLabel, eles)
    event.getByLabel(rhoLabel, rho)
    rho_val = rho.product()[0]
    for i in xrange(triggerBits.product().size()):
        if names.triggerName(i).find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v")==-1:
         continue
	else:
         for ele in eles.product():
	       eta = ele.superCluster().eta()
	       pt = ele.pt()
	       eA = getEffectiveArea(eta)
	       pf_iso = (ele.pfIsolationVariables().sumChargedHadronPt + max(0, ele.pfIsolationVariables().sumNeutralHadronEt + ele.pfIsolationVariables().sumPhotonEt - eA*rho_val))/pt
	       track_iso = ele.dr03TkSumPt()/pt
	       h_pfiso_wo.Fill(pf_iso)
               h_trackiso_wo.Fill(track_iso)
	       if not triggerBits.product().accept(i):
		 h_pfiso_wi.Fill(pf_iso)
		 h_trackiso_wi.Fill(track_iso)
	       
print 'pfiso_wo', h_pfiso_wo.Integral()
print 'trackiso_wo', h_trackiso_wo.Integral()
print 'pfiso_wi', h_pfiso_wi.Integral()
print 'trackiso_wi', h_trackiso_wo.Integral()
h_pfiso_wo.SetLineColor(kRed)
h_pfiso_wo.SetStats(0)
h_pfiso_wo.GetYaxis().SetRangeUser(1,1.1*h_pfiso_wo.Integral())
h_pfiso_wo.Draw()
h_trackiso_wo.SetLineColor(kBlack)
h_trackiso_wo.Draw('SAME')
h_pfiso_wi.SetLineColor(kBlue)
h_pfiso_wi.Draw('SAME')
h_trackiso_wi.SetLineColor(kGreen)
h_trackiso_wi.Draw('SAME')

l1 = ROOT.TLegend(0.65,0.75,0.9,0.9)
l1.AddEntry(h_pfiso_wo,'pfiso without HLT')
l1.AddEntry(h_trackiso_wo,'trackiso without HLT')
l1.AddEntry(h_pfiso_wi,'pfiso with HLT')
l1.AddEntry(h_trackiso_wi,'trackiso with HLT')
l1.Draw()

c1.SetLogy()
c1.Update()
c1.Print('selection.png')
