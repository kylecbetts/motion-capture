cmake_minimum_required(VERSION 3.16)

project(MotionCapture VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(MotionCaptureApp
    src/main.cpp
)

qt_add_resources(MotionCaptureApp "resources"
    PREFIX "/"
    FILES
        resources/fonts/Exo2.ttf
)

qt_add_qml_module(MotionCaptureApp
    URI MotionCapture
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

set_target_properties(MotionCaptureApp PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(MotionCaptureApp
    PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS MotionCaptureApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
