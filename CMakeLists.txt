cmake_minimum_required(VERSION 2.8)

project(GravWaves)
#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(wxWidgets COMPONENTS core base gl)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS iostreams random REQUIRED)

set(SOURCE
	main.cpp
	BasicFrame.cpp
	ErrorHandler.cpp
	GeometryDefines.cpp
	HeightmapExporter.cpp
	Parser.cpp
	Render.cpp
	Triangulation.cpp
	PointBinaryTreeSort.h
)

set(HEADER
	main.h
	BasicFrame.h
	ErrorHandler.h
	GeometryDefines.h
	HeightmapExporter.h
	Parser.h
	Render.h
	SharedDefines.h
	Triangulation.h
	PointBinaryTreeSort.h
)

include_directories(${Boost_INCLUDE_DIRS} ${wxWidgets_INCLUDE_DIRS})

add_executable(	${PROJECT_NAME}
				${SOURCE}
				${HEADER}
 )

target_link_libraries(	${PROJECT_NAME}
						${wxWidgets_LIBRARIES}
						${Boost_LIBRARY}
 )
 
 if(WIN32)
   set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
endif(WIN32)
