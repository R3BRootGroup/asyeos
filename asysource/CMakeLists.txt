##############################################################################
#   Copyright (C) 2022 GSI Helmholtzzentrum für Schwerionenforschung GmbH    #
#   Copyright (C) 2022-2026 Members of R3B Collaboration                     #
#                                                                            #
#             This software is distributed under the terms of the            #
#                 GNU General Public Licence (GPL) version 3,                #
#                    copied verbatim in the file "LICENSE".                  #
#                                                                            #
# In applying this license GSI does not waive the privileges and immunities  #
# granted to it by virtue of its status as an Intergovernmental Organization #
# or submit itself to any jurisdiction.                                      #
##############################################################################

# Create a library called "libR3BAsysource" which includes the source files given in
# the array. The extension is already found. Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
    #cmake-format: sortable
    ${CMAKE_CURRENT_SOURCE_DIR}
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

    set(SRCS
    R3BAsyChimeraReader.cxx
    R3BAsyKrabReader.cxx
    )
    
    set(STRUCT_HEADERS
    ext/ext_h101_chimera.h
    ext/ext_h101_krab.h
    )

    set(HEADERS
    R3BAsyChimeraReader.h
    R3BAsyKrabReader.h
    )

    set(HEADERS ${STRUCT_HEADERS} ${HEADERS})

    add_library_with_dictionary(
    LIBNAME
    R3BAsySource
    LINKDEF
    R3BAsySourceLinkDef.h
    HEADERS
    ${HEADERS}
    SRCS
    ${SRCS}
    INCLUDEDIRS
    ${INCLUDE_DIRECTORIES}
    DEPENDENCIES
    R3BBase 
    R3BData 
    R3BSource
    R3BAsyData)

