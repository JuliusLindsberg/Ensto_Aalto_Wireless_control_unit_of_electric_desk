
#include "DebugPrinter.hpp"
#include <stdio.h>
#include <zephyr.h>

bool DPInitialized = false;


#define ITM_ENA   (*(volatile unsigned int*)0xE0000E00) // ITM Enable
#define ITM_TPR   (*(volatile unsigned int*)0xE0000E40) // Trace Privilege
                                                        // Register
#define ITM_TCR   (*(volatile unsigned int*)0xE0000E80) // ITM Trace Control Reg.
#define ITM_LSR   (*(volatile unsigned int*)0xE0000FB0) // ITM Lock Status
                                                        // Register
#define DHCSR     (*(volatile unsigned int*)0xE000EDF0) // Debug register
#define DEMCR     (*(volatile unsigned int*)0xE000EDFC) // Debug register
#define TPIU_ACPR (*(volatile unsigned int*)0xE0040010) // Async Clock
                                                        // prescaler register
#define TPIU_SPPR (*(volatile unsigned int*)0xE00400F0) // Selected Pin Protocol
                                                        // Register
#define DWT_CTRL  (*(volatile unsigned int*)0xE0001000) // DWT Control Register
#define FFCR      (*(volatile unsigned int*)0xE0040304) // Formatter and flush
                                                        // Control Register
uint32_t _ITMPort  = 0; // The stimulus port from which SWO data is received
                   // and displayed.
uint32_t TargetDiv = 1; // Has to be calculated according to
                   // the CPU speed and the output baud rate

static void _EnableSWO() {
  uint32_t StimulusRegs;
  //
  // Enable access to SWO registers
  //
  DEMCR |= (1 << 24);
  ITM_LSR = 0xC5ACCE55;
  //
  // Initially disable ITM and stimulus port
  // To make sure that nothing is transferred via SWO
  // when changing the SWO prescaler etc.
  //
  StimulusRegs = ITM_ENA;
  StimulusRegs &= ~(1 << _ITMPort);
  ITM_ENA = StimulusRegs; // Disable ITM stimulus port
  ITM_TCR = 0; // Disable ITM
  //
  // Initialize SWO (prescaler, etc.)
  //
  TPIU_SPPR = 0x00000002; // Select NRZ mode
  TPIU_ACPR = TargetDiv - 1; // Example: 72/48 = 1,5 MHz
  ITM_TPR = 0x00000000;
  DWT_CTRL = 0x400003FE;
  FFCR = 0x00000100;
  //
  // Enable ITM and stimulus port
  //
  ITM_TCR = 0x1000D; // Enable ITM
  ITM_ENA = StimulusRegs | (1 << _ITMPort); // Enable ITM stimulus port
}

#define ITM_STIM_U32 (*(volatile unsigned int*)0xE0000000) // STIM word access
#define ITM_STIM_U8  (*(volatile         char*)0xE0000000) // STIM Byte access
#define ITM_ENA      (*(volatile unsigned int*)0xE0000E00) // ITM Enable Register
#define ITM_TCR      (*(volatile unsigned int*)0xE0000E80) // ITM Trace Control
                                                           // Register
void SWO_PrintChar(char c) {
  //
  // Check if ITM_TCR.ITMENA is set
  //
  if ((ITM_TCR & 1) == 0) {
    return;
  }
  //
  // Check if stimulus port is enabled
  //
  if ((ITM_ENA & 1) == 0) {
    return;
  }
  //
  // Wait until STIMx is ready,
  // then send data
  //
  while ((ITM_STIM_U8 & 1) == 0);
  ITM_STIM_U8 = c;
}


void SWO_PrintString(const char *s) {
  //
  // Print out character per character
  //
  while (*s) {
    SWO_PrintChar(*s++);
  }
}


void SWO_PrintInt(const int number)
{
  char charBuffer[20];
  sprintf(charBuffer,"%d", number);
  SWO_PrintString(charBuffer);
}

DebugPrinter::DebugPrinter()
{
    if(!DPInitialized)
    {
        DPInitialized = true;
        //untested!
        _EnableSWO();
    }
}

void DebugPrinter::PrintString(const char* string)
{
    SWO_PrintString(string);
}

void DebugPrinter::PrintCharacter(const char c)
{
    SWO_PrintChar(c);
}

void DebugPrinter::PrintInt(const int number)
{
    SWO_PrintInt(number);
}

const DebugPrinter& DebugPrinter::operator<<(const int a)
{
    PrintInt(a);
    return *this;
}

const DebugPrinter& DebugPrinter::operator<<(const char a)
{
    PrintCharacter(a);
    return *this;
}

const DebugPrinter& DebugPrinter::operator<<(const char* a)
{
    PrintString(a);
    return *this;
}