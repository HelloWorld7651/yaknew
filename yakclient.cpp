#include "yakclient.h"
#include "NetworkManager.h"
#include "EventNetwork.h"
#include "LogManager.h"
#include <string>
/*
#define yak_port "9876"
#define message_size 1024

enum class MessageType{
    UNDEFINED = -1, EXIT, CHAT
};
*/
struct PacketHeader{
    int size; // size of message
    MessageType type; //type of message
};

using namespace df;

yakclient::yakclient(df::TextBox *box){
    setType("YakClient");
    text_box = box;

    //Connect to the server
    int res = NM.connect("127.0.0.1", yak_port);

    if (res == -1) {
        LM.writeLog("YakClient:Could not connect to server.");
        text_box->addText("Error: Server down.\n");
    } else {
        LM.writeLog("YakClient: Connected to server.");
        text_box->addText("Connected to Chat!\n");
    }

    //register interest
    registerInterest(df::NETWORK_EVENT);
}

yakclient::~yakclient(){
    PacketHeader header;
    header.type = MessageType::EXIT;
    header.size = sizeof(header);
    
    NM.send(&header, sizeof(header));
    NM.closeAll();
}

int yakclient::eventHandler(const df::Event *p_e){
    if(p_e->getType() == df::NETWORK_EVENT){
        const EventNetwork *network = dynamic_cast<const EventNetwork*>(p_e);

        if(network->getLabel() == NetworkEventLabel::DATA){
            handleMessage();
        }
        return 1;
    }
    return 0;
}

void yakclient::handleMessage(){
    //read header
    PacketHeader header;
    int bytes = NM.receive(&header, sizeof(header), false);

    if(bytes != sizeof(header)) return;

    //read text data
    int text_length = header.size - sizeof(PacketHeader);
    char buffer[message_size];
    memset(buffer,0,message_size);

    if(text_length > 0){
        NM.receive(buffer, text_length, false);
    }

    //process message
    if(header.type == MessageType::CHAT){
        //add a new line after each person
        std::string message = std::string(buffer) + "\n";
        text_box -> addText(buffer);
    }
}

void yakclient::sendMessage(std::string text) {
    //calculate total size send both in order to server
    int text_len = text.length() + 1; 
    PacketHeader header;
    header.type = MessageType::CHAT;
    header.size = sizeof(header) + text_len;

    NM.send(&header, sizeof(header));
    NM.send(text.c_str(), text_len);
}
