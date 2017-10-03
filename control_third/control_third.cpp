// control_second.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "control_third.h"
#include "util.h"
#include "service_control.h"

#define CONTROL_FAILED -1
#define _pause _getch()

int main()
{
	std::wstringstream driver_path;
	driver_path << get_current_module_dirEx()
		<< "\\"
		<< process_control;

	service_control scm(driver_path.str().c_str(),
						third_study_service,
						third_study_service_display,
						third_study_altitude,
						third_study_flag,
						false);

	//
	//	filter 서비스 설치
	//
	if (true != scm.install_service(false))
	{
		printf("scm.install_service() failed.\n");
		return CONTROL_FAILED;
	}

	printf("%ws installed.\n", third_study_service);
	printf("Press any key to start...\n");
	_pause;

	//
	//	filter 서비스 시작
	//

	if (true != scm.start_service())
	{
		printf("scm.start_service() failed.\n");;
		return -1;
	}
	printf("%ws started.\n", third_study_service);;
	printf("Press any key to stop...\n");;
	_pause;

	//
	//	filter 서비스 종료
	// 
	if (true != scm.stop_service())
	{
		printf("scm.stop_service() failed. \n");;
		return -1;
	}
	printf("%ws stopped.\n", third_study_service);;
	printf("Press any key to uninstall...\n");;
	_pause;

	//
	//	filter 서비스 제거 
	// 
	if (true != scm.uninstall_service())
	{
		printf("scm.uninstall_service() failed. \n");;
		return -1;
	}
	printf("%ws uninstalled.\n", third_study_service);;
	printf("Press any key to finish...\n");;
	_pause;

	return 0;
}

