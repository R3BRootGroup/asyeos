# Create a library called "libR3BAsyOnline" which includes the source files given in
# the array. The extension is already found. Any number of sources could be listed here.

set(SRCS
    R3BAsyChimeraOnlineSpectra.cxx
    R3BAsyKrabOnlineSpectra.cxx
    R3BAsyTofDOnlineSpectra.cxx
   )

change_file_extension(*.cxx *.h HEADERS "${SRCS}")

add_library_with_dictionary(
    LIBNAME
    R3BAsyOnline
    LINKDEF
    R3BAsyOnlineLinkDef.h
    HEADERS
    ${HEADERS}
    SRCS
    ${SRCS}
    INCLUDEDIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDENCIES
    R3BAsyData 
    Spectrum 
    R3BBase 
    R3BData
    R3BTracking
    R3BTCal
    R3BTofD)
