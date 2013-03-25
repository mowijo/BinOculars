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


ADD_SUBDIRECTORY(../lib/sqlhighlighter/src sqlhighlighter)
ADD_SUBDIRECTORY(model)
ADD_SUBDIRECTORY(gui)


QT4_ADD_RESOURCES(QRC_IMAGES images.qrc)

SET( SOURCES
    main.cpp
)


IF( MINGW )
	ADD_CUSTOM_COMMAND(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ms-windows-icon.o
		COMMAND windres.exe -I${CMAKE_CURRENT_SOURCE_DIR} -i${CMAKE_CURRENT_SOURCE_DIR}/ms-windows-icon.rc  -o ${CMAKE_CURRENT_BINARY_DIR}/ms-windows-icon.o
	)
	set (SOURCES ${SOURCES} ms-windows-icon.o)
ENDIF( MINGW )


ADD_EXECUTABLE( BinOkulars WIN32 ${SOURCES} ${UI} ${QRC_IMAGES} )
TARGET_LINK_LIBRARIES( BinOkulars ${QT_LIBRARIES} gui tokenizer model )
