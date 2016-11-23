/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUITOUCH.C
Purpose     : Touch screen manager
----------------------------------------------------------------------
This module handles the touch screen. It is configured in the file
GUITouch.conf.h (Should be located in the Config\ directory).
----------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Protected.h"
#include "ARC_TouchScreen.h"

/* Generate code only if configuration says so ! */
#if GUI_SUPPORT_TOUCH

#include "GUITouchConf.h"    /* Located in GUIx, will include GUITouchConf.h */

/*********************************************************************
*
*       Defines, config defaults
*
**********************************************************************
*/

#ifndef GUI_TOUCH_AD_LEFT         /* max value returned by AD-converter */
  #define GUI_TOUCH_AD_LEFT 30   
#endif

#ifndef GUI_TOUCH_AD_RIGHT        /* min value returned by AD-converter */
  #define GUI_TOUCH_AD_RIGHT 220    
#endif

#ifndef GUI_TOUCH_AD_TOP          /* max value returned by AD-converter */
  #define GUI_TOUCH_AD_TOP 30
#endif

#ifndef GUI_TOUCH_AD_BOTTOM       /* min value returned by AD-converter */
  #define GUI_TOUCH_AD_BOTTOM 220
#endif

#ifndef GUI_TOUCH_SWAP_XY         /* Is XY of touch swapped ? */
  #define GUI_TOUCH_SWAP_XY 0
#endif

#ifndef GUI_TOUCH_MIRROR_X
  #define GUI_TOUCH_MIRROR_X 0
#endif

#ifndef GUI_TOUCH_MIRROR_Y
  #define GUI_TOUCH_MIRROR_Y 0
#endif

#ifndef GUI_TOUCH_YSIZE
  #define GUI_TOUCH_YSIZE LCD_YSIZE
#endif

#ifndef GUI_TOUCH_XSIZE
  #define GUI_TOUCH_XSIZE LCD_XSIZE
#endif

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

typedef struct {int Min; int Max; } tMinMax;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static int xPhys, yPhys;

static tMinMax xyMinMax[2] = {
#if ((GUI_TOUCH_SWAP_XY==0) && (GUI_TOUCH_MIRROR_X==0)) || ((GUI_TOUCH_SWAP_XY) && (GUI_TOUCH_MIRROR_Y==0))
  { GUI_TOUCH_AD_LEFT, GUI_TOUCH_AD_RIGHT },
#else
  { GUI_TOUCH_AD_RIGHT, GUI_TOUCH_AD_LEFT },
#endif
#if ((GUI_TOUCH_SWAP_XY==0) && (GUI_TOUCH_MIRROR_Y==0)) || ((GUI_TOUCH_SWAP_XY) && (GUI_TOUCH_MIRROR_X==0))
  { GUI_TOUCH_AD_TOP,  GUI_TOUCH_AD_BOTTOM }
#else
  { GUI_TOUCH_AD_BOTTOM,  GUI_TOUCH_AD_TOP }
#endif
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _AD2X
*
* Purpose:
*   Convert physical value into (logical) coordinates.
*/

/*********************************************************************
*
*       _Log2Phys
*/
static int _Log2Phys(int l, I32 l0, I32 l1, I32 p0, I32 p1) {
  return p0+ ((p1 - p0) * (l - l0)) / (l1 - l0);
}

/*********************************************************************
*
*       _StoreUnstable
*/
static void _StoreUnstable(int x, int y) {
  static int _xLast = -1;
  static int _yLast = -1;
  int xOut, yOut;

  if ((x != -1) && (y != -1) && (_xLast != -1) && (_yLast != -1)) {
    xOut = _xLast;    
    yOut = _yLast;    
  } else {
    xOut = -1;
    yOut = -1;    
  }
  _xLast = x;
  _yLast = y;
  GUI_TOUCH_StoreUnstable(xOut, yOut);
}

void StoreUnstable_Invalid(void)
{
    _StoreUnstable(-1, -1);
}
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_TOUCH_GetxPhys
*/
int  GUI_TOUCH_GetxPhys(void) {
  return xPhys;
}

/*********************************************************************
*
*       GUI_TOUCH_GetyPhys
*/
int  GUI_TOUCH_GetyPhys(void) {
  return yPhys;
}

/*********************************************************************
*
*       GUI_TOUCH_SetDefaultCalibration
*/
void GUI_TOUCH_SetDefaultCalibration(void) {
  xyMinMax[0].Min = GUI_TOUCH_AD_LEFT;
  xyMinMax[0].Max = GUI_TOUCH_AD_RIGHT;
  xyMinMax[1].Min = GUI_TOUCH_AD_TOP;
  xyMinMax[1].Max = GUI_TOUCH_AD_BOTTOM;
}

/*********************************************************************
*
*       GUI_TOUCH_Calibrate
*/
int GUI_TOUCH_Calibrate(int Coord, int Log0, int Log1, int Phys0, int Phys1) {
  int l0 = 0;
  int l1 = (Coord == GUI_COORD_X) ? LCD_XSIZE - 1 : LCD_YSIZE - 1;
  if (labs(Phys0 - Phys1) < 20) {
    return 1;
  }
  if (labs(Log0 - Log1) < 20) {
    return 1;
  }
  xyMinMax[Coord].Min = _Log2Phys(l0, Log0, Log1, Phys0, Phys1);  
  xyMinMax[Coord].Max = _Log2Phys(l1, Log0, Log1, Phys0, Phys1);
  return 0;
}

/*********************************************************************
*
*       GUI_TOUCH_GetCalData
*/
void GUI_TOUCH_GetCalData(int Coord, int* pMin,int* pMax) {
  *pMin = xyMinMax[Coord].Min;
  *pMax = xyMinMax[Coord].Max; 
}
  
/*********************************************************************
*
*       GUI_TOUCH_Exec
*/
void GUI_TOUCH_Exec(void) {
  #ifndef WIN32
  pen_state_struct *pen_st;
  pen_st = ARC_get_penstate();
  /* calculate Min / Max values */
  
  if(ARC_TouchScreen_Rd_LCD_XY())
  {
      _StoreUnstable(pen_st->x_converted, pen_st->y_converted);
  }
  #endif /* WIN32 */
}

#else

void GUI_TOUCH_DriverAnalog_C(void);  /* Avoid "no prototype" warnings */
void GUI_TOUCH_DriverAnalog_C(void) {}

#endif    /* defined(GUI_SUPPORT_TOUCH) && GUI_SUPPORT_TOUCH */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
