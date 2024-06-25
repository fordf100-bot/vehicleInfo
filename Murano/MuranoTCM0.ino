//Full emulator for Nissan Murano CVT Controller. Vehicle equipped with ABS, no traction or stability control. Original CVT controller is still connected to vehicle, but can bus wires are cut and connected to emulator board instead.

//Use at your own risk!!! There can be glitches associated with this code that you will either have to deal with or fix!

#include <SPI.h>
#include <mcp_can.h>
const int spiCSPin = 53;
unsigned long previousCanSend = 0;

MCP_CAN CAN(spiCSPin);

int sw3m = 43;	//sw3m, sw2, sw3, sw4 are as noted in Nissan Service Manuals, avaliable at https://www.nicoclub.com/nissan-service-manuals
int sw2 = 8;	//these are only required if retaining the OEM CVT controller for purposes of reverse lights and starting interlock	
int sw3 = 4;	// If you want to directly wire up your reverse lights and starting interlock circuit, you don't need these outputs or the CVT controller
int sw4 = 5;
int vss = 9;        //Ouput from emulator to output shaft speed sensor, not actually needed!
int abs_speed = 0;  //speed from ABS pump, CAN ID may be different on cars with stability assist
int vsp_speed = 0;  
int varA = 0;
int varB = 0;
int freq = 0;

int nss = A3;  //neutral saftey switch
int reverse = A2;  // reverse switch
int clutch = A4; // Clutch switch

int driveLockout = 0;

unsigned char stmp251[8] = {0, 0, 0, 0, 0, 0, 23, 30};  // All the predefined can messages you'll need for emulation
unsigned char stmp254[8] = {231, 0, 100, 0, 32, 0, 0, 254};
//unsigned char stmp254[8] = {231, 0, 100, 0, 32, 0, 0, 254};

unsigned char stmp255[8] = {0, 16, 67, 65, 0, 8, 254, 254};
unsigned char stmp255_2[8] = {96, 208, 67, 65, 0, 4, 254, 254};
unsigned char stmp255_R[8] = {128, 16, 67, 65, 0, 2, 254, 254}; 

unsigned char stmp6DA[8] = {0, 248, 237, 0, 0, 0, 0, 0};
unsigned char stmp6DA_2[8] = {0, 120, 237, 0, 12, 3, 0, 0};
unsigned char stmp6DA_R[8] = {0, 248, 237, 0, 06, 04, 0, 0};

unsigned char stmp6DB[8] = {0, 0, 3, 24, 228, 237, 0, 30};
unsigned char stmp6DB_2[8] = {0, 0, 2, 0, 228, 237, 0, 30};

unsigned char stmp6DC[8] = {0, 0, 2, 228, 228, 0, 0, 58};
unsigned char stmp6DC_2[8] = {0, 0, 2, 56, 64, 0, 0, 146};

unsigned long lastSend = 0;
unsigned long lastSend1 = 0;
unsigned long lastSend2 = 0;
int gear = 0;
int moving = 0;

void setup() {

  pinMode(sw3m, OUTPUT);
  pinMode(sw2, OUTPUT);
  pinMode(sw3, OUTPUT);
  pinMode(sw4, OUTPUT);
  pinMode(vss, OUTPUT);

  digitalWrite(sw2, HIGH);  //put in  neutral
  digitalWrite(sw3, LOW);
  digitalWrite(sw4, LOW);
  digitalWrite(sw3m, HIGH);

  Serial.begin(9600);

  while (CAN_OK != CAN.begin(CAN_500KBPS, MCP_8MHz))
  {
    Serial.println("CAN BUS init Failed");
    delay(100);
  }
  Serial.println("CAN BUS Shield Init OK!");

  digitalWrite(sw2, HIGH);  //make car think its in neutral intitally
  digitalWrite(sw3, LOW);
  digitalWrite(sw4, LOW);
  digitalWrite(sw3m, HIGH);
  gear = 0;

}


