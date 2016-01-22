cmake_minimum_required(VERSION 3.0)
find_package(Boost COMPONENTS thread system REQUIRED)
add_executable(main main.cpp)
TARGET_LINK_LIBRARIES(main ${ZEROMQ_LIBRARIES} ${Boost_LIBRARIES})