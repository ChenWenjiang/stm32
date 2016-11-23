#include "types.h"
#include "globalvar.h"

unsigned int loadLedColor(void);

STATUS storeLedColor(void);

unsigned char loadAlarmListHead(void);

unsigned char loadAlarmHistory(unsigned char Nbefore);

STATUS storeAlarmHistory(unsigned char alarmLoc);

unsigned char loadUSARTConfiguration(void);

STATUS storeUSARTConfiguration(unsigned char config);

unsigned char loadModbusAddr(void);

STATUS storeModbusAddr(unsigned char addr);

