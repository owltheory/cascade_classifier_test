cmake_minimum_required(VERSION 3.3)
project(classifier_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#modules
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
#find_package( OpenCV REQUIRED )

#set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} /usr/local/lib)
link_libraries(/usr/local/lib)

include_directories(/usr/local/include/opencv)
#set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} /usr/local/lib)

set(SOURCE_FILES main.bak.cpp main.cpp)
#add_executable(classifier_test ${SOURCE_FILES})
add_executable(classifier_test main.cpp)
target_link_libraries(classifier_test libopencv_core.so libopencv_imgproc.so libopencv_objdetect.so libopencv_highgui.so)