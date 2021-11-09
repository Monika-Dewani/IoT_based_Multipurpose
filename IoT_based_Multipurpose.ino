#include <LiquidCrystal.h>
LiquidCrystal lcd(5,18,19,21,22,23);
#include "WiFi.h"
#include "WiFiClient.h"

#include <HTTPClient.h> 
#include <IRremote.h>

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;


const char* ssid = "MDD";
const char* password =  "MDD123456";
String Link,Link1;
HTTPClient http;
String getstatus;

WiFiClient client;

int Relay1= 32;  // Assigning Pin D2/4 as the name Relay1
int Relay2= 33;  // Assigning Pin D3/0 as the name Relay2int Relay1= 4;  // Assigning Pin D2/4 as the name Relay1

int Relay3= 25;  // Assigning Pin D2/4 as the name Relay1
int Relay4= 26;
int sw=27;

int a=0;
int b=0;
int c=0;
int d=0;
int e=0;

 


void setup()         // Code under this setup run once.
{
  Serial.begin(9600);        // Sets the data rate in bits per second (baud) for serial data transmission
  lcd.begin(16,2);
 

pinMode(Relay3, OUTPUT);     // Declaring LED1 pin as an output.
pinMode(Relay4, OUTPUT);     // Declaring LED2 pin as an output.
pinMode(Relay1, OUTPUT);   // Declaring Relay1 pin as an output.
pinMode(Relay2, OUTPUT);   // Declaring Relay2 pin as an output.
pinMode(sw, INPUT);

 if(digitalRead(sw)==0)
 {

  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
    lcd_cmd();
  }
 
  Serial.println("Connected to the WiFi network");
 }else if(digitalRead(sw)==1)
 {
   Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  lcd_cmd();
 }
}


