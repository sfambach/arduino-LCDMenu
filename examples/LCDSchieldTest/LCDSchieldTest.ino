//Sample using MenuEditor library
#include <LiquidCrystal.h>

#include "Item.h"
#include "ItemMenu.h"
#include "ItemBool.h"
#include "ItemInt.h"

/*******************************************************
  This Program shows how to use the menu classes
  This program was written for the LCD Shield for the
  Arduino UNO but should also work with other LCD displays.
  For other LCD Displays, make sure you change the button
  code.
  
  The Code for the LCD Shield was written by 
  from Mark Bramwell, July 2010

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  // For V1.1 us this threshold
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 250)  return btnUP;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT;

  Serial.println(adc_key_in);
  return btnNONE;  // when all others fail, return this...
}

Item * current;

void* intWert(void* wert) {

  int* i = (int*)wert;
  return (void*)i;
}

boolean b1 = false;
boolean b2 = true;
int i1 = 20;

void buildMenu() {

  // create a main menu node
  ItemMenu* root = new ItemMenu( "Hauptmenue", NULL);

  // create a boolean value item
  Item* child = new ItemBool("Boolean 1",root, &b1 , NULL );
  root->addChild(child);

  // create another boolean item
  child = new ItemBool("Boolean 2",root, &b2 , NULL );
  root->addChild(child);

  // create an integer item
  child = new ItemInt("Integer 1", root, &i1, -1 , 100, NULL );
  root->addChild(child);

  // create another menu as submenun
  ItemMenu* sub1 = new ItemMenu( "Submenue 1", NULL);
  root->addChild(sub1);

  // add items to the submenu
  child = new ItemBool("Boolean 11",root, &b2 , NULL );
  sub1->addChild(child);

  child = new ItemInt("Integer 11", root, &i1, -1 , 100, NULL );
  sub1->addChild(child);

  // create another menu as submenun
  ItemMenu* sub2 = new ItemMenu( "Submenue 2", NULL);
  root->addChild(sub2);

  // add items to the second submenu
  child = new ItemBool("Boolean 21",root, &b2 , NULL );
  sub2->addChild(child);

  child = new ItemInt("Integer 21", root, &i1, -1 , 100, NULL );
  sub2->addChild(child);

  // set the current menu to root
  current = root;
}

void setup()
{
  Serial.begin(115200);
  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0, 0);
  buildMenu();
}

void loop()
{

  // print name of current node
  lcd.setCursor(0, 0);
  lcd.print(current->getName());

  // start second line 
  // navigation to the left available?
  if (current->optionLeft()) {
    lcd.setCursor(0, 1);
    lcd.print("<");
  }

  // display content of this node
  lcd.setCursor(1, 1);
  lcd.print(current->getContent());

  // navigation to the right available?
  if (current->optionRight()) {
    lcd.setCursor(15, 1);
    lcd.print(">");
  }

  // cehck the buttons
  lcd_key = read_LCD_buttons();

  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
    case btnRIGHT: current->right(); lcd.clear(); break;
    case btnLEFT:  current->left(); lcd.clear();  break;
    case btnUP:    current = current->up(); lcd.clear(); break;
    case btnDOWN:  current = current->down(); lcd.clear(); break;
    case btnSELECT: break;
    case btnNONE:  break; 
  }

  // Take some time, if not the buttons are to fast ;) 
  int ms = millis();
  while (read_LCD_buttons() != btnNONE && (millis()- ms) < 500)
  {
    delay(1);
  }

}

