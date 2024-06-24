/*
* Example reading GameCube controller using Task based JoybusOverUart.
* Task Scheduler depends on https://github.com/arkhipenko/TaskScheduler
*
* In order to wire this up, we need to tie the UART's Rx and Tx pins together,
* using a Schottky diode, as shown here (https://github.com/dword1511/onewire-over-uart).
* Any Arduino compatible MCU should work with this library.
* Hardware required/used is a serial port capable of 1250000 bps baud-rate.
* Interrupts aren't blocked nor used.
* 
* Optional Mock controller task.
* Optional Controller display visualization https://github.com/GitMoDu/ArduinoGraphicsEngine .
*/

#define SERIAL_BAUD_RATE 115200

// Enable to skip Nintendo64 controller and just show a demo of the output.
#define USE_MOCK_CONTROLLER

// Enable to use ArduinoGraphicsEngine for displaying live link info.
// Depends on https://github.com/GitMoDu/ArduinoGraphicsEngine
//#define USE_CONTROLLER_DISPLAY
//#define GRAPHICS_ENGINE_MEASURE

#define _TASK_OO_CALLBACKS
#include <TaskScheduler.h>

#include <GameCubeController.h>
#include "GCControllerLogTask.h"

#if defined(USE_MOCK_CONTROLLER)
#include "MockControllerReadTask.h"
#else
#include <GameCubeOverUart.h>
#include <GameCubeControllerReadTask.h>
#endif

#if defined(USE_CONTROLLER_DISPLAY)
#include <ArduinoGraphicsEngineTask.h>
#include "../src/Display/DisplayDefinitions.h"
#include "GCControllerDrawer.h"
#endif

static constexpr uint32_t UpdatePeriodMicros = 5000;
static constexpr HardwareSerial* JoyBusSerial = &Serial3;

// Process scheduler.
Scheduler SchedulerBase{};

// Controller data with extra state flag.
GameCubeController::state_data_t ControllerState{};

// Controller data updater.
#if defined(USE_MOCK_CONTROLLER)
MockControllerReadTask ReadTask(&SchedulerBase, ControllerState, UpdatePeriodMicros);
#else
GameCubeControllerReadTask ReadTask(&SchedulerBase, ControllerState, JoyBusSerial, UpdatePeriodMicros);
#endif

// Serial log task.
GCControllerLogTask LogTask(&SchedulerBase, ControllerState);

#if defined(USE_CONTROLLER_DISPLAY)
// Display task.
GraphicsEngineTask DisplayEngine(&SchedulerBase, &FrameBuffer, &ScreenDriver, 16666);

// Controller Display Drawer and static Layout.
using ControllerLayout = GCControllerLayout<0, 0, FrameBufferType::FrameWidth, FrameBufferType::FrameHeight>;
GCControllerDrawer<ControllerLayout> ControllerDrawer(&FrameBuffer, ControllerState);

#if defined(GRAPHICS_ENGINE_MEASURE)
// Optional display log task.
EngineLogTask<1000> EngineLog(&SchedulerBase, &DisplayEngine);
#endif
#endif

void setup()
{
	Serial.begin(SERIAL_BAUD_RATE);

#if !defined(ARDUINO_ARCH_RP2040)
	while (!Serial)
		;
#endif

	delay(1000);

	// Serial Joy requires a start to initialize the serial hardware.
	ReadTask.Start();

#if defined(USE_CONTROLLER_DISPLAY)
	DisplayEngine.SetDrawer(&ControllerDrawer);
	DisplayEngine.Start();
#endif

	Serial.println(F("GameCube Controller over UART"));
}

void loop()
{
	SchedulerBase.execute();
}