void loop()           // Code under this loop runs forever.
{

  if(digitalRead(sw)==1)
  {
    lcd.setCursor(0,0);
  lcd.print("   Use Remote   ");

  if (irrecv.decode(&results)) {
    Serial.println(results.value, DEC);

    if((results.value==1 || results.value==2049)&& a==0)
    {
      digitalWrite(Relay1,1);     // Making LED1 LOW.
      Serial.println("Relay1 ON");
      lcd.setCursor(0,1);
      lcd.print("  Focus1 ON  ");
      
      a=1;
      }
      else if((results.value==1 || results.value==2049)&& a==1)
      {
        digitalWrite(Relay1,0);     // Making LED1 LOW.
      Serial.println("Relay1 Off");
       lcd.setCursor(0,1);
      lcd.print("  Focus1 OFF  ");
      a=0;
        }

      else if((results.value==2 || results.value==2050)&& b==0)
      {
        digitalWrite(Relay2,1);     // Making LED1 LOW.
      Serial.println("Relay2 On");
       lcd.setCursor(0,1);
      lcd.print("  Focus2 ON  ");
      b=1;
        }
        else if((results.value==2 || results.value==2050)&& b==1)
      {
        digitalWrite(Relay2,0);     // Making LED1 LOW.
      Serial.println("Relay2 Off");
       lcd.setCursor(0,1);
      lcd.print("  Focus2 OFF  ");
      b=0;
        }

        else if((results.value==3 || results.value==2051)&& c==0)
      {
        digitalWrite(Relay3,1);     // Making LED1 LOW.
      Serial.println("Relay3 On");
       lcd.setCursor(0,1);
      lcd.print("  Focus3 ON  ");
      c=1;
        }
        else if((results.value==3 || results.value==2051)&& c==1)
      {
        digitalWrite(Relay3,0);     // Making LED1 LOW.
      Serial.println("Relay3 Off");
       lcd.setCursor(0,1);
      lcd.print("  Focus3 OFF  ");
      c=0;
        }

        else if((results.value==4 || results.value==2052)&& d==0)
      {
        digitalWrite(Relay4,1);     // Making LED1 LOW.
      Serial.println("Relay4 On");
       lcd.setCursor(0,1);
      lcd.print("  Focus4 ON  ");
      d=1;
        }
        else if((results.value==4 || results.value==2052)&& d==1)
      {
        digitalWrite(Relay4,0);     // Making LED1 LOW.
      Serial.println("Relay4 Off");
       lcd.setCursor(0,1);
      lcd.print("  Focus4 OFF  ");
      d=0;
        }
        else if((results.value==0 || results.value==2048)&& e==0)
      { digitalWrite(Relay1,1);    // Making Led1 LOW.
      digitalWrite(Relay2,1);    // Making Led2 LOW.
      digitalWrite(Relay3,1);  // Making Relay1 LOW.
      digitalWrite(Relay4,1);  // Making Relay2 LOW.
      Serial.println("All ON");
       lcd.setCursor(0,1);
      lcd.print("  Focuses ON  ");
      e=1;
      }
      else if((results.value==0 || results.value==2048)&& e==1)
      { digitalWrite(Relay1,0);    // Making Led1 LOW.
      digitalWrite(Relay2,0);    // Making Led2 LOW.
      digitalWrite(Relay3,0);  // Making Relay1 LOW.
      digitalWrite(Relay4,0);  // Making Relay2 LOW.
      Serial.println("All OFF");
       lcd.setCursor(0,1);
      lcd.print("  Focuses OFF  ");
      e=0;
      }

     
    
    irrecv.resume(); // Receive the next value

    
  }
  delay(100);
  }
  else if(digitalRead(sw)==0)
  {

lcd.setCursor(0,0);
  lcd.print("  Use IoT App.  ");



  
   Link= "https://mdbelectrosoft.in/MDBES/Workshop.php?unit=4";
    http.begin(Link);     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload
 
   //Print HTTP return code
  Serial.print("payload= "); 
  Serial.println(payload);    //Print request response payload
  int myvalue=payload.toInt();
  Serial.println(myvalue);
  
   
    
 if (myvalue == 1) 
   {
      digitalWrite(Relay1,1);     // Making LED1 LOW.
      Serial.println("Relay1 ON");
       lcd.setCursor(0,1);
      lcd.print("  Focus1 ON  ");
   }
  else if (myvalue== 2) 
     {
      digitalWrite(Relay1,0);     // Making LED1 LOW.
      Serial.println("Relay1 OFF");
       lcd.setCursor(0,1);
      lcd.print("  Focus1 OFF  ");
     }
  else if (myvalue == 3) 
     {
      digitalWrite(Relay2,1);     // Making LED1 LOW.
      Serial.println("Relay2 ON");
       lcd.setCursor(0,1);
      lcd.print("  Focus2 ON  ");
     }
  else if (myvalue == 4) 
     {
      digitalWrite(Relay2,0);     // Making LED1 LOW.
      Serial.println("Relay2 OFF");
       lcd.setCursor(0,1);
      lcd.print("  Focus2 OFF  ");
     }
  else if (myvalue == 5) 
     {
      digitalWrite(Relay3,1);   // Making Relay1 LOW.
      Serial.println("Relay3 ON");
       lcd.setCursor(0,1);
      lcd.print("  Focus3 ON  ");
     }
  else if (myvalue == 6) 
     {
       digitalWrite(Relay3,0);   // Making Relay1 LOW.
      Serial.println("Relay3 OFF");
       lcd.setCursor(0,1);
      lcd.print("  Focus3 OFF  ");
     }
  else if (myvalue == 7) 
     {
      digitalWrite(Relay4,1);   // Making Relay2 LOW.
      Serial.println("Relay4 on");
       lcd.setCursor(0,1);
      lcd.print("  Focus4 ON  ");
     }
  else if (myvalue == 8)
     {
      digitalWrite(Relay4, 0);  // Making Relay2 HIGH.
      Serial.println("Relay4 off");
       lcd.setCursor(0,1);
      lcd.print("  Focus4 OFF  ");
     }
  else if (myvalue == 9)
     {
      digitalWrite(Relay1,1);    // Making Led1 LOW.
      digitalWrite(Relay2,1);    // Making Led2 LOW.
      digitalWrite(Relay3,1);  // Making Relay1 LOW.
      digitalWrite(Relay4,1);  // Making Relay2 LOW.
      Serial.println("All ON");
       lcd.setCursor(0,1);
      lcd.print("  Focuses ON  ");
     }
  else if (myvalue == 10)
     {
      digitalWrite(Relay1,0);    // Making Led1 LOW.
      digitalWrite(Relay2,0);    // Making Led2 LOW.
      digitalWrite(Relay3,0);  // Making Relay1 LOW.
      digitalWrite(Relay4,0);  // Making Relay2 LOW.
      Serial.println("All Off");
       lcd.setCursor(0,1);
      lcd.print("  Focuses OFF  ");
     }
        
}
}

void lcd_cmd()
{
  for(int i=0;i<4;i++)
  {
  lcd.setCursor(0,0);
  lcd.print("  Multipurpose  ");
  lcd.setCursor(0,1);
  lcd.print("Controller Acces");
  delay(400);
  lcd.clear();
  delay(300);
  
  }
  
  
  

  

  
  }
