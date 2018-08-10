import ROOT
import sys
from DataFormats.FWLite import Events, Handle

from math import hypot, pi

def deltaPhi(phi1,phi2):
    ## Catch if being called with two objects                                                                                                                                             
    if type(phi1) != float and type(phi1) != int:
        phi1 = phi1.phi
    if type(phi2) != float and type(phi2) != int:
        phi2 = phi2.phi
    ## Otherwise                                                                                                                                                                          
    dphi = (phi1-phi2)
    while dphi >  pi: dphi -= 2*pi
    while dphi < -pi: dphi += 2*pi
    return dphi

def deltaR(eta1,phi1,eta2=None,phi2=None):
    ## catch if called with objects                                                                                                                                                       
    if eta2 == None:
        return deltaR(eta1.eta,eta1.phi,phi1.eta,phi1.phi)
    ## otherwise                                                                                                                                                                          
    return hypot(eta1-eta2, deltaPhi(phi1,phi2))

events_DYjets = Events (['root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/FE6DFC4B-91E5-E611-9EA2-0025905A6076.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/FACC175D-A5E5-E611-940F-70106F4A44AC.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/FA68D6E8-7DE5-E611-9158-0CC47A4C8EC6.root'])
events_zg = Events (['root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/ZGToLLG_01J_5f_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/810000/46736EB0-5D08-E811-A92F-02163E019B3C.root'])

xs_DYjets = 5765.4
xs_zg = 47.46

geninfo,geninfoLabel = Handle("GenEventInfoProduct"), "generator"
handlePruned  = Handle ("std::vector<reco::GenParticle>")
handlePacked  = Handle ("std::vector<pat::PackedGenParticle>")
labelPruned = ("prunedGenParticles")
labelPacked = ("packedGenParticles")

# loop over events
count= 0
countweighted = 0

th1f_zg_njets = ROOT.TH1F("wgjets njets","",7,-0.5,6.5)
th1f_DYjets_njets = ROOT.TH1F("wjets njets","",7,-0.5,6.5)

th1f_zg_photon_pt = ROOT.TH1F("wgjets photon pt","",10,25,125)
th1f_DYjets_photon_pt = ROOT.TH1F("wjets photon pt","",10,25,125)

th1f_zg_lepton_pt = ROOT.TH1F("wgjets lepton pt","",10,25,125)
th1f_DYjets_lepton_pt = ROOT.TH1F("wjets lepton pt","",10,25,125)

th1f_zg_delta_r = ROOT.TH1F("wgjets delta r","",35,0,3.5)
th1f_DYjets_delta_r = ROOT.TH1F("wjets delta r","",35,0,3.5)

th1f_zg_njets.Sumw2()
th1f_DYjets_njets.Sumw2()

th1f_zg_photon_pt.Sumw2()
th1f_DYjets_photon_pt.Sumw2()

th1f_zg_lepton_pt.Sumw2()
th1f_DYjets_lepton_pt.Sumw2()

th1f_zg_delta_r.Sumw2()
th1f_DYjets_delta_r.Sumw2()

for event in events_DYjets:

    if count > 1000000:
        break

    if count % 10000 == 0:
        print "count = " + str(count)

    count +=1

    event.getByLabel (labelPacked, handlePacked)

    packed = handlePacked.product()

    event.getByLabel (labelPruned, handlePruned)

    pruned = handlePruned.product()

    event.getByLabel(geninfoLabel,geninfo)

    gen = geninfo.product()

    if gen.weight() > 0:
        countweighted += 1
    else:
        countweighted -= 1

    nelectrons = 0

    for p in pruned :

        if abs(p.pdgId()) == 11 and p.pt() > 25 and abs(p.eta()) < 2.5 and (p.statusFlags().isPrompt()) and p.status() == 1  :
            nelectrons += 1
            electron = p

    if nelectrons != 2:
        continue

    nphotons = 0        

    for p in pruned :

        if abs(p.pdgId()) == 22 and p.pt() > 25 and abs(p.eta()) < 2.5 and (p.statusFlags().isPrompt()) and p.status() == 1   :
            nphotons += 1
            photon = p

    if nphotons != 1:
        continue

    if deltaR(electron.eta(), electron.phi(), photon.eta(), photon.phi()) < 0.5:
        continue

    njets = 0        

    for p in pruned :

        if (abs(p.pdgId()) == 1 or abs(p.pdgId()) == 2 or abs(p.pdgId()) == 3 or abs(p.pdgId()) == 4 or abs(p.pdgId()) == 5 or abs(p.pdgId()) == 21) and p.pt() > 30 and p.statusFlags().isPrompt() and p.statusFlags().isLastCopy()  :
#        if (abs(p.pdgId()) == 1 or abs(p.pdgId()) == 2) and p.pt() > 30 and p.statusFlags().isPrompt() and p.statusFlags().isLastCopy()  :
            njets +=1

    if gen.weight() > 0:
        th1f_DYjets_njets.Fill(njets,1)
        th1f_DYjets_photon_pt.Fill(photon.pt(),1)
        th1f_DYjets_lepton_pt.Fill(electron.pt(),1)
        th1f_DYjets_delta_r.Fill(deltaR(electron.eta(), electron.phi(), photon.eta(), photon.phi()),1)
    else:
        th1f_DYjets_njets.Fill(njets,-1)
        th1f_DYjets_photon_pt.Fill(photon.pt(),-1)
        th1f_DYjets_lepton_pt.Fill(electron.pt(),-1)
        th1f_DYjets_delta_r.Fill(deltaR(electron.eta(), electron.phi(), photon.eta(), photon.phi()),-1)

    #print njets

c = ROOT.TCanvas()

