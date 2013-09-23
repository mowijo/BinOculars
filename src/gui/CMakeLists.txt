cmake_minimum_required(VERSION 2.8)

PROJECT(Gui)
 
SET(CMAKE_CXX_FLAGS "-Wall")

set(CMAKE_INCLUDE_CURRENT_DIR ON)


INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
    ${CMAKE_BINARY_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
) 
  
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
set(CMAKE_AUTOMOC ON)

SET( SOURCES
    CommandHistory.cpp
    DatabaseSelector.cpp
    DatabaseStructureModel.cpp
    FieldDialog.cpp
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
    FieldDialog.ui
    MainWindow.ui
    QuickOpenDialog.ui
)

QT5_ADD_RESOURCES(QRC_IMAGES images.qrc)


QT5_WRAP_UI( UI ${FORMS} )

ADD_LIBRARY( gui STATIC ${SOURCES} ${UI} ${QRC_IMAGES})

qt5_use_modules(gui Widgets)
qt5_use_modules(gui Sql)
