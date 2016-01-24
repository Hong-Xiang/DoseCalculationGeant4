#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"



PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(),
      fParticleGun(0)
{
    fParticleGun = new G4ParticleGun(1);

    G4ParticleDefinition* particleDefinition
            = G4ParticleTable::GetParticleTable()->FindParticle("e-");
    fParticleGun->SetParticleDefinition(particleDefinition);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    fParticleGun->SetParticlePosition(G4ThreeVector(0,0,-8*cm));
    fParticleGun->SetParticleEnergy(50.*MeV);
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}



void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{   
    fParticleGun->GeneratePrimaryVertex(anEvent);
}


