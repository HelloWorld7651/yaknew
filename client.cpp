//
// client.cpp - client interface
// 
// System includes.

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "NetworkManager.h"
#include "Sentry.h"

// Game includes.
#include "NameEntry.h"

// Function protoypes.
void populateWorld();

///////////////////////////////////////////////
int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }

  // Setup logging.
  LM.setLogLevel(1);
  LM.setFlush(true);
  LM.writeLog("Chat (v%.1f)", 1.0);
  
  // Dragonfly splash screen.
  df::splash();

  // Create initial game objects.
  populateWorld();

  // Run game 
  GM.run();

  // Shut everything down.
  GM.shutDown();

  // All is well.
  return 0;
}

// Create initial game objects.
void populateWorld() {

  new df::Sentry();

  // Get name.  NameEntry spawns others upon callback.
  NameEntry *p_n = new NameEntry();
  if (!p_n) {
    LM.writeLog("main(): Error! Cannot allocate NameEntry.");
    exit(-1);
  }

}