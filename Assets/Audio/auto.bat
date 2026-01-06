@echo off
setlocal enabledelayedexpansion

:: 대상 디렉토리 (현재 폴더 기준)
set "TARGET_DIR=."
set "OUTPUT_FILE=AudioList.csv"

:: 헤더 작성
echo Path,FileName > "%OUTPUT_FILE%"

:: 현재 실행 경로의 길이 계산 (상대 경로 변환용)
set "ROOT_PATH=%~dp0"

for /r "%TARGET_DIR%" %%f in (*) do (
    if exist "%%f" (
        set "FULL_PATH=%%f"
        set "FILE_NAME=%%~nf"
        set "BASE_NAME=%%~nxf"

        :: 자기 자신(csv, bat)은 제외
        if not "!BASE_NAME!"=="%~nx0" if not "!BASE_NAME!"=="%OUTPUT_FILE%" (
            
            :: 전체 경로에서 루트 경로 부분을 제거하여 상대 경로 생성
            set "RELATIVE_PATH=!FULL_PATH:%ROOT_PATH%=.\!"
            
            echo !RELATIVE_PATH!,!FILE_NAME! >> "%OUTPUT_FILE%"
        )
    )
)

echo CSV 상대 경로 리스트 생성 완료: %OUTPUT_FILE%
pause