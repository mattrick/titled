project (filmweb)
cmake_minimum_required (VERSION 2.6)

# C++ sets
set (CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x")
#

# CMake sets
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${filmweb_SOURCE_DIR}/cmake/Modules/")
#

# Boost package
# for Xpressive we don't need any .lib files, so REQUIRED COMPONENTS list is empty
find_package ( Boost )
include_directories ( ${Boost_INCLUDE_DIRS} )
add_definitions( -DBOOST_ALL_NO_LIB )
#

# SQLite3x package
find_package ( SQLite3x )
include_directories(${SQLite3x_INCLUDE_DIRS})
link_directories(${SQLite3x_LIB_DIR})
#

# QT4 package
find_package ( Qt4 REQUIRED COMPONENTS QtCore QtGui QtWebKit QtNetwork )
include(${QT_USE_FILE})
#

add_subdirectory(sqlite3x)
add_subdirectory(src)