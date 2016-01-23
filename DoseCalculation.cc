#include "G4MTRunManager.hh"

#include "G4UImanager.hh"
#include "G4UIcommand.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"

#include "G4VModularPhysicsList.hh"
#include "FTFP_BERT.hh"

#include "ActionInitialization.hh"

int main(int argc,char** argv)
{  
    G4int nThreads = 8;
    G4Random::setTheEngine(new CLHEP::RanecuEngine);

    G4MTRunManager * runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(nThreads);    

    DetectorConstruction* detConstruction = new DetectorConstruction();
    runManager->SetUserInitialization(detConstruction);

    G4VModularPhysicsList* physicsList = new FTFP_BERT;
    runManager->SetUserInitialization(physicsList);

    ActionInitialization* actionInitialization
            = new ActionInitialization();
    runManager->SetUserInitialization(actionInitialization);

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    if ( argc > 1 ) {
        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command+argv[2]);
    }
    else  {        
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;
}

