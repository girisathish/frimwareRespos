/*
 * sydantek.h
 *
 * Copyright (c) 2020 and onwards, Carditek Medical Devices, Pvt. Ltd.
 * All rights reserved.
 */

#ifndef APPLICATION_SERVICES_SYDANTEK_R3_H_
#define APPLICATION_SERVICES_SYDANTEK_R3_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <bcomdef.h>

// UUID "a965db41-5e30-ad9e-fe47-02a5822878 ??"; service at 0, ...
#define SYDANTEK_UUID(id) (id) /* 0x55 */, 0x78, 0x28, 0x82, 0xa5, 0x02, \
    0x47, 0xfe, 0x9e, 0xad, 0x30, 0x5e, 0x41, 0xdb, 0x65, 0xa9

extern bStatus_t Sydantek_AddService(uint8_t rspTaskId);
extern uint8_t Sydantek_ProcessTimerEvent(); // status will return notification filaed

#define SYDANTEK_TIMER_PERIOD_MSECS 5

enum AFE_ErrorCodes {
AFE_INIT_ERROR=0,
AFE_INIT_SUCCESS=1,
AFE_TRANSFER_ERR=-1,        // This error is returned from SendToAFE() if there is failure in SPI_transfer
AFE_DEFINED_ID=0x92         //ID expected to be returned by ADS1298
};

enum FrmaeFormats{
    FRAMETYPE_OLD=0xFF,
    FRAMETYPE00=0x00,
    FRAMETYPE01=0x01,
    FRAMETYPE02=0x02,
    FRAMETYPE03=0x03,
    FRAMETYPE04=0x04,
    FRAMETYPE05=0x05
};


#define SYN 0xE5
#define ID 0x85
#define ETX 0x83
#define EOT 0x84


#define FRAME_TYPE FRAMETYPE_OLD

// AFE needs 1ms interrupt to take data out once every ms at 1000 samples per second
#define AFE_PERIODIC_EVT_PERIOD  100
// event generation for RTOS
#define AFE_PERIODIC_EVT         0x0010

#define AFE_DATA_LENGTH         27      //3 bytes of status and 3 bytes per channel for 8 channels
#define DATA_PACKET_LEN      160// 160//160
enum AFE_REGISTERS1{
//ADDRESS REGISTER (Hex) BIT 7 BIT 6 BIT 5 BIT 4 BIT 3 BIT 2 BIT 1 BIT 0
//DEVICE SETTINGS (READ-ONLY REGISTERS)
AFE_ID          =0x00,          //00h ID xx DEV_ID7 DEV_ID6 DEV_ID5 1 0 DEV_ID2 DEV_ID1 DEV_ID0
                                //GLOBAL SETTINGS ACROSS CHANNELS
AFE_CONFIG1     =0x01,          //01h CONFIG1 06 HR DAISY_EN CLK_EN 0 0 DR2 DR1 DR0
AFE_CONFIG2     =0x02,          //02h CONFIG2 40 0 0 WCT_CHOP INT_TEST 0 TEST_AMP TEST_FREQ1 TEST_FREQ0
AFE_CONFIG3     =0x03,          //03h CONFIG3 40 PD_REFBUF 1 VREF_4V RLD_MEAS RLDREF_INT PD_RLD RLD_LOFF_ RLD_STAT SENS
AFE_LOFF        =0x04,          //04h LOFF 00 COMP_TH2 COMP_TH1 COMP_TH0 VLEAD_OFF_ ILEAD_OFF1 ILEAD_OFF0 FLEAD_OFF1 FLEAD_OFF0 EN
                                //CHANNEL-SPECIFIC SETTINGS
AFE_CH1SET      =0x05,          //05h CH1SET 00 PD1 GAIN12 GAIN11 GAIN10 0 MUX12 MUX11 MUX10
AFE_CH2SET      =0x06,          //06h CH2SET 00 PD2 GAIN22 GAIN21 GAIN20 0 MUX22 MUX21 MUX20
AFE_CH3SET      =0x07,          //07h CH3SET 00 PD3 GAIN32 GAIN31 GAIN30 0 MUX32 MUX31 MUX30
AFE_CH4SET      =0x08,          //08h CH4SET 00 PD4 GAIN42 GAIN41 GAIN40 0 MUX42 MUX41 MUX40
AFE_CH5SET      =0x09,          //09h CH5SET (1) 00 PD5 GAIN52 GAIN51 GAIN50 0 MUX52 MUX51 MUX50
AFE_CH6SET      =0x0A,          //0Ah CH6SET (1) 00 PD6 GAIN62 GAIN61 GAIN60 0 MUX62 MUX61 MUX60
AFE_CH7SET      =0x0B,          //0Bh CH7SET (1) 00 PD7 GAIN72 GAIN71 GAIN70 0 MUX72 MUX71 MUX70
AFE_CH8SET      =0x0C,          //0Ch CH8SET (1) 00 PD8 GAIN82 GAIN81 GAIN80 0 MUX82 MUX81 MUX80
AFE_RLD_SENSP   =0x0D,          //0Dh RLD_SENSP (2) 00 RLD8P(1) RLD7P(1) RLD6P(1) RLD5P(1) RLD4P RLD3P RLD2P RLD1P
AFE_RLD_SENSN   =0x0E,          //0Eh RLD_SENSN (2) 00 RLD8N(1) RLD7N(1) RLD6N(1) RLD5N(1) RLD4N RLD3N RLD2N RLD1N
AFE_LOFF_SENSP  =0x0F,          //0Fh LOFF_SENSP (2) 00 LOFF8P LOFF7P LOFF6P LOFF5P LOFF4P LOFF3P LOFF2P LOFF1P
AFE_LOFF_SENSN  =0x10,          //10h LOFF_SENSN (2) 00 LOFF8N LOFF7N LOFF6N LOFF5N LOFF4N LOFF3N LOFF2N LOFF1N
AFE_LOFF_FLIP   =0x11,          //11h LOFF_FLIP 00 LOFF_FLIP8 LOFF_FLIP7 LOFF_FLIP6 LOFF_FLIP5 LOFF_FLIP4 LOFF_FLIP3 LOFF_FLIP2 LOFF_FLIP1
                                //LEAD-OFF STATUS REGISTERS (READ-ONLY REGISTERS)
AFE_LOFF_STATP  =0x12,          //12h LOFF_STATP 00 IN8P_OFF IN7P_OFF IN6P_OFF IN5P_OFF IN4P_OFF IN3P_OFF IN2P_OFF IN1P_OFF
AFE_LOFF_STATN  =0x13,          //13h LOFF_STATN 00 IN8N_OFF IN7N_OFF IN6N_OFF IN5N_OFF IN4N_OFF IN3N_OFF IN2N_OFF IN1N_OFF
                                //GPIO AND OTHER REGISTERS
AFE_LOFF_GPIO   =0x14,          //14h GPIO 0F GPIOD4 GPIOD3 GPIOD2 GPIOD1 GPIOC4 GPIOC3 GPIOC2 GPIOC1
AFE_PACE        =0x15,          //15h PACE 00 0 0 0 PACEE1 PACEE0 PACEO1 PACEO0 PD_PACE
AFE_RESP        =0x16,          //16h RESP 00 RESP_ RESP_MOD_ 1 RESP_PH2 RESP_PH1 RESP_PH0 RESP_CTRL1 RESP_CTRL0 DEMOD_EN1 EN1
AFE_CONFIG4     =0x17,          //17h CONFIG4 00 RESP_FREQ2 RESP_FREQ1 RESP_FREQ0 0 SINGLE_ WCT_TO_ PD_LOFF_ 0 SHOT RLD COMP
AFE_WCT1        =0x18,          //18h WCT1 00 aVF_CH6 aVL_CH5 aVR_CH7 avR_CH4 PD_WCTA WCTA2 WCTA1 WCTA0
AFE_WCT2        =0x19           //19h WCT2 00 PD_WCTC PD_WCTB WCTB2 WCTB1 WCTB0 WCTC2 WCTC1 WCTC0

};

