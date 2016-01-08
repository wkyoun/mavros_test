#include <ros/ros.h>
#include <std_msgs/String.h>
#include <termios.h>
#include <stdio.h>
//#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <keyboard/Key.h>
/*
#define KEYCODE_R 0x43
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
*/
/*
char getch()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);           // save old settings
  newt = oldt;
  lnewt.c_lflag &= ~(ICANON);                 // disable buffering
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings

  int c = getchar();  // read character (non-blocking)

  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
  return c;
}
*/


geometry_msgs::TwistStamped vs;

void sendCommand(const keyboard::Key &key){

   ROS_INFO_STREAM("In keyboard");

   switch (key.code)
   {
        case 'w':
        {
            ROS_INFO_STREAM("up");
            vs.twist.linear.z += 0.1;
            break;
        }
        case 's':
        {
            ROS_INFO_STREAM("down");
            vs.twist.linear.z -= 0.1;
            break;
        }
        case 'j':
        {
            ROS_INFO_STREAM("left");
            vs.twist.linear.y += 0.1;
            break;
        }
        case 'l':
        {
            ROS_INFO_STREAM("right");
            vs.twist.linear.y -= 0.1;
            break;
        }
        case 'i':
        {
            ROS_INFO_STREAM("forward");
            vs.twist.linear.x += 0.1;
            break;
        }
        case 'k':
        {
            ROS_INFO_STREAM("backward");
            vs.twist.linear.x -= 0.1;
            break;
        }
        case 'u':
        {
            ROS_INFO_STREAM("rotate left");
            vs.twist.angular.z += 0.1;
            break;
        }
        case 'o':
        {
            ROS_INFO_STREAM("rotate right");
            vs.twist.angular.z -= 0.1;
            break;
        }

    }
}



int main(int argc, char **argv)
{
   ros::init(argc, argv, "mavros_test");
   ros::NodeHandle n;

//   ros::Publisher chatter_pub = n.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local",100);

   ros::Publisher vel_pub = n.advertise<geometry_msgs::TwistStamped>("/mavros/setpoint_velocity/cmd_vel", 10);
   ros::Subscriber commandSubscriber = n.subscribe("/keyboard/keydown",10,sendCommand);
   ros::Rate loop_rate(10);

 //  geometry_msgs::PoseStamped msg;


//   int count = 1;

   while(ros::ok()){
       /*
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
*/
           ROS_INFO_STREAM("In ROS");
       vs.header.stamp = ros::Time::now();
       vs.header.seq++;
       vel_pub.publish(vs);
/*
       char c = getch();   // call your non-blocking input function
       switch(c)
       {
        case KEYCODE_L:
           ROS_INFO_STREAM("LEFT");

           break;
        case KEYCODE_R:
           ROS_INFO_STREAM("RIGHT");
           break;
        case KEYCODE_U:
           ROS_INFO_STREAM("UP");
           break;
        case KEYCODE_D:
           ROS_INFO_STREAM("DOWN");
           break;
       }

*/

       ros::spinOnce();
//       count++;
       loop_rate.sleep();
   }

   return 0;
}
