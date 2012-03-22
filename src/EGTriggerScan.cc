// -*- C++ -*-
//
// Package:    EGTriggerScan
// Class:      EGTriggerScan
// 
/**\class EGTriggerScan EGTriggerScan.cc EXO/EGTriggerScan/src/EGTriggerScan.cc

     [Notes on implementation]
*/
//
// Original Author:  Shih-Chuan Kao
//         Created:  Thu Feb  9 17:11:15 CST 2012
// $Id$
//
//
#include "EGTriggerScan.h"
#include "EGNtuple.h"

using namespace edm ;
using namespace std ;

//
// constructors and destructor
//
//EGTriggerScan::EGTriggerScan(const edm::ParameterSet& iConfig)  : HLTFilter(iConfig) 
EGTriggerScan::EGTriggerScan(const edm::ParameterSet& iConfig)
{

  rootFileName  = iConfig.getUntrackedParameter<string> ("rootFileName");
  photonSrc     = iConfig.getParameter< edm::InputTag > ("photonSource");
  jetSrc        = iConfig.getParameter< edm::InputTag > ("jetSource");
  trackSrc      = iConfig.getParameter< edm::InputTag > ("trackSource");
  etcutEB       = iConfig.getParameter<double> ("etcutEB");
  etcutEE       = iConfig.getParameter<double> ("etcutEE");
  nPhotons      = iConfig.getParameter<int> ("nPhotons");
  jetPtCut      = iConfig.getParameter<double> ("jetPtCut");
  nJets         = iConfig.getParameter<int> ("nJets");
  trkPtCut      = iConfig.getParameter<double> ("trkPtCut");
  nTracks       = iConfig.getParameter<int> ("nTracks");
  rechitsEB     = iConfig.getParameter< edm::InputTag > ("RecHitsEB");
  rechitsEE     = iConfig.getParameter< edm::InputTag > ("RecHitsEE");

  //relaxed_ = iConfig.getUntrackedParameter<bool> ("relaxed",true) ;
  //L1IsoCollTag_= iConfig.getParameter< edm::InputTag > ("L1IsoCand"); 
  //L1NonIsoCollTag_= iConfig.getParameter< edm::InputTag > ("L1NonIsoCand"); 

  theFile  = new TFile( rootFileName.c_str(), "RECREATE") ;
  theFile->cd () ;
  theTree  = new TTree ( "EGScan","EGScan" ) ;
  setBranches( theTree, leaves ) ;

}


EGTriggerScan::~EGTriggerScan() {
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   theFile->cd () ;
   theTree->Write() ;
   theFile->Close() ;

}


//
// member functions
//

