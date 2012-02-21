import FWCore.ParameterSet.Config as cms

egTriggerScan = cms.EDAnalyzer('EGTriggerScan',
    rootFileName = cms.untracked.string('egscan.root'),
    #photonSource = cms.InputTag( "hltEG75EtFilter" ),
    photonSource = cms.InputTag( "hltL1IsoRecoEcalCandidate" ),
    etcutEB = cms.double( 70.0 ),
    etcutEE = cms.double( 70.0 ),
    nPhotons   = cms.int32( 1 ),
    jetSource = cms.InputTag( "hltAntiKT5ConvPFJets" ),
    jetPtCut  = cms.double( 25.0 ),
    nJets     = cms.int32( 1 ),
    trackSource = cms.InputTag( "hltL1IsoEgammaRegionalCTFFinalFitWithMaterial" ),
    trkPtCut  = cms.double( 3.0 ),
    nTracks   = cms.int32( 0 ),
    RecHitsEB = cms.InputTag("hltEcalRecHitAll", "EcalRecHitsEB"),
    RecHitsEE = cms.InputTag("hltEcalRecHitAll", "EcalRecHitsEE")
)
