/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_ASYKRAB_EXT_H101_KRAB_H__
#define __GUARD_H101_ASYKRAB_EXT_H101_KRAB_H__

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

typedef struct EXT_STR_h101_ASYKRAB_t
{
  /* RAW */
  uint32_t KRAB_SAMP_TBOX /* [0,512] */;
  uint32_t KRAB_SAMP_TBOXI[512 EXT_STRUCT_CTRL(KRAB_SAMP_TBOX)] /* [1,512] */;
  uint32_t KRAB_SAMP_TBOXv[512 EXT_STRUCT_CTRL(KRAB_SAMP_TBOX)] /* [-1,-1] */;
  uint32_t KRAB_SAMP_TRIGONE /* [0,512] */;
  uint32_t KRAB_SAMP_TRIGONEI[512 EXT_STRUCT_CTRL(KRAB_SAMP_TRIGONE)] /* [1,512] */;
  uint32_t KRAB_SAMP_TRIGONEv[512 EXT_STRUCT_CTRL(KRAB_SAMP_TRIGONE)] /* [-1,-1] */;
  uint32_t KRAB_SAMP_TRIGTWO /* [0,512] */;
  uint32_t KRAB_SAMP_TRIGTWOI[512 EXT_STRUCT_CTRL(KRAB_SAMP_TRIGTWO)] /* [1,512] */;
  uint32_t KRAB_SAMP_TRIGTWOv[512 EXT_STRUCT_CTRL(KRAB_SAMP_TRIGTWO)] /* [-1,-1] */;
  uint32_t KRAB_SAMP_ACCEPT /* [0,512] */;
  uint32_t KRAB_SAMP_ACCEPTI[512 EXT_STRUCT_CTRL(KRAB_SAMP_ACCEPT)] /* [1,512] */;
  uint32_t KRAB_SAMP_ACCEPTv[512 EXT_STRUCT_CTRL(KRAB_SAMP_ACCEPT)] /* [-1,-1] */;
  uint32_t KRAB_I /* [0,33] */;
  uint32_t KRAB_Iv[33 EXT_STRUCT_CTRL(KRAB_I)] /* [-1,-1] */;
  uint32_t KRAB_DATA /* [0,33] */;
  uint32_t KRAB_DATAv[33 EXT_STRUCT_CTRL(KRAB_DATA)] /* [-1,-1] */;

} EXT_STR_h101_ASYKRAB;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_ASYKRAB_onion_t
{
  /* RAW */
  uint32_t KRAB_SAMP_TBOX;
  uint32_t KRAB_SAMP_TBOXI[512 /* KRAB_SAMP_TBOX */];
  uint32_t KRAB_SAMP_TBOXv[512 /* KRAB_SAMP_TBOX */];
  uint32_t KRAB_SAMP_TRIGONE;
  uint32_t KRAB_SAMP_TRIGONEI[512 /* KRAB_SAMP_TRIGONE */];
  uint32_t KRAB_SAMP_TRIGONEv[512 /* KRAB_SAMP_TRIGONE */];
  uint32_t KRAB_SAMP_TRIGTWO;
  uint32_t KRAB_SAMP_TRIGTWOI[512 /* KRAB_SAMP_TRIGTWO */];
  uint32_t KRAB_SAMP_TRIGTWOv[512 /* KRAB_SAMP_TRIGTWO */];
  uint32_t KRAB_SAMP_ACCEPT;
  uint32_t KRAB_SAMP_ACCEPTI[512 /* KRAB_SAMP_ACCEPT */];
  uint32_t KRAB_SAMP_ACCEPTv[512 /* KRAB_SAMP_ACCEPT */];
  uint32_t KRAB_I;
  uint32_t KRAB_Iv[33 /* KRAB_I */];
  uint32_t KRAB_DATA;
  uint32_t KRAB_DATAv[33 /* KRAB_DATA */];

} EXT_STR_h101_ASYKRAB_onion;

/*******************************************************/

#define EXT_STR_h101_ASYKRAB_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* RAW */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     KRAB_SAMP_TBOX,                  UINT32,\
                    "KRAB_SAMP_TBOX",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     KRAB_SAMP_TBOXI,                 UINT32,\
                    "KRAB_SAMP_TBOXI",                 "KRAB_SAMP_TBOX",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     KRAB_SAMP_TBOXv,                 UINT32,\
                    "KRAB_SAMP_TBOXv",                 "KRAB_SAMP_TBOX",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     KRAB_SAMP_TRIGONE,               UINT32,\
                    "KRAB_SAMP_TRIGONE",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     KRAB_SAMP_TRIGONEI,              UINT32,\
                    "KRAB_SAMP_TRIGONEI",              "KRAB_SAMP_TRIGONE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     KRAB_SAMP_TRIGONEv,              UINT32,\
                    "KRAB_SAMP_TRIGONEv",              "KRAB_SAMP_TRIGONE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     KRAB_SAMP_TRIGTWO,               UINT32,\
                    "KRAB_SAMP_TRIGTWO",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     KRAB_SAMP_TRIGTWOI,              UINT32,\
                    "KRAB_SAMP_TRIGTWOI",              "KRAB_SAMP_TRIGTWO",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     KRAB_SAMP_TRIGTWOv,              UINT32,\
                    "KRAB_SAMP_TRIGTWOv",              "KRAB_SAMP_TRIGTWO",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     KRAB_SAMP_ACCEPT,                UINT32,\
                    "KRAB_SAMP_ACCEPT",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     KRAB_SAMP_ACCEPTI,               UINT32,\
                    "KRAB_SAMP_ACCEPTI",               "KRAB_SAMP_ACCEPT",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     KRAB_SAMP_ACCEPTv,               UINT32,\
                    "KRAB_SAMP_ACCEPTv",               "KRAB_SAMP_ACCEPT",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     KRAB_I,                          UINT32,\
                    "KRAB_I",33,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     KRAB_Iv,                         UINT32,\
                    "KRAB_Iv",                         "KRAB_I",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     KRAB_DATA,                       UINT32,\
                    "KRAB_DATA",33,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     KRAB_DATAv,                      UINT32,\
                    "KRAB_DATAv",                      "KRAB_DATA",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_ASYKRAB_EXT_H101_KRAB_H__*/

/*******************************************************/
