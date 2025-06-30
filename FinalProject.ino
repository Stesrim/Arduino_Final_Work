#include <LiquidCrystal.h>
#include <Keypad.h>
  int BASE = 2;  //第一顆 LED 接的 I/O 腳
  int NUM = 8;   //LED 的總數
  int index = 0; //跑馬燈的計數指標，由0開始　
  int TimeLeft = 60;
  #define Ls138_A 30
  #define Ls138_B 31
  #define Ls138_C 32
  //led的接角
  #define R0 2
  #define R1 3
  #define R2 4
  #define R3 5
  #define R4 6
  #define R5 7
  #define R6 8
  #define R7 9
  //keypad
  #define row_size 8
  #define col_size 8
  #define delay_time 300
  const byte ROWS =4;
  const byte COLS = 4;
  int Score = 0;
  bool check = false;
  bool game = false;
  int personBest = 0;
  char hexaKeys[ROWS][COLS]={
      {'F', 'E','D','C'},
      {'B','3','6','9'},
      {'A','2','5','8'},
      {'0','1','4','7'}
  };
  byte rowPins[ROWS]={25,24,23,22};
  byte colPins[COLS]={29,28,27,26};
  
  LiquidCrystal lcd(49,48,47,43,42,41);
  Keypad customKeypad = Keypad(makeKeymap(hexaKeys),rowPins, colPins, ROWS, COLS);
  unsigned long runTime;
  unsigned long nowTime;
  unsigned long Time1;
  unsigned long Time2;
  int BASE1 = 33;
  //偵測按鈕點是否被點擊
  int DIPSW1state;
  int DIPSW2state;
  int DIPSW3state;
  int DIPSW4state;
  //紀錄先前的按鈕是否被點擊
  int EXDIPSW1state;
  int EXDIPSW2state;
  int EXDIPSW3state;
  int EXDIPSW4state;
  //速度設定
  int Change[3]= {2000, 1300, 750};
  int Speed = 0;
  
// the setup routine runs once when you press reset:
void setup() { 
  //初始化所有的接口  
  for (int i = BASE1; i< BASE1 + 4; i++){
    pinMode(i, INPUT_PULLUP);
  }   
  lcd.begin(16,2);
  for (int i = BASE; i < BASE + NUM; i ++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);   
  }
    pinMode(A15, HIGH);
    
  for (int i = BASE; i < BASE + NUM; i ++) {
    digitalWrite(i, HIGH);
  }
  randomSeed(analogRead(A0));
}

