#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
std_msgs::String arduino_msg;

void messageParser( const std_msgs::String& piMsg);

ros::Publisher arduinoMsg("arduinoMsg", &arduino_msg);
ros::Subscriber<std_msgs::String> piMsg("piMsg", &messageParser );


void setup()
{
  pinMode(13, OUTPUT);
  
  nh.initNode();
  nh.advertise(arduinoMsg);
  nh.subscribe(piMsg);
}

void loop()
{
  nh.spinOnce();
  delay(10);
}

void messageParser( const std_msgs::String& pi_msg){
  if(strcmp(pi_msg.data, "LED_ON") == 0)
  {
    digitalWrite(13, HIGH);
  }
  else if(strcmp(pi_msg.data, "LED_OFF") == 0)
  {
    digitalWrite(13, LOW);
  }
    arduino_msg.data = pi_msg.data;
    arduinoMsg.publish( &arduino_msg );      
}

