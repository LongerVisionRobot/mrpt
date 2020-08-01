include(../../cmakemodules/AssureCMakeRootFile.cmake) # Avoid user mistake in CMake source directory

# ----------------------------------------------------------------------------
#  Auxiliary static library: gtest (Google test framework)
#   Used in mrpt-* libraries for Unit Testing
# ----------------------------------------------------------------------------

project(mrptgtest)

# Fix a "bug" in VS11 (MSVC 2012):
if(MSVC)
	add_definitions(-D_VARIADIC_MAX=10)
endif(MSVC)

include_directories("include")
include_directories(".")

add_library(${PROJECT_NAME}
	STATIC
	src/gtest-all.cc
	)

mrpt_lib_target_requires_cpp17(${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if (UNIX AND MRPT_COMPILER_IS_GCC_OR_CLANG)
	target_compile_options(${PROJECT_NAME} PRIVATE "-fPIC")
endif()



set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "3rd party")
