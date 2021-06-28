
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// HFCommClient.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"


void NumericString(CString& strValue, BOOL bNotDisplayZero = FALSE)
{
	CString strReturn;
	strValue.Trim();
	strValue.Remove(',');

	if (strValue.Find('.') != -1)
		strReturn.Format("%lf", _ttof(strValue));
	else
		strReturn.Format("%I64d", (INT64)_ttof(strValue));

	if (bNotDisplayZero && !_ttof(strReturn)) strReturn.Empty();

	strValue = strReturn;
}