#include "stdafx.h"
#include "regstry_control.h"

HKEY RUCreateKey(
	_In_ HKEY RootKey,
	_In_ const wchar_t* SubKey,
	_In_ bool ReadOnly
	)
{
	DWORD ret = ERROR_SUCCESS;
	DWORD disposition = 0;
	HKEY sub_key_handle = NULL;
	REGSAM sam = (true == ReadOnly) ? KEY_READ : KEY_ALL_ACCESS;

	ret = RegCreateKeyExW(RootKey, SubKey, 0, NULL, 0, sam, NULL, &sub_key_handle, &disposition);
	if (ERROR_SUCCESS != ret)
	{
		printf("RegCreateKeyExW(%ws) failed, ret = %u\n", SubKey, ret);
		return NULL;
	}
	else
	{
		return sub_key_handle;
	}
}

bool RUSetString(
	_In_ HKEY key_handle,
	_In_ const wchar_t* value_name,
	_In_ const wchar_t* value
	)
{
	_ASSERTE(nullptr != key_handle);
	_ASSERTE(nullptr != value_name);
	_ASSERTE(nullptr != value);
	if (nullptr == key_handle || nullptr == value_name || nullptr == value) return false;

	DWORD ret = RegSetValueExW(key_handle,
							   value_name,
							   0,
							   REG_SZ,
							   (LPBYTE)value,
							   static_cast<uint32_t>(((wcslen(value) + 1) * sizeof(wchar_t))));
	if (ERROR_SUCCESS != ret)
	{
		printf("RegSetValueExW(%ws) failed, ret = %u\n",
			   value_name,
			   ret);
		return false;
	}

	return true;
}

bool RUWriteDword(
	_In_ HKEY key_handle,
	_In_ const wchar_t* value_name,
	_In_ DWORD value
	)
{
	_ASSERTE(nullptr != key_handle);
	_ASSERTE(nullptr != value_name);
	if (nullptr == key_handle || nullptr == value_name) return false;

	DWORD ret = RegSetValueExW(key_handle,
							   value_name,
							   0,
							   REG_DWORD,
							   (PBYTE)&value,
							   sizeof(DWORD));
	if (ERROR_SUCCESS != ret)
	{
		printf("RegSetValueExW(%ws) failed, ret = %u\n",
			   value_name,
			   ret);
		return false;
	}

	return true;
}

void RUCloseKey(_In_ HKEY Key)
{
	DWORD ret = RegCloseKey(Key);
	if (ERROR_SUCCESS != ret)
	{
		//printf( "RegCloseKey() failed, ret = %u", ret )
	}
}