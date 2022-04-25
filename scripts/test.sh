#!/bin/sh
set -eou pipefail
cd $(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

cd ../

./scripts/build.sh
clear

cd bin

do_test() {
	N="test-darwin-mouse-location$1"
	set +e
	o=$(eval ./$N)
	ec=$?
	set -e
	ansi --cyan --bg-black --italic "<$N> :: $ec -> $o"
	return $ec
}

do_test 0
do_test 2
do_test 1
