# Create a library called "libR3BasyData" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
    #cmake-format: sortable
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${R3BROOT_SOURCE_DIR}/r3bdata
    ${R3BROOT_SOURCE_DIR}/r3bdata/califaData
    ${R3BROOT_SOURCE_DIR}/r3bdata/neulandData
    ${R3BASY_SOURCE_DIR}/asydata
    ${R3BASY_SOURCE_DIR}/asydata/chimeraData
    ${R3BASY_SOURCE_DIR}/asydata/krabData
    )

set(SRCS
    chimeraData/R3BAsyChimeraPoint.cxx
    chimeraData/R3BAsyChimeraHitData.cxx
    chimeraData/R3BAsyChimeraMappedData.cxx
    chimeraData/R3BAsyChimeraMatchedData.cxx
    chimeraData/R3BAsyChimeraArrayData.cxx
    chimeraData/R3BAsyChimeraPhysData.cxx
    chimeraData/R3BAsyChimeraIdData.cxx
    chimeraData/R3BAsyChiKrabPhysData.cxx
    krabData/R3BAsyKrabPoint.cxx
    krabData/R3BAsyKrabHitData.cxx
    krabData/R3BAsyKrabMappedData.cxx
    krabData/R3BAsyKrabArrayData.cxx
    krabData/R3BAsyKrabPhysData.cxx
   )

 change_file_extension(*.cxx *.h HEADERS "${SRCS}")

add_library_with_dictionary(
    LIBNAME
    R3BAsyData
    LINKDEF
    R3BAsyDataLinkDef.h
    HEADERS
    ${HEADERS}
    SRCS
    ${SRCS}
    INCLUDEDIRS
    ${INCLUDE_DIRECTORIES}
    DEPENDENCIES
    R3BData 
    R3BBase
    m)
 
