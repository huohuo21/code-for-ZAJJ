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

events_DYjets = Events (['root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/FE6DFC4B-91E5-E611-9EA2-0025905A6076.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/FACC175D-A5E5-E611-940F-70106F4A44AC.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/FA68D6E8-7DE5-E611-9158-0CC47A4C8EC6.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/FA48B1F1-0DF1-E611-A5C1-02163E011CDB.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/F8E67C19-C7E4-E611-9333-F832E4CC4D39.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/F81F42AB-9FE5-E611-8BB1-0025905B8572.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/F6F73F10-13E4-E611-A8A2-0025901AC12A.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/F6E03A52-4CE4-E611-AA96-BC305B390A9A.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/F6D062B0-14F1-E611-B7BA-02163E0141C2.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/F6CAD34B-7EE5-E611-9536-0025905A6084.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/F6C6CF59-A5E5-E611-90A3-0CC47A4C8E86.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/F679BEBA-EFE3-E611-ADEE-D8D385AE8862.root'])
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

th1f_zg_njets = ROOT.TH1F("zg njets","",7,-0.5,6.5)
th1f_DYjets_njets = ROOT.TH1F("DYjets njets","",7,-0.5,6.5)

th1f_zg_photon_pt = ROOT.TH1F("zg photon pt","",10,25,125)
th1f_DYjets_photon_pt = ROOT.TH1F("DYjets photon pt","",10,25,125)

th1f_zg_lepton1_pt = ROOT.TH1F("zg lepton1 pt","",10,25,125)
th1f_DYjets_lepton1_pt = ROOT.TH1F("DYjets lepton1 pt","",10,25,125)

th1f_zg_lepton2_pt = ROOT.TH1F("zg lepton2 pt","",10,25,125)
th1f_DYjets_lepton2_pt = ROOT.TH1F("DYjets lepton2 pt","",10,25,125)

th1f_zg_delta1_r = ROOT.TH1F("zg delta1 r","",35,0,3.5)
th1f_DYjets_delta1_r = ROOT.TH1F("DYjets delta1 r","",35,0,3.5)

th1f_zg_delta2_r = ROOT.TH1F("zg delta2 r","",35,0,3.5)
th1f_DYjets_delta2_r = ROOT.TH1F("DYjets delta2 r","",35,0,3.5)

th1f_zg_njets.Sumw2()
th1f_DYjets_njets.Sumw2()

th1f_zg_photon_pt.Sumw2()
th1f_DYjets_photon_pt.Sumw2()

th1f_zg_lepton1_pt.Sumw2()
th1f_DYjets_lepton1_pt.Sumw2()

th1f_zg_lepton2_pt.Sumw2()
th1f_DYjets_lepton2_pt.Sumw2()

th1f_zg_delta1_r.Sumw2()
th1f_DYjets_delta1_r.Sumw2()

th1f_zg_delta2_r.Sumw2()
th1f_DYjets_delta2_r.Sumw2()

for event in events_DYjets:

    if count > 10000000:
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
    event_larger2electron = 0

    for p in pruned :

        if abs(p.pdgId()) == 11 and p.pt() > 25 and abs(p.eta()) < 2.5 and (p.statusFlags().isPrompt()) and p.status() == 1  :
	    if nelectrons==0:
		electron1 = p
	    if nelectrons==1:
		electron2 = p
            nelectrons += 1
    if nelectrons >2:
	event_larger2electron +=1
    if nelectrons != 2:
        continue

    nphotons = 0        

    for p in pruned :

        if abs(p.pdgId()) == 22 and p.pt() > 25 and abs(p.eta()) < 2.5 and (p.statusFlags().isPrompt()) and p.status() == 1   :
    	    if deltaR(electron1.eta(), electron1.phi(), p.eta(), p.phi()) < 0.5 or deltaR(electron2.eta(), electron2.phi(), p.eta(), p.phi()) < 0.5:
	        continue
            nphotons += 1
            photon = p

    if nphotons != 1:
        continue


    njets = 0        

    for p in pruned :

        if (abs(p.pdgId()) == 1 or abs(p.pdgId()) == 2 or abs(p.pdgId()) == 3 or abs(p.pdgId()) == 4 or abs(p.pdgId()) == 5 or abs(p.pdgId()) == 21) and p.pt() > 30 and p.statusFlags().isPrompt() and p.statusFlags().isLastCopy()  :
	    if deltaR(electron1.eta(), electron1.phi(), p.eta(), p.phi()) < 0.7 or deltaR(electron2.eta(), electron2.phi(), p.eta(), p.phi()) < 0.7 or deltaR(photon.eta(), photon.phi(), p.eta(), p.phi()) < 0.7:
                continue
