/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_ASYCHIMERA_EXT_H101_CHIMERA_H__
#define __GUARD_H101_ASYCHIMERA_EXT_H101_CHIMERA_H__

#ifndef __CINT__
# include <stdint.h>
#else
/* For CINT (old version trouble with stdint.h): */
# ifndef uint32_t
typedef unsigned int uint32_t;
typedef          int  int32_t;
# endif
#endif
#ifndef EXT_STRUCT_CTRL
# define EXT_STRUCT_CTRL(x)
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
  uint32_t CHIM_S1FRONTDE /* [0,32] */;
  uint32_t CHIM_S1FRONTDEI[32 EXT_STRUCT_CTRL(CHIM_S1FRONTDE)] /* [1,32] */;
  uint32_t CHIM_S1FRONTDEv[32 EXT_STRUCT_CTRL(CHIM_S1FRONTDE)] /* [0,65535] */;
  uint32_t CHIM_S1BACKDE /* [0,32] */;
  uint32_t CHIM_S1BACKDEI[32 EXT_STRUCT_CTRL(CHIM_S1BACKDE)] /* [1,32] */;
  uint32_t CHIM_S1BACKDEv[32 EXT_STRUCT_CTRL(CHIM_S1BACKDE)] /* [0,65535] */;
  uint32_t CHIM_S1FRONTTOF /* [0,32] */;
  uint32_t CHIM_S1FRONTTOFI[32 EXT_STRUCT_CTRL(CHIM_S1FRONTTOF)] /* [1,32] */;
  uint32_t CHIM_S1FRONTTOFv[32 EXT_STRUCT_CTRL(CHIM_S1FRONTTOF)] /* [0,65535] */;
  uint32_t CHIM_S1BACKTOF /* [0,32] */;
  uint32_t CHIM_S1BACKTOFI[32 EXT_STRUCT_CTRL(CHIM_S1BACKTOF)] /* [1,32] */;
  uint32_t CHIM_S1BACKTOFv[32 EXT_STRUCT_CTRL(CHIM_S1BACKTOF)] /* [0,65535] */;
  uint32_t CHIM_S2FRONTDE /* [0,32] */;
  uint32_t CHIM_S2FRONTDEI[32 EXT_STRUCT_CTRL(CHIM_S2FRONTDE)] /* [1,32] */;
  uint32_t CHIM_S2FRONTDEv[32 EXT_STRUCT_CTRL(CHIM_S2FRONTDE)] /* [0,65535] */;
  uint32_t CHIM_S2BACKDE /* [0,32] */;
  uint32_t CHIM_S2BACKDEI[32 EXT_STRUCT_CTRL(CHIM_S2BACKDE)] /* [1,32] */;
  uint32_t CHIM_S2BACKDEv[32 EXT_STRUCT_CTRL(CHIM_S2BACKDE)] /* [0,65535] */;
  uint32_t CHIM_S2FRONTTOF /* [0,32] */;
  uint32_t CHIM_S2FRONTTOFI[32 EXT_STRUCT_CTRL(CHIM_S2FRONTTOF)] /* [1,32] */;
  uint32_t CHIM_S2FRONTTOFv[32 EXT_STRUCT_CTRL(CHIM_S2FRONTTOF)] /* [0,65535] */;
  uint32_t CHIM_S2BACKTOF /* [0,32] */;
  uint32_t CHIM_S2BACKTOFI[32 EXT_STRUCT_CTRL(CHIM_S2BACKTOF)] /* [1,32] */;
  uint32_t CHIM_S2BACKTOFv[32 EXT_STRUCT_CTRL(CHIM_S2BACKTOF)] /* [0,65535] */;
  uint32_t CHIM_PATTERNCHI /* [0,32] */;
  uint32_t CHIM_PATTERNCHII[32 EXT_STRUCT_CTRL(CHIM_PATTERNCHI)] /* [1,32] */;
  uint32_t CHIM_PATTERNCHIv[32 EXT_STRUCT_CTRL(CHIM_PATTERNCHI)] /* [0,65535] */;

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
  struct {
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
  } CHIM_S[2];
  uint32_t CHIM_PATTERNCHI;
  uint32_t CHIM_PATTERNCHII[32 /* CHIM_PATTERNCHI */];
  uint32_t CHIM_PATTERNCHIv[32 /* CHIM_PATTERNCHI */];

} EXT_STR_h101_ASYCHIMERA_onion;

/*******************************************************/

