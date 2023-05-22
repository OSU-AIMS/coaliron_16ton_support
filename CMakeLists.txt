cmake_minimum_required(VERSION 3.5)
project(coaliron_16ton_support)


####################
## Compiler Setup ##
####################

find_package(ament_cmake REQUIRED)


#############
## Install ##
#############

# Install Misc ROS Elements
install(
  DIRECTORY config
            urdf
            launch
            meshes
            #srdf
  DESTINATION share/${PROJECT_NAME}/)


ament_package()