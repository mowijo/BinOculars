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


ADD_SUBDIRECTORY(../lib/sqlhighlighter/src sqlhighlighter)

SET( SOURCES
        Field.cpp
	DataBase.cpp  
	DatabaseStructureModel.cpp  
	MainWindow.cpp  
	Settings.cpp  
	SqlConsole.cpp  
	Table.cpp  
	main.cpp
)

SET( FORMS
	MainWindow.ui 
)

QT4_WRAP_UI( UI ${FORMS} )

ADD_EXECUTABLE( CaptainOates ${SOURCES} ${UI})
TARGET_LINK_LIBRARIES( CaptainOates ${QT_LIBRARIES} tokenizer)
