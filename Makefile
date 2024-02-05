c ?= $(shell date +%Y-%m-%d)
p ?= 
project_name = cpp_telegram_gpt
# path_to_your_vcpkg_toolchain
#linux ===== /home/user/vcpkg/scripts/buildsystems/vcpkg.cmake
#windows ===== C:/dev/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake
vcpkg_path ?= ~/projects/vcpkg/vcpkg  
vcpkg_find:
	$(vcpkg_path) search "$(p)"
vcpkg_install:
	$(vcpkg_path) install
mkdir_build:
	mkdir build
build_project_release_linux: mkdir_build
	cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$(vcpkg_path) -DVCPKG_TARGET_TRIPLET=x64-linux
	cmake --build build --config Release -- -j 4
build_project_debug_linux: mkdir_build
	cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$(vcpkg_path) -DVCPKG_TARGET_TRIPLET=x64-linux
	cmake --build build --config Debug -- -j 4
build_project_release_windows: mkdir_build
	cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$(vcpkg_path) -DVCPKG_TARGET_TRIPLET=x64-windows
	cmake --build build --config Release -- /m
build_project_debug_windows: mkdir_build
	cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$(vcpkg_path) -DVCPKG_TARGET_TRIPLET=x64-windows
	cmake --build build --config Debug -- /m
run_project_linux:
	./build/$(project_name)
debug_project_linux:
	gdb -ex run ./build/$(project_name)
run_project_windows:
	.\build\Release\$(project_name).exe
debug_project_windows:
	gdb -ex run .\build\Debug\$(project_name).exe

