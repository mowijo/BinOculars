cmake_minimum_required(VERSION 2.8)

PROJECT(BinOcularsTests)
 
SET(CMAKE_CXX_FLAGS "-Wall")

FIND_PACKAGE( Qt4 REQUIRED )
SET( QT_USE_QTSQL TRUE )
INCLUDE( ${QT_USE_FILE} )
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

QT4_ADD_RESOURCES( RESOURCE_FILES ${RESOURCES} )

ADD_EXECUTABLE( tests ${SOURCES} ${RESOURCE_FILES} )
TARGET_LINK_LIBRARIES( tests ${QT_QTTEST_LIBRARY} model ${QT_LIBRARIES} )