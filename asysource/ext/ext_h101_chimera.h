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
    uint32_t CHIM_S1FRONTDE /* [0,32] */;
    uint32_t CHIM_S1FRONTDEI[32 EXT_STRUCT_CTRL(CHIM_S1FRONTDE)] /* [1,32] */;
    uint32_t CHIM_S1FRONTDEv[32 EXT_STRUCT_CTRL(CHIM_S1FRONTDE)] /* [0,65535] */;
    uint32_t CHIM_S1BACKDE /* [0,32] */;
    uint32_t CHIM_S1BACKDEI[32 EXT_STRUCT_CTRL(CHIM_S1BACKDE)] /* [1,32] */;
    uint32_t CHIM_S1BACKDEv[32 EXT_STRUCT_CTRL(CHIM_S1BACKDE)] /* [0,65535] */;
    uint32_t CHIM_S1BACKTOF /* [0,32] */;
    uint32_t CHIM_S1BACKTOFI[32 EXT_STRUCT_CTRL(CHIM_S1BACKTOF)] /* [1,32] */;
    uint32_t CHIM_S1BACKTOFv[32 EXT_STRUCT_CTRL(CHIM_S1BACKTOF)] /* [0,65535] */;
    uint32_t CHIM_PATTERNCHI /* [0,32] */;
    uint32_t CHIM_PATTERNCHII[32 EXT_STRUCT_CTRL(CHIM_PATTERNCHI)] /* [1,32] */;
    uint32_t CHIM_PATTERNCHIv[32 EXT_STRUCT_CTRL(CHIM_PATTERNCHI)] /* [0,65535] */;
    uint32_t CHIM_FAST /* [0,399] */;
    uint32_t CHIM_FASTI[399 EXT_STRUCT_CTRL(CHIM_FAST)] /* [1,399] */;
    uint32_t CHIM_FASTv[399 EXT_STRUCT_CTRL(CHIM_FAST)] /* [0,65535] */;
    uint32_t CHIM_RG_FAST /* [0,399] */;
    uint32_t CHIM_RG_FASTI[399 EXT_STRUCT_CTRL(CHIM_RG_FAST)] /* [1,399] */;
    uint32_t CHIM_RG_FASTv[399 EXT_STRUCT_CTRL(CHIM_RG_FAST)] /* [0,255] */;
    uint32_t CHIM_RG_SLOW /* [0,399] */;
    uint32_t CHIM_RG_SLOWI[399 EXT_STRUCT_CTRL(CHIM_RG_SLOW)] /* [1,399] */;
    uint32_t CHIM_RG_SLOWv[399 EXT_STRUCT_CTRL(CHIM_RG_SLOW)] /* [0,255] */;
    uint32_t CHIM_RG_SIL /* [0,376] */;
    uint32_t CHIM_RG_SILI[376 EXT_STRUCT_CTRL(CHIM_RG_SIL)] /* [1,376] */;
    uint32_t CHIM_RG_SILv[376 EXT_STRUCT_CTRL(CHIM_RG_SIL)] /* [0,255] */;
    uint32_t CHIM_SLOW /* [0,399] */;
    uint32_t CHIM_SLOWI[399 EXT_STRUCT_CTRL(CHIM_SLOW)] /* [1,399] */;
    uint32_t CHIM_SLOWv[399 EXT_STRUCT_CTRL(CHIM_SLOW)] /* [0,65535] */;
    uint32_t CHIM_TIME /* [0,399] */;
    uint32_t CHIM_TIMEI[399 EXT_STRUCT_CTRL(CHIM_TIME)] /* [1,399] */;
    uint32_t CHIM_TIMEv[399 EXT_STRUCT_CTRL(CHIM_TIME)] /* [0,65535] */;
    uint32_t CHIM_SIL /* [0,376] */;
    uint32_t CHIM_SILI[376 EXT_STRUCT_CTRL(CHIM_SIL)] /* [1,376] */;
    uint32_t CHIM_SILv[376 EXT_STRUCT_CTRL(CHIM_SIL)] /* [0,65535] */;
    uint32_t CHIM_TOFSIL /* [0,376] */;
    uint32_t CHIM_TOFSILI[376 EXT_STRUCT_CTRL(CHIM_TOFSIL)] /* [1,376] */;
    uint32_t CHIM_TOFSILv[376 EXT_STRUCT_CTRL(CHIM_TOFSIL)] /* [0,65535] */;

} EXT_STR_h101_ASYCHIMERA;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_ASYCHIMERA_onion_t
{
    /* RAW */
    struct
    {
        uint32_t FRONTDE;
        uint32_t FRONTDEI[32 /* FRONTDE */];
        uint32_t FRONTDEv[32 /* FRONTDE */];
        uint32_t BACKDE;
        uint32_t BACKDEI[32 /* BACKDE */];
        uint32_t BACKDEv[32 /* BACKDE */];
        uint32_t BACKTOF;
        uint32_t BACKTOFI[32 /* BACKTOF */];
        uint32_t BACKTOFv[32 /* BACKTOF */];
    } CHIM_S[1];
    uint32_t CHIM_PATTERNCHI;
    uint32_t CHIM_PATTERNCHII[32 /* CHIM_PATTERNCHI */];
    uint32_t CHIM_PATTERNCHIv[32 /* CHIM_PATTERNCHI */];
    uint32_t CHIM_FAST;
    uint32_t CHIM_FASTI[399 /* CHIM_FAST */];
    uint32_t CHIM_FASTv[399 /* CHIM_FAST */];
    uint32_t CHIM_RG_FAST;
    uint32_t CHIM_RG_FASTI[399 /* CHIM_RG_FAST */];
    uint32_t CHIM_RG_FASTv[399 /* CHIM_RG_FAST */];
    uint32_t CHIM_RG_SLOW;
    uint32_t CHIM_RG_SLOWI[399 /* CHIM_RG_SLOW */];
    uint32_t CHIM_RG_SLOWv[399 /* CHIM_RG_SLOW */];
    uint32_t CHIM_RG_SIL;
    uint32_t CHIM_RG_SILI[376 /* CHIM_RG_SIL */];
    uint32_t CHIM_RG_SILv[376 /* CHIM_RG_SIL */];
    uint32_t CHIM_SLOW;
    uint32_t CHIM_SLOWI[399 /* CHIM_SLOW */];
    uint32_t CHIM_SLOWv[399 /* CHIM_SLOW */];
    uint32_t CHIM_TIME;
    uint32_t CHIM_TIMEI[399 /* CHIM_TIME */];
    uint32_t CHIM_TIMEv[399 /* CHIM_TIME */];
    uint32_t CHIM_SIL;
    uint32_t CHIM_SILI[376 /* CHIM_SIL */];
    uint32_t CHIM_SILv[376 /* CHIM_SIL */];
    uint32_t CHIM_TOFSIL;
    uint32_t CHIM_TOFSILI[376 /* CHIM_TOFSIL */];
    uint32_t CHIM_TOFSILv[376 /* CHIM_TOFSIL */];

} EXT_STR_h101_ASYCHIMERA_onion;

