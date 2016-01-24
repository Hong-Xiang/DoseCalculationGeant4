#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "PVParameterisation.hh"
#include "G4PVParameterised.hh"

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction()
{
}


DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* water = nistManager->FindOrBuildMaterial("G4_WATER");
    G4Material* vacuum = nistManager->FindOrBuildMaterial("G4_Galactic");
    G4Box* worldBox = new G4Box("worldBox",10*mm,10*mm,10*cm);
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox,vacuum,"worldLog");
    G4PVPlacement* world = new G4PVPlacement(0,G4ThreeVector(),worldLog,"world",0,false,0);

    G4int Nrep = 5;
    G4Box* phantomBox = new G4Box("phantom",1*mm, 1*mm, 1*mm);
    G4LogicalVolume* phantomLog = new G4LogicalVolume(phantomBox, water, "phatomLog");
    PVParameterisation* pvpara = new PVParameterisation(Nrep);
    G4PVParameterised* phatom = new G4PVParameterised("phantom", phantomLog, worldLog, kZAxis, Nrep, pvpara);
    return world;
}

void DetectorConstruction::ConstructSDandField()
{
}
