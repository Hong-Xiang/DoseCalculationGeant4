#include "PVParameterisation.hh"
#include <fstream>
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
PVParameterisation::PVParameterisation(G4int Nrep)
    : G4VPVParameterisation(), Ncp(Nrep)
{
    inputParameters();
}

void PVParameterisation::ComputeTransformation(const G4int id, G4VPhysicalVolume *pvol) const
{
    pvol->SetTranslation(G4ThreeVector(fxc.at(id),fyc.at(id),fzc.at(id)));
}

G4VSolid *PVParameterisation::ComputeSolid(const G4int id, G4VPhysicalVolume *pvol)
{
    G4Box* box = static_cast<G4Box*>(pvol->GetLogicalVolume()->GetSolid());
    box->SetXHalfLength(fhx.at(id));
    box->SetYHalfLength(fhy.at(id));
    box->SetZHalfLength(fhz.at(id));
    return box;
}

G4Material *PVParameterisation::ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol, const G4VTouchable *parentTouch)
{
    return fMaterialName.at(repNo);
}

void PVParameterisation::inputParameters()
{
    G4NistManager* nistManager = G4NistManager::Instance();
    std::ifstream fmin("material.in");
    for (int i = 0; i < Ncp; ++i) {
        G4String tmp;
        fmin >> tmp;
        fMaterialName.push_back(nistManager->FindOrBuildMaterial(tmp));
    }
    fmin.close();
    std::ifstream fpin("position.in");
    for (int i = 0; i < Ncp; ++i) {
        G4double xc, yc, zc, hx, hy, hz;
        fpin >> xc >> yc >> zc >> hx >> hy >> hz;
        fxc.push_back(xc*mm);
        fyc.push_back(yc*mm);
        fzc.push_back(zc*mm);
        fhx.push_back(hx*mm);
        fhy.push_back(hy*mm);
        fhz.push_back(hz*mm);
    }
    fpin.close();
}
