#include <SPI.h>
#include <mcp_can.h>
const int spiCSPin = 9;
unsigned long previousCanSend = 0;

MCP_CAN CAN(spiCSPin);

int i = 0;
int j = 0;
int k = 0;
int counter = 0;
byte var = 0;

unsigned char stmp78[8] = {0xDF, 0x3C, 0xFF, 0xE0, 0x98, 0xC0, 0x00, 0x00};
unsigned char stmp79[8] = {0xDF, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp86[8] = {0x3E, 0x83, 0x81, 0x5B, 0xE9, 0x98, 0x08, 0x00};
unsigned char stmpFD[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp165[8] = {0x40, 0x00, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x00};
unsigned char stmp166[8] = {0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp215[8] = {0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10};
unsigned char stmp21C[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp240[8] = {0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp245[8] = {0x80, 0x17, 0xE8, 0x01, 0x80, 0x00, 0x00, 0x00};
unsigned char stmp25D[8] = {0x07, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp420[8] = {0x4D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF2, 0x80};
unsigned char stmp4F0[8] = {0x14, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//unsigned char stmp9E[8] = {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80};
unsigned char stmp9F[8] = {0x40, 0x64, 0x04, 0x09, 0x7F, 0x00, 0x69, 0x02};  //Reverse = 0x41, PND = 0x40
unsigned char stmp202[8] = {0x00, 0x03, 0x08, 0x00, 0x00, 0x00, 0x18, 0x93}; //tacho and vss, vss = 0 for sensor mounted normal to direction of travel, must provide vss if                        										//mounted at an other angle relative to direction of travel
//unsigned char stmp202[8] = {0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x18, 0x93};
//unsigned char stmp228[8] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//unsigned char stmp340[8] = {0x68, 0x00, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00};

unsigned char stmp50[8] = {0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp91[8] = {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp9A[8] = {0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00};
unsigned char stmp9B[8] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp9E[8] = {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80};
unsigned char stmp217[8] = {0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp228[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp340[8] = {0x00, 0x00, 0x01, 0x0C, 0x00, 0x00, 0x02, 0x00};
unsigned char stmp40A[8] = {0xBF, 0x03, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp413[8] = {0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp43D[8] = {0x00, 0x10, 0x29, 0x31, 0x36, 0x24, 0x00, 0x00};
unsigned char stmp4F5[8] = {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp4F8[8] = {0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp511[3] = {0x03, 0x02, 0x00};

unsigned char stmp40A1[8] = {0xC1, 0x00, 0x4A, 0x4D, 0x31, 0x42, 0x4E, 0x31};
unsigned char stmp40A2[8] = {0xC1, 0x01, 0x4C, 0x37, 0x33, 0x48, 0x31, 0x31};
unsigned char stmp40A3[8] = {0xC1, 0x02, 0x31, 0x33, 0x35, 0x30, 0x35, 0x00};
unsigned char stmp40A4[8] = {0xC1, 0x03, 0x38, 0x00, 0x1B, 0x09, 0x94, 0x00};
unsigned char stmp40A5[8] = {0xC1, 0x04, 0x00, 0x00, 0x07, 0xBD, 0x00, 0x00};
unsigned char stmp40A6[8] = {0xC0, 0x00, 0x82, 0xDD, 0xC3, 0x09, 0x06, 0x33};
unsigned char stmp40A7[8] = {0xC0, 0x01, 0x00, 0x03, 0x5A, 0x18, 0x00, 0x49};
unsigned char stmp40A8[8] = {0xBF, 0x00, 0x3D, 0x00, 0x00, 0x88, 0xFF, 0x00};
unsigned char stmp40A9[8] = {0xBF, 0x01, 0x21, 0x0D, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp40A10[8] = {0xBF, 0x02, 0x22, 0x00, 0x00, 0x00, 0x00, 0x0F};
unsigned char stmp40A11[8] = {0xBF, 0x03, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp40A12[8] = {0xBF, 0x04, 0x31, 0x00, 0x00, 0x10, 0x00, 0x00};
unsigned char stmp40A13[8] = {0xBF, 0x05, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char stmp40A14[8] = {0xBF, 0x06, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00};
unsigned char stmp40A15[8] = {0xBF, 0x07, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00};
unsigned char stmp40A16[8] = {0xC0, 0x00, 0x82, 0xDD, 0xC3, 0x13, 0x06, 0x33};
unsigned char stmp40A17[8] = {0xC0, 0x01, 0x00, 0x03, 0x5A, 0x18, 0x00, 0x4A};
unsigned char stmp40A18[8] = {0xBF, 0x00, 0x3D, 0x6A, 0x00, 0x89, 0xFF, 0x00};
unsigned char stmp40A19[8] = {0xBF, 0x08, 0x21, 0x20, 0x01, 0x00, 0x00, 0x00};
unsigned char stmp40A20[8] = {0xBF, 0x09, 0x21, 0x00, 0x00, 0x40, 0x00, 0x00};
unsigned char stmp40A21[8] = {0xBF, 0x10, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00};
unsigned char stmp40A22[8] = {0xBF, 0x11, 0x30, 0x03, 0xA4, 0x00, 0x00, 0x00};

unsigned long lastSend = 0;
unsigned long lastSend1 = 0;
unsigned long lastSend2 = 0;

void setup() {


  Serial.begin(9600);

  while (CAN_OK != CAN.begin(CAN_125KBPS, MCP_16MHz))
  {
    Serial.println("CAN BUS init Failed");
    delay(100);
  }
  Serial.println("CAN BUS Shield Init OK!");


}


void loop() {
  unsigned char len = 0;
  unsigned char buf[8];
  unsigned long canId = 0;

  if (CAN_MSGAVAIL == CAN.checkReceive())
  {
    CAN.readMsgBuf(&len, buf);
    canId = CAN.getCanId();
    //Serial.println(canId);
  }

  if (canId == 0x477) {

    Serial.print(buf[0], HEX);
    Serial.print(" ");
    Serial.print(buf[1], HEX);
    Serial.print(" ");
    Serial.print(buf[2], HEX);
    Serial.print(" ");
    Serial.print(buf[3], HEX);
    Serial.print(" ");
    Serial.print(buf[4], HEX);
    Serial.print(" ");
    Serial.println("");
  }





  if ((millis() - lastSend > 20)) {


    CAN.sendMsgBuf(0x78, 0, 8, stmp78);
    CAN.sendMsgBuf(0x86, 0, 8, stmp86);
    CAN.sendMsgBuf(0x9E, 0, 8, stmp9E);
    CAN.sendMsgBuf(0x9F, 0, 8, stmp9F);


    lastSend = millis();

    i = stmp78[6];
    i = i + 16;

    j = stmp86[5];
    j = j + 1;
    //j = stmp2170[7];
    // j = j - 1;


    if (stmp78[6] == 240) {
      stmp78[6] = 0x00;
      i = stmp78[6];

    }


    if (stmp86[5] == 155) {
      stmp86[6] = 0x98;
      j = stmp86[6];

    }

    stmp78[6] = i;
    stmp86[5] = j;
  }






  if ((millis() - lastSend1 > 20)) {

    CAN.sendMsgBuf(0x202, 0, 8, stmp202);


    lastSend1 = millis();

    var = stmpFD[2];
    var = var + 80;
    //j = stmp2170[7];
    // j = j - 1;


    /* if (stmpFD[6] == 240) {
       stmp78[6] = 0x00;
       i = stmp78[6];

      }
    */

    stmpFD[2] = var;






  }



  if ((millis() - lastSend2 > 100)) {

    CAN.sendMsgBuf(0x91, 0, 8, stmp91);
    counter++;

    if (counter == 1) {
      // CAN.sendMsgBuf(0x40A, 0, 8, stmp40A1);
    }

    if (counter == 2) {
      // CAN.sendMsgBuf(0x40A, 0, 8, stmp40A2);
    }

    if (counter == 3) {
      //CAN.sendMsgBuf(0x40A, 0, 8, stmp40A3);
    }

    if (counter == 4) {
      CAN.sendMsgBuf(0x40A, 0, 8, stmp40A4);
    }

    if (counter == 5) {
      // CAN.sendMsgBuf(0x40A, 0, 8, stmp40A5);
    }

    if (counter == 6) {
      // CAN.sendMsgBuf(0x40A, 0, 8, stmp40A6);
    }

    if (counter == 7) {
      // CAN.sendMsgBuf(0x40A, 0, 8, stmp40A7);
    }

    if (counter == 8) {
      //  CAN.sendMsgBuf(0x40A, 0, 8, stmp40A8);
    }

    if (counter == 9) {
      CAN.sendMsgBuf(0x40A, 0, 8, stmp40A9);
    }

    if (counter == 10) {
      //  CAN.sendMsgBuf(0x40A, 0, 8, stmp40A10);
    }

    if (counter == 11) {
      //  CAN.sendMsgBuf(0x40A, 0, 8, stmp40A11);
    }

    if (counter == 12) {
      //  CAN.sendMsgBuf(0x40A, 0, 8, stmp40A12);
    }

    if (counter == 13) {
      //  CAN.sendMsgBuf(0x40A, 0, 8, stmp40A13);
    }

    if (counter == 14) {
      //  CAN.sendMsgBuf(0x40A, 0, 8, stmp40A14);
    }

    if (counter == 15) {
      CAN.sendMsgBuf(0x40A, 0, 8, stmp40A15);
    }

    if (counter == 16) {
      CAN.sendMsgBuf(0x40A, 0, 8, stmp40A16);
    }

    if (counter == 17) {
      CAN.sendMsgBuf(0x40A, 0, 8, stmp40A17);
    }
    if (counter == 18) {
      CAN.sendMsgBuf(0x40A, 0, 8, stmp40A18);
    }
    if (counter == 19) {
     CAN.sendMsgBuf(0x40A, 0, 8, stmp40A19);
    }
    if (counter == 200) {
      CAN.sendMsgBuf(0x40A, 0, 8, stmp40A20);
    }
    if (counter == 21) {
      CAN.sendMsgBuf(0x40A, 0, 8, stmp40A21);
    }
    if (counter == 22) {
      CAN.sendMsgBuf(0x40A, 0, 8, stmp40A22);
      counter = 0;
    }






    lastSend2 = millis();


    k = stmp91[3];
    k = k + 1;


    if (stmp91[3] == 15) {
      stmp91[3] = 0x00;
      k = stmp91[3];

    }


    stmp91[3] = k;


  }






}
