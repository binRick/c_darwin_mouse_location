#!/usr/bin/env bash
set -eou pipefail
cd $(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
cd ../

[[ -d deps ]] || clib i -c -q

[[ -d bin ]] && rm -rf bin
mkdir -p bin

build_test() {
	gcc tests/test-darwin-mouse-location$1.c \
		-framework ApplicationServices \
		-o bin/test-darwin-mouse-location$1

}

build_test 0
build_test 1
build_test 2
