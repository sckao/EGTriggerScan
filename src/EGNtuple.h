#ifndef EGNtuple_h
#define EGNtuple_h

#include "TChain.h" 

#define MAXJET 20
#define MAXPHO 20
#define MAXTRK 30

struct EGNtuple
{
  
  unsigned int runId;
  unsigned int lumiSection;
  unsigned int orbit;
  unsigned int bx;
  unsigned int eventId;
  
  int   nJets ;
  float jetPx[MAXJET];
  float jetPy[MAXJET];
  float jetPz[MAXJET];
  float jetE[MAXJET];

  int   nPhotons ;
  float phoPx[MAXPHO];
  float phoPy[MAXPHO];
  float phoPz[MAXPHO];
  float phoE[MAXPHO];
  float sMin[MAXPHO];
  float sMaj[MAXPHO];
  float sTime[MAXPHO];

  int   nTracks ;
  float trkPx[MAXTRK];
  float trkPy[MAXTRK];
  float trkPz[MAXTRK];
  float trkE[MAXTRK];
  float dR[MAXTRK];

};



//typedef EGNtuple EcalTimeTreeContent;


// ------------------------------------------------------------------------
//! branch addresses settings
void setBranchAddresses(TTree* chain, EGNtuple& treeVars);
//! create branches for a tree
void setBranches(TTree* chain, EGNtuple& treeVars);
//! initialize branches
void initializeBranches(TTree* chain, EGNtuple& treeVars);

#endif
