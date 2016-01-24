#pragma once

#include "globals.hh"
#include "G4VPVParameterisation.hh"
#include <vector>
#include <G4String.hh>
#include <G4Material.hh>

class PVParameterisation : public G4VPVParameterisation
{
public:
    PVParameterisation(G4int Nrep);
    virtual void ComputeTransformation(const G4int id, G4VPhysicalVolume*pvol) const;
    virtual G4VSolid* ComputeSolid(const G4int id, G4VPhysicalVolume *pvol);
    virtual G4Material* ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol, const G4VTouchable *parentTouch);
    void inputParameters();
private:
    G4int Ncp;
    std::vector<G4Material*> fMaterialName;
    std::vector<G4double> fxc, fyc, fzc, fhx, fhy, fhz;
};
