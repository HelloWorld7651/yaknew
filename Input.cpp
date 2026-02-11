//
// Input.cpp
//

// Engine includes.
#include "Color.h"
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "yakclient.h"

class yakclient;
// Game includes.
#include "Input.h"


Input::Input(std::string name, df::TextBox *p_text_box, yakclient *p_client) {
  setType("Input");
  setText("");
  setBorder(true);
  setColor(df::WHITE);
  setLocation(df::BOTTOM_CENTER);
  setLimit(40); // In characters
  m_p_text_box = p_text_box;
  m_p_client = p_client;
  m_name = name + " : ";
  setViewString(m_name);
}

// On callback, add message to TextBox.
void Input::callback() {

  LM.writeLog("Input::callback(): Input: %s", getText().c_str());
  if (getText() == "quit" || getText() == "exit")
    GM.setGameOver();

  //send to server
  std::string full_msg = m_name+ getText();
  m_p_client->sendMessage(full_msg);
  //clear input
  setText("");

}