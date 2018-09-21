//16u2側　開発版

#include <HID-Project.h>
#include <HID-Settings.h>

const int pinLed = LED_BUILTIN;
uint8_t BinData[16][2];
uint8_t mem[16][2];
uint16_t recv_data[10];

void setup()
{
  pinMode(2,INPUT);
  pinMode(pinLed, OUTPUT);
  Serial.begin(115200);//USBへ
  Serial1.begin(115200);//328pへ

  Gamepad.begin();//ゲームパッド化?する
}

void loop(){
  while(1){
  if(digitalRead(2) == HIGH){
  SerialRecv();
  makeBIN();
  JoyToButton();
  Press();
  Axis16bit();
  Axis8bit();
  Dpad();
  
  //PrintRecv();//シリアルデータをprint
  //PrintBIN();//バイナリデータをprint
  //Printmem();
  Serial.flush();
  
  Gamepad.write();// Functions above only set the values.This writes the report to the host.
  }
  }
}

void SerialRecv(void){
  int num = 9,
      low,
      high;
  char n;
  //Serial.println(Serial1.available());
     // 受信バッファに３バイト（ヘッダ＋int）以上のデータが着ているか確認
  if ( Serial1.available() >= sizeof('A') + sizeof(int) ) {
    // ヘッダの確認
    n = Serial1.read();
    //Serial.print(n);
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
    delayMicroseconds(100);
    //Serial.println(num);
      low = Serial1.read(); // 下位バイトの読み取り
      high = Serial1.read(); // 上位バイトの読み取り
      //Serial.println(high);
      //Serial.print(low);
      recv_data[num]= makeWord(high,low);
  }
  else{
    Serial1.write('H');//準備完了を伝える。
  }
  /*
  else {
    while(Serial1.available()){ 
    Serial1.read(); 
    }
  }*/
}


void makeBIN(void){//レシーブデータをバイナリ配列(15*8)へ
  uint16_t UintData;
  for(uint8_t LineNum =0;LineNum<=1;LineNum++){
      UintData = recv_data[LineNum];
      for(uint8_t temp = 0;temp <=15;temp++){
        BinData[temp][LineNum] = UintData % 2;
        UintData = UintData / 2;
       // Serial.print(BinData[temp][LineNum]);
      }
     // Serial.print("\t");
  }
  //Serial.print("\n");

}

void Press(void){//バイナリ配列をPCへ
  for(uint8_t temp1 = 0;temp1<=15;temp1++){
        if(mem[temp1][0] < BinData[temp1][0]){
          Gamepad.press(temp1 + 1);//ゲームパッドは１から始まる
          //Serial.println("press");
        }
        else if(mem[temp1][0] > BinData[temp1][0]){
          Gamepad.release(temp1 + 1);
          //Serial.println("release");
          }
          mem[temp1][0] = BinData[temp1][0];
  }
  for(uint8_t temp2 = 0;temp2<=15;temp2++){
        if(mem[temp2][1] < BinData[temp2][1]){
          Gamepad.press(temp2 + 17);
          //Serial.println("press");
        }
        else if(mem[temp2][1] > BinData[temp2][1]){
          Gamepad.release(temp2 + 17);
          //Serial.println("release");
        }
        mem[temp2][1] = BinData[temp2][1];
  }
}
void Axis16bit(void){
  int16_t resize[4];
  for(int temp=0;temp<=3;temp++){
  resize[temp] = recv_data[temp+2]*64+32-32767;//Axis()はデータ引き伸ばし+負数化が必要
  }
    Gamepad.xAxis(resize[0]);//軸1
    Gamepad.yAxis(resize[1]);
    Gamepad.rxAxis(resize[2]);//軸2
    Gamepad.ryAxis(resize[3]);
    //Serial.print(resize[2]);
    //Serial.print("\t");
    //Serial.println(resize[3]);
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
void JoyToButton(void){//軸データをスイッチデータに
  //軸１
  if(recv_data[2] > 700){
    BinData[8][1] = 0;
    BinData[9][1] = 1;
   // Serial.println("up");
  }
  else if(recv_data[2] < 300){
    BinData[8][1] = 1;
    BinData[9][1] = 0;
   // Serial.println("down");
  }
  else {
    BinData[8][1] = 0;
    BinData[9][1] = 0;
    //Serial.println("center");
  }
  //軸２
  if(recv_data[3] > 700){
    BinData[10][1] = 0;
    BinData[11][1] = 1;
  }
  else if(recv_data[3] < 300){
    BinData[10][1] = 1;
    BinData[11][1] = 0;
  }
  else {
    BinData[10][1] = 0;
    BinData[11][1] = 0;
  }
  //軸３
  if(recv_data[4] > 700){
    BinData[12][1] = 0;
    BinData[13][1] = 1;
  }
  else if(recv_data[4] < 300){
    BinData[12][1] = 1;
    BinData[13][1] = 0;
  }
  else {
    BinData[12][1] = 0;
    BinData[13][1] = 0;
  }
  //軸４
  if(recv_data[5] > 700){
    BinData[14][1] = 0;
    BinData[15][1] = 1;
  }
  else if(recv_data[5] < 300){
    BinData[14][1] = 1;
    BinData[15][1] = 0;
  }
  else {
    BinData[14][1] = 0;
    BinData[15][1] = 0;
  }
}
//-----------------デバッグ用-----------------
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
  Serial.flush();
}
void PrintBIN(void){//8行すべてのデータ
  Serial.print("Bin");
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
    Serial.print("Bin");
  Serial.print(BinData[0][1]);  
  Serial.print(BinData[1][1]);  
  Serial.print(BinData[2][1]); 
  Serial.print(BinData[3][1]);  
  Serial.print(BinData[4][1]); 
  Serial.print(BinData[5][1]); 
  Serial.print(BinData[6][1]); 
  Serial.print(BinData[7][1]);
  Serial.print(BinData[8][1]);  
  Serial.print(BinData[9][1]);  
  Serial.print(BinData[10][1]); 
  Serial.print(BinData[11][1]);  
  Serial.print(BinData[12][1]); 
  Serial.print(BinData[13][1]); 
  Serial.print(BinData[14][1]); 
  Serial.print(BinData[15][1]);
  Serial.print("\t");
  Serial.print("\n");
}
void Printmem(void){//8行すべてのデータ
  Serial.print("mem");
  Serial.print(mem[0][0]);  
  Serial.print(mem[1][0]);  
  Serial.print(mem[2][0]);  
  Serial.print(mem[3][0]);  
  Serial.print(mem[4][0]);  
  Serial.print(mem[5][0]);  
  Serial.print(mem[6][0]);  
  Serial.print(mem[7][0]);  
  Serial.print(mem[8][0]);  
  Serial.print(mem[9][0]); 
  Serial.print(mem[10][0]);  
  Serial.print(mem[11][0]);  
  Serial.print(mem[12][0]);  
  Serial.print(mem[13][0]); 
  Serial.print(mem[14][0]);  
  Serial.print(mem[15][0]);  
  Serial.print("\t");   
  Serial.print("\n");
}
