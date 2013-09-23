cmake_minimum_required(VERSION 2.8)

PROJECT(BinOkulars)
 
SET(CMAKE_CXX_FLAGS "-Wall")



find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
set(CMAKE_AUTOMOC ON)

SET(CMAKE_AUTOMOC ON)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
    ${CMAKE_CURRENT_BINARY_DIR}
) 


ADD_SUBDIRECTORY(../lib/sqlhighlighter/src sqlhighlighter)
ADD_SUBDIRECTORY(model)
ADD_SUBDIRECTORY(gui)


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


ADD_EXECUTABLE( BinOkulars WIN32 ${SOURCES} ${UI}  )
TARGET_LINK_LIBRARIES( BinOkulars ${QT_LIBRARIES} gui tokenizer model )

qt5_use_modules(BinOkulars Widgets)
qt5_use_modules(BinOkulars Sql)
