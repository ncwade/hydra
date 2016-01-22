cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

include_directories(${gtest_SOURCE_DIR}/include
                    ${gmock_SOURCE_DIR}/include)

add_executable(test_hydra test_hydra.cpp)

find_package(Boost COMPONENTS thread system)

target_link_libraries(test_hydra gtest gtest_main
                      ${Boost_THREAD_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY})
