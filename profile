#!/usr/bin/env sh


rm cachegrind.out.*
rm callgrind.out.*


valgrind --tool=callgrind ./build/lir < data/big.lir


kcachegrind callgrind.out.* &