enum  AFE_OPCODES {
AFE_OPCODE_WAKEUP   =0x02,      //Wakeup from standby mode 0000 0010 (02h) �
AFE_OPCODE_STANDBY =0x04,       //Enter standby mode 0000 0100 (04h) �
AFE_OPCODE_RESET    =0x06,      //Reset the device 0000 0110 (06h) �
AFE_OPCODE_START    =0x08,      //Start/restart (synchronize) conversions 0000 1000 (08h) �
AFE_OPCODE_STOP     =0x0A,          //Stop conversion 0000 1010 (0Ah) �
AFE_OPCODE_RDATAC   =0x10,      //Enable Read Data Continuous mode. 0001 0000 (10h) � This mode is the default mode at power up.(1)
AFE_OPCODE_SDATAC   =0x11,      //Stop Read Data Continuously mode 0001 0001 (11h) �
AFE_OPCODE_RDATA    =0x12,      //Read data by command; supports multiple read back. 0001 0010 (12h) �
AFE_OPCODE_RREG     =0x20,          //Read n nnnn registers starting at address r rrrr 001r rrrr (2xh)(2) 000n nnnn (2)
AFE_OPCODE_WREG     =0x40           //Write n nnnn registers starting at address r rrrr 010r rrrr (4xh)(2) 000n nnnn (2)
};


enum  AFE_CH_ADD {
CH_1=3,
CH_2=6,
CH_3=9,
CH_4=12,
CH_5=15,
CH_6=18,
CH_7=21,
CH_8=24
};


enum  AFE_CH_V4 {
LEAD_1   =CH_2,
LEAD_2   =CH_3,
V1   =CH_8,//CH_8,
V2   =CH_1,//CH_1,
V3   =CH_6,
V4   =CH_5,
V5   =CH_4,
V6   =CH_7
};


#define SCAN_BUF_SIZE 1
#define SCAN_BUF_SIZE_Dummy 12
#define SCAN_BUF_SIZE_Run 10


//---------------------------------------------------------------------------
typedef struct {
     uint8_t cOneScanData[27]; // contains 24 bits of status + 24 bits of data for each channel
     uint8_t iTimeStamp;
                                // in the same order as it comes out of AFE

} strOneScan;


typedef struct {
      uint8_t iIptr;             // varies from 0-Max scan buffer size. Used by Periodic event to push scan data into the buffer
     uint8_t iOptr;             // varies from 0-Max scan buffer size. Used by BLE event to take out data
     uint8_t iCount;                // tells how many Scan data points are available
     strOneScan ScanData[SCAN_BUF_SIZE];
      uint8_t iOverrunFlag;      // This will be set when In pointer overtakes Outpointer
      uint8_t iTime;
} strScanBuffer;


//typedef struct{
//    volatile unsigned int iCurrentSec; // variable to read the time from the hardware
//    unsigned int iPreviousSec;
//    unsigned int iEncodeTime;
//    union{
//        unsigned int iTimeValue;
//        char cHHMMSS[3];
//    }Derivetime;
//}Timeobject;



/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task creation function for the Heart Rate.
 */
//extern void HeartRate_createTask(void);
void PutDataIntoScanBuffer(void);



/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task creation function for the Heart Rate.
 */
extern void Sydantek_Afeinit(void);
/*********************************************************************
*********************************************************************/







#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_SERVICES_SYDANTEK_H_ */
