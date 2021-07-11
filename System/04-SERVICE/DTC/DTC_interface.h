/**
 * @file DTC_interface.h
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief  
 * @version 1
 * @date 2021-5-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef DTC_INTERFACE_H
#define DTC_INTERFACE_H

#define DTC_EEPROM_START_ADDRESS			0x0000

#define DTC_TEST_RESULT_UNCOMPLITED			0
#define DTC_TEST_RESULT_PASSED				1
#define DTC_TEST_RESULT_FAILED				2
#define DTC_NUMBER							19

typedef enum
{
    DTC_UsonicEchoDisconnect = 0x00,
    DTC_UsonicEchoNoReceive = 0x01,
    DTC_UsonicCloseDistance = 0x02,
    DTC_UsonicNormalDistance = 0x03,
    DTC_UsonicLongDistance = 0x04,
    DTC_CANTxFailure = 0x05,
    DTC_CANNonEmptyFilter = 0x06,
    DTC_VSenVoltageHigh = 0x07,
    DTC_VSenVoltageLOW = 0x08,
	DTC_VSenNotReading = 0x09,
	DTC_SpeedNotMatched = 0x10,
	DTC_SpeedExceededLimit = 0x11,
	DTC_SpeedNotReading = 0x12,
	DTC_I2CStartBitNotGenerated = 0x13,
	DTC_I2CAddressNotTransmitted = 0x14,
	DTC_I2CTxFailure = 0x15,
	DTC_I2CRxFailure = 0x16,
	DTC_UARTTxFailure = 0x17,
	DTC_UARTRxFailure = 0x18,
} dtcCategory_e;



	// **************************** General Failure Information ***********************************
	
	/*dctCat_NoSubtypeInformation = 0x00,			
	dctCat_GeneralElectricalFailure = 0x01,		
	dctCat_GeneralSignalFailure = 0x02,			
	dctCat_PWM = 0x03,							
	dctCat_SystemInternalFailure = 0x04,		
	dctCat_SystemProgrammingFailure = 0x05,		
	dctCat_AlgorithmBasedFailure = 0x06,		
	dctCat_MechanicalFailure = 0x07,			
	dctCat_BusSignalOrMessageFailure = 0x08,	
	dctCat_ComponentFailure = 0x09,				
	
	// **************************** General Electrical Failures ***********************************
	// This category includes standard wiring failure modes (i.e. shorts and opens), and direct current (DC) quantities related by Ohm's Law.
	dctCat_CircuitShortToGround = 0x11,
	dctCat_CircuitShortToBattery = 0x12,
	dctCat_CircuitOpen = 0x13,
	dctCat_CircuitShortToGroundOrOpen = 0x14,
	dctCat_CircuitShortToBatteryOrOpen = 0x15,
	dctCat_CircuitVoltageBelowThreshold = 0x16,
	dctCat_CircuitVoltageAboveThreshold = 0x17,
	dctCat_CircuitCurrentBelowThreshold = 0x18,
	dctCat_CircuitCurrentAboveThreshold = 0x19,
	dctCat_CircuitResistanceBelowThreshold = 0x1A,
	dctCat_CircuitResistanceAboveThreshold = 0x1B,
	dctCat_CircuitVoltageOutOfRange = 0x1C,
	dctCat_CircuitCurrentOutOfRange = 0x1D,
	dctCat_CircuitResistanceOutOfRange = 0x1E,
	dctCat_CircuitIntermittent = 0x1F,
	
	// ***************************** General Signal Failures **************************************
	// specifies quantities related to amplitude, frequency or rate of change, and wave shape.
	
	dctCat_SignalAmplitudeLowerMinimum = 0x21,
	dctCat_SignalAmplitudeHigherMaximum = 0x22,
	dctCat_SignalStuckLow = 0x23,					// ������ ������ ����� �������� ������
	dctCat_SignalStuckHigh = 0x24,					// ������ ������ ����� �������� �������
	dctCat_SignalWaveformFailure = 0x25,
	dctCat_SignalRateOfChangeBelowThreshold = 0x26,	// ������ �������� ������� ��������
	dctCat_SignalRateOfChangeAboveThreshold = 0x27,	// ������ �������� ������� ������
	dctCat_SignalBiasLevelFailure = 0x28,			// �������� �������� ������� ����� ������� � �.�.
	dctCat_SignalInvalid = 0x29,					// �������� ������
	dctCat_SignalErratic = 0x2F,					// Signal is momentarily implausible (not long enough for �signal invalid�) or discontinuous.
	
	// ***************************** System Internal Failures *************************************

	dctCat_GeneralChecksumFailure = 0x41,			// �������� ����������� ����� ��� ��������� ���� ������
	dctCat_GeneralMemoryFailure = 0x42,				// ������ ������ ��� ��������� �� ����
	dctCat_SpecialMemoryFailure = 0x43,				// ������ �������������� ������ ��� ��������� �� ����
	dctCat_DataMemoryFailure = 0x44,				// ������ ������ ������ (RAM)
	dctCat_ProgramMemoryFailure = 0x45,				// ������ ����������� ������ (ROM/Flash)
	dctCat_CalibrationMemoryFailure = 0x46,			// ������ ������ ����������/���������� (EEPROM)
	dctCat_WatchdogOrSafetyFailure = 0x47,
	dctCat_SupervisionSoftwareFailure = 0x48,
	dctCat_InternalElectronicFailure = 0x49,		// ����������� ����������� ���
	dctCat_IncorrectComponentInstalled = 0x4A,		// � ��� ��������� �������� (����������������) ���������
	dctCat_OverTemperature = 0x4B,					// ����������� ��� �� ��������� �������� ���������
	
		// **************************** System Programming Failures ***********************************
	
	dctCat_NotProgrammed = 0x51,
	dctCat_NotActivated = 0x52,						
	dctCat_Deactivated = 0x53,						
	dctCat_MissingCalibration = 0x54,				
	dctCat_NotConfigured = 0x55,					
	
	// ****************************** Algorithm Based Failures ************************************
		
	dctCat_SignalCalculationFailure = 0x61,
	dctCat_SignalCompareFailure = 0x62,				// ��� ��������� 2-� ��� ����� �������� �� �������������
	dctCat_CircuitOrComponentProtectionTimeout = 0x63,	// ���� ������� ���������� �������� ������� �����
	dctCat_SignalPlausibilityFailure = 0x64,		// ������������� ������
	dctCat_SignalHasTooFewTransitions = 0x65,
	dctCat_SignalHasTooManyTransitions = 0x66,
	dctCat_SignalIncorrectAfterEvent = 0x67,
	dctCat_EventInformation = 0x68,
	
	// ********************************* Mechanical Failures **************************************
			
	dctCat_ActuatorStuck = 0x71,					
	dctCat_ActuatorStuckOpen = 0x72,				
	dctCat_ActuatorStuckClosed = 0x73,				
	dctCat_ActuatorSlipping = 0x74,					
	dctCat_EmergencyPositionNotReachable = 0x75,	
	dctCat_WrongMountingPosition = 0x76,			
	dctCat_CommandedPositionNotReachable = 0x77,	
	dctCat_AlignmentOrAdjustmentIncorrect = 0x78,	
	dctCat_MechanicalLinkageFailure = 0x79,			
	dctCat_FluidLeakOrSealFailure = 0x7A,			
	dctCat_LowFluidLevel = 0x7B,		*/			
	