/*******************************************************/

#define EXT_STR_h101_ASYCHIMERA_ITEMS_INFO(ok, si, offset, struct_t, printerr)                                        \
    do                                                                                                                \
    {                                                                                                                 \
        ok = 1;                                                                                                       \
        /* RAW */                                                                                                     \
        EXT_STR_ITEM_INFO2_LIM(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_S1FRONTDE, UINT32, "CHIM_S1FRONTDE", 32, 0 /*flags*/);           \
        EXT_STR_ITEM_INFO2_ZZP(ok,                                                                                    \
                               si,                                                                                    \
                               offset,                                                                                \
                               struct_t,                                                                              \
                               printerr,                                                                              \
                               CHIM_S1FRONTDEI,                                                                       \
                               UINT32,                                                                                \
                               "CHIM_S1FRONTDEI",                                                                     \
                               "CHIM_S1FRONTDE",                                                                      \
                               0 /*flags*/);                                                                          \
        EXT_STR_ITEM_INFO2_ZZP(ok,                                                                                    \
                               si,                                                                                    \
                               offset,                                                                                \
                               struct_t,                                                                              \
                               printerr,                                                                              \
                               CHIM_S1FRONTDEv,                                                                       \
                               UINT32,                                                                                \
                               "CHIM_S1FRONTDEv",                                                                     \
                               "CHIM_S1FRONTDE",                                                                      \
                               0 /*flags*/);                                                                          \
        EXT_STR_ITEM_INFO2_LIM(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_S1BACKDE, UINT32, "CHIM_S1BACKDE", 32, 0 /*flags*/);             \
        EXT_STR_ITEM_INFO2_ZZP(ok,                                                                                    \
                               si,                                                                                    \
                               offset,                                                                                \
                               struct_t,                                                                              \
                               printerr,                                                                              \
                               CHIM_S1BACKDEI,                                                                        \
                               UINT32,                                                                                \
                               "CHIM_S1BACKDEI",                                                                      \
                               "CHIM_S1BACKDE",                                                                       \
                               0 /*flags*/);                                                                          \
        EXT_STR_ITEM_INFO2_ZZP(ok,                                                                                    \
                               si,                                                                                    \
                               offset,                                                                                \
                               struct_t,                                                                              \
                               printerr,                                                                              \
                               CHIM_S1BACKDEv,                                                                        \
                               UINT32,                                                                                \
                               "CHIM_S1BACKDEv",                                                                      \
                               "CHIM_S1BACKDE",                                                                       \
                               0 /*flags*/);                                                                          \
        EXT_STR_ITEM_INFO2_LIM(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_S1BACKTOF, UINT32, "CHIM_S1BACKTOF", 32, 0 /*flags*/);           \
        EXT_STR_ITEM_INFO2_ZZP(ok,                                                                                    \
                               si,                                                                                    \
                               offset,                                                                                \
                               struct_t,                                                                              \
                               printerr,                                                                              \
                               CHIM_S1BACKTOFI,                                                                       \
                               UINT32,                                                                                \
                               "CHIM_S1BACKTOFI",                                                                     \
                               "CHIM_S1BACKTOF",                                                                      \
                               0 /*flags*/);                                                                          \
        EXT_STR_ITEM_INFO2_ZZP(ok,                                                                                    \
                               si,                                                                                    \
                               offset,                                                                                \
                               struct_t,                                                                              \
                               printerr,                                                                              \
                               CHIM_S1BACKTOFv,                                                                       \
                               UINT32,                                                                                \
                               "CHIM_S1BACKTOFv",                                                                     \
                               "CHIM_S1BACKTOF",                                                                      \
                               0 /*flags*/);                                                                          \
        EXT_STR_ITEM_INFO2_LIM(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_PATTERNCHI, UINT32, "CHIM_PATTERNCHI", 32, 0 /*flags*/);         \
        EXT_STR_ITEM_INFO2_ZZP(ok,                                                                                    \
                               si,                                                                                    \
                               offset,                                                                                \
                               struct_t,                                                                              \
                               printerr,                                                                              \
                               CHIM_PATTERNCHII,                                                                      \
                               UINT32,                                                                                \
                               "CHIM_PATTERNCHII",                                                                    \
                               "CHIM_PATTERNCHI",                                                                     \
                               0 /*flags*/);                                                                          \
        EXT_STR_ITEM_INFO2_ZZP(ok,                                                                                    \
                               si,                                                                                    \
                               offset,                                                                                \
                               struct_t,                                                                              \
                               printerr,                                                                              \
                               CHIM_PATTERNCHIv,                                                                      \
                               UINT32,                                                                                \
                               "CHIM_PATTERNCHIv",                                                                    \
                               "CHIM_PATTERNCHI",                                                                     \
                               0 /*flags*/);                                                                          \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, CHIM_FAST, UINT32, "CHIM_FAST", 399, 0 /*flags*/); \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_FASTI, UINT32, "CHIM_FASTI", "CHIM_FAST", 0 /*flags*/);          \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_FASTv, UINT32, "CHIM_FASTv", "CHIM_FAST", 0 /*flags*/);          \
        EXT_STR_ITEM_INFO2_LIM(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_RG_FAST, UINT32, "CHIM_RG_FAST", 399, 0 /*flags*/);              \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_RG_FASTI, UINT32, "CHIM_RG_FASTI", "CHIM_RG_FAST", 0 /*flags*/); \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_RG_FASTv, UINT32, "CHIM_RG_FASTv", "CHIM_RG_FAST", 0 /*flags*/); \
        EXT_STR_ITEM_INFO2_LIM(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_RG_SLOW, UINT32, "CHIM_RG_SLOW", 399, 0 /*flags*/);              \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_RG_SLOWI, UINT32, "CHIM_RG_SLOWI", "CHIM_RG_SLOW", 0 /*flags*/); \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_RG_SLOWv, UINT32, "CHIM_RG_SLOWv", "CHIM_RG_SLOW", 0 /*flags*/); \
        EXT_STR_ITEM_INFO2_LIM(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_RG_SIL, UINT32, "CHIM_RG_SIL", 376, 0 /*flags*/);                \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_RG_SILI, UINT32, "CHIM_RG_SILI", "CHIM_RG_SIL", 0 /*flags*/);    \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_RG_SILv, UINT32, "CHIM_RG_SILv", "CHIM_RG_SIL", 0 /*flags*/);    \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, CHIM_SLOW, UINT32, "CHIM_SLOW", 399, 0 /*flags*/); \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_SLOWI, UINT32, "CHIM_SLOWI", "CHIM_SLOW", 0 /*flags*/);          \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_SLOWv, UINT32, "CHIM_SLOWv", "CHIM_SLOW", 0 /*flags*/);          \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, CHIM_TIME, UINT32, "CHIM_TIME", 399, 0 /*flags*/); \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_TIMEI, UINT32, "CHIM_TIMEI", "CHIM_TIME", 0 /*flags*/);          \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_TIMEv, UINT32, "CHIM_TIMEv", "CHIM_TIME", 0 /*flags*/);          \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, CHIM_SIL, UINT32, "CHIM_SIL", 376, 0 /*flags*/);   \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_SILI, UINT32, "CHIM_SILI", "CHIM_SIL", 0 /*flags*/);             \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_SILv, UINT32, "CHIM_SILv", "CHIM_SIL", 0 /*flags*/);             \
        EXT_STR_ITEM_INFO2_LIM(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_TOFSIL, UINT32, "CHIM_TOFSIL", 376, 0 /*flags*/);                \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_TOFSILI, UINT32, "CHIM_TOFSILI", "CHIM_TOFSIL", 0 /*flags*/);    \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, CHIM_TOFSILv, UINT32, "CHIM_TOFSILv", "CHIM_TOFSIL", 0 /*flags*/);    \
                                                                                                                      \
    } while (0);

#endif /*__GUARD_H101_ASYCHIMERA_EXT_H101_CHIMERA_H__*/

/*******************************************************/
