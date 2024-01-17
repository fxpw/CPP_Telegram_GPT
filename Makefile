m ?= $(shell date +%Y-%m-%d)
c ?= $(shell date +%Y-%m-%d)
p ?= 
project_name = cpp_telegram_gpt
path_to_your_vcpkg = ~/projects/vcpkg/vcpkg 
gitfetch:
	git fetch
gitmerge:
	git merge
gitcommit:
	git add . 
	git commit -m "$(c)"
gitpush:
	git push origin main
find:
	$(path_to_your_vcpkg) search "$(p)"
install:
	$(path_to_your_vcpkg) install
build_project_release:
	cmake --build ./build --config Release --target all -j 4 -- 
build_project_debug:
	cmake --build ./build --config Debug --target all -j 4 -- 
run_project:
	./build/$(project_name)
debug_project:
	gdb -ex run ./build/$(project_name)
