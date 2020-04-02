find_path(CONDUIT_INCLUDE_DIRS NAMES conduit.hpp HINTS ${CONDUIT_DIR}/include/conduit)

set(CONDUIT_LIBS_LIST
  conduit
  conduit_blueprint
  conduit_relay)

set(CONDUIT_LIBRARIES)
foreach (LIB ${CONDUIT_LIBS_LIST})
  find_library(CONDUIT_LIB_${LIB}
    NAMES ${LIB}
    HINTS ${CONDUIT_DIR}/lib)

  if (CONDUIT_LIB_${LIB})
    set(CONDUIT_LIBRARIES ${CONDUIT_LIBRARIES} ${CONDUIT_LIB_${LIB}})
  endif ()
endforeach ()

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CONDUIT DEFAULT_MSG CONDUIT_LIBRARIES CONDUIT_INCLUDE_DIRS)

MARK_AS_ADVANCED(CONDUIT_INCLUDE_DIRS CONDUIT_LIBRARIES)
