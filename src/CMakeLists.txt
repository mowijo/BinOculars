cmake_minimum_required(VERSION 2.8)

PROJECT(BinOkulars)
 
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

QT4_ADD_RESOURCES(QRC_IMAGES images.qrc)

SET( SOURCES
    CommandHistory.cpp
    DataBase.cpp
    DatabaseSelector.cpp
    DatabaseStructureModel.cpp
    Field.cpp
    Log.cpp
    LogDelegate.cpp
    LogFilter.cpp
    LogView.cpp
    main.cpp
    MainWindow.cpp
    QueryResultModel.cpp
    QuickOpenDialog.cpp
    RememberDialog.cpp
    Settings.cpp
    SqlConsole.cpp
    Table.cpp
    TableView.cpp
)


IF( MINGW )
	ADD_CUSTOM_COMMAND(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ms-windows-icon.o
		COMMAND windres.exe -I${CMAKE_CURRENT_SOURCE_DIR} -i${CMAKE_CURRENT_SOURCE_DIR}/ms-windows-icon.rc  -o ${CMAKE_CURRENT_BINARY_DIR}/ms-windows-icon.o
	)
	set (SOURCES ${SOURCES} ms-windows-icon.o)
ENDIF( MINGW )


SET( FORMS
    MainWindow.ui
    QuickOpenDialog.ui
)

QT4_WRAP_UI( UI ${FORMS} )

ADD_EXECUTABLE( BinOkulars WIN32 ${SOURCES} ${UI} ${QRC_IMAGES} )
TARGET_LINK_LIBRARIES( BinOkulars ${QT_LIBRARIES} tokenizer)
