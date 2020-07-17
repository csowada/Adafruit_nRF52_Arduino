#ifndef APP_CONFIG_H
#define APP_CONFIG_H

// NRFX_CLOCK_ENABLED
#define NRFX_POWER_ENABLED              1
#define NRFX_POWER_CONFIG_IRQ_PRIORITY 6
// // #define NRFX_POWER_DEFAULT_CONFIG_IRQ_PRIORITY  7
#define NRFX_CLOCK_ENABLED 1

#define NRFX_SPIM_ENABLED            1
#define NRFX_SPIM_MISO_PULL_CFG      1 // pulldown
#define NRFX_SPIM_EXTENDED_ENABLED   0

#define NRFX_SPIM0_ENABLED           0 // used as I2C
#define NRFX_SPIM1_ENABLED           0 // used as I2C
#define NRFX_SPIM2_ENABLED           1

#ifdef NRF52840_XXAA
  #define NRFX_QSPI_ENABLED   1
  #define NRFX_SPIM3_ENABLED  1
#else
  #define NRFX_QSPI_ENABLED   0
  #define NRFX_SPIM3_ENABLED  0
#endif

#endif