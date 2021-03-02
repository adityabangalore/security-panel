#include <LiquidCrystal.h>                          //Import LiquidCrystal library

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);                //Create LiquidCyrstal object lcd with necessary parameters              

#define None 0                                      //Assign pin numbers to keypad function
#define Right 1
#define Up 2
#define Down 3
#define Left 4
#define Select 5

String user_code = "";                              //Create instance variables for the codes and system status
String master_code = "URDLLDRU";
String system_status = "Unarmed";
String asterisks = "";

byte count = 0;                                     //Create instance variables that track certain variable states
byte old_count;
byte wrongpwd_counter = 0;
int correctpwd_counter = 0;
int changeCodeActive = 0;

int readButtons() {                                 //Create function that takes analog input from buttons and interprets them
  int btnRead = analogRead(0);
  if(btnRead == 0) {
    return Right;
  }
  if(btnRead == 99) {
    return Up;
  }
  if(btnRead == 258) {
    return Down;
  }
  if(btnRead == 411) {
    return Left;
  }
  if(btnRead == 640) {
    return Select;
  }
  else {
    return None;
  }
}

void homeScreen() {                                     //Create homescreen defaults
  lcd.setCursor(0,0);
  lcd.print("Code:");
  lcd.setCursor(0,1);
  lcd.print("Status:");
  if(system_status == "Unarmed") {
    system_status = "Unarmed";
    lcd.setCursor(11,1);
    lcd.print("      ");
    delay(100);
    lcd.setCursor(9,1);
    lcd.print(system_status);
  }
  else if(system_status == "Armed") {
     system_status = "Armed";
     lcd.setCursor(9,1);
     lcd.print("        ");
     delay(100);
     lcd.setCursor(11,1);
     lcd.print(system_status);
  }
}

void typeCode(int col, int row) {                                   //Function that allows user to type a code; To preserve
  String uc = user_code.substring(user_code.length() - 1);          //privacy, codes are typed in as asterisks, but stored
  int reading = readButtons();                                      //as values.
  lcd.setCursor(col,row);
  switch(reading) {
    case None:
      break;
    case Right:
      if(uc == "R") {
        if(old_count != count) {
          delay(300);
          if(readButtons() == Right) {
            user_code = user_code + "R";
            asterisks = asterisks + "*";
            lcd.print(asterisks);
            break;
          }
          else {
            break;
          }
        }
      }
      if(uc != "R") {
        user_code = user_code + "R";
        asterisks = asterisks + "*";
        lcd.print(asterisks);
        old_count = count;
        count += 1;
        break;
      }
    case Up:
      if(uc == "U") {
        if(old_count != count) {
          delay(300);
          if(readButtons() == Up) {
            user_code = user_code + "U";
            asterisks = asterisks + "*";
            lcd.print(asterisks);
            break;
          }
          else {
            break;
          }
        }
      }
      if(uc != "U") {
        user_code = user_code + "U";
        asterisks = asterisks + "*";
        lcd.print(asterisks);
        old_count = count;
        count += 1;
        break;
      }
    case Down:
      if(uc == "D") {
        if(old_count != count) {
          delay(300);
          if(readButtons() == Down) {
            user_code = user_code + "D";
            asterisks = asterisks + "*";
            lcd.print(asterisks);
            break;
          }
          else {
            break;
          }
        }
      }
      if(uc != "D") {
        user_code = user_code + "D";
        asterisks = asterisks + "*";
        lcd.print(asterisks);
        old_count = count;
        count += 1;
        break;
      }
    case Left:
      if(uc == "L") {
        if(old_count != count) {
          delay(300);
          if(readButtons() == Left) {
            user_code = user_code + "L";
            asterisks = asterisks + "*";
            lcd.print(asterisks);
            break;
          }
          else {
            break;
          }
        }
      }
      if(uc != "L") {
        user_code = user_code + "L";
        asterisks = asterisks + "*";
        lcd.print(asterisks);
        old_count = count;
        count += 1;
        break;
      }
    case Select:
      changeCode();
      break;
  }
}

void checkCode() {                                                          //Check if the input code matches master code.
  if(user_code.length() == 8 && user_code != master_code) {
    user_code = "";
    asterisks = "";
    wrongpwd_counter += 1;
    delay(200);
    if(wrongpwd_counter < 5) {
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(8,0);
      lcd.print("        ");
      for(byte n = 0; n <= 1; n++) {
        lcd.setCursor(1,0);
        lcd.print("Incorrect Code");
        delay(500);
        lcd.setCursor(1,0);
        lcd.print("                ");
        delay(500);
      }
      homeScreen();
    }
    else if(wrongpwd_counter == 5) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("System Locked");
      lcd.setCursor(0,1);
      lcd.print("Time Left:");
      for(int n = 60; n >= 0; n--) {
        if(n >= 10) {
          lcd.setCursor(14,1);
          lcd.print(n);
          delay(1000);
        }
        else if(n < 10 && n > 0) {
          lcd.setCursor(14,1);
          lcd.print("0");
          lcd.setCursor(15,1);
          lcd.print(n);
          delay(1000);
        }
        else if(n == 0) {
          lcd.clear();
          wrongpwd_counter = 0;
          homeScreen();
        }
      }
    }
  }
  if(user_code.length() == 8 && user_code == master_code) {
    delay(200);
    user_code = "";
    asterisks = "";
    wrongpwd_counter  = 0;
    correctpwd_counter += 1;
    if(correctpwd_counter > 0) {
      lcd.setCursor(8,0);
      lcd.print("        ");
      if(system_status == "Unarmed") {
        system_status = "Armed";
        lcd.setCursor(9,1);
        lcd.print("        ");
        delay(100);
        lcd.setCursor(11,1);
        lcd.print(system_status);
      }
      else if(system_status == "Armed") {
        system_status = "Unarmed";
        lcd.setCursor(11,1);
        lcd.print("      ");
        delay(100);
        lcd.setCursor(9,1);
        lcd.print(system_status);
      }
    }
  }
  else if(user_code.length() > 8) {
    user_code = "";
    asterisks = "";
    lcd.print(asterisks);
  }
}

void changeCode() {                                               //Provide method for user to change master code.
  String old_code = master_code;
  user_code = "";
  asterisks = "";
  wrongpwd_counter = 0;
  delay(300);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current Code:");
  lcd.setCursor(0,1);
  while(HIGH) {
    typeCode(0,1);
    if(user_code.length() == 8 && user_code == master_code) {
      delay(200);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("New Code:");
      user_code = "";
      asterisks = "";
      while(HIGH) {
        if(user_code.length() == 8) {
          delay(200);
          master_code = user_code;
          lcd.clear();
          homeScreen();
          correctpwd_counter = -1;
          break;
        }
        else if(user_code.length() < 8) {
          typeCode(0,1);
        }
      }
      break;
    }
    else if(user_code.length() == 8 && user_code != master_code) {
      delay(200);
      lcd.clear();
      user_code = "";
      asterisks = "";
      for(byte n = 0; n <= 1; n++) {
        lcd.setCursor(1,0);
        lcd.print("Incorrect Code");
        delay(500);
        lcd.clear();
        delay(500);
      }
      homeScreen();
      break;
    }
  }
}

void setup() {                                                    //Start the program
  lcd.begin(16,2);
  homeScreen();
  Serial.begin(9600);
  analogWrite(10, 100);
}

void loop() {                                                    //Run necessary functions to allow program to work.
  typeCode(8,0);
  checkCode();
}
