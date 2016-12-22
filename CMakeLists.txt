cmake_minimum_required(VERSION 2.8)
project(classifier_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#modules
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
#find_package( OpenCV REQUIRED )

# dirs on nest
link_directories(/usr/local/Cellar/opencv/2.4.13.2/lib)
include_directories(/usr/local/Cellar/opencv/2.4.13.2/include)

# link_directories(/usr/local/lib)
# include_directories(/usr/local/include/)

set(SOURCE_FILES main.bak.cpp main.cpp)
#add_executable(classifier_test ${SOURCE_FILES})
add_executable(classifier_test main.cpp)
target_link_libraries(classifier_test opencv_core opencv_imgproc opencv_objdetect opencv_highgui opencv_videoio)
