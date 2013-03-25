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
    gui/CommandHistory.cpp
    model/DataBase.cpp
    gui/DatabaseSelector.cpp
    gui/DatabaseStructureModel.cpp
    model/Field.cpp
    model/Log.cpp
    gui/LogDelegate.cpp
    model/LogFilter.cpp
    gui/LogView.cpp
    main.cpp
    gui/MainWindow.cpp
    gui/QueryResultModel.cpp
    gui/QuickOpenDialog.cpp
    gui/RememberDialog.cpp
    gui/Settings.cpp
    gui/SqlConsole.cpp
    model/Table.cpp
    gui/TableView.cpp
)


IF( MINGW )
	ADD_CUSTOM_COMMAND(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ms-windows-icon.o
		COMMAND windres.exe -I${CMAKE_CURRENT_SOURCE_DIR} -i${CMAKE_CURRENT_SOURCE_DIR}/ms-windows-icon.rc  -o ${CMAKE_CURRENT_BINARY_DIR}/ms-windows-icon.o
	)
	set (SOURCES ${SOURCES} ms-windows-icon.o)
ENDIF( MINGW )


SET( FORMS
    gui/MainWindow.ui
    gui/QuickOpenDialog.ui
)

QT4_WRAP_UI( UI ${FORMS} )

ADD_EXECUTABLE( BinOkulars WIN32 ${SOURCES} ${UI} ${QRC_IMAGES} )
TARGET_LINK_LIBRARIES( BinOkulars ${QT_LIBRARIES} tokenizer)
