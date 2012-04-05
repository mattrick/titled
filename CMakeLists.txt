project (titled)
cmake_minimum_required (VERSION 2.6)

# C++ sets
set (CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x")
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

# QT4 package
find_package (Qt4 REQUIRED COMPONENTS QtCore QtGui QtWebKit QtNetwork)
include (${QT_USE_FILE})
#

add_subdirectory (sqlite3x)

file (GLOB titled_SOURCES "${titled_SOURCE_DIR}/src/*.cpp")
file (GLOB titled_HEADERS "${titled_SOURCE_DIR}/src/*.hpp" "${titled_SOURCE_DIR}/src/*.h")

qt4_wrap_cpp (titled_QT_HEADERS_MOC ${titled_HEADERS})
qt4_add_resources (titled_RCC "${titled_SOURCE_DIR}/resources/resources.qrc")

add_executable (titled ${titled_SOURCES} ${titled_QT_HEADERS_MOC} ${titled_RCC})
target_link_libraries (titled ${Boost_PROGRAM_OPTIONS_LIBRARY} ${SQLite3x_LIBRARIES} ${QT_LIBRARIES} dl pthread)