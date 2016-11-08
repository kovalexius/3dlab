
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package( X11 REQUIRED )

include_directories( ${X11_INCLUDE_DIR} )

add_executable( FiguresOOP
                main.cpp )
                
target_link_libraries( FiguresOOP
                       ${X11_LIBRARIES}
                      )