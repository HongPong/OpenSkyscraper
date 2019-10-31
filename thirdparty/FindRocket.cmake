# Locates RmlUi (former libRocket) GUI library
#
# This module defines the following variables:
# - For each module X (core, controls, debugger)
#   - RML_X_LIBRARY
#   - RML_X_FOUND
# - RML_LIBRARIES
# - RML_FOUND
# - RML_INCLUDE_DIR


set(RMLDIR "" CACHE PATH "rml directory")

set(FIND_RML_PATHS
	${RMLDIR}
	#/usr/local
	#/usr
	/sw
	/opt/local
	/opt/csw
	/opt
)

# find the include directory
find_path(
	RML_INCLUDE_DIR Rml/Core.h
	PATH_SUFFIXES include
	HINTS ${FIND_RML_PATHS}
	
)
if (RML_INCLUDE_DIR)
	set(RML_FOUND TRUE)
endif()

# find the components
foreach (component ${Rml_FIND_COMPONENTS})
	# convert the component name to lowercase and capitalized versions
	string(TOUPPER ${component} component_upper)
	string(SUBSTRING ${component} 0  1 component_f)
	string(SUBSTRING ${component} 1 -1 component_r)
	string(TOUPPER ${component_f} component_f)
	string(TOLOWER ${component_r} component_r)
	set(component_cap ${component_f}${component_r})
	
	# try to find the library
	# debug library
    find_library(
		RML_${component_upper}_LIBRARY_DEBUG
		NAMES Rml${component_cap}_d
		PATH_SUFFIXES lib64 lib
		HINTS ${FIND_RML_PATHS}
	)
				 
	# release library
	find_library(
		RML_${component_upper}_LIBRARY_RELEASE
		NAMES Rml${component_cap}
		PATH_SUFFIXES lib64 lib
		HINTS ${FIND_RML_PATHS}
	)
	
	# check whether we've found the library
	if (RML_${component_upper}_LIBRARY_DEBUG OR RML_${component_upper}_LIBRARY_RELEASE)
		set(RML_${component_upper}_FOUND TRUE)
		
		# if both are found, set RML_XXX_LIBRARY to contain both
        if (RML_${component_upper}_LIBRARY_DEBUG AND RML_${component_upper}_LIBRARY_RELEASE)
            set(RML_${component_upper}_LIBRARY debug     ${RML_${component_upper}_LIBRARY_DEBUG}
                                                  optimized ${RML_${component_upper}_LIBRARY_RELEASE})
        endif()

        # if only one debug/release variant is found, set the other to be equal to the found one
        if (RML_${component_upper}_LIBRARY_DEBUG AND NOT RML_${component_upper}_LIBRARY_RELEASE)
            # debug and not release
            set(RML_${component_upper}_LIBRARY_RELEASE ${RML_${component_upper}_LIBRARY_DEBUG})
            set(RML_${component_upper}_LIBRARY         ${RML_${component_upper}_LIBRARY_DEBUG})
        endif()
        if (RML_${component_upper}_LIBRARY_RELEASE AND NOT RML_${component_upper}_LIBRARY_DEBUG)
            # release and not debug
            set(RML_${component_upper}_LIBRARY_DEBUG ${RML_${component_upper}_LIBRARY_RELEASE})
            set(RML_${component_upper}_LIBRARY       ${RML_${component_upper}_LIBRARY_RELEASE})
        endif()
	else()
		set(RML_FOUND FALSE)
		set(RML_${component_upper}_FOUND FALSE)
		set(RML_${component_upper}_LIBRARY "")
		set(FIND_RML_MISSING "${FIND_RML_MISSING} RML_${component_upper}_LIBRARY")
	endif()
	
	# mark as advanced
    MARK_AS_ADVANCED(RML_${component_upper}_LIBRARY
                     RML_${component_upper}_LIBRARY_RELEASE
                     RML_${component_upper}_LIBRARY_DEBUG)
	
	# add to the list of libraries
	set(RML_LIBRARIES ${RML_LIBRARIES} "${RML_${component_upper}_LIBRARY}")
endforeach()

# handle errors
if (NOT RML_FOUND)
	set(FIND_RML_ERROR "Could NOT find Rml (missing: ${FIND_RML_MISSING})")
	if (Rml_FIND_REQUIRED)
		message(FATAL_ERROR ${FIND_RML_ERROR})
	elseif (NOT Rml_FIND_QUIETLY)
		message("${FIND_RML_ERROR}")
	endif()
else()
	message("Found Rml: ${RML_LIBRARIES}")
endif()
