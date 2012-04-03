set(EXECUTABLE_OUTPUT_PATH ${filmweb_SOURCE_DIR}/bin)

file (GLOB filmweb_SOURCES *.cpp)

file (GLOB filmweb_HEADERS *.hpp *.h)

qt4_wrap_cpp(filmweb_QT_HEADERS_MOC
	${filmweb_HEADERS})
	
qt4_add_resources(filmweb_RCC "${filmweb_SOURCE_DIR}/resources/resources.qrc")

add_executable(filmweb ${filmweb_SOURCES} ${filmweb_QT_HEADERS_MOC} ${filmweb_RCC})

target_link_libraries(filmweb ${Boost_PROGRAM_OPTIONS_LIBRARY} ${SQLite3x_LIBRARIES} ${QT_LIBRARIES} dl pthread)