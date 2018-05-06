#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
std_msgs::String arduino_msg;
bool sendEnable = false;

void messageParser( const std_msgs::String& piMsg);

ros::Publisher arduinoMsg("arduinoMsg", &arduino_msg);
ros::Subscriber<std_msgs::String> piMsg("piMsg", &messageParser );

bool last_reading;
long last_debounce_time=0;
long debounce_delay=50;
bool published = true;

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
  digitalWrite(7, HIGH);
  last_reading = ! digitalRead(7);
  
  nh.initNode();
  nh.advertise(arduinoMsg);
  nh.subscribe(piMsg);
}

void loop()
{
  Check_Button();
  
  if(sendEnable == true)
  {
    arduinoMsg.publish( &arduino_msg );    
    sendEnable = false;
  }
  //delay(1000);
  nh.spinOnce();  
}

void messageParser( const std_msgs::String& pi_msg){
  if(strcmp(pi_msg.data, "LED_ON") == 0)
  {
    digitalWrite(13, HIGH);
    //arduino_msg.data = pi_msg.data;
    //sendEnable = true;
  }
  else if(strcmp(pi_msg.data, "LED_OFF") == 0)
  {
    digitalWrite(13, LOW);
    //arduino_msg.data = pi_msg.data;
    //sendEnable = true;
  }
  else
  {
    arduino_msg.data = "UNKNOWN MSG";
    sendEnable = true;
  }
}

void Check_Button()
{
    bool reading = ! digitalRead(7);
  
  if (last_reading!= reading){
      last_debounce_time = millis();
      published = false;
  }
  
  //if the button value has not changed for the debounce delay, we know its stable
  if ( !published && (millis() - last_debounce_time)  > debounce_delay) {
//    digitalWrite(led_pin, reading);
    if(reading == LOW)
      arduino_msg.data = "SWITCH_ON";
    else
      arduino_msg.data = "SWITCH_OFF";
     
    sendEnable = true;
    published = true;
  }

  last_reading = reading;
}

