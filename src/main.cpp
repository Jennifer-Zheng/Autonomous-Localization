//Update as needed 
#include <iostream>
#include "ros/ros.h"
#include <cstdlib>
#include <ros/ros.h>
#include <tf/tf.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>
#include <actionlib/server/simple_action_server.h>
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseArray.h"
#include <geometry_msgs/Point.h>
#include <math.h>
#include <vector>


//libraries we may need
/*#include <geometry_msgs/Twist.h>
#include <tf/tf.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>
#include <actionlib/server/simple_action_server.h>
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseArray.h"
*/ 

//using namespace std;
//using namespace cv;

int main(int argc, char **argv) {
  printf("I'm running");
  ros::init(argc, argv, "move_base_client");
  ros::NodeHandle n;

  actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base",true);
  ac.waitForServer();
 
  
  
  move_base_msgs::MoveBaseGoal goal;
  
  double x = 12;
  double y = 0;
  double yaw = 0;
  
  while (ros::ok())
  {
    
    //set the header
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.header.frame_id = "/base_link";
    
    //set relative x, y, and angle
    goal.target_pose.pose.position.x = x;
    goal.target_pose.pose.position.y = 0.0;
    goal.target_pose.pose.position.z = 0.0;
    goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(1.2);

	//send the goal
    ac.sendGoal(goal);
    
    //block until the action is completed
    ac.waitForResult();

  }

   return 0;
}
