#ifndef __API_H__
#define __API_H__

#define EXPORT extern "C" __declspec(dllexport)

#include <objbase.h>
#include <winioctl.h>
#include "public.h"


#define CAN200_DEPRECATE_TEXT(_Text) __declspec(deprecated(_Text))
#define CAN200_DEPRECATE(_Replacement) CAN200_DEPRECATE_TEXT("This function is deprecated. Consider using " #_Replacement " instead.")

//EXPORT RX_TX_Buffer msgbuf[];
EXPORT int __stdcall CAN200_GetNumberDevice(int *count);
EXPORT HANDLE __stdcall CAN200_Open(int number);
EXPORT int __stdcall CAN200_Close(HANDLE Handle);
EXPORT int __stdcall CAN200_SetWorkMode(HANDLE Handle, int Channel, int Mode);
EXPORT int __stdcall CAN200_GetWorkMode(HANDLE Handle, int Channel, int *Mode);
EXPORT int __stdcall CAN200_SetDriverMode(HANDLE Handle, int Channel, int Mode);
EXPORT int __stdcall CAN200_GetConfig(HANDLE Handle, pTCAN_VPDData Buffer);
EXPORT int __stdcall CAN200_SetCANSpeed(HANDLE Handle, int Channel, unsigned int Speed);
EXPORT int __stdcall CAN200_GetCANSpeed(HANDLE Handle, int Channel, unsigned int *Speed);
EXPORT int __stdcall CAN200_GetStatus(HANDLE Handle, int Channel, int *Status);
EXPORT int __stdcall CAN200_SetInterruptSource(HANDLE Handle, int Channel, int Source);
EXPORT int __stdcall CAN200_GetInterruptSource(HANDLE Handle, int Channel, int *Source);
EXPORT int __stdcall CAN200_SetCommand(HANDLE Handle, int Channel, int Command);
EXPORT int __stdcall CAN200_SetTxBuffer(HANDLE Handle, int Channel, pRX_TX_Buffer Buffer);
EXPORT int __stdcall CAN200_DefEvent(HANDLE Handle, int Channel, HANDLE hEvent);
EXPORT int __stdcall CAN200_GetEventData(HANDLE Handle, int Channel, pTEventData Buffer);
EXPORT int __stdcall CAN200_GetRxBuffer(HANDLE Handle, int Channel, pRX_TX_Buffer Buffer);
EXPORT int __stdcall CAN200_B_SetInputFilter(HANDLE Handle, int Channel, bFilter_t *filter);
EXPORT int __stdcall CAN200_B_GetInputFilter(HANDLE Handle, int Channel, bFilter_t *filter);
EXPORT int __stdcall CAN200_P_SetInputFilter(HANDLE Handle, int Channel, pFilter_t *filter);
EXPORT int __stdcall CAN200_P_GetInputFilter(HANDLE Handle, int Channel, pFilter_t *filter);
EXPORT int __stdcall CAN200_P_SetRxErrorCounter(HANDLE Handle, int Channel, int Counter);
EXPORT int __stdcall CAN200_P_GetRxErrorCounter(HANDLE Handle, int Channel, int *Counter);
EXPORT int __stdcall CAN200_P_SetTxErrorCounter(HANDLE Handle, int Channel, int Counter);
EXPORT int __stdcall CAN200_P_GetTxErrorCounter(HANDLE Handle, int Channel, int *Counter);
EXPORT int __stdcall CAN200_P_SetErrorWarningLimit(HANDLE Handle, int Channel, int Limit);
EXPORT int __stdcall CAN200_P_GetErrorWarningLimit(HANDLE Handle, int Channel, int *Limit);
EXPORT int __stdcall CAN200_P_GetArbitrationLostCapture(HANDLE Handle, int Channel, int *Data);
EXPORT int __stdcall CAN200_P_GetRxMessageCounter(HANDLE Handle, int Channel, int *Counter);
EXPORT int __stdcall CAN200_P_GetErrorCode(HANDLE Handle, int Channel, int *Code);
EXPORT int __stdcall CAN200_GetOverCounter(HANDLE Handle, int Channel, int *Counter);
EXPORT void __stdcall CAN200_HardReset(HANDLE Handle, int Channel);
EXPORT int __stdcall CAN200_SetCANReg(HANDLE Handle, int Channel, int Port, int Data);
EXPORT int __stdcall CAN200_GetCANReg(HANDLE Handle, int Channel, int Port, int *Data);
EXPORT int __stdcall CAN200_Recv(HANDLE Handle, int Channel, pRX_TX_Buffer Buffer, int timeout);
EXPORT int __stdcall CAN200_RecvPack(HANDLE Handle, int Channel, int *count, int timeout);
EXPORT int __stdcall CAN200_GetLastError(void);
EXPORT UINT64 __stdcall CAN200_GetAPIVer();
//EXPORT void __stdcall CAN200_GetBuf(UCHAR *arr, int count_pack);
EXPORT BYTE __stdcall CAN200_GetByte(int num);
EXPORT void __stdcall CAN200_Recv_Enable(HANDLE Handle, int Channel, int timeout);
EXPORT void __stdcall CAN200_Recv_Disable();
EXPORT int __stdcall CAN200_Pop(pRX_TX_Buffer Buffer);
EXPORT int __stdcall CAN200_VecSize();
EXPORT int __stdcall CAN200_ClearBuf(HANDLE Handle, int Channel);



