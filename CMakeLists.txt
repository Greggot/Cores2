cmake_minimum_required(VERSION 3.25)
project(cores)

# PACKAGES - wxWidgets, OpenGL, GLM
find_package(wxWidgets REQUIRED COMPONENTS net core base gl)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

set(SOURCE_FILES
    src/application/app_application.cpp
    src/application/app_main_window.cpp

    src/ui/ui_scene_viewer.cpp

    src/ux/ux_camera_controller.cpp

    src/visualization/vi_axes.cpp
    src/visualization/vi_drawable.cpp
)
file(COPY "shaders/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/shaders/")

add_executable(cores ${SOURCE_FILES})
set_property(TARGET cores PROPERTY CXX_STANDARD 17)

# LIBRARIES 
target_link_libraries(cores ${wxWidgets_LIBRARIES})
target_link_libraries(cores ${OPENGL_LIBRARIES})
target_link_libraries(cores ${OPENGL_GLU_LIBRARY})
target_link_libraries(cores ${GLEW_LIBRARIES})
target_link_libraries(cores glm::glm)

# INCLUDES
target_include_directories(cores PUBLIC inc)
target_include_directories(cores PUBLIC ${OPENGL_INCLUDE_DIRS})
if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()