// ------------ method called for each event  ------------
void EGTriggerScan::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  // get hold of filtered photon candidates
  /*
  Handle<trigger::TriggerFilterObjectWithRefs> PrevFilterOutput;
  iEvent.getByLabel( photonSrc, PrevFilterOutput);

  vector<edm::Ref<reco::RecoEcalCandidateCollection> > recoecalcands;   
  PrevFilterOutput->getObjects(trigger::TriggerCluster, recoecalcands);

  edm::Ref<reco::RecoEcalCandidateCollection> ref; // Ref to Candidate object to be recorded in filter object
  for (unsigned int i=0; i<recoecalcands.size(); i++) {
      ref = recoecalcands[i] ;
      if( ( fabs(ref->eta()) < 1.479 &&  ref->et()  >= etcutEB ) || ( fabs(ref->eta()) >= 1.479 &&  ref->et()  >= etcutEE ) ){
        // ...
      }
  }
  */

  // get hold of collection of objects
  Handle<reco::RecoEcalCandidateCollection> egCands;
  iEvent.getByLabel( photonSrc , egCands);

  // get hold of collection of objects
  //Handle<reco::CaloJetCollection> jets;
  Handle<reco::PFJetCollection> jets;
  iEvent.getByLabel( jetSrc , jets);

  // get hold of collection of objects
  Handle<reco::TrackCollection> tracks;
  iEvent.getByLabel( trackSrc , tracks);

  Handle<EcalRecHitCollection>      rechitsEB_ ;
  Handle<EcalRecHitCollection>      rechitsEE_ ;
  iEvent.getByLabel( rechitsEB,     rechitsEB_ );
  iEvent.getByLabel( rechitsEE,     rechitsEE_ );

  int nEg_test = 0 ;
  for (reco::RecoEcalCandidateCollection::const_iterator it = egCands->begin(); it != egCands->end(); it++ ) {
      if( ( fabs( it->eta()) < 1.479 &&  it->et()  >= etcutEB ) || ( fabs( it->eta()) >= 1.479 &&  it->et()  >= etcutEE ) ){
        nEg_test++ ;
      }
      if ( nEg_test > 0 ) break ;
  }
 
  if ( nEg_test > 0  ) {

     initializeBranches( theTree, leaves );

     leaves.bx          = iEvent.bunchCrossing();
     leaves.lumiSection = iEvent.id().luminosityBlock();
     leaves.orbit       = iEvent.orbitNumber();
     leaves.runId       = iEvent.id ().run () ;
     leaves.eventId     = iEvent.id ().event () ;

     int nEg = 0 ;  
     double maxPhoPt = 0 ;
     LorentzVector phoP4 ;
     for (reco::RecoEcalCandidateCollection::const_iterator it = egCands->begin(); it != egCands->end(); it++ ) {
         if( ( fabs( it->eta()) < 1.479 &&  it->et()  >= 30. ) || ( fabs( it->eta()) >= 1.479 &&  it->et()  >= 30. ) ){

           leaves.phoPx[nEg] = it->p4().Px() ;
	   leaves.phoPy[nEg] = it->p4().Py() ;
	   leaves.phoPz[nEg] = it->p4().Pz() ;
	   leaves.phoE[nEg]  = it->p4().E() ;
	   if ( it->pt() > maxPhoPt ) {
              maxPhoPt = it->pt() ;
              phoP4 = LorentzVector( it->p4().Px(), it->p4().Py(), it->p4().Pz(), it->p4().E() );
           }

            // S_Minor Cuts from the seed cluster
	    reco::CaloClusterPtr SCseed = it->superCluster()->seed() ;
	    const EcalRecHitCollection* rechits = ( fabs( it->eta()) < 1.479 ) ? rechitsEB_.product() : rechitsEE_.product() ;

	    Cluster2ndMoments moments = EcalClusterTools::cluster2ndMoments(*SCseed, *rechits);
	    float sMin =  moments.sMin  ;
	    float sMaj =  moments.sMaj  ;

	    // seed Time 
	    pair<DetId, float> maxRH = EcalClusterTools::getMaximum( *SCseed, rechits );
	    DetId seedCrystalId = maxRH.first;
	    EcalRecHitCollection::const_iterator seedRH = rechits->find(seedCrystalId);
	    float seedTime = (float)seedRH->time();

	    leaves.sMin[nEg]  = sMin ;
	    leaves.sMaj[nEg]  = sMaj ;
	    leaves.sTime[nEg]  = seedTime ;

           nEg++;
           if ( nEg >= MAXPHO ) break ;
      }
     }
     leaves.nPhotons = nEg ;

     int nJ = 0;
     //for (reco::CaloJetCollection::const_iterator it = jets->begin(); it != jets->end(); it++ )  {
     for (reco::PFJetCollection::const_iterator it = jets->begin(); it != jets->end(); it++ )  {
         if (  it->pt() < jetPtCut ) continue ;
	 leaves.jetPx[nJ] = it->p4().Px() ;
	 leaves.jetPy[nJ] = it->p4().Py() ;
	 leaves.jetPz[nJ] = it->p4().Pz() ;
	 leaves.jetE[nJ]  = it->p4().E()  ;
	 nJ++ ;
         if ( nJ >= MAXJET ) break ;
     }
     leaves.nJets = nJ ;

     int nTrk = 0 ;
     for (reco::TrackCollection::const_iterator it = tracks->begin(); it != tracks->end(); it++ )  {
         if ( it->pt() < trkPtCut ) continue ;
         LorentzVector trkP4( it->px(), it->py(), it->pz(), it->p() ) ;
         double dR =  ROOT::Math::VectorUtil::DeltaR( trkP4 , phoP4 ) ;

	 leaves.trkPx[nTrk] = it->px() ;
	 leaves.trkPy[nTrk] = it->py() ;
	 leaves.trkPz[nTrk] = it->pz() ;
	 leaves.trkE[nTrk]  = it->p()  ;
         leaves.dR[nTrk] = dR ;
         //cout<<" trk"<< nTrk <<" dR = "<< dR <<endl ;
         nTrk++ ;
         if ( nTrk >= MAXTRK ) break ;
     }
     leaves.nTracks = nTrk ;
     //cout<<" nTracks = "<< nTrk <<endl ;
     theTree->Fill();   
  }

}

/*
// ------------ method called once each job just before starting event loop  ------------
void 
EGTriggerScan::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EGTriggerScan::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
EGTriggerScan::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
EGTriggerScan::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
EGTriggerScan::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
EGTriggerScan::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
EGTriggerScan::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
*/

//define this as a plug-in
DEFINE_FWK_MODULE(EGTriggerScan);
