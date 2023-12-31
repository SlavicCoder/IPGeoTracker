cmake_minimum_required(VERSION 3.16)

project(IPGeoTracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Sql Network)

qt_standard_project_setup()

qt_add_executable(appIPGeoTracker
    main.cpp
)

qt_add_qml_module(appIPGeoTracker
    URI IPGeoTracker
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES
    SOURCES dbmanager.h dbmanager.cpp
    SOURCES ipstackapi.h ipstackapi.cpp
    SOURCES geolocationdatamanager.h geolocationdatamanager.cpp
    QML_FILES BusyIndicatorOverlay.qml
    QML_FILES PreviewPopup.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appIPGeoTracker PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appIPGeoTracker
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appIPGeoTracker
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Sql
    PRIVATE Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS appIPGeoTracker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
