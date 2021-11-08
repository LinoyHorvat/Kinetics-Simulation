/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: finish */
#define  PANEL_conc_B                     2       /* control type: numeric, callback function: (none) */
#define  PANEL_RATE_k_1                   3       /* control type: numeric, callback function: (none) */
#define  PANEL_TIME_INTERVAL              4       /* control type: numeric, callback function: (none) */
#define  PANEL_RATE_k2                    5       /* control type: numeric, callback function: (none) */
#define  PANEL_PICTUR_REC                 6       /* control type: pictRing, callback function: reactionfunc3 */
#define  PANEL_RATE_k1                    7       /* control type: numeric, callback function: (none) */
#define  PANEL_conc_C                     8       /* control type: numeric, callback function: (none) */
#define  PANEL_conc_A                     9       /* control type: numeric, callback function: (none) */
#define  PANEL_BACK                       10      /* control type: command, callback function: back3_func */
#define  PANEL_QUIT                       11      /* control type: command, callback function: quit */
#define  PANEL_NUMERICTANK_C              12      /* control type: scale, callback function: (none) */
#define  PANEL_NUMERICTANK_B              13      /* control type: scale, callback function: (none) */
#define  PANEL_NUMERICTANK_A              14      /* control type: scale, callback function: (none) */
#define  PANEL_CONTINUE                   15      /* control type: command, callback function: resumefunc */
#define  PANEL_Stop                       16      /* control type: command, callback function: stopfunc */
#define  PANEL_HALF_LIFE                  17      /* control type: numeric, callback function: (none) */
#define  PANEL_GRAPH_2                    18      /* control type: graph, callback function: (none) */
#define  PANEL_GRAPH                      19      /* control type: graph, callback function: (none) */
#define  PANEL_FILE                       20      /* control type: command, callback function: writefile */
#define  PANEL_BINARYSWITCH               21      /* control type: binary, callback function: bin_func */
#define  PANEL_EQ_LINER                   22      /* control type: ring, callback function: (none) */

#define  PANEL_1                          2       /* callback function: finish */
#define  PANEL_1_QUITBUTTON               2       /* control type: command, callback function: QuitCallback */
#define  PANEL_1_TEXTMSG                  3       /* control type: textMsg, callback function: (none) */
#define  PANEL_1_TEXTMSG_2                4       /* control type: textMsg, callback function: (none) */
#define  PANEL_1_REAC_TYP                 5       /* control type: ring, callback function: reactionfunc */
#define  PANEL_1_PICTUR_REC               6       /* control type: pictRing, callback function: reactionfunc */
#define  PANEL_1_CONTINUE                 7       /* control type: command, callback function: continuefunc */

#define  PANEL_2                          3       /* callback function: finish2 */
#define  PANEL_2_TEXTMSG_2                2       /* control type: textMsg, callback function: (none) */
#define  PANEL_2_conc_B                   3       /* control type: numeric, callback function: (none) */
#define  PANEL_2_RATE_k_1                 4       /* control type: numeric, callback function: (none) */
#define  PANEL_2_TIME_INTERVAL            5       /* control type: numeric, callback function: (none) */
#define  PANEL_2_RATE_k2                  6       /* control type: numeric, callback function: (none) */
#define  PANEL_2_BACK                     7       /* control type: command, callback function: back2_func */
#define  PANEL_2_START                    8       /* control type: command, callback function: startfunc */
#define  PANEL_2_RATE_k1                  9       /* control type: numeric, callback function: (none) */
#define  PANEL_2_conc_A                   10      /* control type: numeric, callback function: (none) */
#define  PANEL_2_RING                     11      /* control type: ring, callback function: (none) */
#define  PANEL_2_TIMER                    12      /* control type: timer, callback function: timerfunc */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK back2_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK back3_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK bin_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK continuefunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK finish(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK finish2(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK reactionfunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK reactionfunc3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK resumefunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK startfunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK stopfunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timerfunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK writefile(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif