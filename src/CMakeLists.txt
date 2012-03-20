set(EXECUTABLE_OUTPUT_PATH ${filmweb_SOURCE_DIR}/bin)

add_executable(filmweb main.cpp)

target_link_libraries(filmweb ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Poco_LIBRARIES} ${SQLite3x_LIBRARIES} dl pthread)