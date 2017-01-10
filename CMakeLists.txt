cmake_minimum_required(VERSION 2.8)

project(GravWaves)
#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(wxWidgets COMPONENTS core base gl)

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS random REQUIRED)

set(SOURCE
	main.cpp
	BasicFrame.cpp
	ErrorHandler.cpp
	HeightmapExporter.cpp
	Render.cpp
	Triangulation.cpp
	PointBinaryTreeSort.cpp
	StlExporter.cpp
	DataStorage.cpp
)

set(HEADER
	main.h
	BasicFrame.h
	ErrorHandler.h
	GeometryDefines.h
	HeightmapExporter.h
	Render.h
	SharedDefines.h
	Triangulation.h
	PointBinaryTreeSort.h
	StlExporter.h
	DataStorage.h
)

set(P2T
	poly2tri/poly2tri.h
	poly2tri/sweep/advancing_front.cc
	poly2tri/sweep/advancing_front.h
	poly2tri/sweep/cdt.cc
	poly2tri/sweep/cdt.h
	poly2tri/sweep/sweep.cc
	poly2tri/sweep/sweep.h
	poly2tri/sweep/sweep_context.cc
	poly2tri/sweep/sweep_context.h
	poly2tri/common/shapes.cc
	poly2tri/common/shapes.h
	poly2tri/common/utils.h
)

include_directories(${Boost_INCLUDE_DIRS} ${wxWidgets_INCLUDE_DIRS})
link_directories(${BOOST_LIBRARY_DIR})

add_executable(	${PROJECT_NAME}
				${SOURCE}
				${HEADER}
				${P2T}
 )

target_link_libraries(	${PROJECT_NAME}
						${wxWidgets_LIBRARIES}
						${Boost_LIBRARIES}
 )
 
 if(WIN32)
   set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
endif(WIN32)

source_group("p2t"  FILES ${P2T})
