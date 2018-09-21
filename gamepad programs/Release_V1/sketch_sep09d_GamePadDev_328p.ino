//328p側 開発版
#define LED_PIN LED_BUILTIN
//Switches SW"Nunber" "PinNumber"
#define SW0 2
#define SW1 3
#define SW2 4
#define SW3 5
#define SW4 6
#define SW5 7
#define SW6 8
#define SW7 9
#define SW8 10
#define SW9 11
#define SW10 12
#define SW11 13
#define SW12 14
#define SW13 15
#define SW14 16
#define SW15 17
#define SW16 18
#define SW17 19
#define SW18 20
#define SW19 21
#define SW20 22
#define SW21 23
#define SW22 24
#define SW23 25
#define SW24 26
#define SW25 27
#define SW26 28
#define SW27 29
#define SW28 30
#define SW29 31
#define SW30 32
#define SW31 33
#define SW_Used 8 //0から数えて何番目まで埋まってるかを書くこと！
int sw[32];
uint16_t Line[8];//Line0~7
uint16_t ana[4];

void setup() {
    pinMode(LED_PIN,OUTPUT);
    pinMode(SW0,INPUT_PULLUP);
    pinMode(SW1,INPUT_PULLUP);
    pinMode(SW2,INPUT_PULLUP);
    pinMode(SW3,INPUT_PULLUP);
    pinMode(SW4,INPUT_PULLUP);
    pinMode(SW5,INPUT_PULLUP);
    pinMode(SW6,INPUT_PULLUP);
    pinMode(SW7,INPUT_PULLUP);
    pinMode(SW8,INPUT_PULLUP);
    /*未使用ピンの定義はバグの元。
    pinMode(SW9,INPUT_PULLUP);
    pinMode(SW10,INPUT_PULLUP);
    pinMode(SW11,INPUT_PULLUP);
    pinMode(SW12,INPUT_PULLUP);
    pinMode(SW13,INPUT_PULLUP);
    pinMode(SW14,INPUT_PULLUP);
    pinMode(SW15,INPUT_PULLUP);
    pinMode(SW16,INPUT_PULLUP);
    pinMode(SW17,INPUT_PULLUP);
    pinMode(SW18,INPUT_PULLUP);
    pinMode(SW19,INPUT_PULLUP);
    pinMode(SW20,INPUT_PULLUP);
    pinMode(SW21,INPUT_PULLUP);
    pinMode(SW22,INPUT_PULLUP);
    pinMode(SW23,INPUT_PULLUP);
    pinMode(SW24,INPUT_PULLUP);
    pinMode(SW25,INPUT_PULLUP);
    pinMode(SW26,INPUT_PULLUP);
    pinMode(SW27,INPUT_PULLUP);
    pinMode(SW28,INPUT_PULLUP);
    pinMode(SW29,INPUT_PULLUP);
    pinMode(SW30,INPUT_PULLUP);
    pinMode(SW31,INPUT_PULLUP);
    */
    Serial.begin(115200);
    
}

void loop() {
  while(1){
  if(digitalRead(13) == HIGH){
  if(Serial.read() == 'H'){
    ana[0]=analogRead(0);
    ana[1]=analogRead(1);
    ana[2]=analogRead(2);
    ana[3]=analogRead(3);
    PushSW();
    sendUintData(Line[0],0);
    sendUintData(Line[1],1);
    sendUintData(ana[0],2);   
    sendUintData(ana[1],3);
    sendUintData(ana[2],4);
    sendUintData(ana[3],5);
    sendUintData(0x0000,6);
    sendUintData(0x0000,7);
    /*
    Serial.print(analogRead(2));
    Serial.print("\t");
    Serial.println(analogRead(3));
    delay(100);
    */
    Serial.flush();
    CleanLine();
    //Serial.write('H');
  }
  }
  }
}

void sendUintData(uint16_t val,int n){
  if(n == 0){
    Serial.write('A');//ヘッダ
    Serial.write(lowByte(val));
    Serial.write(highByte(val));
  }
  else if(n == 1){
    Serial.write('B');//ヘッダ
    Serial.write(lowByte(val));
    Serial.write(highByte(val));
  }
  else if(n == 2){
    delay(1);
    Serial.write('C');//ヘッダ
    Serial.write(lowByte(val));
    Serial.write(highByte(val));
  }
  else if(n == 3){
    delay(1);
    Serial.write('D');//ヘッダ
    Serial.write(lowByte(val));
    Serial.write(highByte(val));
  }
  else if(n == 4){
    delay(1);
    Serial.write('E');//ヘッダ
    Serial.write(lowByte(val));
    Serial.write(highByte(val));
  }
  else if(n == 5){
    delay(1);
    Serial.write('F');//ヘッダ
    Serial.write(lowByte(val));
    Serial.write(highByte(val));
  }
  else if(n == 6){
    Serial.write('G');//ヘッダ
    Serial.write(lowByte(val));
    Serial.write(highByte(val));
  }
  else if(n == 7){
    Serial.write('H');//ヘッダ
    Serial.write(lowByte(val));
    Serial.write(highByte(val));
  }
  Serial.flush();
  }
  
void PushSW(void){ //押されたボタンをLine配列に書き込む
     for(int temp=0;temp<=SW_Used;temp++){
     sw[temp] = digitalRead(temp + 2); //sw配列にスイッチデータ書き込み
        if(sw[temp] == 0){//**注　不論理
            if(temp <=15){  //Switch0~15
              Line[0] = Line[0] + power_int(temp); 
              }
              else{  //Switch16~31
              Line[1] = Line[1] + power_int(temp); 
              }
        }
     }
}
int power_int(int val){
    int pow = 1;
    for(int n=0;n<val;n++){
      pow = pow * 2;
    }
    return pow;
}

void CleanLine(void){
   Line[0]=0;
   Line[1]=0;
   Line[2]=0;
   Line[3]=0;   
   Line[4]=0;
   Line[5]=0;
   Line[6]=0;
   Line[7]=0;
}
