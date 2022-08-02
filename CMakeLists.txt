cmake_minimum_required(VERSION 3.5)

project(Chess_QT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH QT_DIR)
set(CMAKE_PREFIX_PATH CMAKE_DIR)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.h    src/mainwindow.cpp
        src/chessboard.h    src/chessboard.cpp
        src/chessitem.h     src/chessitem.cpp
        src/chessbox.h      src/chessbox.cpp
        src/game.h          src/game.cpp
        src/state.h         src/state.cpp

        src/king.h          src/king.cpp
        src/queen.h         src/queen.cpp
        src/rook.h          src/rook.cpp
        src/bishop.h        src/bishop.cpp
        src/knight.h        src/knight.cpp
        src/pawn.h          src/pawn.cpp
)

qt6_add_resources(PROJECT_SOURCES ./res/resource.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Chess_QT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Chess_QT SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Chess_QT
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Chess_QT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Chess_QT PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Chess_QT)
endif()
