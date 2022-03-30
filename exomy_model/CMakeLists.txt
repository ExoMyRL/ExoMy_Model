cmake_minimum_required(VERSION 2.8.3)

project(exomy_model)

find_package(catkin REQUIRED)

catkin_package()

find_package(roslaunch)
#add_executable(joint_command_node $(find exomy_model)/exomy_sim/src/joint_command_node.cpp)
#target_link_libraries(joint_command_node)

foreach(dir config launch meshes urdf)
	install(DIRECTORY ${dir}/
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)
