# Create a library called  "libR3BAsyChim" which includes the source files given in
# the array.
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
    #cmake-format: sortable
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${R3BROOT_SOURCE_DIR}/r3bbase
    ${R3BROOT_SOURCE_DIR}/r3bdata
    ${R3BROOT_SOURCE_DIR}/tracking
    ${R3BASY_SOURCE_DIR}/asydata
    ${R3BASY_SOURCE_DIR}/asydata/chimeraData
    ${R3BASY_SOURCE_DIR}/chimera
    ${R3BASY_SOURCE_DIR}/chimera/sim
    ${R3BASY_SOURCE_DIR}/chimera/pars
    ${R3BASY_SOURCE_DIR}/chimera/ana
    ${R3BASY_SOURCE_DIR}/krab/ana
    )

    file(
    GLOB 
    SRCS 
    ./sim/*.cxx  
    ./pars/*.cxx 
    ./ana/*.cxx 
    ./ana/TCsIParams.cxx
    ./ana/TCsIIdent.cxx
    ./ana/TCCHIResult.cxx
    ./ana/TCCHICsIEnergy.cxx
    ./ana/TRootCHIEvent.cxx
    ./ana/TRootDefine.cxx
    )

    change_file_extension(*.cxx *.h HEADERS "${SRCS}")
    
    
    
    add_library_with_dictionary(
    LIBNAME
    R3BAsyChim
    LINKDEF
    R3BAsyChimLinkDef.h
    HEADERS
    ${HEADERS}
    SRCS
    ${SRCS}
    INCLUDEDIRS
    ${INCLUDE_DIRECTORIES}
    DEPENDENCIES
    R3BAsyData 
    R3BData 
    R3BBase
    m)