th1f_DYjets_njets.Scale(xs_DYjets*1000*36/countweighted)
th1f_DYjets_photon_pt.Scale(xs_DYjets*1000*36/countweighted)
th1f_DYjets_lepton_pt.Scale(xs_DYjets*1000*36/countweighted)
th1f_DYjets_delta_r.Scale(xs_DYjets*1000*36/countweighted)

th1f_DYjets_njets.SetLineWidth(3)
th1f_DYjets_photon_pt.SetLineWidth(3)
th1f_DYjets_lepton_pt.SetLineWidth(3)
th1f_DYjets_delta_r.SetLineWidth(3)

th1f_DYjets_njets.SetLineColor(ROOT.kRed)
th1f_DYjets_photon_pt.SetLineColor(ROOT.kRed)
th1f_DYjets_lepton_pt.SetLineColor(ROOT.kRed)
th1f_DYjets_delta_r.SetLineColor(ROOT.kRed)

count = 0
countweighted = 0

for event in events_zg:

    if count > 10000:
        break

    if count % 1000 == 0:
        print "count = " + str(count)

    count +=1

    event.getByLabel (labelPacked, handlePacked)

    packed = handlePacked.product()

    event.getByLabel (labelPruned, handlePruned)

    pruned = handlePruned.product()

    event.getByLabel(geninfoLabel,geninfo)

    gen = geninfo.product()

    if gen.weight() > 0:
        countweighted += 1
    else:
        countweighted -= 1

    nelectrons = 0

    for p in pruned :

#        if abs(p.pdgId()) == 11 and p.pt() > 25 and (p.statusFlags().isPrompt() or p.statusFlags().isPromptTauDecayProduct()) and p.status() == 1  :
        if abs(p.pdgId()) == 11 and p.pt() > 25 and abs(p.eta()) < 2.5 and (p.statusFlags().isPrompt())and p.status() == 1  :
            nelectrons += 1
            electron = p

    if nelectrons != 22
        continue

    nphotons = 0        

    for p in pruned :

#        if abs(p.pdgId()) == 22 and p.pt() > 25 and (p.statusFlags().isPrompt() or p.statusFlags().isPromptTauDecayProduct()) and p.status() == 1   :
        if abs(p.pdgId()) == 22 and p.pt() > 25 and abs(p.eta()) < 2.5 and (p.statusFlags().isPrompt()) and p.status() == 1   :
            nphotons += 1
            photon = p

    if nphotons != 1:
        continue

    if deltaR(electron.eta(), electron.phi(), photon.eta(), photon.phi()) < 0.5:
        continue

    njets = 0        

    for p in pruned :

        if (abs(p.pdgId()) == 1 or abs(p.pdgId()) == 2 or abs(p.pdgId()) == 3 or abs(p.pdgId()) == 4 or abs(p.pdgId()) == 5 or abs(p.pdgId()) == 21) and p.pt() > 30 and p.statusFlags().isPrompt() and p.statusFlags().isLastCopy()  :
#        if (abs(p.pdgId()) == 1 or abs(p.pdgId()) == 2) and p.pt() > 30 and p.statusFlags().isPrompt() and p.statusFlags().isLastCopy()  :
            njets +=1

    if gen.weight() > 0:
        th1f_zg_njets.Fill(njets,1)
        th1f_zg_photon_pt.Fill(photon.pt(),1)
        th1f_zg_lepton_pt.Fill(electron.pt(),1)
        th1f_zg_delta_r.Fill(deltaR(electron.eta(), electron.phi(), photon.eta(), photon.phi()),1)
    else:
        th1f_wjets_njets.Fill(njets,-1)
        th1f_wjets_photon_pt.Fill(photon.pt(),-1)
        th1f_wjets_lepton_pt.Fill(electron.pt(),-1)
        th1f_wjets_delta_r.Fill(deltaR(electron.eta(), electron.phi(), photon.eta(), photon.phi()),-1)
    #print njets

th1f_zg_njets.Scale(xs_zg*1000*36/countweighted)
th1f_zg_photon_pt.Scale(xs_zg*1000*36/countweighted)
th1f_zg_lepton_pt.Scale(xs_zg*1000*36/countweighted)
th1f_zg_delta_r.Scale(xs_zg*1000*36/countweighted)

th1f_zg_njets.SetLineWidth(3)
th1f_zg_photon_pt.SetLineWidth(3)
th1f_zg_lepton_pt.SetLineWidth(3)
th1f_zg_delta_r.SetLineWidth(3)

th1f_zg_njets.SetLineColor(ROOT.kBlue)
th1f_zg_photon_pt.SetLineColor(ROOT.kBlue)
th1f_zg_lepton_pt.SetLineColor(ROOT.kBlue)
th1f_zg_delta_r.SetLineColor(ROOT.kBlue)

if th1f_zg_lepton_pt.GetMaximum() > th1f_DYjets_lepton_pt.GetMaximum():
    th1f_zg_lepton_pt.Draw()
    th1f_zg_lepton_pt.GetXaxis().SetTitle("lepton pt (GeV)")
    th1f_zg_lepton_pt.SetStats(0)
    th1f_DYjets_lepton_pt.Draw("same")
else:
    th1f_DYjets_lepton_pt.Draw()
    th1f_DYjets_lepton_pt.GetXaxis().SetTitle("lepton pt (GeV)")
    th1f_DYjets_lepton_pt.SetStats(0)
    th1f_zg_lepton_pt.Draw("same")

leg=ROOT.TLegend(.50,.65,.80,.80)

leg.AddEntry(th1f_zg_lepton_pt,"zg+jets","l")
leg.AddEntry(th1f_DYjets_lepton_pt,"z+jets","l")

leg.Draw("same")

c.SaveAs("zg_DY.png")

