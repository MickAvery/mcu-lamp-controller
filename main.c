/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "hal.h"

/**
 * configurations related to serial
 */
#define UART_TX_PORT   GPIOA
#define UART_TX_PADNUM 0

#define UART_RX_PORT   GPIOA
#define UART_RX_PADNUM 1

#define UART_PIN_ALTMODE 8

/**
 * configurations related to I2S
 */

#define I2S_SD_PORT   GPIOC
#define I2S_SD_PADNUM 3

#define I2S_CLK_PORT   GPIOB
#define I2S_CLK_PADNUM 10

#define I2S_PIN_ALTMODE 5

#define I2S_BUFF_SIZE 1U

static uint8_t i2s_buf[I2S_BUFF_SIZE] = {0U}; /* destination buffer for I2S signals */

static const I2SConfig i2s_conf = {
  NULL, /* tx buffer */
  i2s_buf, /* rx buffer */
  I2S_BUFF_SIZE, /* tx+rx buffer size */
  NULL /* callback */
};

/**
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   */
  halInit();

  /*
   * Enabling interrupts, initialization done.
   */
  osalSysEnable();

  /*
   * Activates the serial driver 2 using the driver default configuration.
   * PA2(TX) and PA3(RX) are routed to USART2.
   */
  sdStart(&SD4, NULL);
  palSetPadMode(UART_TX_PORT, UART_TX_PADNUM, PAL_MODE_ALTERNATE(UART_PIN_ALTMODE));
  palSetPadMode(UART_RX_PORT, UART_RX_PADNUM, PAL_MODE_ALTERNATE(UART_PIN_ALTMODE));

  /*
   * Activate I2S peripheral
   */
  i2sStart(&I2SD2, &i2s_conf);
  palSetPadMode(I2S_SD_PORT, I2S_SD_PADNUM, PAL_MODE_ALTERNATE(I2S_PIN_ALTMODE));
  palSetPadMode(I2S_CLK_PORT, I2S_CLK_PADNUM, PAL_MODE_ALTERNATE(I2S_PIN_ALTMODE));

  /*
   * Normal main() thread activity, in this demo it just performs
   * a shell respawn upon its termination.
   */
  while (true) {
    chnWriteTimeout(&SD4, (uint8_t *)"Hello World!\r\n", 14, TIME_INFINITE);

    palSetPad(GPIOD, GPIOD_LED3);       /* Orange.  */
    osalThreadSleepMilliseconds(500);
    palClearPad(GPIOD, GPIOD_LED3);     /* Orange.  */
    osalThreadSleepMilliseconds(500);
  }
}
