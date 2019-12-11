cmake_minimum_required(VERSION 2.8)

project(vox_test)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions( -Wall -Wl,--no-as-needed -pthread -lpthread -std=gnu++11 -DGL_GLEXT_PROTOTYPES )
elseif (MSVC)
    #add_definitions( -DGL_GLEXT_PROTOTYPES -std=c++11 )
endif()

find_package(Qt4 REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_AUTOMOC ON)
set(QT_USE_QTOPENGL TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include (${QT_USE_FILE})

include_directories( 
                ${CMAKE_SOURCE_DIR}/glExt/
                ${CMAKE_SOURCE_DIR}/geoMath/
                   )             

set( WIDGET_MOC src/widget.h src/widget.cpp)
set( GLVOXEL_MOC src/glvoxel.h src/glvoxel.cpp)

#qt4_wrap_cpp( MOC_SOURCES ${WIDGET_MOC} ${GLVOXEL_MOC} )
#qt4_generate_moc(MOC_SOURCES)

add_executable( voxtest
                ./src/main.cpp
                ${CMAKE_SOURCE_DIR}/glExt/glExtInit.cpp
                ${CMAKE_SOURCE_DIR}/glExt/glExtInit.h
                ${CMAKE_SOURCE_DIR}/glExt/gl_helpers.cpp
                ${CMAKE_SOURCE_DIR}/glExt/gl_helpers.h
                ${CMAKE_SOURCE_DIR}/geoMath/Geometry.cpp
                ${CMAKE_SOURCE_DIR}/geoMath/Geometry.h
                ./src/generate_shapes.cpp
                ./src/generate_shapes.h
                ./src/file_data.cpp
                ./src/file_data.h
                ./src/octree_data.cpp
                ./src/octree_data.h
                ${MOC_SOURCES}
                ${WIDGET_MOC}
                ${GLVOXEL_MOC}
              )

# Copying shaders to work directory
configure_file( ./src/vox.frag ${CMAKE_CURRENT_BINARY_DIR}/vox.frag COPYONLY )
configure_file( ./src/vox.vert ${CMAKE_CURRENT_BINARY_DIR}/vox.vert COPYONLY )

message(STATUS "Library dir: " + ${QT_LIBRARY_DIR} )
message(STATUS "Qt4: " + ${QT4_FOUND} )
message(STATUS "Qt debug: " + ${QT_LIBRARY_DEBUG} )

# Copying dll to working directory
if ( WIN32 )
foreach ( _variableName ${QT_SHARED_LIBRARY} )
    message(STATUS "Copying file: " +  ${_variableName} )
	configure_file( ${_variableName}, ${CMAKE_CURRENT_BINARY_DIR}/${_variableName}, COPYONLY )
endforeach()
endif()

target_link_libraries( voxtest ${QT_LIBRARIES} ${OPENGL_LIBRARIES} )