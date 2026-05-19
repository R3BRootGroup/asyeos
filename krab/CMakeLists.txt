# Create a library called  "libR3BAsyKrab" which includes the source files given in
# the array.
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
    #cmake-format: sortable
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${R3BROOT_SOURCE_DIR}/r3bbase
    ${R3BROOT_SOURCE_DIR}/r3bdata
    ${R3BROOT_SOURCE_DIR}/tracking
    ${R3BASY_SOURCE_DIR}/asydata
    ${R3BASY_SOURCE_DIR}/asydata/krabData
    ${R3BASY_SOURCE_DIR}/krab
    ${R3BASY_SOURCE_DIR}/krab/sim
    ${R3BASY_SOURCE_DIR}/krab/pars
    ${R3BASY_SOURCE_DIR}/krab/ana
    )

    file(
    GLOB 
    SRCS 
    ./sim/*.cxx  
    ./pars/*.cxx 
    ./ana/*.cxx )

    change_file_extension(*.cxx *.h HEADERS "${SRCS}")
    
    add_library_with_dictionary(
    LIBNAME
    R3BAsyKrab
    LINKDEF
    R3BAsyKrabLinkDef.h
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
