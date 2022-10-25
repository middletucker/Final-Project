/***************************************************************************//**
 * @file
 * @brief Simple button baremetal examples functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "sl_simple_led_instances.h"
#include "sl_simple_button_instances.h"
#include "simple_button_baremetal.h"
#include "time.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#ifndef BUTTON_INSTANCE_0
#define BUTTON_INSTANCE_0   sl_button_btn0
#endif

#ifndef LED_INSTANCE_0
#define LED_INSTANCE_0      sl_led_led0
#endif

#ifndef LED_INSTANCE_1
#define LED_INSTANCE_1      sl_led_led1
#endif

#ifndef LED_INSTANCE_2
#define LED_INSTANCE_2      sl_led_inst0
#endif

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
int counter;
float duration;
clock_t begin;
clock_t end;
/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/
//
/***************************************************************************//**
 * Initialize example.
 ******************************************************************************/
void simple_button_init(void)
{
  return;
}

/***************************************************************************//**
 * Ticking function.
 ******************************************************************************/
void simple_button_process_action(void)
{
  sl_simple_led_turn_on(&LED_INSTANCE_2);
  sl_udelay_wait(10);
//clock begin
  sl_simple_led_turn_off(&LED_INSTANCE_2);
  sl_udelay_wait(2);
}

/***************************************************************************//**
 * Callback on button change.
 ******************************************************************************/
void sl_button_on_change(const sl_button_t *handle)
{
  if (sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED) {
    if (&BUTTON_INSTANCE_0 == handle) {
      if (counter == 0)
        {
          begin = clock();
          counter = 1;
        }
      else
        {
          end = clock();
          counter = 0;
          duration = (double)(end-begin) / CLOCKS_PER_SEC;
        }




    }
  }
}
