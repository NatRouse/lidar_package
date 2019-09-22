#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

float twistboi = 0;
float velboi = 0;
float laserboi = [];

void driveCallback (const geometry_msgs::Twist::ConstPtr& msg )
{
ROS_INFO ( "I heard: [a twist] %f %f", msg->linear.x, msg->angular.z);
velboi = msg->linear.x;
twistboi = msg->angular.z;
}

void sensingCallback (const sensor_msgs::LaserScan::ConstPtr& msg)
{
ROS_INFO ("I feel dat laser.")
laserboi = msg->ranges;
}


int main ( int argc , char ** argv )
{
/**
* The ros::init() function needs to see argc and argv so that it can perform
* any ROS arguments and name remapping that were provided at the command line.
* For programmatic remappings you can use a different version of init() which takes
* remappings directly, but for most command-line programs, passing argc and argv is
* the easiest way to do it. The third argument to init() is the name of the node.
*
* You must call one of the versions of ros::init() before using any other
* part of the ROS system.
*/
ros :: init ( argc , argv , "subscriber_node" );
/**
* NodeHandle is the main access point to communications with the ROS system.
* The first NodeHandle constructed will fully initialize this node, and the last
* NodeHandle destructed will close down the node.
*/
ros :: NodeHandle n ;
/**
* The subscribe() call is how you tell ROS that you want to receive messages
* on a given topic. This invokes a call to the ROS
* master node, which keeps a registry of who is publishing and who
* is subscribing. Messages are passed to a callback function, here
* called chatterCallback. subscribe() returns a Subscriber object that you
* must hold on to until you want to unsubscribe. When all copies of the Subscriber
* object go out of scope, this callback will automatically be unsubscribed from
* this topic.
*
* The second parameter to the subscribe() function is the size of the message
* queue. If messages are arriving faster than they are being processed, this
* is the number of messages that will be buffered up before beginning to throw
* away the oldest ones.
*/
ros::Subscriber drive_sub = n.subscribe("/robot0/des_vel", 1, driveCallback);
ros::Subscriber sensing_sub = n.subscribe("/robot0/laser_1", 1, sensingCallback);


ros::Publisher drive_pub = n.advertise<geometry_msgs::Twist>("/robot0/cmd_vel" , 1);
ros::Rate loop_rate (10);



while (ros::ok())
{
/**
* This is a message object. You stuff it with data, and then publish it.
*/
geometry_msgs::Twist msg;
msg.linear.x = velboi;
msg.angular.z = twistboi;


/**
* The publish() function is how you send messages. The parameter
* is the message object. The type of this object must agree with the type
* given as a template parameter to the advertise<>() call, as was done
* in the constructor above.
*/
drive_pub.publish(msg);
ros::spinOnce();
loop_rate.sleep();
}


/*ros::spin();*/

return 0 ;
}