#        if (abs(p.pdgId()) == 1 or abs(p.pdgId()) == 2) and p.pt() > 30 and p.statusFlags().isPrompt() and p.statusFlags().isLastCopy()  :
            njets +=1

    if gen.weight() > 0:
        th1f_DYjets_njets.Fill(njets,1)
        th1f_DYjets_photon_pt.Fill(photon.pt(),1)
        th1f_DYjets_lepton1_pt.Fill(electron1.pt(),1)
        th1f_DYjets_lepton2_pt.Fill(electron2.pt(),1)
        th1f_DYjets_delta1_r.Fill(deltaR(electron1.eta(), electron1.phi(), photon.eta(), photon.phi()),1)
        th1f_DYjets_delta2_r.Fill(deltaR(electron2.eta(), electron2.phi(), photon.eta(), photon.phi()),1)
    else:
        th1f_DYjets_njets.Fill(njets,-1)
        th1f_DYjets_photon_pt.Fill(photon.pt(),-1)
        th1f_DYjets_lepton1_pt.Fill(electron1.pt(),-1)
        th1f_DYjets_lepton2_pt.Fill(electron2.pt(),-1)
        th1f_DYjets_delta1_r.Fill(deltaR(electron1.eta(), electron1.phi(), photon.eta(), photon.phi()),-1)
        th1f_DYjets_delta2_r.Fill(deltaR(electron2.eta(), electron2.phi(), photon.eta(), photon.phi()),-1)

    #print njets

c1 = ROOT.TCanvas()
c2 = ROOT.TCanvas()
c3 = ROOT.TCanvas()
c4 = ROOT.TCanvas()
c5 = ROOT.TCanvas()
c6 = ROOT.TCanvas()

th1f_DYjets_njets.Scale(xs_DYjets*1000*36/countweighted)
th1f_DYjets_photon_pt.Scale(xs_DYjets*1000*36/countweighted)
th1f_DYjets_lepton1_pt.Scale(xs_DYjets*1000*36/countweighted)
th1f_DYjets_delta1_r.Scale(xs_DYjets*1000*36/countweighted)
th1f_DYjets_lepton2_pt.Scale(xs_DYjets*1000*36/countweighted)
th1f_DYjets_delta2_r.Scale(xs_DYjets*1000*36/countweighted)

th1f_DYjets_njets.SetLineWidth(3)
th1f_DYjets_photon_pt.SetLineWidth(3)
th1f_DYjets_lepton1_pt.SetLineWidth(3)
th1f_DYjets_lepton2_pt.SetLineWidth(3)
th1f_DYjets_delta1_r.SetLineWidth(3)
th1f_DYjets_delta2_r.SetLineWidth(3)

th1f_DYjets_njets.SetLineColor(ROOT.kRed)
th1f_DYjets_photon_pt.SetLineColor(ROOT.kRed)
th1f_DYjets_lepton1_pt.SetLineColor(ROOT.kRed)
th1f_DYjets_lepton2_pt.SetLineColor(ROOT.kRed)
th1f_DYjets_delta1_r.SetLineColor(ROOT.kRed)
th1f_DYjets_delta2_r.SetLineColor(ROOT.kRed)

count = 0
countweighted = 0

for event in events_zg:

    if count > 100000:
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
	    if nelectrons==0:
		electron1 = p
	    if nelectrons==1:
		electron2 = p
            nelectrons += 1

    if nelectrons != 2:
        continue

    nphotons = 0        

    for p in pruned :

