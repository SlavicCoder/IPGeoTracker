# CMakeLists.txt for unit tests
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Sql Network)

qt_standard_project_setup()

add_executable(unit_tests WIN32
    test_dbmanager.cpp
    test_geolocationdatamanager.cpp
    main.cpp
    minitestframework.h
)

# Link your project's source files
target_sources(unit_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/dbmanager.h
    ${CMAKE_SOURCE_DIR}/dbmanager.cpp
    ${CMAKE_SOURCE_DIR}/ipstackapi.h
    ${CMAKE_SOURCE_DIR}/ipstackapi.cpp
    ${CMAKE_SOURCE_DIR}/geolocationdatamanager.h
    ${CMAKE_SOURCE_DIR}/geolocationdatamanager.cpp
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

target_link_libraries(unit_tests
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Sql
    PRIVATE Qt6::Network
)

include(GNUInstallDirs)

# Include any necessary header directories
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR})

# Add a test target that runs your unit tests
add_test(NAME unit_tests COMMAND unit_tests)
