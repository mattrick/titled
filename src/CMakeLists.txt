set(EXECUTABLE_OUTPUT_PATH ${filmweb_SOURCE_DIR}/bin)

#SET(filmweb_SOURCES
#	main.cpp)


SET(filmweb_SOURCES
	main.cpp
	mainwindow.cpp)

SET(filmweb_QT_HEADERS
	mainwindow.h)

qt4_wrap_cpp(filmweb_QT_HEADERS_MOC
	${filmweb_QT_HEADERS})

add_executable(filmweb ${filmweb_SOURCES} ${filmweb_QT_HEADERS_MOC})

target_link_libraries(filmweb ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Poco_LIBRARIES} ${SQLite3x_LIBRARIES} ${QT_LIBRARIES} dl pthread)