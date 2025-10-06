cmake_minimum_required(VERSION 3.5)

project(ComandLine LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

if(ANDROID)
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    if (ANDROID_ABI STREQUAL "armeabi-v7a")
        set(ANDROID_EXTRA_LIBS
            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
    endif()
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(ComandLine SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    parser.cpp
    parser.h
    tree.h
    tree.cpp
    file_data.h
    file_data.cpp
    base_command.h
    base_command.cpp
    ls_command.h
    ls_command.cpp
    cd_command.h
    cd_command.cpp
    exit_command.h
    exit_command.cpp
    command_fabric.cpp
    command_fabric.h
    script_reader.h
    script_reader.cpp
    tree_command.h
    tree_command.cpp
    tail_command.cpp
    tail_command.h
    rmdir_command.h
    rmdir_command.cpp
    chmod_command.h
    chmod_command.cpp
    help_command.h
    help_command.cpp
  )
else()
  add_executable(ComandLine
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    parser.cpp
    parser.h
    tree.h
    tree.cpp
    file_data.h
    file_data.cpp
    base_command.h
    base_command.cpp
    ls_command.h
    ls_command.cpp
    cd_command.h
    cd_command.cpp
    exit_command.h
    exit_command.cpp
    command_fabric.cpp
    command_fabric.h
    script_reader.h
    script_reader.cpp
    tree_command.h
    tree_command.cpp
    tail_command.cpp
    tail_command.h
    rmdir_command.h
    rmdir_command.cpp
    chmod_command.h
    chmod_command.cpp
    help_command.h
    help_command.cpp
  )
endif()

target_link_libraries(ComandLine PRIVATE Qt5::Widgets)
