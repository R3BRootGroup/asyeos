# Create a library called "libR3BAsyOnline" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(SYSTEM_INCLUDE_DIRECTORIES ${SYSTEM_INCLUDE_DIRECTORIES} ${BASE_INCLUDE_DIRECTORIES} )

set(INCLUDE_DIRECTORIES
#put here all directories where header files are located
${R3BROOT_SOURCE_DIR}/r3bbase
${R3BROOT_SOURCE_DIR}/r3bdata
${R3BASY_SOURCE_DIR}/asydata
${R3BASY_SOURCE_DIR}/asydata/chimeraData
${R3BASY_SOURCE_DIR}/asydata/krabData
${R3BASY_SOURCE_DIR}/asyonline
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR} ${FAIRROOT_LIBRARY_DIR} ) 

link_directories( ${LINK_DIRECTORIES})

set(SRCS
R3BAsyChimeraOnlineSpectra.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

set(LINKDEF R3BAsyOnlineLinkDef.h)
set(LIBRARY_NAME R3BAsyOnline)
set(DEPENDENCIES
    Spectrum Base FairTools R3BBase R3BData)

GENERATE_LIBRARY()
