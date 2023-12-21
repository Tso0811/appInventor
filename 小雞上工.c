#include <SimpleDHT.h> 
char dispaly;
int pinDHT11 = 2;  //感測器DAT 接ARDUINO腳位2
SimpleDHT11 dht11;

int trigPin = 7;    //感測器 Trig腳接 Arduino pin 7
int echoPin = 8;    //感測器 Echo 腳接 Arduino pin 8
int Duration;
int Distance;
#define led_pin 12
#define fsr_pin A0

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(trigPin, OUTPUT);      
  pinMode(echoPin, INPUT);    
  digitalWrite(trigPin,LOW);   
  
}

void loop() {
    byte temperature = 0; //溫度
    byte humidity = 0;    //濕度
    int err = SimpleDHTErrSuccess;
    h = dht.readHumidity();     //濕度
    t = dht.readTemperature();  //攝氏溫度
    // start working...
    Serial.println("=================================");
    if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
       Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
       return;
    }

    if (BT.available() > 0) {   //溫度濕度
        if (BT.read() == "H") { //當arduino接收到app傳送的字元"H"
        BT.print("Humidity = %d, Temperature = %d", (int)h, (int)t); //將溫度濕度傳回app
        }
    }



    if (BT.available() > 0) {   //垃圾桶
        if (BT.read() == "D"){  //當arduino接收到app傳送的字元"D"
            digitalWrite(trigPin,HIGH); //發射超音波
            delay(1);
            digitalWrite(trigPin,LOW);
            Duration = pulseIn(echoPin,HIGH); //超音波發射到接收的時間
            Distance = Duration*0.034/2; //計算距離(cm)

            if (Distance<5) {
                BT.print("f");  //傳送f字元給app 代表垃圾桶已滿 
            }
            else{
                BT.print("n");  //傳送n字元給app 代表垃圾桶未滿
            }

            }
 }

 
    
}

