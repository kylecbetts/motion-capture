cmake_minimum_required(VERSION 3.16)

project(MotionCapture VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(XSENS_SDK_DIR "C:/Program Files/Xsens/MVN SDK 2024.0/SDK Files/")

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(MotionCaptureApp
    src/main.cpp
)

qt_add_resources(MotionCaptureApp "resources"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
        resources/fonts/Exo2.ttf
        resources/icons/settings.svg
        resources/icons/query.svg
)

qt_add_qml_module(MotionCaptureApp
    URI MotionCapture
    VERSION 1.0
    QML_FILES
        qml/Main.qml
    SOURCES
        src/xsenscontroller.h
        src/xsenscontroller.cpp
)

set_target_properties(MotionCaptureApp PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_include_directories(MotionCaptureApp
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${XSENS_SDK_DIR}/x64/include
)

target_link_directories(MotionCaptureApp
    PRIVATE
        ${XSENS_SDK_DIR}/x64/lib
)

target_link_libraries(MotionCaptureApp
    PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
        xme64
        xstypes64
)

add_custom_command(TARGET MotionCaptureApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${XSENS_SDK_DIR}/x64/lib/xee_solver64.dll"
        "$<TARGET_FILE_DIR:MotionCaptureApp>"
)

add_custom_command(TARGET MotionCaptureApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${XSENS_SDK_DIR}/x64/lib/xme64.dll"
        "$<TARGET_FILE_DIR:MotionCaptureApp>"
)

add_custom_command(TARGET MotionCaptureApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${XSENS_SDK_DIR}/x64/lib/xsensdeviceapi64.dll"
        "$<TARGET_FILE_DIR:MotionCaptureApp>"
)

add_custom_command(TARGET MotionCaptureApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${XSENS_SDK_DIR}/x64/lib/xstypes64.dll"
        "$<TARGET_FILE_DIR:MotionCaptureApp>"
)

add_custom_command(TARGET MotionCaptureApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${XSENS_SDK_DIR}/rundeps"
        "$<TARGET_FILE_DIR:MotionCaptureApp>"
)

include(GNUInstallDirs)
install(TARGETS MotionCaptureApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
