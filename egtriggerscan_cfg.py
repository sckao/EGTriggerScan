import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:myfile.root'
    )
)

process.test = cms.EDAnalyzer('EGTriggerScan',
    inputSource = cms.InputTag( "hltEgammaL1MatchFilter" ),
    etcutEB = cms.double( 90.0 ),
    etcutEE = cms.double( 90.0 ),
    nCand   = cms.int32( 1 )
)


process.p = cms.Path(process.test)
