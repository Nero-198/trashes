//16u2側　開発版
#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const uint8_t resetPin = IO_MCU_RESET_PIN;
uint8_t BinData[16][7];
int16_t recv_data[8];

void setup()
{
  // Set main MCU by default active
  pinMode(2,INPUT);
  pinMode(pinLed, OUTPUT);

  // Start USB Serial
  Serial1.begin(115200);

  Gamepad.begin();//ゲームパッド化?する
}

void loop(){
  if(digitalRead(2) == HIGH){
  SerialRecv();
  PrintRecv();//シリアルデータをprint
  //PrintBIN();//バイナリデータをprint
  makeBIN();
  Press();
  Axis16bit();
  Axis8bit();
  Dpad();
  
  Gamepad.write();// Functions above only set the values.This writes the report to the host.
  }
}

void SerialRecv(void){
  int n,
      num,
      low,
      high;
  Serial1.write('H');//準備完了を伝える。
     // 受信バッファに３バイト（ヘッダ＋int）以上のデータが着ているか確認
  if ( Serial1.available() >= sizeof('A') + sizeof(int) ) {
    // ヘッダの確認
    n = Serial1.read();
    switch(n){
      case 'A': num = 0 ;
      break;
      case 'B': num = 1 ;
      break;
      case 'C': num = 2 ;
      break;
      case 'D': num = 3 ;
      break;
      case 'E': num = 4 ;
      break;
      case 'F': num = 5 ;
      break;
      case 'G': num = 6 ;
      break;
      case 'H': num = 7 ;
      break;
    }
      low = Serial1.read(); // 下位バイトの読み取り
      high = Serial1.read(); // 上位バイトの読み取り
      recv_data[num]= makeWord(high,low);
  }/*
  else {
    while(Serial1.available()){ 
    Serial1.read(); 
    }
  }*/
  delay(40);
}
//デバッグ用
void PrintRecv(void){//8行すべてのデータ
  Serial.print(recv_data[0]);
  Serial.print("\t");   
  Serial.print(recv_data[1]);
  Serial.print("\t");   
  Serial.print(recv_data[2]);
  Serial.print("\t");   
  Serial.print(recv_data[3]);
  Serial.print("\t");   
  Serial.print(recv_data[4]);
  Serial.print("\t");   
  Serial.print(recv_data[5]);
  Serial.print("\t");   
  Serial.print(recv_data[6]);
  Serial.print("\t");   
  Serial.print(recv_data[7]);
  Serial.print("\n");
  return;
}

void makeBIN(void){//レシーブデータをバイナリ配列(15*8)へ
  uint16_t UintData;
  for(int LineNum =0;LineNum<=1;LineNum++){
      UintData = recv_data[LineNum];
      for(int temp = 0;temp <=15;temp++){
        BinData[temp][LineNum] = UintData % 2;
        UintData = UintData / 2;
      }
  }
}
void Press(void){
  for(uint8_t temp1 = 0;temp1<=15;temp1++){
        if(BinData[temp1][0] == 1){
          Gamepad.press(temp1);
        }
        else if(BinData[temp1][0] == 0){
          Gamepad.release(temp1);
          }
  }
  for(uint8_t temp2 = 0;temp2<=15;temp2++){
        if(BinData[temp2][1] == 1){
          Gamepad.press(temp2);
        }
        else if(BinData[temp2][1] == 0){
          Gamepad.release(temp2);
        }
  }
}
void Axis16bit(void){
    Gamepad.xAxis(recv_data[2]);//軸1
    Gamepad.yAxis(recv_data[3]);
    Gamepad.xAxis(recv_data[4]);//軸2
    Gamepad.yAxis(recv_data[5]);
}
void Axis8bit(void){
    Gamepad.zAxis(lowByte(recv_data[6]));
    Gamepad.rzAxis(highByte(recv_data[6]));
}
void Dpad(void){//今は使わないのでコピーのみ。
    // Go through all dPad positions
    // values: 0-8 (0==centered)
    static uint8_t dpad1 = 0;
    Gamepad.dPad1(0);
    if (dpad1 > 0)
      dpad1 = 0;

    static int8_t dpad2 = 0;
    Gamepad.dPad2(0);
    if (dpad2 < 0)
      dpad2 = 0;
}
void PrintBIN(void){//8行すべてのデータ
  Serial.print(BinData[0][0]);  
  Serial.print(BinData[1][0]);  
  Serial.print(BinData[2][0]); 
  Serial.print(BinData[3][0]);  
  Serial.print(BinData[4][0]); 
  Serial.print(BinData[5][0]); 
  Serial.print(BinData[6][0]); 
  Serial.print(BinData[7][0]);
  Serial.print(BinData[8][0]);  
  Serial.print(BinData[9][0]);  
  Serial.print(BinData[10][0]); 
  Serial.print(BinData[11][0]);  
  Serial.print(BinData[12][0]); 
  Serial.print(BinData[13][0]); 
  Serial.print(BinData[14][0]); 
  Serial.print(BinData[15][0]);
  Serial.print("\t");   
  Serial.print("\n");
  return;
}
