/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_ASYKRAB_EXT_H101_KRAB_H__
#define __GUARD_H101_ASYKRAB_EXT_H101_KRAB_H__

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

typedef struct EXT_STR_h101_ASYKRAB_t
{
    /* RAW */
    uint32_t TIMESTAMP_KRAB_WR_T1 /* [0,65535] */;
    uint32_t TIMESTAMP_KRAB_WR_T2 /* [0,65535] */;
    uint32_t TIMESTAMP_KRAB_WR_T3 /* [0,65535] */;
    uint32_t TIMESTAMP_KRAB_WR_T4 /* [0,65535] */;
    uint32_t KRAB_I /* [0,32] */;
    uint32_t KRAB_Iv[32 EXT_STRUCT_CTRL(KRAB_I)] /* [-1,-1] */;
    uint32_t KRAB_DATA /* [0,32] */;
    uint32_t KRAB_DATAv[32 EXT_STRUCT_CTRL(KRAB_DATA)] /* [-1,-1] */;

} EXT_STR_h101_ASYKRAB;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_ASYKRAB_onion_t
{
    /* RAW */
    uint32_t TIMESTAMP_KRAB_WR_T[4];
    uint32_t KRAB_I;
    uint32_t KRAB_Iv[32 /* KRAB_I */];
    uint32_t KRAB_DATA;
    uint32_t KRAB_DATAv[32 /* KRAB_DATA */];

} EXT_STR_h101_ASYKRAB_onion;

/*******************************************************/

#define EXT_STR_h101_ASYKRAB_ITEMS_INFO(ok, si, offset, struct_t, printerr)                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        ok = 1;                                                                                                        \
        /* RAW */                                                                                                      \
        EXT_STR_ITEM_INFO2_LIM(ok,                                                                                     \
                               si,                                                                                     \
                               offset,                                                                                 \
                               struct_t,                                                                               \
                               printerr,                                                                               \
                               TIMESTAMP_KRAB_WR_T1,                                                                   \
                               UINT32,                                                                                 \
                               "TIMESTAMP_KRAB_WR_T1",                                                                 \
                               65535,                                                                                  \
                               0 /*flags*/);                                                                           \
        EXT_STR_ITEM_INFO2_LIM(ok,                                                                                     \
                               si,                                                                                     \
                               offset,                                                                                 \
                               struct_t,                                                                               \
                               printerr,                                                                               \
                               TIMESTAMP_KRAB_WR_T2,                                                                   \
                               UINT32,                                                                                 \
                               "TIMESTAMP_KRAB_WR_T2",                                                                 \
                               65535,                                                                                  \
                               0 /*flags*/);                                                                           \
        EXT_STR_ITEM_INFO2_LIM(ok,                                                                                     \
                               si,                                                                                     \
                               offset,                                                                                 \
                               struct_t,                                                                               \
                               printerr,                                                                               \
                               TIMESTAMP_KRAB_WR_T3,                                                                   \
                               UINT32,                                                                                 \
                               "TIMESTAMP_KRAB_WR_T3",                                                                 \
                               65535,                                                                                  \
                               0 /*flags*/);                                                                           \
        EXT_STR_ITEM_INFO2_LIM(ok,                                                                                     \
                               si,                                                                                     \
                               offset,                                                                                 \
                               struct_t,                                                                               \
                               printerr,                                                                               \
                               TIMESTAMP_KRAB_WR_T4,                                                                   \
                               UINT32,                                                                                 \
                               "TIMESTAMP_KRAB_WR_T4",                                                                 \
                               65535,                                                                                  \
                               0 /*flags*/);                                                                           \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, KRAB_I, UINT32, "KRAB_I", 32, 0 /*flags*/);         \
        EXT_STR_ITEM_INFO2_ZZP(ok, si, offset, struct_t, printerr, KRAB_Iv, UINT32, "KRAB_Iv", "KRAB_I", 0 /*flags*/); \
        EXT_STR_ITEM_INFO2_LIM(ok, si, offset, struct_t, printerr, KRAB_DATA, UINT32, "KRAB_DATA", 32, 0 /*flags*/);   \
        EXT_STR_ITEM_INFO2_ZZP(                                                                                        \
            ok, si, offset, struct_t, printerr, KRAB_DATAv, UINT32, "KRAB_DATAv", "KRAB_DATA", 0 /*flags*/);           \
                                                                                                                       \
    } while (0);

#endif /*__GUARD_H101_ASYKRAB_EXT_H101_KRAB_H__*/

/*******************************************************/
