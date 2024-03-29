#include "EGNtuple.h"


void setBranches(TTree* chain, EGNtuple& treeVars)
{
  chain -> Branch("runId",         &treeVars.runId,                "runId/i");
  chain -> Branch("lumiSection",   &treeVars.lumiSection,    "lumiSection/i");
  chain -> Branch("orbit",         &treeVars.orbit,                "orbit/i");
  chain -> Branch("bx",            &treeVars.bx,                      "bx/i");
  chain -> Branch("eventId",       &treeVars.eventId,            "eventId/i");
  
  chain -> Branch("nJets",       &treeVars.nJets,                "nJets/I");
  chain -> Branch("nPhotons",    &treeVars.nPhotons,             "nPhotons/I");
  chain -> Branch("nTracks",     &treeVars.nTracks,              "nTracks/I");
  chain -> Branch("nPixels",     &treeVars.nPixels,              "nPixels/I");

  chain -> Branch("jetPx",        treeVars.jetPx,                 "jetPx[nJets]/F");
  chain -> Branch("jetPy",        treeVars.jetPy,                 "jetPy[nJets]/F");
  chain -> Branch("jetPz",        treeVars.jetPz,                 "jetPz[nJets]/F");
  chain -> Branch("jetE",         treeVars.jetE,                  "jetE[nJets]/F");

  chain -> Branch("phoPx",        treeVars.phoPx,                 "phoPx[nPhotons]/F");
  chain -> Branch("phoPy",        treeVars.phoPy,                 "phoPy[nPhotons]/F");
  chain -> Branch("phoPz",        treeVars.phoPz,                 "phoPz[nPhotons]/F");
  chain -> Branch("phoE",         treeVars.phoE,                  "phoE[nPhotons]/F");
  chain -> Branch("sMin",         treeVars.sMin,                  "sMin[nPhotons]/F");
  chain -> Branch("sMaj",         treeVars.sMaj,                  "sMaj[nPhotons]/F");
  chain -> Branch("sTime",        treeVars.sTime,                 "sTime[nPhotons]/F");

  chain -> Branch("pxlPx",        treeVars.pxlPx,                 "pxlPx[nPixels]/F");
  chain -> Branch("pxlPy",        treeVars.pxlPy,                 "pxlPy[nPixels]/F");
  chain -> Branch("pxlPz",        treeVars.pxlPz,                 "pxlPz[nPixels]/F");
  chain -> Branch("pxlE",         treeVars.pxlE,                  "pxlE[nPixels]/F");
  chain -> Branch("nHits",        treeVars.nHits,                 "nHits[nPixels]/I");

}


void initializeBranches(TTree* chain, EGNtuple& treeVars) {

  treeVars.runId = 0;
  treeVars.lumiSection = 0;
  treeVars.orbit = 0;
  treeVars.bx = 0;
  treeVars.eventId = 0; 
  
  treeVars.nJets      = 0 ; 
  treeVars.nPhotons   = 0 ; 
  treeVars.nTracks    = 0 ; 
  treeVars.nPixels    = 0 ; 

  for ( int i=0; i< MAXJET; i++) {
      treeVars.jetPx[i] = 0 ;
      treeVars.jetPy[i] = 0 ;
      treeVars.jetPz[i] = 0 ;
      treeVars.jetE[i] = 0 ;
  }
  for ( int i=0; i< MAXPHO; i++) {
      treeVars.phoPx[i] = 0 ;
      treeVars.phoPy[i] = 0 ;
      treeVars.phoPz[i] = 0 ;
      treeVars.phoE[i] = 0 ;
      treeVars.sMin[i] = -99;
      treeVars.sMaj[i] = -99 ;
      treeVars.sTime[i] = -99 ;
  }
  for ( int i=0; i< MAXTRK; i++) {
      treeVars.trkPx[i] = 0 ;
      treeVars.trkPy[i] = 0 ;
      treeVars.trkPz[i] = 0 ;
      treeVars.trkE[i] = 0 ;
      treeVars.dR[i] = -1 ;
  }
  for ( int i=0; i< MAXTRK; i++) {
      treeVars.pxlPx[i] = 0 ;
      treeVars.pxlPy[i] = 0 ;
      treeVars.pxlPz[i] = 0 ;
      treeVars.pxlE[i] = 0 ;
      treeVars.nHits[i] = 0 ;
  }

}
