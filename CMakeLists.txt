cmake_minimum_required(VERSION 3.25)
project(cores)
# FIND WX_WIDGETS
find_package(wxWidgets REQUIRED COMPONENTS net core base gl)
if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()

set(SOURCE_FILES
    src/application/app_entry_point.cpp
    src/application/app_main_window.cpp

    src/ui/ui_scene_viewer.cpp
)

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  )

add_executable(cores ${SOURCE_FILES})
target_include_directories(cores PUBLIC inc)
target_link_libraries(cores ${wxWidgets_LIBRARIES})
target_link_libraries(cores ${OPENGL_LIBRARIES})