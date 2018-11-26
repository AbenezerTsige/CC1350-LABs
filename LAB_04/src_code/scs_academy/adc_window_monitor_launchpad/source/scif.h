/** \mainpage Driver Overview
  *
  * \section section_drv_info Driver Information
  * This Sensor Controller Interface driver has been generated by the Texas Instruments Sensor Controller
  * Studio tool:
  * - <b>Project name</b>:     ADC Window Monitor for LaunchPad
  * - <b>Project file</b>:     C:/ti/scs_academy/adc_window_monitor_launchpad/adc_window_monitor_launchpad.scp
  * - <b>Code prefix</b>:      -
  * - <b>Operating system</b>: TI-RTOS
  * - <b>Tool version</b>:     2.3.0.684
  * - <b>Tool patches</b>:     None
  * - <b>Target chip</b>:      CC1350, revision -, package QFN48 7x7 RGZ
  * - <b>Created</b>:          2018-11-24 19:57:18.956
  * - <b>Computer</b>:         DESKTOP-QHF2FIQ
  * - <b>User</b>:             Jeffrey
  *
  * No user-provided resource definitions were used to generate this driver.
  *
  * No user-provided procedure definitions were used to generate this driver.
  *
  * Do not edit the generated source code files other than temporarily for debug purposes. Any
  * modifications will be overwritten by the Sensor Controller Studio when generating new output.
  *
  * \section section_drv_modules Driver Modules
  * The driver is divided into three modules:
  * - \ref module_scif_generic_interface, providing the API for:
  *     - Initializing and uninitializing the driver
  *     - Task control (for starting, stopping and executing Sensor Controller tasks)
  *     - Task data exchange (for producing input data to and consume output data from Sensor Controller
  *       tasks)
  * - \ref module_scif_driver_setup, containing:
  *     - The AUX RAM image (Sensor Controller code and data)
  *     - I/O mapping information
  *     - Task data structure information
  *     - Driver setup data, to be used in the driver initialization
  *     - Project-specific functionality
  * - \ref module_scif_osal, for flexible OS support:
  *     - Interfaces with the selected operating system
  *
  * It is possible to use output from multiple Sensor Controller Studio projects in one application. Only
  * one driver setup may be active at a time, but it is possible to switch between these setups. When
  * using this option, there is one instance of the \ref module_scif_generic_interface and
  * \ref module_scif_osal modules, and multiple instances of the \ref module_scif_driver_setup module.
  * This requires that:
  * - The outputs must be generated using the same version of Sensor Controller Studio
  * - The outputs must use the same operating system
  * - The outputs must use different source code prefixes (inserted into all globals of the
  *   \ref module_scif_driver_setup)
  *
  *
  * \section section_project_info Project Description
  * Demonstrates ADC value monitoring, where the Sensor Controller only notifies the System CPU
  * application when the ADC value monitoring state changes.
  * 
  * The monitoring state indicates whether the ADC value is below, inside or above a configurable window:
  * - If below the configurable low threshold, the application indicates this on LaunchPad Green LED
  * - If above the configurable high threshold, the application indicates this on LaunchPad Red LED
  * 
  * The ADC input is by default DIO23 on the LaunchPad. This signal can easily be strapped to GND or 3V3
  * with a jumper to verify that the ADC is operational.
  * 
  * See the header in the application source file ("main.c" or similar) for further details and
  * instructions. This file is located in the source code output directory.
  *
  *
  * \subsection section_io_mapping I/O Mapping
  * Task I/O functions are mapped to the following pins:
  * - ADC Window Monitor:
  *     - <b>A: Sensor output</b>: DIO23
  *
  *
  * \section section_task_info Task Description(s)
  * This driver supports the following task(s):
  *
  *
  * \subsection section_task_desc_adc_window_monitor ADC Window Monitor
  * The Sensor Controller samples a single ADC channel and monitor and maintains a bit-vector that
  * indicates whether the ADC value is:
  * - Below a configurable low threshold
  * - Above a configurable high threshold
  * 
  * The System CPU application is notified when the bit-vector (the monitoring state) changes.
  *
  */




/** \addtogroup module_scif_driver_setup Driver Setup
  *
  * \section section_driver_setup_overview Overview
  *
  * This driver setup instance has been generated for:
  * - <b>Project name</b>:     ADC Window Monitor for LaunchPad
  * - <b>Code prefix</b>:      -
  *
  * The driver setup module contains the generated output from the Sensor Controller Studio project:
  * - Location of task control and scheduling data structures in AUX RAM
  * - The AUX RAM image, and the size the image
  * - Task data structure information (location, size and buffer count)
  * - I/O pin mapping translation table
  * - Task resource initialization and uninitialization functions
  * - Hooks for run-time logging
  *
  * @{
  */
#ifndef SCIF_H
#define SCIF_H

#include <stdint.h>
#include <stdbool.h>
#include "scif_framework.h"
#include "scif_osal_tirtos.h"


/// Target chip name
#define SCIF_TARGET_CHIP_NAME_CC1350
/// Target chip package
#define SCIF_TARGET_CHIP_PACKAGE_QFN48_7X7_RGZ

/// Number of tasks implemented by this driver
#define SCIF_TASK_COUNT 1

/// ADC Window Monitor: Task ID
#define SCIF_ADC_WINDOW_MONITOR_TASK_ID 0


/// ADC Window Monitor: Bit vector: ADC value is above cfg.adcWindowHigh
#define SCIF_ADC_WINDOW_MONITOR_BV_ADC_WINDOW_HIGH 2
/// ADC Window Monitor: Bit vector: ADC value is above cfg.adcWindowLow
#define SCIF_ADC_WINDOW_MONITOR_BV_ADC_WINDOW_LOW 1
/// ADC Window Monitor I/O mapping: Sensor output
#define SCIF_ADC_WINDOW_MONITOR_DIO_A_SENSOR_OUTPUT 23


// All shared data structures in AUX RAM need to be packed
#pragma pack(push, 2)


/// ADC Window Monitor: Task configuration structure
typedef struct {
    uint16_t adcWindowHigh; ///< Window high ADC value
    uint16_t adcWindowLow;  ///< Window low voltage
} SCIF_ADC_WINDOW_MONITOR_CFG_T;


/// ADC Window Monitor: Task output data structure
typedef struct {
    uint16_t adcValue;      ///< Last ADC value
    uint16_t bvWindowState; ///< Bit 0 indicates low, bit 1 indicates high
} SCIF_ADC_WINDOW_MONITOR_OUTPUT_T;


/// Sensor Controller task data (configuration, input buffer(s), output buffer(s) and internal state)
typedef struct {
    struct {
        SCIF_ADC_WINDOW_MONITOR_CFG_T cfg;
        SCIF_ADC_WINDOW_MONITOR_OUTPUT_T output;
    } adcWindowMonitor;
} SCIF_TASK_DATA_T;

/// Sensor Controller task generic control (located in AUX RAM)
#define scifTaskData    (*((volatile SCIF_TASK_DATA_T*) 0x400E00FE))


// Initialized internal driver data, to be used in the call to \ref scifInit()
extern const SCIF_DATA_T scifDriverSetup;


// Restore previous struct packing setting
#pragma pack(pop)


// AUX I/O re-initialization functions
void scifReinitTaskIo(uint32_t bvTaskIds);


// RTC-based tick generation control
void scifStartRtcTicks(uint32_t tickStart, uint32_t tickPeriod);
void scifStartRtcTicksNow(uint32_t tickPeriod);
void scifStopRtcTicks(void);


#endif
//@}


// Generated by DESKTOP-QHF2FIQ at 2018-11-24 19:57:18.956
