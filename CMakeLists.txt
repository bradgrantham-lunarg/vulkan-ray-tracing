cmake_minimum_required(VERSION 3.12.2)

project(vkrt)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

find_package(Vulkan REQUIRED)

find_package(GLFW REQUIRED)

if(NOT Vulkan_FOUND)
    message(
        FATAL_ERROR
            "Vulkan package was not found"
    )
endif()

add_executable(vkrt main.cpp)
target_link_libraries(vkrt ${Vulkan_LIBRARIES} ${GLFW_LIBRARIES})
target_include_directories(vkrt PRIVATE ${Vulkan_INCLUDE_DIRS})
target_include_directories(vkrt PRIVATE ${GLFW_INCLUDE_DIR})
set_property(TARGET vkrt PROPERTY CXX_STANDARD 17)

