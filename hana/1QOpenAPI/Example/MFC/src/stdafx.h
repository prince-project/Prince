
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#define VERSION_INFO	_T("v 2.2")
#define PROGRAM_NAME	_T("하나금융투자 Open API 예제")

#define UM_CHILD_CLOSE	WM_USER + 100	//자식 대화창 종료

/***********************************
* 통신조회 응답 옵션값
***********************************/
namespace CommRecvOpt
{
	enum
	{
		TranCode		= 0, //Tr코드
		PrevNextCode	= 1, //연속데이타 구분(0:없음, 1:이전, 2:다음, 3:이전/다음)
		PrevNextKey		= 2, //연속조회키
		MsgCode			= 3, //메시지코드
		Msg				= 4, //메시지
		SubMsgCode		= 5, //부가메시지코드
		SubMsg			= 6, //부가메시지
		Error			= 7	 //에러여부
	};
}

/***********************************
 * 통신 상태 이벤트
 ***********************************/
namespace CommEvent
{
	enum
	{
		Connected = 100,		// 연결 완료
		Connecting = 101,		// 소켓연결중
		Closed = 102,			// 소켓 단절 상태
		Closing = 103,			// 소켓 단절 중
		ReconnectRequest = 104,	// 재접속 요청
		ConnectFail = 105,		// 소켓 연결 실패

		//서버 공지 메시지
		NotifyMultiLogin = 150,	// 다중접속 알림 메시지
		NotifyEmergency = 151,	// 긴급공지 메시지

		//팝업메시지
		PopUpMsg = 160
	};
}

/***********************************
* FID 데이터 보관용 
* !!!!!!!!! 주의 아래 소스는 절대 수정하시면 안 됩니다!!!!!!!!!!!
***********************************/
class CCommRecvData
{
public:
	CCommRecvData()
	{
		m_ptrBuf = NULL;
		m_nRow = 0;
		m_nCol = 0;
	}

	virtual ~CCommRecvData() {}

	char** m_ptrBuf;
	int m_nRow;
	int m_nCol;

public:

	int GetRowCnt() { return m_nRow; }
	int GetColCnt() { return m_nCol; }

	char* GetItem(int nRow, int nCol)
	{
		if (!m_ptrBuf) return NULL;

		if (nRow < 0 || nCol < 0)
		{
			ASSERT(FALSE);
			return NULL;
		}

		if (nRow >= m_nRow || nCol >= m_nCol)
		{
			ASSERT(FALSE);
			return NULL;
		}

		int nArrIndex = (nRow * m_nCol) + nCol;
		return m_ptrBuf[nArrIndex];
	}
};
