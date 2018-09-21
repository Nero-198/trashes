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
#define SW_Used 33 //0から数えて何番目まで埋まってるかを書くこと！
int sw[31];
int Line[7];//Line0~7

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
    Serial.begin(115200);
    
}

void loop() {
  int sw_Num;
  int incomingByte;

   /* 1,0を16u2に送る。
    Serial.write(1);
    digitalWrite(LED_PIN ,HIGH);
    delay(1000);
    Serial.write(0);
    digitalWrite(LED_PIN ,LOW);
    delay(1000);
    */
    /*0~10の値を16u2に送る
    for(sw = 0;sw<=10;sw++){
      Serial.write(sw);
      */
/*forで入力管理しようとした、失敗。
  for(sw_Num=0;sw_Num<4;sw_Num++){  
    sw = digitalRead(sw_Num+2);
    if(sw = HIGH){
      Serial.write(sw_Num);
      digitalWrite(LED_PIN ,HIGH);
      Serial.println(sw,DEC);
    }
    digitalWrite(LED_PIN ,LOW);
    }
    */
    /*
    if (Serial.available() > 0) { // 受信したデータが存在する
        incomingByte = Serial.read(); // 受信データを読み込む
        if(incomingByte == 0xFF){
              sw[0] = digitalRead(SW0);
              sw[1] = digitalRead(SW1);
              sw[2] = digitalRead(SW2);
              sw[3] = digitalRead(SW3);
              Serial.write(sw,4);
              }
              */
              /*
              sendIntData(12345);
              delay(500);

              sendIntData(-12345);
              delay(500);
              */

    PushSW();
    sendIntData(Line[1]);
    
}

void sendIntData(int val){
    Serial.write('H');//ヘッダ
    Serial.write(lowByte(val));
    Serial.write(highByte(val));
}


void PushSW(void){
  Line[1] = 0;//初期化
  Line[2] = 0;
     for(int temp=0;temp<=SW_Used;temp++){
     sw[temp] = digitalRead(temp + 2); //sw配列にスイッチデータ書き込み
        if(sw[temp] == 0){//**注　不論理
            if(temp <=15){//Switch0~15
              Line[1] = Line[1] + power_int(temp);  
              }
              else{//Switch16~31
              Line[2] = Line[2] + power_int(temp);  
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

