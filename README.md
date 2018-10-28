# SerialROS
Serial with ROS


1. roscore

2. rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0

3. python serial_ros_pi.py

4. rostopic echo piMsg

5. rostopic echo arduinoMsg

6. rostopic pub piMsg std_msgs/String "LED_ON"

