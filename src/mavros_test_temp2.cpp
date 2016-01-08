#include <ros/ros.h>
#include <std_msgs/String.h>
#include <stdio.h>
#include <geometry_msgs/PoseStamped.h>



int main(int argc, char **argv)
{
   ros::init(argc, argv, "mavros_test");
   ros::NodeHandle n;

   ros::Publisher chatter_pub = n.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local",100);

   ros::Rate loop_rate(10);

   geometry_msgs::PoseStamped msg;


   int count = 1;

   while(ros::ok()){
       msg.header.stamp = ros::Time::now();
       msg.header.seq=count;
       msg.header.frame_id = 1;
       msg.pose.position.x = 0.0;//0.001*some_object.position_x;
       msg.pose.position.y = 0.0;//0.001*some_object.position_y;
       msg.pose.position.z =0.6;//0.001*some_object.position_z;
       msg.pose.orientation.x = 0;
       msg.pose.orientation.y = 0;
       msg.pose.orientation.z = 0;
       msg.pose.orientation.w = 1;

       chatter_pub.publish(msg);
       ros::spinOnce();
       count++;
       loop_rate.sleep();
   }

   return 0;
}
