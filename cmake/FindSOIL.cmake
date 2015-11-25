# - Try to find SOIL
# Once done this will define
#
# SOIL_FOUND - system has soil
# SOIL_INCLUDE_DIR - the soil include directory
# SOIL_LIBRARIES - libraries needed to use soil
include( FindPackageHandleStandardArgs )
find_path( SOIL_INCLUDE_DIR "SOIL.h" PATH_SUFFIXES SOIL )
find_library( SOIL_LIBRARIES SOIL )
find_package_handle_standard_args(SOIL DEFAULT_MSG SOIL_LIBRARIES SOIL_INCLUDE_DIR )
if ( SOIL_INCLUDE_DIR AND SOIL_LIBRARIES )
	SET( SOIL_FOUND TRUE )
else ()
	SET( SOIL_FOUND FALSE )
endif ()