cmake_minimum_required(VERSION 2.8)

PROJECT(Gui)
 
SET(CMAKE_CXX_FLAGS "-Wall")

FIND_PACKAGE( Qt4 REQUIRED )
SET(CMAKE_AUTOMOC ON)

SET( QT_USE_QTSQL TRUE )
INCLUDE( ${QT_USE_FILE} )

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
    ${CMAKE_BINARY_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
) 


SET( SOURCES
    CommandHistory.cpp
    DatabaseSelector.cpp
    DatabaseStructureModel.cpp
    LogDelegate.cpp
    LogView.cpp
    MainWindow.cpp
    QueryResultModel.cpp
    QuickOpenDialog.cpp
    RememberDialog.cpp
    Settings.cpp
    SqlConsole.cpp
    TableView.cpp
)

SET( FORMS
    MainWindow.ui
    QuickOpenDialog.ui
)

QT4_ADD_RESOURCES(QRC_IMAGES images.qrc)


QT4_WRAP_UI( UI ${FORMS} )

ADD_LIBRARY( gui STATIC ${SOURCES} ${UI} ${QRC_IMAGES})

