#!/usr/bin/python

import rospy
from std_msgs.msg import String

def callback(data, args):
	p = args	
	if data.data == "SWITCH_ON":
		hello_str = "LED_ON"
	elif data.data == "SWITCH_OFF":
		hello_str = "LED_OFF"
	else:
		pass
	p.publish(hello_str)


if __name__ == '__main__':
    pub = rospy.Publisher('piMsg', String, queue_size=1)
    rospy.init_node('pi', anonymous=True)
    rospy.Subscriber('arduinoMsg', String, callback, (pub))

    rospy.spin()
