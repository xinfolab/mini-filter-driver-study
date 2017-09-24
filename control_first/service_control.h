#pragma once
#include <Windows.h>
#include <string>
#include <memory>

typedef std::shared_ptr<SC_HANDLE> sc_handle_ptr;
struct sc_handle_deleter
{
	void operator()(SC_HANDLE* phandle) const
	{
		CloseServiceHandle(*phandle);
		delete phandle;
	}
};


typedef class service_control
{
public:
	service_control(
		_In_ const wchar_t* binary_path,
		_In_ const wchar_t* service_name,
		_In_ const wchar_t* service_display_name,
		_In_ const wchar_t* altitude,
		_In_ uint32_t flags,
		_In_ bool unistall_service
	);
	~service_control();

	bool install_service(_In_ bool auto_start);

	bool start_service();
	bool start_service(_In_ SC_HANDLE service_handle);

	bool stop_service();
	bool stop_service(_In_ SC_HANDLE service_handle);

	bool service_installed(_In_ SC_HANDLE scm_handle, _Out_ bool& installed);

	bool service_started(_In_ SC_HANDLE service_handle, _Out_ bool& started);

	bool uninstall_service();
	bool uninstall_service(_In_ SC_HANDLE scm_hanlde);

private:
	bool			_unistall_service;
	HANDLE			_driver_handle;
	std::wstring	_binary_path;
	std::wstring	_service_name;
	std::wstring	_service_display_name;

	uint32_t		_service_type;

	bool			_is_minifilter;
	std::wstring	_altitude;
	uint32_t		_flags;

}*pservice_control;
