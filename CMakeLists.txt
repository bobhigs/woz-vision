cmake_minimum_required(VERSION 3.3)
project(opencv)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./build/")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(promenade src/promenade.cpp)
target_link_libraries(promenade ${OpenCV_LIBS})

#add_executable(optical_flow src/optical_flow.cpp)
#target_link_libraries(optical_flow ${OpenCV_LIBS})

add_executable(lkdemo src/lkdemo.cpp)
target_link_libraries(lkdemo ${OpenCV_LIBS})

add_executable(camshiftdemo src/camshiftdemo.cpp)
target_link_libraries(camshiftdemo ${OpenCV_LIBS})

#add_executable(optical_flow_farneback src/optical_flow_farneback.cpp)
#target_link_libraries(optical_flow_farneback ${OpenCV_LIBS})

add_executable(fback src/fback.cpp)
target_link_libraries(fback ${OpenCV_LIBS})

#add_executable(cas src/cas.cpp)
#target_link_libraries(cas ${OpenCV_LIBS})

add_executable(car src/car.cpp)
target_link_libraries(car ${OpenCV_LIBS})

add_executable(findcontours src/findcontours.cpp)
target_link_libraries(findcontours ${OpenCV_LIBS})
#
add_executable(tests src/tests.cpp)
target_link_libraries(tests ${OpenCV_LIBS})

add_executable(video-dev src/video-dev.cpp)
target_link_libraries(video-dev ${OpenCV_LIBS})

add_executable(inRange src/inRange.cpp)
target_link_libraries(inRange ${OpenCV_LIBS})

add_executable(devInRange src/devInRange.cpp)
target_link_libraries(devInRange ${OpenCV_LIBS})

add_executable(erodedilate src/erodedilate.cpp)
target_link_libraries(erodedilate ${OpenCV_LIBS})

add_executable(webCamTracker src/webCamTracker.cpp)
target_link_libraries(webCamTracker ${OpenCV_LIBS})

add_executable(resize src/resize.cpp)
target_link_libraries(resize ${OpenCV_LIBS})

#
#add_executable(vio src/video_input.cpp)
#target_link_libraries(vio ${OpenCV_LIBS})
#
#add_executable(vwrite src/vwrite.cpp)
#target_link_libraries(vwrite ${OpenCV_LIBS})
