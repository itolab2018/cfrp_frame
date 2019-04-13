//電流計測
\#include<FlexiTimer2.h>

unsigned long timer_a = 0;//マイコン起動時からの時間を記録する変数（ミリ秒）
const int ts = 1;//サンプリング時間（ミリ秒）

const int pinI = 1;//アナログ１番ピンを使用する
int current = 0;

int pwm = 0;//この値を０～２５５まで変更することで電圧を０～１２（ｖ）まで変化させることが出来る

void setup() {
    
    //シリアル通信の速度を設定する　シリアルモニターの数値と合わせること
    Serial.begin(115200);
    
    //アナログ入力の基準電圧を１．１（ｖ）に変更する
    analogReference(INTERNAL);
    
    //タイマー割り込みの設定
    FlexiTimer2::set(ts, motorCalculat);
    
    //タイマー割り込みの開始
    FlexiTimer2::start();

    //ピンを出力に設定する
    //５番ピンは"ＰＷＭ出力"に対応している
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
}

void loop() {
    
    //アナログピンから電流を読み込む
    current = analogRead(pinI);
    
    //ピンから信号を出力する
    //２と３を入れ替えると逆転する
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    analogWrite(5, pwm);
}

//１ミリ秒毎にタイマー割り込みで呼び出される関数
void motorCalculat() {
    Serial.print(pwm);
    Serial.print(' ');
    Serial.println(current);
    timer_a += ts;
}
