#include <SPI.h>
#include <mcp_can.h>
const int spiCSPin = 10;
unsigned long previousCanSend = 0;

MCP_CAN CAN(spiCSPin);

int i = 0;
int j = 0;
int counter = 0;
//unsigned char stmp202[8] = {0x30, 0, 0, 0, 0, 0, 0x19, 0xF3};//TACHO
unsigned char stmp202[8] = {0x30, 0x03, 0, 0x00, 0x00, 0, 0x19, 0x93};//TACHO

unsigned char stmp2111[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0x00, 0x20, 0, 0x64};
unsigned char stmp2112[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0x10, 0x10, 0, 0x64};
unsigned char stmp2113[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0x20, 0x00, 0, 0x64};
unsigned char stmp2114[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0x3F, 0xF0, 0, 0x64};
unsigned char stmp2115[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0x4F, 0xE0, 0, 0x64};
unsigned char stmp2116[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0x5F, 0xD0, 0, 0x64};
unsigned char stmp2117[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0x6F, 0xC0, 0, 0x64};
unsigned char stmp2118[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0x7F, 0xB0, 0, 0x64};
unsigned char stmp2119[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0x8F, 0xA0, 0, 0x64};
unsigned char stmp21110[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0x9F, 0x90, 0, 0x64};
unsigned char stmp21111[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0xAF, 0x80, 0, 0x64};
unsigned char stmp21112[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0xBF, 0x70, 0, 0x64};
unsigned char stmp21113[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0xCF, 0x60, 0, 0x64};
unsigned char stmp21114[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0xDF, 0x50, 0, 0x64};
unsigned char stmp21115[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0xEF, 0x40, 0, 0x64};
unsigned char stmp21116[8] = {0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0x30, 0, 0x64};


unsigned char stmp215[8] = {0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10};

unsigned char stmp2170[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0xFC};//From ABS/VSA Modulator