#ifdef __USE__OLD_CAN200_FUNCTIONS__
//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_Open) unsigned short CANOpen(int number);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_Close) void CANClose(int number);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_Open) int SelectCAN(int number);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_Open) void chBaseAddress(unsigned int Base);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_SetWorkMode) unsigned short SetWorkMode(unsigned short Mode);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_GetWorkMode) unsigned short GetWorkMode(void);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_SetDriverMode) void SetDriverMode(unsigned short Mode);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_GetConfig) unsigned short GetConfig(pTCAN_VPDData Buffer);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_SetCANSpeed) unsigned short SetCANSpeed(unsigned int Speed);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_GetStatus) unsigned short GetStatus(void);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_B_SetInputFilter) unsigned short B_SetInputFilter(unsigned short Filter1,
																		  unsigned short Filter2);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_B_SetInterruptSource) void SetInterruptSource(unsigned short Source);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_P_SetInputFilter) unsigned short P_SetInputFilter(unsigned short mode,
																		  unsigned short ACR0,
																		  unsigned short ACR1,
																		  unsigned short ACR2,
																		  unsigned short ACR3,
																		  unsigned short AMR0,
																		  unsigned short AMR1,
																		  unsigned short AMR2,
																		  unsigned short AMR3);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_P_SetRxErrorCounter) unsigned short P_SetRxErrorCounter(unsigned short Counter);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_P_GetRxErrorCounter) int P_GetRxErrorCounter(void);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_P_SetTxErrorCounter) unsigned short P_SetTxErrorCounter(unsigned short Counter);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_P_GetTxErrorCounter) int P_GetTxErrorCounter(void);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_P_SetErrorWarningLimit) unsigned short P_SetErrorWarningLimit(unsigned short Limit);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_P_GetErrorWarningLimit) int P_GetErrorWarningLimit(void);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_P_GetArbitrationLostCapture) int P_GetArbitrationLostCapture(void);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_P_GetRxMessageCounter) int P_GetRxMessageCounter(void);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_P_GetErrorCode) int P_GetErrorCode(void);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_SetCommand) void SetCommand(unsigned short Command);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_SetTxBuffer) unsigned short SetTxBuffer(pRX_TX_Buffer Buffer);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_DefEvent) void DefEvent(HANDLE hEvent, BOOL fEventSet);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_GetEventData) unsigned short GetEventData(pTEventData Buffer);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_GetRxBuffer) unsigned short GetRxBuffer(pRX_TX_Buffer Buffer);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_SetCANReg) void SetCANReg(unsigned short port, unsigned short data);

//-----------------------------------------------------------------------------
CAN200_DEPRECATE(CAN200_GetCANReg) unsigned short GetCANReg(unsigned short port);

#endif /* __USE__OLD_CAN200_FUNCTIONS__ */
/** \endcond */

#endif /* __API_H__ */