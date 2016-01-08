//https://github.com/218Drone/px4_ros_control/blob/master/src/px4_getpoint_node.cpp

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <stdio.h>
#include "geometry_msgs/PoseStamped.h"
#include "std_msgs/Float64.h"
#include <termios.h>



#define KEYCODE_U 0x41
#define KEYCODE_D 0x42

int kfd = 0;
struct termios cooked, raw;

char getch()
{
    char c;
    bool dirty=false;
    // get the console in raw mode
    tcgetattr(kfd, &cooked);
    memcpy(&raw, &cooked, sizeof(struct termios));
    raw.c_lflag &=~ (ICANON | ECHO);
    // Setting a new line, then end of file
    raw.c_cc[VEOL] = 1;
    raw.c_cc[VEOF] = 2;
    tcsetattr(kfd, TCSANOW, &raw);

    if(read(kfd, &c, 1) < 0)
    {
        perror("read():");
        exit(-1);
    }

    return c;

}

int main(int argc, char **argv){


   ros::init(argc, argv, "mavros_test");
   ros::NodeHandle n;
   ros::Publisher pub_att = n.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_attitude/attitude",100);
   ros::Publisher pub_thr = n.advertise<std_msgs::Float64>("/mavros/setpoint_attitude/att_throttle", 100);

   ros::Rate loop_rate(10);

   geometry_msgs::PoseStamped cmd_att;
   std_msgs::Float64 cmd_thr;
   int count = 1;
   double thr = 0.3;

   while(ros::ok()){

       cmd_att.header.stamp = ros::Time::now();
       cmd_att.header.seq=count;
       cmd_att.header.frame_id = 1;
       cmd_att.pose.position.x = 0.0;
       cmd_att.pose.position.y = 0.0;
       cmd_att.pose.position.z = 0.0;
       cmd_att.pose.orientation.x = 0;
       cmd_att.pose.orientation.y = 0;
       cmd_att.pose.orientation.z = 0;
       cmd_att.pose.orientation.w = 0;


       cmd_thr.data = thr;
       pub_att.publish(cmd_att);
       pub_thr.publish(cmd_thr);

       char c = getch();   // call your non-blocking input function
       switch(c)
       {

        case KEYCODE_U:
           ROS_INFO_STREAM("throttle_up");
           thr += 0.1;
           printf("%f\t",thr);
           break;
        case KEYCODE_D:
           ROS_INFO_STREAM("throttle_down");
           thr -= 0.1;
           printf("%f\t",thr);
           break;
       }


       ros::spinOnce();
       count++;
       loop_rate.sleep();
   }

   return 0;
}
