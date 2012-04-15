project (FilmwebProvider)

file (GLOB plugin_SOURCES "${dir}/*.cpp")
file (GLOB plugin_HEADERS "${dir}/*.hpp" "${dir}/*.h")

qt4_wrap_cpp (plugin_QT_HEADERS_MOC ${plugin_HEADERS})

ADD_LIBRARY(FilmwebProvider MODULE ${plugin_SOURCES} ${plugin_QT_HEADERS_MOC})