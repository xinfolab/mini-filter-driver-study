# Minifilter driver study

# 실습 환경

## 디버거 설정 (빌드 머신)

[Download the Windows Driver Kit (WDK)](https://developer.microsoft.com/en-us/windows/hardware/windows-driver-kit) 를 참조하고, VMWare 또는 VirtualBox, Hyper-V 등을 통해 가상머신을 생성한다. 실습에서는 VMWare 를 사용한다.  

1. Visual Studio 설치 ( [Visual studio 2015](https://go.microsoft.com/fwlink/p/?LinkId=534599) )
    + 반드시 C/C++ 개발환경을 모두 설치해야 함 (설치 옵션 선택)
1. SDK 설치 ( [Window SDK for Windows 10, version 1703](https://go.microsoft.com/fwlink/p/?LinkID=845298) )
1. WDK 설치 ( [WDK for Windows 10, version 1703](https://go.microsoft.com/fwlink/p/?LinkId=845980) )

1. Virtual KD 설치 ( [Virtual KD](http://virtualkd.sysprogs.org/) )
    + [install](http://virtualkd.sysprogs.org/tutorials/install/) 에 설명된 대로 Debugger/Debuggee 설정을 완료할 것
    + Debuggee 의 커널을 Break 할 수 있는지 반드시 확인할 것

1. git 설치 

    + [git for Windows](https://git-for-windows.github.io/)
    + [tortoise git](https://tortoisegit.org/download/)

1. WDK 샘플 빌드

    + 개발환경에 [Windows-driver-samples](https://github.com/Microsoft/Windows-driver-samples) 을 다운로드 혹은 clone 해 둔다. 
    + `Windows-driver-samples/filesys/miniFilter/` 아래에 있는 프로젝트들을 Visual studio 2015 를 통해 빌드해본다. 
    + 깔끔하게 빌드가 되지 않는다면 뭔가 문제가 있는것이니 자신의 환경설정에 문제가 없는지 다시 한번 확인한다.

1. Python 3.x 설치 (선택 사항)

1. vcpkg 설치 (선택 사항)

    1. 소스코드 가져오기

            C:\>git clone https://github.com/Microsoft/vcpkg.git c:\work.vcpkg
            Cloning into 'c:\work.vcpkg'...
            ...

    1. 빌드

            C:\work.vcpkg>c:\work.vcpkg\bootstrap-vcpkg.bat
            Microsoft (R) Build Engine version 14.0.25420.1
            ...

    1. Visual Studio 연동 

            C:\work.vcpkg>vcpkg integrate install
            Applied user-wide integration for this vcpkg root.

            All MSBuild C++ projects can now #include any installed libraries.
            Linking will be handled automatically.
            Installing new libraries will make them instantly available.

            CMake projects should use -DCMAKE_TOOLCHAIN_FILE=C:/work.vcpkg/scripts/buildsystems/vcpkg.cmake

            C:\work.vcpkg>

    1. 패키지 설치
            
            C:\work.vcpkg>vcpkg install boost:x86-windows boost:x86-windows-static boost:x64-windows boost:x64-windows-static
            C:\work.vcpkg>vcpkg install curl:x86-windows curl:x86-windows-static curl:x64-windows curl:x64-windows-static
            C:\work.vcpkg>vcpkg install sqlite3:x86-windows sqlite3:x86-windows-static sqlite3:x64-windows sqlite3:x64-windows-static
            C:\work.vcpkg>vcpkg install jsoncpp:x86-windows jsoncpp:x86-windows-static jsoncpp:x64-windows jsoncpp:x64-windows-static
            C:\work.vcpkg>vcpkg install gtest:x86-windows gtest:x86-windows-static gtest:x64-windows 


## 디버기 설정

+ VMWARE (Virtual Box 도 가능)
+ Windows 10 x64 가상머신 
    + 아니면 [Free Windows Image](https://developer.microsoft.com/en-us/microsoft-edge/tools/vms/) 에서 다운로드
+ [Virtual KD](http://virtualkd.sysprogs.org/)
    + [install](http://virtualkd.sysprogs.org/tutorials/install/) 에 설명된 대로 Debugger/Debuggee 설정을 완료할 것