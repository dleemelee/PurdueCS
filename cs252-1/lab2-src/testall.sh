#!/bin/bash

(make clean && make)
mkdir test-out
echo "==================================="
for i in $(ls tests); do
    echo "running test \"$i\""
    echo "-----------------------------------"
    ./fliz < tests/$i > test-out/$i.out
    ./rfliz < tests/$i > test-out/$i.org.out

    diff test-out/$i.out test-out/$i.org.out > /dev/null

    if [ $? != 0 ]; then
        echo "test \"$i\" failed!"
        echo "diff (yours, theirs):"
        diff test-out/$i.out test-out/$i.org.out
    else
        echo "test \"$i\" passed!"
    fi
    echo "-----------------------------------"
    echo
done

rm -rf test-out
