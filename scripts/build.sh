#!/usr/bin/env bash
set -eou pipefail
cd $(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
cd ../
DEBUG=${DEBUG:-0}

[[ -d deps ]] || clib i -c -q

[[ -d bin ]] && rm -rf bin
mkdir -p bin

get_test_files() {
	\find tests -type f -name "*.c" | \sort -u
}

build_test_file() {
	cmd="gcc $1 \
		-framework ApplicationServices \
        -o bin/$(basename $1 .c)"
	[[ "$DEBUG" == 1 ]] && ansi >&2 --yellow --bg-black --italic "$cmd"
	eval "$cmd"

}
build_test() {
	gcc tests/test-darwin-mouse-location$1.c \
		-framework ApplicationServices \
		-o bin/test-darwin-mouse-location$1

}

build_test_files() {
	while read -r test_file; do
		build_test_file "$test_file" &
	done < <(get_test_files)
	wait
}

main() {
	build_test_files
}

main
