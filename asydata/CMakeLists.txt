# Create a library called "libR3BasyData" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(SYSTEM_INCLUDE_DIRECTORIES ${SYSTEM_INCLUDE_DIRECTORIES} ${BASE_INCLUDE_DIRECTORIES} )

set(INCLUDE_DIRECTORIES
${R3BROOT_SOURCE_DIR}/r3bdata
${R3BROOT_SOURCE_DIR}/r3bdata/califaData
${R3BROOT_SOURCE_DIR}/r3bdata/neulandData
${R3BASY_SOURCE_DIR}/asydata
${R3BASY_SOURCE_DIR}/asydata/chimeraData
${R3BASY_SOURCE_DIR}/asydata/krabData
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR} ${FAIRROOT_LIBRARY_DIR} )

link_directories( ${LINK_DIRECTORIES})

set(SRCS
chimeraData/R3BAsyChimeraPoint.cxx
chimeraData/R3BAsyChimeraHitData.cxx
chimeraData/R3BAsyChimeraMappedData.cxx
chimeraData/R3BAsyChimeraArrayData.cxx
krabData/R3BAsyKrabPoint.cxx
krabData/R3BAsyKrabHitData.cxx
krabData/R3BAsyKrabMappedData.cxx
krabData/R3BAsyKrabArrayData.cxx
)


# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")
SET(HEADERS ${HEADERS} ${R3BROOT_SOURCE_DIR}/r3bdata/R3BDetectorList.h)

set(LINKDEF  R3BAsyDataLinkDef.h)
set(LIBRARY_NAME R3BAsyData)
set(DEPENDENCIES
    Base FairTools R3BData R3BBase Core m)

GENERATE_LIBRARY()
