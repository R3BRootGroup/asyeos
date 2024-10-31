# The name of our project is “R3BASY”.CMakeLists files in this project can
# refer to the R3BROOT root source directory of the project as ${R3BROOT_SOURCE_DIR},
# the ASYEOS root source directory as ${R3BASY_SOURCE_DIR}(for the asyeos specifics) or
# as ${CMAKE_SOURCE_DIR} and to the root binary directory of the project as
# ${R3BASY_BINARY_DIR} or ${CMAKE_BINARY_DIR}.

# Recurse into the given subdirectories.This does not actually cause
# another cmake executable to run.The same process will walk through
# the project's entire directory structure.

Set(R3BASY_SOURCE_DIR ${R3BROOT_SOURCE_DIR}/asyeos)
message(STATUS "${BBlue}ASYEOS project was FOUND${CR} ")
message("    - ${Cyan}ASYEOS_DIR${CR} = ${BGreen}${R3BASY_SOURCE_DIR}${CR}")

# ASYEOS specific
if(WITH_UCESB) 
   add_subdirectory(asysource) 
endif(WITH_UCESB)
add_subdirectory(chimera)
add_subdirectory(krab)
add_subdirectory(asydata)
add_subdirectory(asyonline)
add_subdirectory(common)
