
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// HFCommClient.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

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