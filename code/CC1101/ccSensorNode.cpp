#include "ccSensorNode.h"


//CONSTRUCTOR//

CCSENSORNODE::CCSENSORNODE(byte id, byte twinNode)

{

    _id = id;
    _twinNode = twinNode;
    _syncWord = (19,9);    
              
}


//DESTRUCTOR//
CCSENSORNODE::~CCSENSORNODE()

{

	
}

//METHODS

void CCSENSORNODE::setup()

{

    Serial.begin(115200); // 9600 // 38400
    
    ledBlinkSetup();
    
    rfChipInit();

    initBattMonitor();   

}
    





void CCSENSORNODE::initBattMonitor()

{

    analogComparator.setOn(AIN0,AIN1);  //we instruct the lib to use voltages on the pins PD6 and PD7  

}

boolean CCSENSORNODE::ccReceive()

{   
    
    CCPACKET ccPacket; 
    boolean validPacket = false; 

    byte cc11 = _cc1101.receiveData(&ccPacket);
   
    if(cc11 > 0) // some data was received      
    {
        if (ccPacket.crc_ok && ccPacket.length > 1) // the whole ccPacket was properly received
        {  
            _ccPacketHandler.setPacket(ccPacket);

            if(ccPacket.RECEIVER_ID == _id) 
            {                 
                validPacket = true; 
            }          
       
        }
    }
    
    return validPacket;
   
}

void CCSENSORNODE::ccHandle()

{

    byte key = _ccPacketHandler.getAdminKey();
      
    switch (key)
    {
        case ACKNOWLEDGE_REQUEST:
            if (_ccPacketHandler.hashMatches()) 
                _ccPacketHandler._ccClear = true;
            else
                Serial.println("False acknowledge! Resending prev. package");
            break;    
        case TEST: // test packet received
            ccAcknowledge();
            break;
        default: // unknown packet received
            Serial.print("Unknown packet received, key: ");
            Serial.println(key);
            break; 
    }
}


boolean CCSENSORNODE::bubbleIsSender()

{
   byte sender = _ccPacketHandler.getPacketSender();   
 
   if(sender == _id || sender == _twinNode)
       return true;
   else
       return false;
}





void CCSENSORNODE::reportAccelEvent()

{

    _ccPacketHandler.buildPacket(BROADCAST, _id, SHAKE_EVENT);
    ccSend();    

}


void CCSENSORNODE::reportRSSI()

{

    byte rawRSSI = _ccPacketHandler.getPacketRSSI();
    byte nearNodeId = _ccPacketHandler.getPacketSender();
    sendRSSI(rawRSSI,nearNodeId); 

}



void CCSENSORNODE::reportLowBatt()

{
    _ccPacketHandler.buildPacket(SERVER_01, _id, LOW_BATTERY);
    ccSend();    
}


void CCSENSORNODE::sendRSSI(byte rawRSSI,byte nearNodeId)
{
    _ccPacketHandler.buildRSSIPacket(_id, rawRSSI,nearNodeId);
    ccSend();  
    _ccPacketHandler._ccClear = true;      
}


