/*
 * File: Chart.c
 *
 * Code generated for Simulink model 'Chart'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue May  3 18:41:47 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Chart.h"

/* Named constants for Chart: '<Root>/Chart' */
#define IN_State1                      ((uint8_T)1U)
#define IN_State2                      ((uint8_T)2U)

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
void Chart_step(void)
{
  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/u'
   */
  if (rtDW.is_active_c3_Chart == 0U) {
    rtDW.is_active_c3_Chart = 1U;
    rtDW.is_c3_Chart = IN_State1;

    /* Outport: '<Root>/y' */
    rtY.y = -1.0;

    /*  entry action
       during: */
  } else if (rtDW.is_c3_Chart == IN_State1) {
    /* Outport: '<Root>/y' */
    rtY.y = -1.0;
    if (rtU.u <= 0.0) {
      /*  [transition condition]{action} */
      rtDW.is_c3_Chart = IN_State2;

      /* Outport: '<Root>/y' */
      rtY.y = 1.0;
    }
  } else {
    /* Outport: '<Root>/y' */
    /* case IN_State2: */
    rtY.y = 1.0;
    if (rtU.u > 0.0) {
      rtDW.is_c3_Chart = IN_State1;

      /* Outport: '<Root>/y' */
      rtY.y = -1.0;

      /*  entry action
         during: */
    }
  }

  /* End of Chart: '<Root>/Chart' */
}

/* Model initialize function */
void Chart_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
