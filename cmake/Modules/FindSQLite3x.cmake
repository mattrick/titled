# - Find the SQLite3x includes and libraries.
# The following variables are set if SQLite3x is found.  If SQLite3x is not
# found, SQLite3x_FOUND is set to false.
#  SQLite3x_FOUND        - True when the SQLite3x include directory is found.
#  SQLite3x_INCLUDE_DIRS - the path to where the SQLite3x include files are.
#  SQLite3x_LIBRARY_DIR - The path to where the SQLite3x library files are.
#  SQLite3x_BINARY_DIRS - The path to where the SQLite3x dlls are.
#  SQLite3x_LIBRARIES - list of all libs from requested components.

MESSAGE(STATUS "Searching for SQLite3x library...")

SET(SQLite3x_INCLUDE_PATH_DESCRIPTION "top-level directory containing the SQLite3x include directories. E.g /usr/local/include/ or c:\\SQLite3x\\include\\SQLite3x-1.3.2")
SET(SQLite3x_INCLUDE_DIR_MESSAGE "Set the SQLite3x_INCLUDE_DIR cmake cache entry to the ${SQLite3x_INCLUDE_PATH_DESCRIPTION}")
SET(SQLite3x_LIBRARY_PATH_DESCRIPTION "top-level directory containing the SQLite3x libraries.")
SET(SQLite3x_LIBRARY_DIR_MESSAGE "Set the SQLite3x_LIBRARY_DIR cmake cache entry to the ${SQLite3x_LIBRARY_PATH_DESCRIPTION}")

SET(SQLite3x_DIR_SEARCH $ENV{SQLite3x_ROOT})
IF(SQLite3x_DIR_SEARCH)
  FILE(TO_CMAKE_PATH ${SQLite3x_DIR_SEARCH} SQLite3x_DIR_SEARCH)
ENDIF(SQLite3x_DIR_SEARCH)

IF(NOT SQLite3x_DIR_SEARCH)
  SET(SQLite3x_DIR_SEARCH ${CMAKE_CURRENT_LIST_DIR}/../../sqlite3x/)
ENDIF(NOT SQLite3x_DIR_SEARCH)

#IF(WIN32)
#  SET(SQLite3x_DIR_SEARCH
#    ${SQLite3x_DIR_SEARCH}
#    C:/SQLite3x
#    D:/SQLite3x
#    "C:/Program Files/SQLite3x"
#    "C:/Programme/SQLite3x"
#    "D:/Program Files/SQLite3x"
#    "D:/Programme/SQLite3x"
#  )
#ENDIF(WIN32)

SET(SQLite3x_INCLUDE_DIR ${SQLite3x_DIR_SEARCH}/include/)

SET(SQLite3x_FOUND 0)

# Now try to get the include and library path.
IF(SQLite3x_INCLUDE_DIR)
  IF(EXISTS "${SQLite3x_INCLUDE_DIR}/sqlite3x")
    SET(SQLite3x_INCLUDE_DIRS
	${SQLite3x_INCLUDE_DIR}
      ${SQLite3x_INCLUDE_DIR}/sqlite3x
    )
    SET(SQLite3x_FOUND 1)
  ENDIF(EXISTS "${SQLite3x_INCLUDE_DIR}/sqlite3x")

  IF(NOT SQLite3x_LIBRARY_DIR)

    SET(SQLite3x_LIBRARY_DIR ${SQLite3x_SEARCH_DIR}/lib)
    SET(SQLite3x_LIBRARIES "sqlite3x")

	ENDIF(NOT SQLite3x_LIBRARY_DIR)

ENDIF(SQLite3x_INCLUDE_DIR)

IF(NOT SQLite3x_FOUND)
    MESSAGE(STATUS "SQLite3x was not found. ${SQLite3x_INCLUDE_DIR_MESSAGE}")
ELSE(NOT SQLite3x_FOUND)
  MESSAGE(STATUS "  Found SQLite3x!")
ENDIF(NOT SQLite3x_FOUND)