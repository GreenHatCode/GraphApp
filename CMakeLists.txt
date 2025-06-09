cmake_minimum_required(VERSION 3.2...4.0)
project(GraphApp)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

add_executable(${PROJECT_NAME} WIN32 ${HEADER_FILES} ${SOURCE_FILES})

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# WxWidgets
find_package(wxWidgets REQUIRED COMPONENTS net core base xrc xml)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
	include(${wxWidgets_USE_FILE})
endif()

# Put all libraries into a variable
set(LIBS ${wxWidgets_LIBRARIES})
# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/thirdparty"
)

# COPYING RESOURCES TO BINARY DIR
add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/res"
 		$<TARGET_FILE_DIR:${PROJECT_NAME}>/res
        COMMENT "Copying resources into binary directory")

#add_dependencies(${PROJECT_NAME} copy_resources)


# Define the link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})


