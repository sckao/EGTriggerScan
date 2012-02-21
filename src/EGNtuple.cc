#include "EGNtuple.h"

void setBranchAddresses(TTree* chain, EGNtuple& treeVars)
{
  chain -> SetBranchAddress("runId",       &treeVars.runId);
  chain -> SetBranchAddress("lumiSection", &treeVars.lumiSection);
  chain -> SetBranchAddress("orbit",       &treeVars.orbit);
  chain -> SetBranchAddress("bx",          &treeVars.bx);
  chain -> SetBranchAddress("eventId",     &treeVars.eventId);
  
  chain -> SetBranchAddress("nJets",       &treeVars.nJets       );
  chain -> SetBranchAddress("nPhotons",    &treeVars.nPhotons    );
  chain -> SetBranchAddress("nTracks",     &treeVars.nTracks       );

  chain -> SetBranchAddress("jetPx",        treeVars.jetPx     );
  chain -> SetBranchAddress("jetPy",        treeVars.jetPy     );
  chain -> SetBranchAddress("jetPz",        treeVars.jetPz     );
  chain -> SetBranchAddress("jetE",         treeVars.jetE      );
  
  chain -> SetBranchAddress("phoPx",        treeVars.phoPx     );
  chain -> SetBranchAddress("phoPy",        treeVars.phoPy     );
  chain -> SetBranchAddress("phoPz",        treeVars.phoPz     );
  chain -> SetBranchAddress("phoE",         treeVars.phoE      );
  chain -> SetBranchAddress("sMin",         treeVars.sMin      );
  chain -> SetBranchAddress("sMaj",         treeVars.sMaj      );
  chain -> SetBranchAddress("sTime",        treeVars.sTime     );

  chain -> SetBranchAddress("trkPx",        treeVars.trkPx     );
  chain -> SetBranchAddress("trkPy",        treeVars.trkPy     );
  chain -> SetBranchAddress("trkPz",        treeVars.trkPz     );
  chain -> SetBranchAddress("trkE",         treeVars.trkE      );
  chain -> SetBranchAddress("dR",           treeVars.dR      );
  
}


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

  chain -> Branch("trkPx",        treeVars.trkPx,                 "trkPx[nTracks]/F");
  chain -> Branch("trkPy",        treeVars.trkPy,                 "trkPy[nTracks]/F");
  chain -> Branch("trkPz",        treeVars.trkPz,                 "trkPz[nTracks]/F");
  chain -> Branch("trkE",         treeVars.trkE,                  "trkE[nTracks]/F");
  chain -> Branch("dR",           treeVars.dR,                    "dR[nTracks]/F");

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
      treeVars.sMin[i] = 0 ;
      treeVars.sMaj[i] = 0 ;
      treeVars.sTime[i] = 0 ;
  }
  for ( int i=0; i< MAXTRK; i++) {
      treeVars.trkPx[i] = 0 ;
      treeVars.trkPy[i] = 0 ;
      treeVars.trkPz[i] = 0 ;
      treeVars.trkE[i] = 0 ;
      treeVars.dR[i] = 0 ;
  }

}
