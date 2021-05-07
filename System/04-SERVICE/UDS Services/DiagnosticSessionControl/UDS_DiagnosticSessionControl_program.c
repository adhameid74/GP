/**
 * @file UDS_DiagnosticSessionControl_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 04-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "CAN_interface.h"
#include "DoCAN_interface.h"

#include "UDS_DiagnosticSessionControl_interface.h"
#include "UDS_DiagnosticSessionControl_private.h"
#include "UDS_DiagnosticSessionControl_config.h"

u8 UDS_DiagnosticSessionControl_voidStartDefaultSession()
{
	UDS_u8CURRENT_SESSION = UDS_DEFAULT_SESSION;
}

u8 UDS_DiagnosticSessionControl_voidStartProgrammingSession()
{
	UDS_u8CURRENT_SESSION = UDS_PROGRAMMING_SESSION;
}

u8 UDS_DiagnosticSessionControl_voidStartExtendedSession()
{
	UDS_u8CURRENT_SESSION = UDS_EXTENDED_SESSION;
}

u8 UDS_DiagnosticSessionControl_voidStartSafetySession()
{
	UDS_u8CURRENT_SESSION = UDS_SAFETY_SESSION;
}

u8 UDS_DiagnosticSessionControl_voidStartSession(u8 Copy_u8SessionId)
{
	if (UDS_DEFAULT_SESSION == Copy_u8SessionId)
	{
		UDS_DiagnosticSessionControl_voidStartDefaultSession();
	}
	else if (UDS_PROGRAMMING_SESSION == Copy_u8SessionId)
	{
		UDS_DiagnosticSessionControl_voidStartProgrammingSession();
	}
	else if (UDS_EXTENDED_SESSION == Copy_u8SessionId)
	{
		UDS_DiagnosticSessionControl_voidStartExtendedSession();
	}
	else if (UDS_SAFETY_SESSION == Copy_u8SessionId)
	{
		UDS_DiagnosticSessionControl_voidStartSafetySession();
	}
	else
	{
		// Error
	}
}
