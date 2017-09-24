#pragma once
#include "stdafx.h"

bool
extract_last_tokenW(
	_In_ std::wstring& org_string,
	_In_ const std::wstring& token,
	_Out_ std::wstring& out_string,
	_In_ bool forward,
	_In_ bool delete_token
);


bool
get_module_path(
	_In_ const wchar_t* module_name,
	_Out_ std::wstring& module_path
);

bool get_current_module_path(_Out_ std::wstring& module_path);


std::wstring get_current_module_dirEx();


bool get_current_module_dir(_Out_ std::wstring& module_dir);