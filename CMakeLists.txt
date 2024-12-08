cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization

project(CMakeTest)

find_package( OpenGL REQUIRED )

# GLFW Config
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ONLY_LIBS  ON CACHE BOOL "" FORCE)

# GLEW Config
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)

# GLM Config
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)


# Libraries
add_subdirectory(extern/glew-2.1.0/build/cmake)
add_definitions(-DGLEW_STATIC)
include_directories("${CMAKE_SOURCE_DIR}/extern/glew-2.1.0/include")

add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)
add_subdirectory(extern/spdlog)
add_subdirectory(extern/imgui)

# STB Config
include_directories("${CMAKE_SOURCE_DIR}/extern/stb")
link_directories("${CMAKE_SOURCE_DIR}/extern/stb") 

# Sources
# MY_SOURCES is defined to be a list of all the source files in src
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")
set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 23)
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC GLFW_INCLUDE_NONE=1) # Don't include GLFW's OpenGL headers

# Configure resource files macro
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/")
# Configure debug flags
target_compile_definitions("${CMAKE_PROJECT_NAME}"
    PRIVATE
        # If the debug configuration pass the DEBUG define to the compiler 
        $<$<CONFIG:Debug>:_DEBUG>
)

# Final Link

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES} )
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/glew-2.1.0/include")
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw glew_s spdlog imgui)