#define EXT_STR_h101_ASYCHIMERA_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* RAW */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TIMESTAMP_CHIMERA_ID,            UINT32,\
                    "TIMESTAMP_CHIMERA_ID",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TIMESTAMP_CHIMERA_WR_T1,         UINT32,\
                    "TIMESTAMP_CHIMERA_WR_T1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TIMESTAMP_CHIMERA_WR_T2,         UINT32,\
                    "TIMESTAMP_CHIMERA_WR_T2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TIMESTAMP_CHIMERA_WR_T3,         UINT32,\
                    "TIMESTAMP_CHIMERA_WR_T3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TIMESTAMP_CHIMERA_WR_T4,         UINT32,\
                    "TIMESTAMP_CHIMERA_WR_T4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SYNC_CHECK_CHIMERA,              UINT32,\
                    "SYNC_CHECK_CHIMERA",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SYNC_CHECK_CHIMERARR,            UINT32,\
                    "SYNC_CHECK_CHIMERARR",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     CHIM_S1FRONTDE,                       UINT32,\
                    "CHIM_S1FRONTDE",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S1FRONTDEI,                      UINT32,\
                    "CHIM_S1FRONTDEI",                      "CHIM_S1FRONTDE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S1FRONTDEv,                      UINT32,\
                    "CHIM_S1FRONTDEv",                      "CHIM_S1FRONTDE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     CHIM_S1BACKDE,                        UINT32,\
                    "CHIM_S1BACKDE",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S1BACKDEI,                       UINT32,\
                    "CHIM_S1BACKDEI",                       "CHIM_S1BACKDE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S1BACKDEv,                       UINT32,\
                    "CHIM_S1BACKDEv",                       "CHIM_S1BACKDE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     CHIM_S1FRONTTOF,                      UINT32,\
                    "CHIM_S1FRONTTOF",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S1FRONTTOFI,                     UINT32,\
                    "CHIM_S1FRONTTOFI",                     "CHIM_S1FRONTTOF",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S1FRONTTOFv,                     UINT32,\
                    "CHIM_S1FRONTTOFv",                     "CHIM_S1FRONTTOF",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     CHIM_S1BACKTOF,                       UINT32,\
                    "CHIM_S1BACKTOF",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S1BACKTOFI,                      UINT32,\
                    "CHIM_S1BACKTOFI",                      "CHIM_S1BACKTOF",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S1BACKTOFv,                      UINT32,\
                    "CHIM_S1BACKTOFv",                      "CHIM_S1BACKTOF",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     CHIM_S2FRONTDE,                       UINT32,\
                    "CHIM_S2FRONTDE",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S2FRONTDEI,                      UINT32,\
                    "CHIM_S2FRONTDEI",                      "CHIM_S2FRONTDE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S2FRONTDEv,                      UINT32,\
                    "CHIM_S2FRONTDEv",                      "CHIM_S2FRONTDE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     CHIM_S2BACKDE,                        UINT32,\
                    "CHIM_S2BACKDE",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S2BACKDEI,                       UINT32,\
                    "CHIM_S2BACKDEI",                       "CHIM_S2BACKDE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S2BACKDEv,                       UINT32,\
                    "CHIM_S2BACKDEv",                       "CHIM_S2BACKDE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     CHIM_S2FRONTTOF,                      UINT32,\
                    "CHIM_S2FRONTTOF",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S2FRONTTOFI,                     UINT32,\
                    "CHIM_S2FRONTTOFI",                     "CHIM_S2FRONTTOF",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S2FRONTTOFv,                     UINT32,\
                    "CHIM_S2FRONTTOFv",                     "CHIM_S2FRONTTOF",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     CHIM_S2BACKTOF,                       UINT32,\
                    "CHIM_S2BACKTOF",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S2BACKTOFI,                      UINT32,\
                    "CHIM_S2BACKTOFI",                      "CHIM_S2BACKTOF",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_S2BACKTOFv,                      UINT32,\
                    "CHIM_S2BACKTOFv",                      "CHIM_S2BACKTOF",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     CHIM_PATTERNCHI,                      UINT32,\
                    "CHIM_PATTERNCHI",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_PATTERNCHII,                     UINT32,\
                    "CHIM_PATTERNCHII",                     "CHIM_PATTERNCHI",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     CHIM_PATTERNCHIv,                     UINT32,\
                    "CHIM_PATTERNCHIv",                     "CHIM_PATTERNCHI",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_ASYCHIMERA_EXT_H101_CHIMERA_H__*/

/*******************************************************/
