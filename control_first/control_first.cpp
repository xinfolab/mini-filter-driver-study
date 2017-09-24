// control_first.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "control_first.h"
#include "util.h"
#include "../control_first/service_control.h"

#define CONTROL_FAILED -1
#define _pause _getch()

int main()
{
	std::wstringstream driver_path;
	driver_path << get_current_module_dirEx()
		<< "\\"
		<< first_study;

	service_control scm(driver_path.str().c_str(),
						first_study_service,
						first_study_service_display,
						first_study_altitude,
						first_study_flag,
						false);

	//
	//	filter 서비스 설치
	//
	if (true != scm.install_service(false))
	{
		printf("scm.install_service() failed.\n");
		return CONTROL_FAILED;
	}

	printf("%ws installed.\n", first_study_service);
	printf("Press any key to start...\n");
	_pause;

	//
	//	filter 서비스 시작
	//

	if (true != scm.start_service())
	{
		printf( "scm.start_service() failed.\n" );;
		return -1;
	}
	printf( "%ws started.\n", first_study_service);;
	printf( "Press any key to stop...\n" );;
	_pause;

	//
	//	filter 서비스 종료
	// 
	if (true != scm.stop_service())
	{
		printf( "scm.stop_service() failed. \n" );;
		return -1;
	}
	printf( "%ws stopped.\n", first_study_service);;
	printf( "Press any key to uninstall...\n" );;
	_pause;

	//
	//	filter 서비스 제거 
	// 
	if (true != scm.uninstall_service())
	{
		printf( "scm.uninstall_service() failed. \n" );;
		return -1;
	}
	printf( "%ws uninstalled.\n", first_study_service);;
	printf( "Press any key to finish...\n" );;
	_pause;

    return 0;
}