typedef union
{
	u8 Value;
	struct
	{
		u8
		WarningIndicatorRequested		: 1,		
		IsCritical						: 1,
        AutoRestore						: 1,		
		PowerOff						: 1,	

		dummy							: 4;
	};
} dtcPropBits_t;




typedef struct
{
	u16 Code;			                        //code uniqe for each dtc				
	dtcPropBits_t Bits;
	u8 AgingThreshold;							//the number after which the device may not work probably
	s8 TestFailedThreshold;						//threshold so that the test is considerd failed
	s8 TestPassedThreshold;						//threshold so that the test is considerd passed
	//u16 TestSamplePeriod;					
} dtcProperty_t;

typedef struct
{
	u8
	TestFailed							:	1,      //test failed this operation cycle
	ConfirmedDTC						:	1,      //confirmed dtc and save it in the eeprom
	TestFailedThisOperationCycle		:	1,      //confirmed failed this cycle
	WarningIndicatorRequested			:	1,      //turn the dashboard light
	TestNotCompletedThisOperationCycle	: 	1,		//the test not completed yet
	dummy1								:	3;
} dtcStatus_t;


typedef struct
{
	dtcProperty_t* Property;	
	dtcStatus_t Status;
	s8 FaultDetectionCounter;
	//u16 SamplePeriodCounter;
} dtcItem_t;



u8 DTC_u8DetectFault(dtcItem_t* it, u8 isFault);

#endif
