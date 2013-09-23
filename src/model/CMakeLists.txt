cmake_minimum_required(VERSION 2.8)

PROJECT(Model)
 
SET(CMAKE_CXX_FLAGS "-Wall")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
set(CMAKE_AUTOMOC ON)


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

qt5_use_modules(model Widgets)
qt5_use_modules(model Sql)
