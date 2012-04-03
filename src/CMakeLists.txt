set(EXECUTABLE_OUTPUT_PATH ${filmweb_SOURCE_DIR}/bin)

#SET(filmweb_SOURCES
#	main.cpp)


SET(filmweb_SOURCES
	main.cpp
	Collection.cpp
	CollectionModel.cpp
	CollectionItem.cpp
	ResultsModel.cpp
	ResultsItem.cpp
	FilmwebSearch.cpp
	mainwindow.cpp
	Filter.cpp
	FilterGroup.cpp
	WordDB.cpp)

SET(filmweb_QT_HEADERS
	mainwindow.h
	CollectionModel.hpp
	CollectionItem.hpp
	ResultsModel.hpp
	ResultsItem.hpp
	FilmwebSearch.hpp
	Filter.hpp
	FilterGroup.hpp)

qt4_wrap_cpp(filmweb_QT_HEADERS_MOC
	${filmweb_QT_HEADERS})

add_executable(filmweb ${filmweb_SOURCES} ${filmweb_QT_HEADERS_MOC})

target_link_libraries(filmweb ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Poco_LIBRARIES} ${SQLite3x_LIBRARIES} ${QT_LIBRARIES} dl pthread)
