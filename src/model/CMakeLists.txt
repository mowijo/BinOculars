cmake_minimum_required(VERSION 2.8)

PROJECT(Model)
 
SET(CMAKE_CXX_FLAGS "-Wall")

FIND_PACKAGE( Qt4 REQUIRED )
SET(CMAKE_AUTOMOC ON)

SET( QT_USE_QTSQL TRUE )
INCLUDE( ${QT_USE_FILE} )

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
) 


SET( SOURCES
    DataBase.cpp
    Field.cpp
    Log.cpp
    LogFilter.cpp
    Table.cpp
)

ADD_LIBRARY( model STATIC ${SOURCES} )

