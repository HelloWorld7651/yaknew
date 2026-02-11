// server.cpp   
#include "GameManager.h"
#include "LogManager.h"
#include "yakserver.h"

int main(int argc, char *argv[]) {
  if (GM.startUp()) {
    return 1;
  }

  LM.setFlush(true);
  
  // Instantiate the Server logic
  new yakserver();

  GM.run();
  GM.shutDown();
  return 0;
}