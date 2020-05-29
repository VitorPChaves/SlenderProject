cmake_minimum_required(VERSION 3.6)

project(SlenderProject)

set(CMAKE_DEBUG_POSTFIX _d)
set(THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

list(APPEND CMAKE_MODULE_PATH "${THIRDPARTY_DIR}/cmake-scripts")
include(target_libraries)

find_package(OpenGL REQUIRED)

add_subdirectory(${THIRDPARTY_DIR}/glew)
add_subdirectory(${THIRDPARTY_DIR}/glfw)

include_directories(${THIRDPARTY_DIR}/glew/include)
include_directories(${THIRDPARTY_DIR}/glfw/include)
include_directories(${THIRDPARTY_DIR}/glm)
include_directories(${THIRDPARTY_DIR}/assimp/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${THIRDPARTY_DIR}/assimp/lib)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(GLEW_LIB_NAME glew64)
else()
    set(GLEW_LIB_NAME glew32)
endif()

set(THIRDPARTY_LIBS ${OPENGL_LIBRARY} ${GLEW_LIB_NAME} glfw ${GLFW_LIBRARIES} assimp-vc142-mtd)

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${THIRDPARTY_LIBS})

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	TARGET_DYNAMIC_LIBRARIES(${PROJECT_NAME} ${GLEW_LIB_NAME} glfw)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${THIRDPARTY_DIR}/assimp/lib/assimp-vc142-mtd.dll" "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)