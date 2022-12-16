cmake_minimum_required(VERSION 3.0.2)

project(coaliron_16ton_support)

find_package(catkin REQUIRED
    message_generation
    rosserial_client
    std_msgs
)

add_service_files(
  FILES JointControlPoint.srv
)

generate_messages(
  DEPENDENCIES std_msgs
)

catkin_package(
    CATKIN_DEPENDS message_runtime std_msgs
)

install(
    DIRECTORY launch
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
