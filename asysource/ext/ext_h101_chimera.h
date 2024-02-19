/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_ASYCHIMERA_EXT_H101_H__
#define __GUARD_H101_ASYCHIMERA_EXT_H101_H__

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
  /* INFO */
  uint32_t TRIGGER /* [0,15] */;
  uint32_t EVENTNO /* [-1,-1] */;
  uint32_t TSTAMPLO /* [-1,-1] */;
  uint32_t TSTAMPHI /* [-1,-1] */;
  uint32_t TSTAMPSRCID /* [-1,-1] */;
  uint32_t MERGE_STATUS /* [-1,-1] */;
  uint32_t MERGE_IDMASK /* [-1,-1] */;
  /* RAW */
  uint32_t TIMESTAMP_MASTER_ID /* [0,65535] */;
  uint32_t TIMESTAMP_MASTER_WR_T1 /* [0,65535] */;
  uint32_t TIMESTAMP_MASTER_WR_T2 /* [0,65535] */;
  uint32_t TIMESTAMP_MASTER_WR_T3 /* [0,65535] */;
  uint32_t TIMESTAMP_MASTER_WR_T4 /* [0,65535] */;
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

} EXT_STR_h101_ASYCHIMERA;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_ASYCHIMERA_onion_t
{
  /* INFO */
  uint32_t TRIGGER;
  uint32_t EVENTNO;
  uint32_t TSTAMPLO;
  uint32_t TSTAMPHI;
  uint32_t TSTAMPSRCID;
  uint32_t MERGE_STATUS;
  uint32_t MERGE_IDMASK;
  /* RAW */
  uint32_t TIMESTAMP_MASTER_ID;
  uint32_t TIMESTAMP_MASTER_WR_T[4];
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
  } S[1];

} EXT_STR_h101_ASYCHIMERA_onion;

/*******************************************************/

#define EXT_STR_h101_ASYCHIMERA_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* INFO */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TRIGGER,                         UINT32,\
                    "TRIGGER",15,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     EVENTNO,                         UINT32,\
                    "EVENTNO",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     TSTAMPLO,                        UINT32,\
                    "TSTAMPLO",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     TSTAMPHI,                        UINT32,\
                    "TSTAMPHI",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     TSTAMPSRCID,                     UINT32,\
                    "TSTAMPSRCID",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     MERGE_STATUS,                    UINT32,\
                    "MERGE_STATUS",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     MERGE_IDMASK,                    UINT32,\
                    "MERGE_IDMASK",0/*flags*/); \
  /* RAW */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TIMESTAMP_MASTER_ID,             UINT32,\
                    "TIMESTAMP_MASTER_ID",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TIMESTAMP_MASTER_WR_T1,          UINT32,\
                    "TIMESTAMP_MASTER_WR_T1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TIMESTAMP_MASTER_WR_T2,          UINT32,\
                    "TIMESTAMP_MASTER_WR_T2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TIMESTAMP_MASTER_WR_T3,          UINT32,\
                    "TIMESTAMP_MASTER_WR_T3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TIMESTAMP_MASTER_WR_T4,          UINT32,\
                    "TIMESTAMP_MASTER_WR_T4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     S1FRONTDE,                       UINT32,\
                    "S1FRONTDE",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     S1FRONTDEI,                      UINT32,\
                    "S1FRONTDEI",                      "S1FRONTDE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     S1FRONTDEv,                      UINT32,\
                    "S1FRONTDEv",                      "S1FRONTDE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     S1BACKDE,                        UINT32,\
                    "S1BACKDE",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     S1BACKDEI,                       UINT32,\
                    "S1BACKDEI",                       "S1BACKDE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     S1BACKDEv,                       UINT32,\
                    "S1BACKDEv",                       "S1BACKDE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     S1FRONTTOF,                      UINT32,\
                    "S1FRONTTOF",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     S1FRONTTOFI,                     UINT32,\
                    "S1FRONTTOFI",                     "S1FRONTTOF",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     S1FRONTTOFv,                     UINT32,\
                    "S1FRONTTOFv",                     "S1FRONTTOF",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     S1BACKTOF,                       UINT32,\
                    "S1BACKTOF",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     S1BACKTOFI,                      UINT32,\
                    "S1BACKTOFI",                      "S1BACKTOF",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     S1BACKTOFv,                      UINT32,\
                    "S1BACKTOFv",                      "S1BACKTOF",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_ASYCHIMERA_EXT_H101_H__*/
/*******************************************************/
