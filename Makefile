all: build

mkdir_build:
	rm -rf build
	mkdir -p build

build: mkdir_build
	cd build; cmake ..
	make -C build

build_ninja: mkdir_build
	cd build; cmake -GNinja ..
	ninja -C build

debug: mkdir_build
	cd build; cmake -DCMAKE_BUILD_TYPE=Debug ..
	make -C build

debug_ninja: mkdir_build
	cd build; cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ..
	ninja -C build

format:
	clang-format -style=Chromium src/* -i || clang-format37 -style=Chromium src/* -i

run:
	./build/game

watch_debug:
	if command -v entr > /dev/null; then find . -type f -not -path '*/\.*' -and -not -path '*/build/*' | grep -i '.*[.][c,cpp,h]' | entr -c make debug_ninja; else make debug_ninja; echo "\nInstall entr(1) to automatically run tests on file change.\n See http://entrproject.org/"; fi

watch_run:
	if command -v entr > /dev/null; then find . -type f -not -path '*/\.*' -and -not -path '*/build/*' | grep -i '.*[.][c,cpp,h]' | entr -c make debug_ninja run; else make debug_ninja run; echo "\nInstall entr(1) to automatically run tests on file change.\n See http://entrproject.org/"; fi

install_osx_deps:
	brew install ninja entr

.PHONY: mkdir_build
