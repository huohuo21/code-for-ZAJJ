import FWCore.ParameterSet.Config as cms
### USAGE:
###    cmsRun fitMuonID.py
###
process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.TnP_Muon_Trigger = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
        InputFileNames = cms.vstring(
                                                    # put here the trees corresponding to mc
        "/afs/cern.ch/user/m/melu/work/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/test/TnPUtils/TnPTree_G.root",
),
        InputTreeName = cms.string("fitter_tree"),
        InputDirectoryName = cms.string("tpTree"),
        OutputFileName = cms.string("TnP_MuonTrigger_noptbin_G.root"),
        NumCPU = cms.uint32(8),
        SaveWorkspace = cms.bool(False),

    Variables = cms.PSet(
        mass = cms.vstring("Tag-muon Mass", "76", "125", "GeV/c^{2}"),
        pt = cms.vstring("muon p_{T}", "0", "1000", "GeV/c"),
        phi = cms.vstring("muon #phi", "-3.14", "3.14", ""),
        tag_pt = cms.vstring("tag muon p_{T}", "0", "1000", "GeV/c"),
        eta    = cms.vstring("muon #eta", "-2.5", "2.5", ""),
        abseta = cms.vstring("muon |#eta|", "0", "2.5", ""),
        tag_abseta = cms.vstring("tag muon |#eta|", "0", "2.5", ""),
        tag_nVertices = cms.vstring("Number of vertices", "0", "999", ""),
        combRelIsoPF04dBeta = cms.vstring("pf relative isolation", "0", "999", ""),
        tag_combRelIsoPF04dBeta = cms.vstring("tag pf relative isolation", "0", "999", ""),
        SIP = cms.vstring("Number of vertices", "0", "999", ""),
        run = cms.vstring("Number of vertices", "-999", "999999", "")
    ),

    Categories = cms.PSet(
        Glb   = cms.vstring("Global", "dummy[pass=1,fail=0]"),
        PF    = cms.vstring("PF Muon", "dummy[pass=1,fail=0]"),
        TM    = cms.vstring("Tracker Muon", "dummy[pass=1,fail=0]"),
        mvaIsoCut = cms.vstring("MC true", "dummy[pass=1,fail=0]"),
        mcTrue = cms.vstring("MC true", "dummy[true=1,false=0]"),
        Tight2012 = cms.vstring("Tight2012", "dummy[pass=1,fail=0]"),
        tag_IsoMu20 = cms.vstring("tag_IsoMu20", "dummy[pass=1,fail=0]"),
        IsoMu20 = cms.vstring("IsoMu20", "dummy[pass=1,fail=0]"),
        IsoTkMu20 = cms.vstring("IsoTkMu20", "dummy[pass=1,fail=0]"),
        L1sMu16 = cms.vstring("L1sMu16", "dummy[pass=1,fail=0]"),
        Mu20 = cms.vstring("Mu20", "dummy[pass=1,fail=0]"),
        tag_Mu20 = cms.vstring("tag_Mu20", "dummy[pass=1,fail=0]"),
        tag_Mu17_IsoTrkVVL = cms.vstring("tag_Mu17_IsoTrkVVL", "dummy[pass=1,fail=0]"),
        Mu17_IsoTrkVVL = cms.vstring("Mu17_IsoTrkVVL", "dummy[pass=1,fail=0]"),
        tag_Mu17 = cms.vstring("tag_Mu17", "dummy[pass=1,fail=0]"),
	Mu17 = cms.vstring("Mu17", "dummy[pass=1,fail=0]"),
        L2fL1sMu16L1f0L2Filtered10Q = cms.vstring("L2fL1sMu16L1f0L2Filtered10Q", "dummy[pass=1,fail=0]"),

    ),
        Efficiencies = cms.PSet(
                trigger_pt_eta = cms.PSet(
                UnbinnedVariables = cms.vstring("mass"),
                EfficiencyCategoryAndState = cms.vstring("Mu17", "pass"),
                BinnedVariables = cms.PSet(
                        pt = cms.vdouble(20,9999  ),
                        abseta = cms.vdouble(0.0, 0.9, 1.2, 2.1, 2.4),
                        Tight2012 = cms.vstring("pass"),
                        tag_Mu17 = cms.vstring("pass"),
                        tag_pt =  cms.vdouble(20,9999),
                        tag_abseta = cms.vdouble(0, 2.4),
                        combRelIsoPF04dBeta = cms.vdouble(0,0.15),
                        tag_combRelIsoPF04dBeta = cms.vdouble(0,0.15),
                ),
                BinToPDFmap = cms.vstring("vpvPlusExpo"),
            ),
         ),
    Cuts = cms.PSet(
                combRelIsoPF04dBeta_015 = cms.vstring("combRelIsoPF04dBeta_015", "combRelIsoPF04dBeta", "0.15"),
    ),
    PDFs = cms.PSet(
        voigtPlusExpo = cms.vstring(
            "Voigtian::signal(mass, mean[90,80,100], width[2.495], sigma[3,1,20])",
            "Exponential::backgroundPass(mass, lp[0,-5,5])",
            "Exponential::backgroundFail(mass, lf[0,-5,5])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        vpvPlusExpo = cms.vstring(
            "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
            "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,2,10])",
            "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
            "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
            "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        vpvPlusExpoMin70 = cms.vstring(
            "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
            "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,3,10])",
            "SUM::signal(vFrac[0.8,0.5,1]*signal1, signal2)",
            "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
            "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
            "efficiency[0.9,0.7,1]",
            "signalFractionInPassing[0.9]"
        )
    ),

    binnedFit = cms.bool(False),
    binsForFit = cms.uint32(40),
    saveDistributionsPlot = cms.bool(False),
)

process.p = cms.Path(process.TnP_Muon_Trigger)
