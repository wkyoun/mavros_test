//https://github.com/218Drone/px4_ros_control/blob/master/src/px4_getpoint_node.cpp

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <stdio.h>
#include <geometry_msgs/TwistStamped.h>
#include <termios.h>


#define KEYCODE_R 0x43
#define KEYCODE_L 0x44
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
   ros::Publisher vel_pub = n.advertise<geometry_msgs::TwistStamped>("/mavros/setpoint_velocity/cmd_vel", 10);
   ros::Rate loop_rate(10);

   geometry_msgs::TwistStamped vs;


   while(ros::ok()){

       vs.header.stamp = ros::Time::now();
       vs.header.seq++;

       char c = getch();   // call your non-blocking input function
       switch(c)
       {
        case KEYCODE_L:
           ROS_INFO_STREAM("left");
           vs.twist.linear.y += 0.1;
           break;
        case KEYCODE_R:
           ROS_INFO_STREAM("right");
           vs.twist.linear.y -= 0.1;
           break;
        case KEYCODE_U:
           ROS_INFO_STREAM("forward");
           vs.twist.linear.x += 0.1;
           break;
        case KEYCODE_D:
           ROS_INFO_STREAM("backward");
           vs.twist.linear.x -= 0.1;
           break;
       }

       vel_pub.publish(vs);

       ros::spinOnce();
       loop_rate.sleep();
   }

   return 0;
}
