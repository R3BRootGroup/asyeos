/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_ASYCHIMERA_EXT_H101_CHIMERA_H__
#define __GUARD_H101_ASYCHIMERA_EXT_H101_CHIMERA_H__

#ifndef __CINT__
#include <stdint.h>
#else
/* For CINT (old version trouble with stdint.h): */
#ifndef uint32_t
typedef unsigned int uint32_t;
typedef int int32_t;
#endif
#endif
#ifndef EXT_STRUCT_CTRL
#define EXT_STRUCT_CTRL(x)
#endif

/********************************************************
 *
 * Plain structure (layout as ntuple/root file):
 */

typedef struct EXT_STR_h101_ASYCHIMERA_t
{
    /* RAW */
    uint32_t TIMESTAMP_CHIMERA_ID /* [0,65535] */;
    uint32_t TIMESTAMP_CHIMERA_WR_T1 /* [0,65535] */;
    uint32_t TIMESTAMP_CHIMERA_WR_T2 /* [0,65535] */;
    uint32_t TIMESTAMP_CHIMERA_WR_T3 /* [0,65535] */;
    uint32_t TIMESTAMP_CHIMERA_WR_T4 /* [0,65535] */;
    uint32_t SYNC_CHECK_CHIMERA /* [0,65535] */;
    uint32_t SYNC_CHECK_CHIMERARR /* [0,65535] */;
    uint32_t S1FRONTDE /* [0,32] */;
    uint32_t S1FRONTDEI[32 EXT_STRUCT_CTRL(S1FRONTDE)] /* [1,32] */;
    uint32_t S1FRONTDEv[32 EXT_STRUCT_CTRL(S1FRONTDE)] /* [0,65535] */;
    uint32_t S1BACKDE /* [0,32] */;
    uint32_t S1BACKDEI[32 EXT_STRUCT_CTRL(S1BACKDE)] /* [1,32] */;
    uint32_t S1BACKDEv[32 EXT_STRUCT_CTRL(S1BACKDE)] /* [0,65535] */;
    uint32_t S1FRONTTOF /* [0,32] */;
    uint32_t S1FRONTTOFI[32 EXT_STRUCT_CTRL(S1FRONTTOF)] /* [1,32] */;
    uint32_t S1FRONTTOFv[32 EXT_STRUCT_CTRL(S1FRONTTOF)] /* [0,65535] */;
    uint32_t S1BACKTOF /* [0,32] */;
    uint32_t S1BACKTOFI[32 EXT_STRUCT_CTRL(S1BACKTOF)] /* [1,32] */;
    uint32_t S1BACKTOFv[32 EXT_STRUCT_CTRL(S1BACKTOF)] /* [0,65535] */;
    uint32_t S2FRONTDE /* [0,32] */;
    uint32_t S2FRONTDEI[32 EXT_STRUCT_CTRL(S2FRONTDE)] /* [1,32] */;
    uint32_t S2FRONTDEv[32 EXT_STRUCT_CTRL(S2FRONTDE)] /* [0,65535] */;
    uint32_t S2BACKDE /* [0,32] */;
    uint32_t S2BACKDEI[32 EXT_STRUCT_CTRL(S2BACKDE)] /* [1,32] */;
    uint32_t S2BACKDEv[32 EXT_STRUCT_CTRL(S2BACKDE)] /* [0,65535] */;
    uint32_t S2FRONTTOF /* [0,32] */;
    uint32_t S2FRONTTOFI[32 EXT_STRUCT_CTRL(S2FRONTTOF)] /* [1,32] */;
    uint32_t S2FRONTTOFv[32 EXT_STRUCT_CTRL(S2FRONTTOF)] /* [0,65535] */;
    uint32_t S2BACKTOF /* [0,32] */;
    uint32_t S2BACKTOFI[32 EXT_STRUCT_CTRL(S2BACKTOF)] /* [1,32] */;
    uint32_t S2BACKTOFv[32 EXT_STRUCT_CTRL(S2BACKTOF)] /* [0,65535] */;
    uint32_t PATTERNCHI /* [0,32] */;
    uint32_t PATTERNCHII[32 EXT_STRUCT_CTRL(PATTERNCHI)] /* [1,32] */;
    uint32_t PATTERNCHIv[32 EXT_STRUCT_CTRL(PATTERNCHI)] /* [0,65535] */;

} EXT_STR_h101_ASYCHIMERA;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_ASYCHIMERA_onion_t
{
    /* RAW */
    uint32_t TIMESTAMP_CHIMERA_ID;
    uint32_t TIMESTAMP_CHIMERA_WR_T[4];
    uint32_t SYNC_CHECK_CHIMERA;
    uint32_t SYNC_CHECK_CHIMERARR;
    struct
    {
        uint32_t FRONTDE;
        uint32_t FRONTDEI[32 /* FRONTDE */];
        uint32_t FRONTDEv[32 /* FRONTDE */];
        uint32_t BACKDE;
        uint32_t BACKDEI[32 /* BACKDE */];
        uint32_t BACKDEv[32 /* BACKDE */];
        uint32_t FRONTTOF;
        uint32_t FRONTTOFI[32 /* FRONTTOF */];
        uint32_t FRONTTOFv[32 /* FRONTTOF */];
        uint32_t BACKTOF;
        uint32_t BACKTOFI[32 /* BACKTOF */];
        uint32_t BACKTOFv[32 /* BACKTOF */];
    } S[2];
    uint32_t PATTERNCHI;
    uint32_t PATTERNCHII[32 /* PATTERNCHI */];
    uint32_t PATTERNCHIv[32 /* PATTERNCHI */];

} EXT_STR_h101_ASYCHIMERA_onion;

