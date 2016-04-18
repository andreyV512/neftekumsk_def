#pragma once 
#include "Base.hpp"

class CExpressBase: public CBase
{
public:
	CExpressBase(){}
	void Open(wchar_t *path)
	{
		wchar_t buf[2048];
		GetPrivateProfileSection(L"oledb", buf, 2048, path);//L"./connect.udl");	
		_bstr_t strcnn(buf);

		try
		{
			conn.CreateInstance(__uuidof(ADODB::Connection)); 
			conn->Open( strcnn, L"", L"", NULL);
		}
		catch(...)
		{   
			wsprintf(buf, L"���������� ���������� ���� ������ ����� ���� ����������� '%s'", path);
			MessageBox(0, buf, L"������!!!", MB_ICONHAND);
		}		
	}
};