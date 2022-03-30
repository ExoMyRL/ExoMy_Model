cmake_minimum_required(VERSION 2.8.3)

project(exomy_model)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)
#find_package(exomy_sim_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(exomy REQUIRED)
catkin_package()
include_directories(include ${catkin_INCLUDE_DIRS})

# find_package(roslaunch)
add_executable(joint_command_node ~/exomy_ws/src/ExoMy_Model/exomy_model/src/joint_command_node.cpp)
target_link_libraries(joint_command_node ${catkin_INCLUDE_DIRS} exomy)

foreach(dir config launch meshes urdf)
	install(DIRECTORY ${dir}/
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)
