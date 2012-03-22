#ifndef EGTriggerScan_H
#define EGTriggerScan_H

// -*- C++ -*-
//
// Package:    EGTriggerScan
// Class:      EGTriggerScan
// 
/**\class EGTriggerScan EGTriggerScan.cc EXO/EGTriggerScan/src/EGTriggerScan.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shih-Chuan Kao
//         Created:  Thu Feb  9 17:11:15 CST 2012
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/HLTReco/interface/TriggerFilterObjectWithRefs.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "RecoTracker/TrackProducer/plugins/TrackProducer.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"

//#include "HLTrigger/HLTcore/interface/HLTFilter.h"

#include <TMath.h>
#include <Math/VectorUtil.h>
#include "TFile.h"
#include "TTree.h"
#include "EGNtuple.h"

//
// class declaration
//
using namespace std ;
typedef math::XYZTLorentzVector LorentzVector;

class EGTriggerScan : public edm::EDAnalyzer {

   public:
      explicit EGTriggerScan(const edm::ParameterSet&);
      ~EGTriggerScan();

      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      //static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:

      //virtual void beginJob() ;
      //virtual void endJob() ;
      //virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      //virtual void endRun(edm::Run const&, edm::EventSetup const&);
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
      string rootFileName;
      edm::InputTag photonSrc ;
      double etcutEB ;
      double etcutEE ;
      int    nPhotons   ;
      edm::InputTag jetSrc ;
      double jetPtCut ;
      int    nJets   ;
      edm::InputTag trackSrc ;
      double trkPtCut ;
      int    nTracks   ;
      edm::InputTag rechitsEB ;
      edm::InputTag rechitsEE ;

      TFile*     theFile ;
      TTree*     theTree;
      EGNtuple   leaves ;


};

#endif
