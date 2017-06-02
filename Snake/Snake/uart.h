#include <windows.h> 
#include <stdio.h> 
#include <stdlib.h>
using namespace std;

HANDLE hCom;
OVERLAPPED m_ov;
COMSTAT comstat;
DWORD m_dwCommEvents;

int receive[7];
char sent[12];

bool openport(char *portname)
{
	DWORD dwError;

	hCom = CreateFileA(portname, GENERIC_READ|GENERIC_WRITE , 0 , NULL , OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED , NULL);

	if(hCom == INVALID_HANDLE_VALUE)
	{
		dwError = GetLastError(); //处理错误
	}
	return true;
}
/*
typedef struct _DCB { // dcb    
	DWORD DCBlength;          //DCB结构体大小    
	DWORD BaudRate;          //波特率     
	DWORD fBinary: 1;   //是否是二进制，一般设置为TRUE    
	DWORD fParity: 1;//是否进行奇偶校验     
	DWORD fOutxCtsFlow:1; //CTS线上的硬件握手    
	DWORD fOutxDsrFlow:1; //DSR线上的硬件握手    
	DWORD fDtrControl:2; //DTR控制   
	DWORD fDsrSensitivity:1;     
	DWORD fTXContinueOnXoff:1;     
	DWORD fOutX: 1;     //是否使用XON/XOFF协议    
	DWORD fInX: 1;       //是否使用XON/XOFF协议    
	DWORD fErrorChar: 1;  //发送错误协议    
	DWORD fNull: 1;             
	DWORD fRtsControl:2;       
	DWORD fAbortOnError:1;      
	DWORD fDummy2:17;    
	WORD wReserved;            
	WORD XonLim;   //设置在XON字符发送之前inbuf中允许的最少字节数   
	WORD XoffLim;  //在发送XOFF字符之前outbuf中允许的最多字节数   
	BYTE ByteSize; //数据宽度，一般为8，有时候为7  
	BYTE Parity;   //奇偶校验   
	BYTE StopBits;  //停止位数    
	char XonChar;  //设置表示XON字符的字符,一般是采用0x11这个数值  
	char XoffChar; //设置表示XOFF字符的字符,一般是采用0x13这个数值    
	char ErrorChar;          
	char EofChar;             
	char EvtChar;            
	WORD wReserved1;     } DCB;
	*/
bool setupdcb(int rate_arg)//设置DCB
{
	
	DCB dcb;
	int rate = rate_arg;
	memset(&dcb , 0 , sizeof(dcb));
	if(!GetCommState(hCom,&dcb))//获取当前DCB配置  
		return false;

	dcb.DCBlength = sizeof(dcb);
	dcb.BaudRate = rate;
	dcb.Parity = NOPARITY;
	dcb.ByteSize=8; //每个字节有8位
	dcb.StopBits=ONESTOPBIT; //两个停止位
	if(SetCommState(hCom,&dcb) == 0)
			return false;
	else
		return true;
}

bool setuptimeout(DWORD ReadInterval,DWORD ReadTotalMultiplier,DWORD ReadTotalconstant,DWORD WriteTotalMultiplier,DWORD WriteTotalconstant)
{
	COMMTIMEOUTS timeouts;
	timeouts.ReadIntervalTimeout=ReadInterval;
	timeouts.ReadTotalTimeoutConstant=ReadTotalconstant;
	timeouts.ReadTotalTimeoutMultiplier=ReadTotalMultiplier;
	timeouts.WriteTotalTimeoutConstant;
	timeouts.WriteTotalTimeoutMultiplier=WriteTotalMultiplier;
	if(!SetCommTimeouts(hCom, &timeouts))
	{
		return false;
	}
	else
		return true;
}

void ReceiveChar( )
{
	int count = 0;
	BOOL  bRead = TRUE;
	BOOL  bResult = TRUE;
	DWORD dwError = 0;
	DWORD BytesRead = 0;
	char RXBuff;
	for (;count<7;)
	{
		bResult = ClearCommError(hCom, &dwError, &comstat);
		if (comstat.cbInQue == 0)
			continue;
		if (bRead)
		{
			bResult = ReadFile(hCom,		// Handle to COMM port
			&RXBuff,			// RX Buffer Pointer
			1,					// Read one byte
			&BytesRead,			// Stores number of bytes read
			&m_ov);   		// pointer to the m_ov structure
			//	printf("%d\n",RXBuff);
			receive[count]=RXBuff;
			//	printf("%d\n",receive[count]);
			//	printf("%d\n",bResult);
			if(!bResult)
		{
			count++;
		}
		if (!bResult)
		{
			switch (dwError = GetLastError())
			{
			case ERROR_IO_PENDING:
				{
					bRead = FALSE;
					break;
				}
			default:
				{
					break;
				}
			}
		}
		else
		{
			bRead = TRUE;
		}
	}  // close if (bRead)
	if (!bRead)
	{
		bRead = TRUE;
		bResult = GetOverlappedResult(hCom,	// Handle to COMM port
			&m_ov,	// Overlapped structure
			&BytesRead,		// Stores number of bytes read
			TRUE); 			// Wait flag
	}
}
}


int WriteChar(char* m_szWriteBuffer,DWORD m_nToSend)
{
	BOOL bWrite = TRUE;
	BOOL bResult = TRUE;
	DWORD BytesSent = 0;
	//HANDLE	m_hWriteEvent;
	//ResetEvent(m_hWriteEvent);
	if (bWrite)
	{
		m_ov.Offset = 0;
		m_ov.OffsetHigh = 0;
		// Clear buffer
		bResult = WriteFile(hCom,	// Handle to COMM Port
		m_szWriteBuffer,	// Pointer to message buffer in calling finction
		m_nToSend,		// Length of message to send
		&BytesSent,		// Where to store the number of bytes sent
		&m_ov );			// Overlapped structure
		if (!bResult)
		{
			DWORD dwError = GetLastError();
			switch (dwError)
			{
				case ERROR_IO_PENDING:
				{
					// continue to GetOverlappedResults()
					BytesSent = 0;
					bWrite = FALSE;
					break;
				}
				default:
				{
					// all other error codes
					break;
				}
			}
		}
	} // end if(bWrite)

	if (!bWrite)
	{
		bWrite = TRUE;
		bResult = GetOverlappedResult(hCom,	// Handle to COMM port
					&m_ov,		// Overlapped structure
					&BytesSent,		// Stores number of bytes sent
					TRUE); 			// Wait flag
		// deal with the error code
		if (!bResult)
		{
			printf("GetOverlappedResults() in WriteFile()");
		}
	} // end if (!bWrite)
	// Verify that the data size send equals what we tried to send
	if (BytesSent != m_nToSend)
	{
		printf("WARNING: WriteFile() error.. Bytes Sent: %d; Message Length: %d\n", BytesSent, strlen((char*)m_szWriteBuffer));
	}
	return true;
}