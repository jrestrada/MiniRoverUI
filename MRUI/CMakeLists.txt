cmake_minimum_required(VERSION 3.5)

project(MRUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT6 /home/josue/Qt/6.4.0)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_DIR ${QT6}/gcc_64/lib/cmake/Qt6)
set(Qt6_DIR ${QT6}/gcc_64/lib/cmake/Qt6)
set(Qt6CoreTools_DIR ${QT6}/gcc_64/lib/cmake/Qt6CoreTools/)
set(Qt6GuiTools_DIR ${QT6}/gcc_64/lib/cmake/Qt6GuiTools/)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Gui Multimedia MultimediaWidgets Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Multimedia MultimediaWidgets Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        camview.h
        camview.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MRUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MRUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MRUI SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MRUI
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MRUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


set_target_properties(MRUI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(MRUI PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Multimedia
    Qt::MultimediaWidgets
    Qt::Widgets
)

install(TARGETS MRUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MRUI)
endif()
