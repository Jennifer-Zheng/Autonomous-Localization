#include <iostream>
#include <ros/ros.h>
#include <cstdlib>
#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <math.h>
#include <vector>
#include <std_srvs/Empty.h>


int main(int argc, char **argv) {

  ros::init(argc, argv, "auto_localize");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  geometry_msgs::Twist vel_msg;
  std_srvs::Empty srv;
  ros::Rate loop_rate(10);
  int count = 0;

  while (ros::ok())
  {
    
    //wait for global localization to be called
    ros::service::call("/global_localization", srv);
    ros::Duration(1).sleep();

    /* CODE FOR PURELY LINEAR MOVEMENT
    vel_msg.linear.x = 0.5;
    vel_msg.linear.y = 0;
    vel_msg.linear.z = 0;
    vel_msg.angular.x = 0;
    vel_msg.angular.y = 0;
    vel_msg.angular.z = 0; 
    pub.publish(vel_msg);
    count++;
    */

    //CODE WITH PERIODIC ROTATION 
    int x_count = 0;
    int ang_count = 0;
    //set and publish linear x velocity
    while(ros::ok()){
      vel_msg.linear.x = 0.5;
      vel_msg.linear.y = 0;
      vel_msg.linear.z = 0;
      vel_msg.angular.x = 0;
      vel_msg.angular.y = 0;
      vel_msg.angular.z = 0; 
      pub.publish(vel_msg);
      x_count++;
      //move forward for 5 seconds
      if(x_count > 50)
        break;
      ros::spinOnce();
    }

    //set and publish angular x velocity
    while(ros::ok()){
      vel_msg.linear.x = 0;
      vel_msg.angular.x = (2/3) * 3.14159;
      pub.publish(vel_msg);
      ang_count++;
      //make a complete rotation in 3 seconds
      if(ang_count > 30)
        break;
      ros::spinOnce();
    }

    count++;
    
    //run for 320 seconds total
    if(count > 320){
      break;
    }
    
    //send messages
    ros::spinOnce();
  }
   //zero out velocity
   vel_msg.linear.x = 0;
   return 0;
}
