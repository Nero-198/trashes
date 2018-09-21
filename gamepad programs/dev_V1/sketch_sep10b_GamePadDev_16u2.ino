//16u2側　開発版
#define LED_PIN LED_BUILTIN
const uint8_t resetPin = IO_MCU_RESET_PIN;


void setup()
{
  // Set main MCU by default active
  digitalWrite(resetPin, HIGH);
  pinMode(resetPin, OUTPUT);

  // Start USB Serial
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop(){
  /*
  int incomingByte;
  Serial1.write(0xFF);
  if (Serial1.available() > 0) { // 受信したデータが存在する
    delay(30); 
    byte data_size = Serial.available();
    for(int i=0;i<3;i++){
    incomingByte = Serial1.read(); // 受信データを読み込む

    Serial.print("I received: "); // 受信データを送りかえす
    Serial.println(incomingByte);
   
    }
    */
    int recv_data;

     // 受信バッファに３バイト（ヘッダ＋int）以上のデータが着ているか確認
  if ( Serial1.available() >= sizeof('H') + sizeof(int) ) {
    // ヘッダの確認
    if ( Serial1.read() == 'H' ) {
      int low = Serial1.read(); // 下位バイトの読み取り
      int high = Serial1.read(); // 上位バイトの読み取り
      recv_data = makeWord(high,low); 
      Serial.println(recv_data,HEX);
    }
  }
  
}
