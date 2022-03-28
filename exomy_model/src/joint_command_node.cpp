#include <ros/ros.h>
#include <exomy_msgs/msg/motor_commands.hpp>
#include <exomy_sim_msgs/msg/joint_command.hpp>
#include <exomy_sim_msgs/msg/joint_command_array.hpp>


const std::list<std::string> drive_joint_names = {"DRV_LF_joint", "DRV_RF_joint", "DRV_LM_joint", "DRV_RM_joint", "DRV_LR_joint", "DRV_RR_joint"};
const std::list<std::string> steer_joint_names = {"STR_LF_joint", "STR_RF_joint", "STR_LM_joint", "STR_RM_joint", "STR_LR_joint", "STR_RR_joint"};
ros::Publisher joint_command_pub_;

void motor_commands_callback(const exomy_msgs::msg::MotorCommands::SharedPtr msg) const
{
    exomy_sim_msgs::msg::JointCommandArray joint_command_array_msg; 

    int i = 0;
    for(std::string name : drive_joint_names)
    {
        exomy_sim_msgs::msg::JointCommand joint_command_msg;
        joint_command_msg.header.stamp = ros::Time::now();
        joint_command_msg.name = name;
        joint_command_msg.mode = "VELOCITY";
        joint_command_msg.value = float(msg->motor_speeds[i])/20.0;
        joint_command_array_msg.joint_command_array.push_back(joint_command_msg);
        i++;
    }

    int j = 0;
    for(std::string name : steer_joint_names)
    {
        exomy_sim_msgs::msg::JointCommand joint_command_msg;
        joint_command_msg.header.stamp = ros::Time::now();
        joint_command_msg.name = name;
        joint_command_msg.mode = "POSITION";
        joint_command_msg.value = -msg->motor_angles[j]/180.0*M_PI;
        joint_command_array_msg.joint_command_array.push_back(joint_command_msg);
        j++;
    }

    joint_command_array_msg.header.stamp = ros::Time::now();
    joint_command_pub_.publish(joint_command_array_msg);
}

int main(int argc, char * argv[])
{
    ros::init(argc, argv, "joint_command_node");
    ros::NodeHandle n; 
  
    joint_command_pub_ = n.advertise<exomy_sim_msgs::msg::JointCommandArray>("joint_cmds", 100);
    ros::Subscriber motor_commands_sub_ = n.subscribe<exomy_msgs::msg::MotorCommands>("motor_commands", 100, motor_commands_callback);

    ros::spin();
    return 0;
}


