#include "stdafx.h"
#include "util.h"

bool extract_last_tokenW(
	_In_ std::wstring& org_string,
	_In_ const std::wstring& token,
	_Out_ std::wstring& out_string,
	_In_ bool forward,
	_In_ bool delete_token
	)
{
	if (true == delete_token)
	{
		if (&org_string == &out_string)
		{
#ifndef TEST_EXPORTS
			_ASSERTE(!"prarameters conflict!\n");
#endif
			return false;
		}
	}

	size_t pos = org_string.rfind(token);
	if (std::wstring::npos == pos)
	{
		out_string = org_string;
		return true;
	}

	if (true == forward)
	{
		out_string = org_string.substr(0, pos);
		if (delete_token) org_string.erase(0, pos + token.size());
	}
	else
	{
		out_string = org_string.substr(pos + token.size(), org_string.size());
		if (delete_token) org_string.erase(pos, org_string.size());
	}
	return true;
}

bool get_module_path(
	_In_ const wchar_t * module_name,
	_Out_ std::wstring & module_path
	)
{
	DWORD  ret = 0;
	DWORD  buf_len = MAX_PATH;
	wchar_t* buf = (wchar_t*)malloc(buf_len * sizeof(wchar_t));
	if (NULL == buf) return false;

	for (;;)
	{
		ret = GetModuleFileNameW(GetModuleHandleW(module_name), buf, buf_len);
		if (ret == buf_len)
		{
			// buf 가 작은 경우 buf_len 만큼 버퍼가 잘리고, buf_len 리턴 (에러로 간주)
			// 버퍼 사이즈를 2배 늘려서 재 시도
			free(buf);

			buf_len *= 2;
			buf = (wchar_t*)malloc(buf_len * sizeof(wchar_t));
			if (NULL == buf) return false;
		}
		else
		{
			module_path = buf;
			free(buf);
			return true;
		}
	}

	//return false;	// never reach here!
}

bool get_current_module_path(_Out_ std::wstring & module_path)
{
	return get_module_path(NULL, module_path);
}

std::wstring get_current_module_dirEx()
{
	std::wstring out;
	if (true != get_current_module_dir(out))
	{
		return L"";
	}
	else
	{
		return out;
	}
}

bool get_current_module_dir(_Out_ std::wstring & module_dir)
{
	std::wstring module_path;
	if (true != get_current_module_path(module_path))
	{
		printf("get_current_module_path()\n");
		return false;
	}

	if (true != extract_last_tokenW(module_path,
									L"\\",
									module_dir,
									true,
									false))
	{
		printf("extract_last_tokenW( org=%ws )\n",
			   module_path.c_str());
		module_dir = L"";
		return false;
	}

	return true;
}
