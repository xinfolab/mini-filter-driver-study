#include "process_callback.h"

NTSTATUS 
StartProcessCallback(
	)
{
	PAGED_CODE();

	//
	//	프로세스 콜백 등록
	//
	NTSTATUS status= PsSetCreateProcessNotifyRoutineEx(CreateProcessNotifyRoutineEx,
																  FALSE);
	if (!NT_SUCCESS(status))
	{
		log_err "PsSetCreateProcessNotifyRoutineEx() failed. status=0x%08x",
			status
			log_end;
		return status;
	}

	log_info "process callback registered." log_end;
	return status;
}

void
StopProcessCallback(
	)
{
	PAGED_CODE();

	//
	//	프로세스 콜백 해제
	//
	NTSTATUS status = PsSetCreateProcessNotifyRoutineEx(CreateProcessNotifyRoutineEx,
														TRUE);
	if (!NT_SUCCESS(status))
	{
		log_err "PsSetCreateProcessNotifyRoutineEx() failed. status=0x%08x",
			status
			log_end;
	}

	log_info "process callback registered." log_end;
}

VOID 
CreateProcessNotifyRoutineEx(
	_Inout_ PEPROCESS Process,
	_In_ HANDLE ProcessId,
	_Inout_opt_ PPS_CREATE_NOTIFY_INFO CreateInfo
	)
{
	PAGED_CODE();

	UNREFERENCED_PARAMETER(Process);

	if (NULL == CreateInfo)
	{
		log_info "process exiting. pid=%u", ProcessId log_end;
	}
	else
	{
		//
		//	공부 해봅시다!!
		//
		UNICODE_STRING notepad;
		RtlInitUnicodeString(&notepad, L"notepad.exe");
		if (true == equal_tail_unicode_string(const_cast<PUNICODE_STRING>(CreateInfo->ImageFileName),
											  &notepad,
											  true))
		{
			CreateInfo->CreationStatus = STATUS_ACCESS_DENIED;
			//CreateInfo->CreationStatus = STATUS_OBJECT_NAME_INVALID;
			log_info "block process creating!! ppid=%u, creator=%u, pid=%u, image=%wZ",
				CreateInfo->ParentProcessId,
				CreateInfo->CreatingThreadId.UniqueProcess,
				ProcessId,
				CreateInfo->ImageFileName
				log_end;
		}
		else
		{
			//
			//	프로세스 생성
			//
			log_info "process creating!! ppid=%u, creator=%u, pid=%u, image=%wZ",
				CreateInfo->ParentProcessId,
				CreateInfo->CreatingThreadId.UniqueProcess,
				ProcessId,
				CreateInfo->ImageFileName
				log_end;
		}
		log_info "block process creating!! ppid=%u, creator=%u, pid=%u, image=%wZ",
			CreateInfo->ParentProcessId,
			CreateInfo->CreatingThreadId.UniqueProcess,
			ProcessId,
			CreateInfo->ImageFileName
			log_end;
	}
}
