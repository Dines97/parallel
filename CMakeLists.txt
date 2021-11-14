cmake_minimum_required(VERSION 3.16.3)
project(parallel)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP REQUIRED)

file(GLOB FILE_NAMES *.cpp)
foreach (file_name ${FILE_NAMES})
	get_filename_component(executable_name ${file_name} NAME_WE)
	add_executable(${executable_name} ${file_name})

	target_link_libraries(${executable_name} PRIVATE OpenMP::OpenMP_CXX)
endforeach (file_name ${FILE_NAMES})