#        if abs(p.pdgId()) == 22 and p.pt() > 25 and (p.statusFlags().isPrompt() or p.statusFlags().isPromptTauDecayProduct()) and p.status() == 1   :
        if abs(p.pdgId()) == 22 and p.pt() > 25 and abs(p.eta()) < 2.5 and (p.statusFlags().isPrompt()) and p.status() == 1   :
    	    if deltaR(electron1.eta(), electron1.phi(), p.eta(), p.phi()) < 0.5 or deltaR(electron2.eta(), electron2.phi(), p.eta(), p.phi()) < 0.5:
	        continue
            nphotons += 1
            photon = p

    if nphotons != 1:
        continue


    njets = 0        

    for p in pruned :

        if (abs(p.pdgId()) == 1 or abs(p.pdgId()) == 2 or abs(p.pdgId()) == 3 or abs(p.pdgId()) == 4 or abs(p.pdgId()) == 5 or abs(p.pdgId()) == 21) and p.pt() > 30 and p.statusFlags().isPrompt() and p.statusFlags().isLastCopy()  :
	    if deltaR(electron1.eta(), electron1.phi(), p.eta(), p.phi()) < 0.7 or deltaR(electron2.eta(), electron2.phi(), p.eta(), p.phi()) < 0.7 or deltaR(photon.eta(), photon.phi(), p.eta(), p.phi()) < 0.7:
		continue
#        if (abs(p.pdgId()) == 1 or abs(p.pdgId()) == 2) and p.pt() > 30 and p.statusFlags().isPrompt() and p.statusFlags().isLastCopy()  :
            njets +=1

    if gen.weight() > 0:
        th1f_zg_njets.Fill(njets,1)
        th1f_zg_photon_pt.Fill(photon.pt(),1)
        th1f_zg_lepton1_pt.Fill(electron1.pt(),1)
        th1f_zg_lepton2_pt.Fill(electron2.pt(),1)
        th1f_zg_delta1_r.Fill(deltaR(electron1.eta(), electron1.phi(), photon.eta(), photon.phi()),1)
        th1f_zg_delta2_r.Fill(deltaR(electron2.eta(), electron2.phi(), photon.eta(), photon.phi()),1)
    else:
        th1f_zg_njets.Fill(njets,-1)
        th1f_zg_photon_pt.Fill(photon.pt(),-1)
        th1f_zg_lepton1_pt.Fill(electron1.pt(),-1)
        th1f_zg_lepton2_pt.Fill(electron2.pt(),-1)
        th1f_zg_delta1_r.Fill(deltaR(electron1.eta(), electron1.phi(), photon.eta(), photon.phi()),-1)
        th1f_zg_delta2_r.Fill(deltaR(electron2.eta(), electron2.phi(), photon.eta(), photon.phi()),-1)
    #print njets

th1f_zg_njets.Scale(xs_zg*1000*36/countweighted)
th1f_zg_photon_pt.Scale(xs_zg*1000*36/countweighted)
th1f_zg_lepton1_pt.Scale(xs_zg*1000*36/countweighted)
th1f_zg_lepton2_pt.Scale(xs_zg*1000*36/countweighted)
th1f_zg_delta1_r.Scale(xs_zg*1000*36/countweighted)
th1f_zg_delta2_r.Scale(xs_zg*1000*36/countweighted)

th1f_zg_njets.SetLineWidth(3)
th1f_zg_photon_pt.SetLineWidth(3)
th1f_zg_lepton1_pt.SetLineWidth(3)
th1f_zg_lepton2_pt.SetLineWidth(3)
th1f_zg_delta1_r.SetLineWidth(3)
th1f_zg_delta2_r.SetLineWidth(3)

th1f_zg_njets.SetLineColor(ROOT.kBlue)
th1f_zg_photon_pt.SetLineColor(ROOT.kBlue)
th1f_zg_lepton1_pt.SetLineColor(ROOT.kBlue)
th1f_zg_lepton2_pt.SetLineColor(ROOT.kBlue)
th1f_zg_delta1_r.SetLineColor(ROOT.kBlue)
th1f_zg_delta2_r.SetLineColor(ROOT.kBlue)


f=ROOT.TFile.Open('out.root','RECREATE')
f.cd()
th1f_zg_njets.Write()
th1f_DYjets_njets.Write()

th1f_zg_photon_pt.Write()
th1f_DYjets_photon_pt.Write()

th1f_zg_lepton1_pt.Write()
th1f_DYjets_lepton1_pt.Write()

th1f_zg_lepton2_pt.Write()
th1f_DYjets_lepton2_pt.Write()

th1f_zg_delta1_r.Write()
th1f_DYjets_delta1_r.Write()

th1f_zg_delta2_r.Write()
th1f_DYjets_delta2_r.Write()

f.Close()
