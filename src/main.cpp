/**

Copyright (c) 2016, Borella Jocelyn
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "ros/ros.h"
#include "move_base_msgs/MoveBaseActionGoal.h"
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>


std::time_t t = std::time(0);
std::string path = std::to_string(t)+"posen.xml";

void chatterCallback(const move_base_msgs::MoveBaseActionGoal::ConstPtr& msg)
{
    std::string xmlString;

    float x =  msg->goal.target_pose.pose.position.x;
    float y = msg->goal.target_pose.pose.position.y;
    float z = msg->goal.target_pose.pose.position.z;

    float xq = msg->goal.target_pose.pose.orientation.x;
    float yq = msg->goal.target_pose.pose.orientation.y;
    float zq = msg->goal.target_pose.pose.orientation.z;
    float wq = msg->goal.target_pose.pose.orientation.w;

    ROS_INFO("I heard x : [%f]",x);
    ROS_INFO("I heard y : [%f]",y);
    ROS_INFO("I heard z : [%f]",z);

    ROS_INFO("I heard x quat : [%f]",xq);
    ROS_INFO("I heard y quat : [%f]",yq);
    ROS_INFO("I heard z quat : [%f]",zq);
    ROS_INFO("I heard w quat : [%f]",wq);

    xmlString += "<Pose X=\""+std::to_string(x)+"\" ";
    xmlString += "Y=\""+std::to_string(y)+"\" ";
    xmlString += "Z=\""+std::to_string(z)+"\" ";
    xmlString += "XQ=\""+std::to_string(xq)+"\" ";
    xmlString += "YQ=\""+std::to_string(yq)+"\" ";
    xmlString += "ZQ=\""+std::to_string(zq)+"\" ";
    xmlString += "WQ=\""+std::to_string(wq)+"\"></Pose>";

    std::ofstream pose_xml_file(path,std::ofstream::out|std::ofstream::app);
    pose_xml_file << xmlString << std::endl;
    pose_xml_file.close();

}

int main(int argc, char **argv)
{

    std::string xmlString = "<?xml version=\"1.0\" encoding=\"utf-8\"?>";
    std::ofstream pose_xml_file(path,std::ofstream::out|std::ofstream::app);
    pose_xml_file << xmlString << std::endl << "<Posen>" << std::endl;

    ros::init(argc, argv, "asr_rviz_pose_manager");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("move_base/goal", 1000, chatterCallback);

    ros::spin();

    pose_xml_file << "</Posen>" << std::endl;
    pose_xml_file.close();


    return 0;
}
