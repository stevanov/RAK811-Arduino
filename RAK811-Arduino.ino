#include "SoftwareSerial.h"
#include "keys.h"

#define LoRaWAN 0
#define LoRaP2P 1
#define OTAA 0
#define ABP 1
#define STATUS_RECV_DATA  "at+recv=0,0,0"
#define STATUS_TX_COMFIRMED  "at+recv=1,0,0"
#define STATUS_TX_UNCOMFIRMED  "at+recv=2,0,0"
#define STATUS_JOINED_SUCCESS  "at+recv=3,0,0"
#define STATUS_JOINED_FAILED  "at+recv=4,0,0"
#define STATUS_TX_TIMEOUT  "at+recv=5,0,0"
#define STATUS_RX2_TIMEOUT  "at+recv=6,0,0"
#define STATUS_DOWNLINK_REPEATED  "at+recv=7,0,0"
#define STATUS_WAKE_UP  "at+recv=8,0,0"
#define STATUS_P2PTX_COMPLETE  "at+recv=9,0,0"
#define STATUS_UNKNOWN  "at+recv=100,0,0"

#define SWTXpin 11
#define SWRXpin 10

//SoftwareSerial DebugSerial(SWRXpin,SWTXpin);
#define ATSerial Serial1
#define DebugSerial Serial


void setup() {
  DebugSerial.begin(115200);
  ATSerial.begin(115200);
  ATSerial.setTimeout(10000);
  while(DebugSerial.read() >= 0) {}
    while(!DebugSerial);
  DebugSerial.println("Boot");
}

int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout){

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    memset(response, '\0', 100); // Clean response buffer
    
    delay(100); // Delay to be sure no passed commands interfere
    
    while( ATSerial.available() > 0) ATSerial.read();    // Wait for clean input buffer
    
    ATSerial.println(ATcommand);    // Send the AT command 

    previous = millis();

    // this loop waits for the answer
    do{
        // if there are data in the UART input buffer, reads it and checks for the asnwer
        if(ATSerial.available() != 0){    
            response[x] = ATSerial.read();
            x++;
            // check if the desired answer is in the response of the module
            if (strstr(response, expected_answer) != NULL){
                answer = 1;
            }
        }
    // Waits for the answer with time out
    } while((answer == 0) && ((millis() - previous) < timeout));    

    return answer;
}

void loop() {
  bool res;

  while (!sendATcommand("at+version", "OK2.0.2.2\r\n", 2000)){
    DebugSerial.println("1 Did not get expected response, retry");
  }
  
  while (!sendATcommand("at+band", "OKEU868\r\n", 2000)){
    DebugSerial.println("2 Did not get expected response, retry");
  }
  
  while (!sendATcommand("at+mode=0", "OK\r\n", 2000)){
    DebugSerial.println("3 Did not get expected response, retry");
  }
  //RETRY
  
  while (!sendATcommand("at+set_config=app_key:YOURKEYHERE", "OK\r\n", 2000)){
    DebugSerial.println("4 Did not get expected response, retry");
  }
  //RETRY
  
  while (!sendATcommand("at+set_config=app_eui:YOURKEYHERE", "OK\r\n", 2000)){
    DebugSerial.println("5 Did not get expected response, retry");
  }
  //RETRY
  
  while (!sendATcommand("at+set_config=dev_eui:YOURKEYHERE", "OK\r\n", 2000)){
    DebugSerial.println("6 Did not get expected response, retry");
  }
  //RETRY
  
  while (!sendATcommand("at+join=otaa", "OK\r\n", 2000)){
    DebugSerial.println("7 Did not get expected response, retry");
  }
  //RETRY

  // response = ATSerial.readStringUntil('\n');
  // //IF AFTER 10 SECONDS JOIN FAILED, RETRY 
  
  // if (response == STATUS_JOINED_SUCCESS) {
  //   DebugSerial.println("STATUS_JOINED_SUCCESS");
  //   DebugSerial.println("BLEEPITYBLOOP, SENDING!");
  //   //SOME SORT OF VALIDATION NEEDED HERE, CANT TEST BECAUSE OUT OF RANGE
  //   //    while (RAKLoRa.rk_sendData(1,1,buffer)) {
  //   //      DebugSerial.println(RAKLoRa.rk_recvData());
  //   //    }
  //   //SOME SORT OF VALIDATION NEEDED HERE, CANT TEST BECAUSE OUT OF RANGE
    
  // } else if (response == STATUS_RX2_TIMEOUT) {
  //   DebugSerial.println("STATUS_RX2_TIMEOUT");
  // }

  //Retry
  delay(5000);
}
