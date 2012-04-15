project (plugins)

include_directories("${titled_SOURCE_DIR}/src")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${titled_BINARY_DIR}/bin/plugins)

file (GLOB sub-dir *)
foreach (dir ${sub-dir})
	if (IS_DIRECTORY ${dir})
		add_subdirectory(${dir})
	endif ()
endforeach ()