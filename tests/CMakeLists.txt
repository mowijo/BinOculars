cmake_minimum_required(VERSION 2.8)

PROJECT(BinOcularsTests)
 
SET(CMAKE_CXX_FLAGS "-Wall")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Test REQUIRED)
set(CMAKE_AUTOMOC ON)

INCLUDE_DIRECTORIES ( ${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES ( ${CMAKE_CURRENT_SOURCE_DIR}/../src)

ADD_SUBDIRECTORY(../src/model model)

set(CMAKE_AUTOMOC ON) 

SET( SOURCES
    main.cpp
    DataBaseTest.cpp
    FieldTest.cpp
    LibModelTestSuite.cpp
    TableTest.cpp
    TestDataBaseProvider.cpp
)


SET( RESOURCES
    TestResources/resources.qrc
)

QT5_ADD_RESOURCES( RESOURCE_FILES ${RESOURCES} )

ADD_EXECUTABLE( tests ${SOURCES} ${RESOURCE_FILES} )
TARGET_LINK_LIBRARIES( tests model  )

qt5_use_modules(tests Widgets)
qt5_use_modules(tests Sql)
qt5_use_modules(tests Test)
