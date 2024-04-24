# Create a library called "libR3BAsysource" which includes the source files given in
# the array. The extension is already found. Any number of sources could be listed here.

set(SYSTEM_INCLUDE_DIRECTORIES ${SYSTEM_INCLUDE_DIRECTORIES} ${BASE_INCLUDE_DIRECTORIES} ${ucesb_INCLUDE_DIR} )

set(INCLUDE_DIRECTORIES
#put here all directories where header files are located
${R3BROOT_SOURCE_DIR}/r3bsource
${R3BROOT_SOURCE_DIR}/r3bsource/base
${R3BROOT_SOURCE_DIR}/r3bsource/base/utils
${R3BROOT_SOURCE_DIR}/r3bbase
${R3BROOT_SOURCE_DIR}/r3bdata/wrData
${R3BASY_SOURCE_DIR}/asydata
${R3BASY_SOURCE_DIR}/asydata/chimeraData
${R3BASY_SOURCE_DIR}/asydata/krabData
${R3BASY_SOURCE_DIR}/asysource
${R3BASY_SOURCE_DIR}/asysource/ext
)

set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR} ${FAIRROOT_LIBRARY_DIR} ${ucesb_LIBRARY_DIR} )

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})
link_directories( ${LINK_DIRECTORIES})

#file(GLOB SRCS *.cxx)

set(SRCS
R3BAsyChimeraReader.cxx
R3BAsyKrabReader.cxx
)

Set(STRUCT_HEADERS
ext/ext_h101_chimera.h
ext/ext_h101_krab.h
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")
Set(HEADERS ${STRUCT_HEADERS} ${HEADERS})

set(LINKDEF R3BAsySourceLinkDef.h)
set(DEPENDENCIES
    R3BBase Base R3BAsyData R3Bsource ${ucesb_LIBRARY_SHARED} FairTools)
set(LIBRARY_NAME R3BAsySource)

GENERATE_LIBRARY()