unsigned char stmp130[8] = {0x00, 0x00, 0xA0, 0x10, 0x10, 0x00, 0x00, 0xFF};
unsigned char stmp165[8] = {0x46, 0x80, 0x1A, 0x31, 0xE0, 0x00, 0x18, 0xB4};
unsigned char stmp166[8] = {0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0xD0, 0x00};
unsigned char stmp167[8] = {0x00, 0x30, 0x14, 0x40, 0x3D, 0xD8, 0x00, 0x00};//Roller
unsigned char stmp200[8] = {0x7F, 0xD6, 0x80, 0xF5, 0x80, 0x02, 0x06, 0xA4};//Roller
unsigned char stmp21C[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp21D[8] = {0x7F, 0x3F, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF};
unsigned char stmp21F[8] = {0x00, 0x64, 0x00, 0x7F, 0x01, 0x17, 0x88, 0xFB};//Roller
unsigned char stmp242[8] = {0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF6};//Roller
unsigned char stmp243[8] = {0x98, 0x00, 0x09, 0x60, 0x02, 0x00, 0x00, 0xAD};//Roller
unsigned char stmp244[8] = {0x64, 0xF0, 0x64, 0xF0, 0x64, 0xF0, 0x64, 0xF0};
unsigned char stmp245[8] = {0x80, 0x17, 0xE8, 0x01, 0x80, 0x00, 0x00, 0x00};
unsigned char stmp246[8] = {0xC0, 0x07, 0xFF, 0x08, 0x00, 0x20, 0x80, 0x00};//Roller
unsigned char stmp25D[8] = {0x07, 0xF8, 0x3C, 0xF4, 0x18, 0x00, 0x00, 0x00};//Roller

unsigned char stmp21E1[8] = {0, 0, 0, 0, 0, 0, 0x00, 0xFF};
unsigned char stmp21E2[8] = {0, 0, 0, 0, 0, 0, 0x01, 0xFE};
unsigned char stmp21E3[8] = {0, 0, 0, 0, 0, 0, 0x02, 0xFD};
unsigned char stmp21E4[8] = {0, 0, 0, 0, 0, 0, 0x03, 0xFC};
unsigned char stmp21E5[8] = {0, 0, 0, 0, 0, 0, 0x04, 0xFB};
unsigned char stmp21E6[8] = {0, 0, 0, 0, 0, 0, 0x05, 0xFA};
unsigned char stmp21E7[8] = {0, 0, 0, 0, 0, 0, 0x06, 0xF9};
unsigned char stmp21E8[8] = {0, 0, 0, 0, 0, 0, 0x07, 0xF8};
unsigned char stmp21E9[8] = {0, 0, 0, 0, 0, 0, 0x08, 0xF7};
unsigned char stmp21E0[8] = {0, 0, 0, 0, 0, 0, 0x09, 0xF6};
unsigned char stmp21E11[8] = {0, 0, 0, 0, 0, 0, 0x0A, 0xF5};
unsigned char stmp21E12[8] = {0, 0, 0, 0, 0, 0, 0x0B, 0xF4};
unsigned char stmp21E13[8] = {0, 0, 0, 0, 0, 0, 0x0C, 0xF3};
unsigned char stmp21E14[8] = {0, 0, 0, 0, 0, 0, 0x0D, 0xF2};
unsigned char stmp21E15[8] = {0, 0, 0, 0, 0, 0, 0x0E, 0xF1};
unsigned char stmp21E16[8] = {0, 0, 0, 0, 0, 0, 0x0F, 0xF0};

unsigned char stmp78[8] = {0x90, 0, 0x07, 0xB7, 0x46, 0x5F, 0x94, 0x78};
unsigned char stmp79[8] = {0x90, 0x10, 0x07, 0xF8, 0, 0, 0, 0x6F};

/*
  unsigned char stmp6DA[8] = {0, 248, 237, 0, 0, 0, 0, 0};
  unsigned char stmp6DA_2[8] = {0, 120, 237, 0, 12, 3, 0, 0};
  unsigned char stmp6DA_R[8] = {0, 248, 237, 0, 06, 04, 0, 0};

  unsigned char stmp6DB[8] = {0, 0, 3, 24, 228, 237, 0, 30};
  unsigned char stmp6DB_2[8] = {0, 0, 2, 0, 228, 237, 0, 30};

  unsigned char stmp6DC[8] = {0, 0, 2, 228, 228, 0, 0, 58};
  unsigned char stmp6DC_2[8] = {0, 0, 2, 56, 64, 0, 0, 146};
*/
unsigned long lastSend = 0;
unsigned long lastSend1 = 0;
unsigned long lastSend2 = 0;

void setup() {


  Serial.begin(9600);

  while (CAN_OK != CAN.begin(CAN_500KBPS, MCP_8MHz))
  {
    Serial.println("CAN BUS init Failed");
    delay(100);
  }
  Serial.println("CAN BUS Shield Init OK!");


}


void loop() {
  /*
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

    }
  */
  if ((millis() - lastSend > 20)) {

    counter = 0; //did not need to see these rolling counters, only those for 217


    if (counter == 0) {
    //  CAN.sendMsgBuf(0x211, 0, 8, stmp2111);
    //  CAN.sendMsgBuf(0x21E, 0, 8, stmp21E1);
    }
    if (counter == 2) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp2112);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E2);
    }
    if (counter == 3) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp2113);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E3);
    }
    if (counter == 4) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp2114);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E4);
    }
    if (counter == 5) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp2115);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E5);
    }
    if (counter == 6) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp2116);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E6);
    }
    if (counter == 7) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp2117);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E7);
    }
    if (counter == 8) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp2118);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E8);
    }
    if (counter == 9) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp2119);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E9);
    }
    if (counter == 10) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp21110);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E0);
    }
    if (counter == 11) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp21111);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E11);
    }

    if (counter == 12) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp21112);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E12);
    }
    if (counter == 13) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp21113);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E13);
    }
    if (counter == 14) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp21114);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E14);
    }
    if (counter == 15) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp21115);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E15);
    }
    if (counter == 16) {
      CAN.sendMsgBuf(0x211, 0, 8, stmp21116);
      CAN.sendMsgBuf(0x21E, 0, 8, stmp21E16);
      counter = 0;
    }




    CAN.sendMsgBuf(0x202, 0, 8, stmp202);
    //CAN.sendMsgBuf(0x130, 0, 8, stmp130);
    //CAN.sendMsgBuf(0x165, 0, 8, stmp165);
    //CAN.sendMsgBuf(0x166, 0, 8, stmp166);
    //CAN.sendMsgBuf(0x167, 0, 8, stmp167);
    //CAN.sendMsgBuf(0x200, 0, 8, stmp200);
   // CAN.sendMsgBuf(0x21C, 0, 8, stmp21C);
   // CAN.sendMsgBuf(0x21D, 0, 8, stmp21D);
   // CAN.sendMsgBuf(0x21C, 0, 8, stmp21C);
   // CAN.sendMsgBuf(0x21D, 0, 8, stmp21D);
   // CAN.sendMsgBuf(0x21F, 0, 8, stmp21F);
   // CAN.sendMsgBuf(0x242, 0, 8, stmp242);
   // CAN.sendMsgBuf(0x243, 0, 8, stmp243);
   // CAN.sendMsgBuf(0x244, 0, 8, stmp244);
   // CAN.sendMsgBuf(0x245, 0, 8, stmp245);
   // CAN.sendMsgBuf(0x246, 0, 8, stmp246);
   // CAN.sendMsgBuf(0x25D, 0, 8, stmp25D);
    
   // CAN.sendMsgBuf(0x78, 0, 8, stmp78);
  //  CAN.sendMsgBuf(0x79, 0, 8, stmp79);
 //   CAN.sendMsgBuf(0x215, 0, 8, stmp215);
    CAN.sendMsgBuf(0x217, 0, 8, stmp2170);


    lastSend = millis();


    i = stmp2170[6];
    i = i + 1;
    j = stmp2170[7];
    j = j - 1;


    if (stmp2170[6] == 223) {
      stmp2170[6] = 0xD0;
      stmp2170[7] = 0xFC;
      i = stmp2170[6];
      j = stmp2170[7];

    }

    //   if (stmp2170[6] == 220) {
    //     //Serial.println("reset");
    //     stmp2170[6] = i + 1;
    //     stmp2170[7] = j - 1;

    //      i = stmp2170[6];
    //      j = stmp2170[7];
    // }

    stmp2170[6] = i;
    stmp2170[7] = j;



  }






}
