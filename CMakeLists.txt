cmake_minimum_required(VERSION 3.0)

# Setup the project.
# Its name is defined to be the controller directory name.
get_filename_component(PROJECT ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT})

find_package( OpenCV REQUIRED )

set(DIRS ${CMAKE_SOURCE_DIR}"/src/algorithms/" ${CMAKE_SOURCE_DIR}"/src/data_structures/")
set(DIR_FILES ${CMAKE_SOURCE_DIR}"/src/algorithms/*.hpp" ${CMAKE_SOURCE_DIR}"/src/data_structures/*.hpp")


message(STATUS ${DIRS})

include_directories(DIRS)

file(GLOB_RECURSE HEADERS ${DIR_FILES})


# Get C or C++ sources in the current directory (only).
file(GLOB_RECURSE C_SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE CPP_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
set(SOURCES ${C_SOURCES} ${CPP_SOURCES} ${HEADERS})



# Set the  Webots home path (change it according to your installation method)
set(WEBOTS_HOME "/usr/local/webots")
#set(WEBOTS_HOME "/snap/webots/current/usr/share/webots")

# Link with the Webots controller library.
link_directories($ENV{WEBOTS_HOME}/lib/controller)
set (LIBRARIES m ${CMAKE_SHARED_LIBRARY_PREFIX}Controller${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_PREFIX}CppController${CMAKE_SHARED_LIBRARY_SUFFIX} ${OpenCV_LIBS})
include_directories($ENV{WEBOTS_HOME}/include/controller/c $ENV{WEBOTS_HOME}/include/controller/cpp ${OpenCV_INCLUDE_DIRS})

message(STATUS ${SOURCES})

# Setup the target executable.
add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} ${LIBRARIES})

# Copy the target executable at the right location.
add_custom_command(TARGET ${PROJECT} POST_BUILD COMMAND ${CMAKE_COMMAND} -E
  copy ${CMAKE_BINARY_DIR}/${PROJECT} ${CMAKE_SOURCE_DIR}
)
