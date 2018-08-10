import ROOT
import sys
from DataFormats.FWLite import Events, Handle

from math import hypot, pi

events_DYjets = Events (['root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/FE6DFC4B-91E5-E611-9EA2-0025905A6076.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/FACC175D-A5E5-E611-940F-70106F4A44AC.root','root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/90000/FA68D6E8-7DE5-E611-9158-0CC47A4C8EC6.root'])
events_zg = Events (['root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv2/ZGToLLG_01J_5f_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/810000/46736EB0-5D08-E811-A92F-02163E019B3C.root'])

xs_DYjets = 5765.4
xs_zg = 47.46

geninfo,geninfoLabel = Handle("GenEventInfoProduct"), "generator"
handlePruned  = Handle ("std::vector<reco::GenParticle>")
labelPruned = ("genParticles")
#labelPruned = ("prunedGenParticles")

for event in events_DYjets:

    if count > 1000:
        break
    if count % 100 == 0:
        print "count = " + str(count)
    count +=1

    event.getByLabel (labelPruned, handlePruned)
    pruned = handlePruned.product()

    event.getByLabel(geninfoLabel,geninfo)
    gen = geninfo.product()

    if gen.weight() > 0:
        countweighted += 1
    else:
        countweighted -= 1

    for p in pruned :
        if abs(p.pdgId()) == 22 and p.pt() > 25 and abs(p.eta()) < 2.5 and (p.statusFlags().isPrompt()) and p.status() == 1   :
	print p.mother()


