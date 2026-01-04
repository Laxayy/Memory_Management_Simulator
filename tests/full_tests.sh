BIN=./memsim
TESTS=tests
ACTUAL=$TESTS/actual

mkdir -p "$ACTUAL"

normalize(){
    sed \
        -e 's/^> *//' \
        -e '/^Memory Simulator$/d' \
        -e '/^Type .help. for commands$/d' \
        -e '/^Exiting simulator$/d' \
        -e '/^[[:space:]]*$/d'
}

run_test() {
    NAME=$1
    INPUT=$2
    EXPECTED=$3
    OUTPUT=$ACTUAL/$NAME.out

    echo "Running $NAME..."

    "$BIN" < "$INPUT" | normalize > "$OUTPUT"
    if diff -u "$EXPECTED" "$OUTPUT" > /dev/null; then
        echo "$NAME PASSED"
    else
        echo "$NAME FAILED"
        diff -u "$EXPECTED" "$OUTPUT"
    fi
    echo
}

run_test first_fit  tests/allocator/testcases/first_fit.txt  tests/allocator/expected/first_fit.out
run_test best_fit   tests/allocator/testcases/best_fit.txt   tests/allocator/expected/best_fit.out
run_test worst_fit  tests/allocator/testcases/worst_fit.txt  tests/allocator/expected/worst_fit.out
run_test buddy      tests/allocator/testcases/buddy.txt      tests/allocator/expected/buddy.out
run_test cache_direct tests/cache/testcases/cache_direct.txt tests/cache/expected/cache_direct.out
run_test vm_basic tests/virtual_memory/testcases/vm_basic.txt tests/virtual_memory/expected/vm_basic.out
run_test vm_replacement tests/virtual_memory/testcases/vm_replacement.txt tests/virtual_memory/expected/vm_replacement.out
run_test full_system tests/integration/testcases/full_system.txt tests/integration/expected/full_system.out