void loop() {
   boolean start = false;
   //遊戲開始前
   while (start == false){
    if (check== false){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Type 1 to Start");
      lcd.setCursor(0,1);
      lcd.print("2 to Look PB");
      check = true;
    }
    //抓輸入的鍵位
    char customKey = customKeypad.getKey();
    if (customKey == '1'){
      //做遊戲開始前的初始化
      Score = 0;
      start = true;
      game = true;
      check = false;
      EXDIPSW1state = HIGH;
      EXDIPSW2state = HIGH;
      EXDIPSW3state = HIGH;
      EXDIPSW4state = HIGH;
    }else if (customKey == '2'){
      //顯示個人最佳紀錄
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Your PB is ");
      lcd.print (personBest);
      delay(5000);
      check = false;
    }
  }
  //遊戲過程
  while (start == true){
    //這邊是對遊戲初始化的部分
    if(game){
      Speed = 0;
      runTime = millis();
      nowTime = millis();
      //Time1 Time2 是判斷按鈕點擊的誤差值
      Time1 = millis();
      Time2 = millis();
      TimeLeft = 30;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Your score : ");
      lcd.setCursor(13,0);
      lcd.print(Score);
      lcd.setCursor(0,1);
      lcd.print("Time Left : ");
      lcd.setCursor(12,1);
      lcd.print(TimeLeft);
      lcd.print("s");
      game = false;
      //生成隨機數字代表地鼠出現的位置
      int p = random(4);
      for (int i = BASE; i < BASE + NUM; i ++){
        digitalWrite(p, HIGH);
      }
      digitalWrite(2+p*2, LOW);
      digitalWrite(3+p*2, LOW);
    }
    
    //抓按鍵是否被點取
    DIPSW1state = digitalRead(33);
    DIPSW2state = digitalRead(34);
    DIPSW3state = digitalRead(35);
    DIPSW4state = digitalRead(36);
    //如果是先前狀態沒點擊&抓到目前點擊
    if(DIPSW1state== LOW && EXDIPSW1state == HIGH){
      //按到正確的則加分 錯誤的則扣分
      if( digitalRead(9)== LOW){
        Score++;
      }else{
        Score--;  
      }
      Time2 = Time1;
      delay(100);
      //先前狀態改成按下去
      EXDIPSW1state = LOW;
      //重新生成一個新的地鼠
      int p = random(4);
      for (int i = BASE; i < BASE + NUM; i ++){
        digitalWrite(i, HIGH);
      }
      digitalWrite(2+p*2, LOW);
      digitalWrite(3+p*2, LOW);
      //更新分數
      lcd.setCursor(13,0);
      lcd.print(Score);
      lcd.setCursor(13,0);
      lcd.print("    ");
      lcd.setCursor(13,0);
      lcd.print(Score);
    }
    //底下的2, 3, 4 都是類似的動作所以不多做贅述
    if(DIPSW2state== LOW && EXDIPSW2state == HIGH){
      if( digitalRead(7)== LOW){
        Score++;
      }else{
        Score--;  
      }
      Time2 = Time1;
      delay(100);
      EXDIPSW2state = LOW;
      int p = random(4);
      for (int i = BASE; i < BASE + NUM; i ++){
        digitalWrite(i, HIGH);
      }
      digitalWrite(2+p*2, LOW);
      digitalWrite(3+p*2, LOW);
      lcd.setCursor(13,0);
      lcd.print("    ");
      lcd.setCursor(13,0);
      lcd.print(Score);
    }
    if(DIPSW3state== LOW && EXDIPSW3state == HIGH){
      if( digitalRead(5)== LOW){
        Score++;
      }else{
        Score--;  
      }
      Time2 = Time1;
      delay(100);
      EXDIPSW3state = LOW;
      int p = random(4);
      for (int i = BASE; i < BASE + NUM; i++){
        digitalWrite(i, HIGH);
      }
      digitalWrite(2+p*2, LOW);
      digitalWrite(3+p*2, LOW);
      lcd.setCursor(13,0);
      lcd.print("    ");
      lcd.setCursor(13,0);
      lcd.print(Score);
    }
    if(DIPSW4state== LOW && EXDIPSW4state == HIGH){
      if( digitalRead(3)== LOW){
        Score++;
      }else{
        Score--;  
      }
      Time2 = Time1;
      delay(100);
      EXDIPSW4state = LOW;
      int p = random(4);
      for (int i = BASE; i < BASE + NUM; i ++){
        digitalWrite(i, HIGH);
      }
      digitalWrite(2+p*2, LOW);
      digitalWrite(3+p*2, LOW);
      lcd.setCursor(13,0);
      lcd.print("    ");
      lcd.setCursor(13,0);
      lcd.print(Score);
    }
    //如果按鈕被放開則將先前狀態改成放開
    if(DIPSW1state == HIGH){
      EXDIPSW1state = HIGH;
    }
    if(DIPSW2state == HIGH){
      EXDIPSW2state = HIGH;
    }
    if(DIPSW3state == HIGH){
      EXDIPSW3state = HIGH;
    }
    if(DIPSW4state == HIGH){
      EXDIPSW4state = HIGH;
    }
    nowTime = millis();
    Time1 = millis();
    //changeRatSpace
    //更新地鼠的位置 由Change[Speed]的值決定
    if(Time1 - Time2 >= Change[Speed]){
      Time2 = Time1;
      int p = random(4);
      for (int i = BASE; i < BASE + NUM; i ++){
        digitalWrite(i, HIGH);
      }
      digitalWrite(2+p*2, LOW);
      digitalWrite(3+p*2, LOW);
    }
    //timeLeft
    //這邊是每過一秒 遊戲剩餘時間就減少1
    if (nowTime - runTime>= 1000){
      runTime = nowTime;
      TimeLeft--;
      if (TimeLeft < 10){
        lcd.setCursor(12,1);
        lcd.print(TimeLeft);
        lcd.print("s");
        lcd.print(" ");
        
      }else{
        lcd.setCursor(12,1);
        lcd.print(TimeLeft);
        lcd.print("s");
      }
      //在19秒9秒的時候增加1層的移動速度
      if(TimeLeft == 19){
        Speed++;
      }
      if(TimeLeft == 9){
        Speed++;
      }
      //如果遊戲時間結束
      //則進入結算畫面並且回到初始畫面
      if (TimeLeft == 0){
        start = false; 
        for (int p = BASE; p < BASE + NUM; p ++){
          digitalWrite(p, HIGH);
        }
        //如果分數打破最佳紀錄 則更新最佳紀錄
        if (Score > personBest){
          personBest = Score;
        }
        //顯示結算畫面並在5秒後回到初始畫面
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.clear();      
        lcd.print("Your score : ");
        lcd.setCursor(13,0);
        lcd.print(Score);
        lcd.setCursor(0,1);
        lcd.print("Your PB is ");
        lcd.print(personBest);
        delay(5000);
      }
    }
  }   
}
