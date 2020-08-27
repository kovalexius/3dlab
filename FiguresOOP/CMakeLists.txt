
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package( X11 REQUIRED )

include_directories( ${X11_INCLUDE_DIR} )

add_executable(FiguresOOP
                ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
				 ${CMAKE_CURRENT_SOURCE_DIR}/testXLib.cpp)
                
target_link_libraries( FiguresOOP
                       ${X11_LIBRARIES}
                      )