/*******************************************************/

#define EXT_STR_h101_ASYCHIMERA_ITEMS_INFO(ok, si, offset, struct_t, printerr)                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        ok = 1;                                                                                                        \
        /* RAW */                                                                                                      \
        EXT_STR_ITEM_INFO2_LIM(ok,                                                                                     \
                               si,                                                                                     \
                               offset,                                                                                 \
                               struct_t,                                                                               \
                               printerr,                                                                               \
                               TIMESTAMP_CHIMERA_ID,                                                                   \
                               UINT32,                                                                                 \
                               "TIMESTAMP_CHIMERA_ID",                                                                 \
                               65535,                                                                                  \
                               0 /*flags*/);                                                                           \
        EXT_STR_ITEM_INFO2_LIM(ok,                                                                                     \
                               si,                                                                                     \
                               offset,                                                                                 \
                               struct_t,                                                                               \
                               printerr,                                                                               \
                               TIMESTAMP_CHIMERA_WR_T1,                                                                \
                               UINT32,                                                                                 \
                               "TIMESTAMP_CHIMERA_WR_T1",                                                              \
                               65535,                                                                                  \
                               0 /*flags*/);                                                                           \
        EXT_STR_ITEM_INFO2_LIM(ok,                                                                                     \
                               si,                                                                                     \
                               offset,                                                                                 \
                               struct_t,                                                                               \
                               printerr,                                                                               \
                               TIMESTAMP_CHIMERA_WR_T2,                                                                \
                               UINT32,                                                                                 \
                               "TIMESTAMP_CHIMERA_WR_T2",                                                              \
                               65535,                                                                                  \
                               0 /*flags*/);                                                                           \
        EXT_STR_ITEM_INFO2_LIM(ok,                                                                                     \
                               si,                                                                                     \
                               offset,                                                                                 \
                               struct_t,                                                                               \
                               printerr,                                                                               \
                               TIMESTAMP_CHIMERA_WR_T3,                                                                \
                               UINT32,                                                                                 \
                               "TIMESTAMP_CHIMERA_WR_T3",                                                              \
                               65535,                                                                                  \
                               0 /*flags*/);                                                                           \
        EXT_STR_ITEM_INFO2_LIM(ok,                                                                                     \
                               si,                                                                                     \
                               offset,                                                                                 \
                               struct_t,                                                                               \
                               printerr,                                                                               \
                               TIMESTAMP_CHIMERA_WR_T4,                                                                \
                               UINT32,                                                                                 \
                               "TIMESTAMP_CHIMERA_WR_T4",                                                              \
                               65535,                                                                                  \
                               0 /*flags*/);                                                                           \
        EXT_STR_ITEM_INFO2_LIM(                                                                                        \
            ok, si, offset, struct_t, printerr, SYNC_CHECK_CHIMERA, UINT32, "SYNC_CHECK_CHIMERA", 65535, 0 /*flags*/); \
        EXT_STR_ITEM_INFO2_LIM(ok,                                                                                     \
                               si,                                                                                     \
                               offset,                                                                                 \
                               struct_t,                                                                               \
                               printerr,                                                                               \
                               SYNC_CHECK_CHIMERARR,                                                                   \
                               UINT32,                                                                                 \
                               "SYNC_CHECK_CHIMERARR",                                                                 \
                               65535,                                                                                  \
                               0 /*flags*/);                                                                           \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, S1FRONTDE, UINT32, "S1FRONTDE", 32, 0 /*flags*/);   \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S1FRONTDEI, UINT32, "S1FRONTDEI", "S1FRONTDE", 0 /*flags*/);           \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S1FRONTDEv, UINT32, "S1FRONTDEv", "S1FRONTDE", 0 /*flags*/);           \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, S1BACKDE, UINT32, "S1BACKDE", 32, 0 /*flags*/);     \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S1BACKDEI, UINT32, "S1BACKDEI", "S1BACKDE", 0 /*flags*/);              \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S1BACKDEv, UINT32, "S1BACKDEv", "S1BACKDE", 0 /*flags*/);              \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, S1FRONTTOF, UINT32, "S1FRONTTOF", 32, 0 /*flags*/); \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S1FRONTTOFI, UINT32, "S1FRONTTOFI", "S1FRONTTOF", 0 /*flags*/);        \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S1FRONTTOFv, UINT32, "S1FRONTTOFv", "S1FRONTTOF", 0 /*flags*/);        \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, S1BACKTOF, UINT32, "S1BACKTOF", 32, 0 /*flags*/);   \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S1BACKTOFI, UINT32, "S1BACKTOFI", "S1BACKTOF", 0 /*flags*/);           \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S1BACKTOFv, UINT32, "S1BACKTOFv", "S1BACKTOF", 0 /*flags*/);           \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, S2FRONTDE, UINT32, "S2FRONTDE", 32, 0 /*flags*/);   \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S2FRONTDEI, UINT32, "S2FRONTDEI", "S2FRONTDE", 0 /*flags*/);           \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S2FRONTDEv, UINT32, "S2FRONTDEv", "S2FRONTDE", 0 /*flags*/);           \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, S2BACKDE, UINT32, "S2BACKDE", 32, 0 /*flags*/);     \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S2BACKDEI, UINT32, "S2BACKDEI", "S2BACKDE", 0 /*flags*/);              \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S2BACKDEv, UINT32, "S2BACKDEv", "S2BACKDE", 0 /*flags*/);              \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, S2FRONTTOF, UINT32, "S2FRONTTOF", 32, 0 /*flags*/); \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S2FRONTTOFI, UINT32, "S2FRONTTOFI", "S2FRONTTOF", 0 /*flags*/);        \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S2FRONTTOFv, UINT32, "S2FRONTTOFv", "S2FRONTTOF", 0 /*flags*/);        \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, S2BACKTOF, UINT32, "S2BACKTOF", 32, 0 /*flags*/);   \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S2BACKTOFI, UINT32, "S2BACKTOFI", "S2BACKTOF", 0 /*flags*/);           \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, S2BACKTOFv, UINT32, "S2BACKTOFv", "S2BACKTOF", 0 /*flags*/);           \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, PATTERNCHI, UINT32, "PATTERNCHI", 32, 0 /*flags*/); \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, PATTERNCHII, UINT32, "PATTERNCHII", "PATTERNCHI", 0 /*flags*/);        \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, PATTERNCHIv, UINT32, "PATTERNCHIv", "PATTERNCHI", 0 /*flags*/);        \
                                                                                                                       \
    } while (0);

#endif /*__GUARD_H101_ASYCHIMERA_EXT_H101_CHIMERA_H__*/

/*******************************************************/
