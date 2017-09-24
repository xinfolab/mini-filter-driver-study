#pragma once
#include "stdafx.h"

HKEY
RUCreateKey(
	_In_ HKEY RootKey,
	_In_ const wchar_t* SubKey,
	_In_ bool ReadOnly
	);


bool
RUSetString(
	_In_ HKEY key_handle,
	_In_ const wchar_t* value_name,
	_In_ const wchar_t* value
	);


bool
RUWriteDword(
	_In_ HKEY key_handle,
	_In_ const wchar_t* value_name,
	_In_ DWORD value
);


void RUCloseKey(_In_ HKEY Key);