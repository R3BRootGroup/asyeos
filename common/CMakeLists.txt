# Create a library called  "libR3BAsyCommon" which includes the source files given in
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
    ${R3BASY_SOURCE_DIR}/asydata/krabData
    ${R3BASY_SOURCE_DIR}/common
    ${R3BASY_SOURCE_DIR}/common/ana
    ${R3BROOT_SOURCE_DIR}/neuland
    )


set(SRCS
##Put here your sourcefiles
    ana/R3BAsyCommonAna.cxx
    ana/R3BAsyCommonAnaNC.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
change_file_extension(*.cxx *.h HEADERS "${SRCS}")

add_library_with_dictionary(
    LIBNAME
    R3BAsyCommon
    LINKDEF
    R3BAsyCommonLinkDef.h
    HEADERS
    ${HEADERS}
    SRCS
    ${SRCS}
    INCLUDEDIRS
    ${INCLUDE_DIRECTORIES}
    DEPENDENCIES
    R3BBase 
    R3BData 
    R3BAsyData)
