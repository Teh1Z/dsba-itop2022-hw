cmake_minimum_required(VERSION 3.5)

project(BigHomework VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        country.h
        country.cpp
        countrymodel.h
        countrymodel.cpp
        csvparser.h
        csvparser.cpp
        regionmodel.h
        regionmodel.cpp
        region.h
        region.cpp
        countrydialog.h
        countrydialog.cpp
        countrydialog.ui
        countriesmodel.h
        countriesmodel.cpp
        watchlistmodel.h
        watchlistmodel.cpp
        watchlistdialog.h
        watchlistdialog.cpp
        watchlistdialog.ui
        addcountrydialog.h
        addcountrydialog.cpp
        addcountrydialog.ui
        logowidget.h
        logowidget.cpp
        ratingmodel.h
        ratingmodel.cpp
        datadialog.h
        datadialog.cpp
        datadialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BigHomework
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BigHomework APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BigHomework SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BigHomework
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BigHomework PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(BigHomework PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BigHomework)
endif()
