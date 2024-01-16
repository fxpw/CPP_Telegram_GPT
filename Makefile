m ?= $(shell date +%Y-%m-%d)
c ?= $(shell date +%Y-%m-%d)
p ?= 
gf:
	git fetch
gm:
	git merge
gp:
	git add . 
	git commit -m "$(c)"
	git push origin main
f:
	~/projects/vcpkg/vcpkg search "$(p)"
p:
	~/projects/vcpkg/vcpkg $(p)
i:
	~/projects/vcpkg/vcpkg install
