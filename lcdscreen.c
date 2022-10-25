#include <stdio.h>

#include "sl_board_control.h"
#include "sl_simple_button_instances.h"

#include "em_assert.h"
#include "glib.h"
#include "dmd.h"
#include "sl_sleeptimer.h"

#include "app.c"
#include "simple_button_baremetal.c"


/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#ifndef BUTTON_INSTANCE_0
#define BUTTON_INSTANCE_0   sl_button_btn0
#endif



/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static GLIB_Context_t glibContext;
static int currentLine = 0;


int distance=17000*duration;
int distancedelay = distance*100;
int xdistance;


sl_sleeptimer_timer_handle_t timer;
bool toggle_timeout = false;

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

static void on_timeout(sl_sleeptimer_timer_handle_t *handle,
                       void *data);

/***************************************************************************//**
 * Initialize example.
 ******************************************************************************/
void memlcd_app_init(void)
{
  int dist[50];
  uint32_t status;

  /* Enable the memory lcd */
  status = sl_board_enable_display();
  EFM_ASSERT(status == SL_STATUS_OK);

  /* Initialize the DMD support for memory lcd display */
  status = DMD_init(0);
  EFM_ASSERT(status == DMD_OK);

  /* Initialize the glib context */
  status = GLIB_contextInit(&glibContext);
  EFM_ASSERT(status == GLIB_OK);

  glibContext.backgroundColor = White;
  glibContext.foregroundColor = Black;

  /* Fill lcd with background color */
  GLIB_clear(&glibContext);

  /* Use Narrow font */
  GLIB_setFont(&glibContext, (GLIB_Font_t *) &GLIB_FontNarrow6x8);


  sprintf("Distance = %ld cm\r\n", distance);

  GLIB_drawStringOnLine(&glibContext,
                                 "Object",
                                 currentLine = 4,
                                 GLIB_ALIGN_LEFT,
                                 5,
                                 9,
                                 true);
  GLIB_drawStringOnLine(&glibContext,
                                 "________________________________________",
                                 currentLine = 5,
                                 GLIB_ALIGN_LEFT,
                                 5,
                                 9,
                                 true);

  if (xdistance < 128)
    {
      GLIB_drawPixel(&glibContext, xdistance, distance);
       xdistance++;
    }

  GLIB_drawStringOnLine(&glibContext,
                          distance,
                          currentLine = 7,
                          GLIB_ALIGN_RIGHT,
                          1,
                          1,
                          true);
  dist[distance]=distance;
  sprintf(dist, "Distance = %ld cm\r\n", distance);

  GLIB_drawStringOnLine(&glibContext,
                          dist,
                          currentLine = 0,
                          GLIB_ALIGN_RIGHT,
                          1,
                          1,
                          true);
  DMD_updateDisplay();

}
void set_leds()
 {
   //if distance > a enter em1/2
   //if distance < x turn on led0
   //if distance < y < x enter sleep mode

   if (distance < 15) {
     // exit em4
     sl_led_turn_on(&sl_led_led1);
   }
   else
     {
       sl_led_turn_off(&sl_led_led1);
     }
   /*else if (distance > 20) {
     // turn led off, enter em2
     sl_led_turn_off(&sl_led_led1);

   } else if (distance < 30)
   {
       //exit em2
   } else if (distance < 10)
   {
         //enter em4
   }
 */

 }
/***************************************************************************//**
 * Ticking function.
 ******************************************************************************/
void memlcd_app_process_action(void)
{
  return;
}

/***************************************************************************//**
 * Callback on button change.
 *
 * This function overrides a weak implementation defined in the simple_button
 * module. It is triggered when the user activates one of the buttons.
 *
 ******************************************************************************/
void blink_init(void)
{
  // Create timer for waking up the system periodically.
  sl_sleeptimer_start_periodic_timer_ms(&timer,
                                        distancedelay,
                                        on_timeout, NULL,
                                        0,
                                        SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);

}

/***************************************************************************//**
 * Blink ticking function.
 ******************************************************************************/
void blink_process_action(void)
{
  if (toggle_timeout == true) {
    sl_led_toggle(&LED_INSTANCE_0);
    toggle_timeout = false;
  }
}




/***************************************************************************//**
 * Sleeptimer timeout callback.
 ******************************************************************************/
static void on_timeout(sl_sleeptimer_timer_handle_t *handle,
                       void *data)
{
  (void)&handle;
  (void)&data;
  toggle_timeout = true;
}
