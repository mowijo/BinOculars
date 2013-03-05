cmake_minimum_required(VERSION 2.8)

PROJECT(CaptainOates)
 
SET(CMAKE_CXX_FLAGS "-Wall")

FIND_PACKAGE( Qt4 REQUIRED )
SET(CMAKE_AUTOMOC ON)
SET( QT_USE_QTSQL TRUE )

INCLUDE( ${QT_USE_FILE} )

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
    ${CMAKE_CURRENT_BINARY_DIR}
) 

if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
        SET(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Release")

ADD_SUBDIRECTORY(../lib/sqlhighlighter/src sqlhighlighter)

SET( SOURCES
        DatabaseSelector.cpp
        Field.cpp
        QueryResultModel.cpp
        QuickOpenDialog.cpp
        RememberDialog.cpp
        DataBase.cpp
        DatabaseStructureModel.cpp
        main.cpp
        MainWindow.cpp
        Settings.cpp
        SqlConsole.cpp
        Table.cpp

)

SET( FORMS
    MainWindow.ui
    QuickOpenDialog.ui
)

QT4_WRAP_UI( UI ${FORMS} )

ADD_EXECUTABLE( CaptainOates ${SOURCES} ${UI})
TARGET_LINK_LIBRARIES( CaptainOates ${QT_LIBRARIES} tokenizer)
