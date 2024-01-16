m ?= $(shell date +%Y-%m-%d)
c ?= $(shell date +%Y-%m-%d)
p ?= 
gf:
	git fetch
gm:
	git merge
gc:
	git add . 
	git commit -m "$(c)"
gp:
	git push origin main
vcpkg-find:
	~/projects/vcpkg/vcpkg search "$(p)"
vcpkg-install:
	~/projects/vcpkg/vcpkg install
