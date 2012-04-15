project (titled)
cmake_minimum_required (VERSION 2.6)

# C++ sets
set (CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -fPIC")
#

# CMake sets
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${titled_SOURCE_DIR}/cmake/Modules/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
#

# SQLite3x package
find_package (SQLite3x)
include_directories (${SQLite3x_INCLUDE_DIRS})
link_directories (${SQLite3x_LIB_DIR})
#

# Qt package
if (USE_QT5)
	set (QT5_MODULES Core Gui Widgets WebKit Network)
	
	foreach (MODULE ${QT5_MODULES})
		set (Qt5${MODULE}_DIR /opt/qt5/lib/cmake/Qt5${MODULE})
		find_package (Qt5${MODULE} REQUIRED)
		include_directories (${Qt5${MODULE}_INCLUDE_DIRS})
		add_definitions (${Qt5${MODULE}_DEFINITONS})
		set (QT_LIBRARIES ${QT_LIBRARIES} ${Qt5${MODULE}_LIBRARIES})
	endforeach (MODULE)
else (USE_QT5)
	find_package (Qt4 REQUIRED COMPONENTS QtCore QtGui QtWebKit QtNetwork)
	include (${QT_USE_FILE})
endif (USE_QT5)
#

add_subdirectory (sqlite3x)
add_subdirectory (plugins)


file (GLOB titled_SOURCES "${titled_SOURCE_DIR}/src/*.cpp")
file (GLOB titled_HEADERS "${titled_SOURCE_DIR}/src/*.hpp" "${titled_SOURCE_DIR}/src/*.h")

if (USE_QT5)
	qt5_wrap_cpp (titled_QT_HEADERS_MOC ${titled_HEADERS})
	qt5_add_resources (titled_RCC "${titled_SOURCE_DIR}/resources/resources.qrc")
else (USE_QT5)
	qt4_wrap_cpp (titled_QT_HEADERS_MOC ${titled_HEADERS})
	qt4_add_resources (titled_RCC "${titled_SOURCE_DIR}/resources/resources.qrc")
endif (USE_QT5)

add_executable (titled ${titled_SOURCES} ${titled_QT_HEADERS_MOC} ${titled_RCC})
target_link_libraries (titled ${Boost_PROGRAM_OPTIONS_LIBRARY} ${SQLite3x_LIBRARIES} ${QT_LIBRARIES} dl pthread)