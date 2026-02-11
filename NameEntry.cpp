//
// NameEntry.cpp
//

// Engine includes.
#include "Color.h"
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"

// Game includes.
#include "Input.h"
#include "NameEntry.h"
#include "TextBox.h"
#include "yakclient.h"

NameEntry::NameEntry() {
  setType("NameEntry");
  setText("");
  setViewString("enter your name: ");
  setBorder(true);
  setColor(df::WHITE);
  setLocation(df::CENTER_CENTER);
  setLimit(20); // In characters
}

// On callback, start chatting.
void NameEntry::callback() {

  LM.writeLog("NameEntry::callback(): name: %s", getText().c_str());

  // Chat input.
  df::TextBox *p_t = new df::TextBox();
  //create box
  p_t->setSize(df::Vector(40, 15));
  p_t->setLocation(df::CENTER_CENTER); 
  p_t->setBorder(true);                
  p_t->setColor(df::WHITE);

  //create network client
  yakclient *p_client = new yakclient(p_t);

  //pass client so input can see
  Input *p_in = new Input(getText(), p_t, p_client);  
  p_in->setLocation(df::Vector(p_t->getPosition().getX(), p_t->getPosition().getY() + 8));
  
  // Done.
  WM.markForDelete(this);
}