#!/usr/bin/env sh


rm cachegrind.out.* > /dev/null 2>&1 &
rm callgrind.out.* > /dev/null 2>&1 &


valgrind --tool=callgrind ./build/lir < data/big.lir > /dev/null 2>&1


kcachegrind callgrind.out.* > /dev/null 2>&1 &

