# computer_graphics

# 1. 사전준비
- Visual Studio 2022 Community
    - Workload: Desktop development with C++
    - include: MSVC v143, Windows 10/11 SDK, C++ CMake tools
- Git for windows

# 2. vcpkg 설치
```cd $env:USERPROFILE
git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat


# 환경변수
$env:VCPKG_ROOT = "$env:USERPROFILE\vcpkg"
[Environment]::SetEnvironmentVariable("VCPKG_ROOT",$env:USERPROFILE+"\vcpkg","User")


# 커밋 해시 확인(매니페스트 baseline에 사용)
git -C $env:VCPKG_ROOT rev-parse HEAD
```

# 3. 프로젝트 구조
```
ProjectName/
  CMakeLists.txt
  vcpkg.json
  assets/
    shaders/
      tri.vert
      tri.frag
  src/
    main.cpp
    shader.hpp
    shader.cpp
    renderer.hpp
    renderer.cpp
```

# 4. 구성 및 빌드
```
# 프로젝트 루트에서
$toolchain = "$env:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake"

cmake -S . -B build -G "Visual Studio 17 2022" -A x64 `
  -DCMAKE_TOOLCHAIN_FILE="$toolchain" `
  -DVCPKG_TARGET_TRIPLET=x64-windows

cmake --build build --config Debug

# 실행
.\build\Debug\app.exe

# 릴리스 빌드
cmake --build build --config Release
```

# 5. Template 재사용
새 프로젝트를 만들 때는 Template folder를 복사
```
Copy-Item -Recurse -Force <Template 위치> <새 프로젝트 위치>
```

# 6. Clean build
```
Remove-Item -Recurse -Force .\build -ErrorAction SilentlyContinue
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 `
  -DCMAKE_TOOLCHAIN_FILE="$toolchain" `
  -DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build build --config Debug
```

# 7. build script
```
# build.bat
@echo off
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake
cmake --build build
```

```
# 파일 빌드 및 실행
# 루트 디렉토리에서
./build.bat
```