void loop() {


  vsp_speed = abs_speed * 9.5 * 4; //linear regession to frequency

  varA = vsp_speed / 256;
  varB = vsp_speed % 256;


  unsigned char stmp6DB[8] = {0, abs_speed, 3, 24, 228, 237, 0, 30};
  unsigned char stmp254[8] = {231, 0, 100, 0, varB, varA, 0, 254};


  //tone(vss, 200);  // Leftover from before I decided to completely emulate the CVT controller. This output fed the output shaft speed sensor input on the CVT controller

  if (analogRead(reverse) < 200 && analogRead(nss) > 250) {  //reverse
    digitalWrite(sw2, LOW);
    digitalWrite(sw3, LOW);
    digitalWrite(sw4, HIGH);
    digitalWrite(sw3m, HIGH);
    gear = 2;
  }

  if (analogRead(nss) > 250 && analogRead(reverse) > 250 && driveLockout == 0) {  //drive
    digitalWrite(sw2, HIGH);
    digitalWrite(sw3, HIGH);
    digitalWrite(sw4, HIGH);
    digitalWrite(sw3m, LOW);
    gear = 1;
  }

  driveLockout = 0;
  
  //clutch start0
  if (((analogRead(clutch) < 200) || (analogRead(nss) < 200)) && moving == 0) {  //neutral
    digitalWrite(sw2, HIGH);
    digitalWrite(sw3, LOW);
    digitalWrite(sw4, LOW);
    digitalWrite(sw3m, HIGH);
    driveLockout = 1;
    gear = 0;
  }

  if (abs_speed > 0){  //set moving flag first time car moves on key cycle
    moving = 1;
  }



  //CAN- Cruise Control
  unsigned char len = 0;
  unsigned char buf[8];
  unsigned long canId = 0;

  if (CAN_MSGAVAIL == CAN.checkReceive())
  {
    CAN.readMsgBuf(&len, buf);
    canId = CAN.getCanId();
    //Serial.println(canId);
  }

  if (canId == 645) {
    abs_speed = buf[4];  //read Vehicle speed from ABS module
  }

  if ((millis() - lastSend > 10) && gear == 1) {  //CAN Commands To make car think it's in drive
    CAN.sendMsgBuf(0x251, 0, 8, stmp251);
    CAN.sendMsgBuf(0x254, 0, 8, stmp254);
    CAN.sendMsgBuf(0x255, 0, 8, stmp255);
    CAN.sendMsgBuf(0x6DA, 0, 8, stmp6DA);
    CAN.sendMsgBuf(0x6DB, 0, 8, stmp6DB);
    CAN.sendMsgBuf(0x6DC, 0, 8, stmp6DC);
    lastSend = millis();
    //Serial.println("lastsned");
  }

  if ((millis() - lastSend1 > 10) && gear == 0) { //CAN Commands to make car think it's in neutral
    CAN.sendMsgBuf(0x251, 0, 8, stmp251);
    CAN.sendMsgBuf(0x254, 0, 8, stmp254);
    CAN.sendMsgBuf(0x255, 0, 8, stmp255_2);
    CAN.sendMsgBuf(0x6DA, 0, 8, stmp6DA_2);
    CAN.sendMsgBuf(0x6DB, 0, 8, stmp6DB_2);
    CAN.sendMsgBuf(0x6DC, 0, 8, stmp6DC_2);
    lastSend1 = millis();
    //Serial.println("lastsned1");
  }

  if ((millis() - lastSend2 > 10) && gear == 2) { //CAN Commands to make car think it's in reverse
    CAN.sendMsgBuf(0x251, 0, 8, stmp251);
    CAN.sendMsgBuf(0x254, 0, 8, stmp254);
    CAN.sendMsgBuf(0x255, 0, 8, stmp255_R);
    CAN.sendMsgBuf(0x6DA, 0, 8, stmp6DA_R);
    CAN.sendMsgBuf(0x6DB, 0, 8, stmp6DB);
    CAN.sendMsgBuf(0x6DC, 0, 8, stmp6DC);
    lastSend2 = millis();
    //Serial.println("lastsned");
  }
  
  /*
    for (int i = 0; i < 200; i += 1) {  //again, more left overs

    freq = (17.62314 * 80) + 0;
    Serial.println(freq);
    Serial.println(i);
    tone(vss, freq);
    delay(50);
    }

  */

  freq = (17.62314 * abs_speed) + 0; //7.20741
  //tone(vss, 600);
  //Serial.println(freq);


}
