mkdir -p tests/logs

run_log() {
    NAME=$1
    INPUT=$2
    OUTPUT=tests/logs/$NAME.log

    ./memsim < "$INPUT" \
        | sed -e 's/^> *//' \
              -e '/^Memory Simulator$/d' \
              -e '/^Type .help. for commands$/d' \
        > "$OUTPUT"
}

run_log first_fit  tests/allocator/testcases/first_fit.txt
run_log best_fit   tests/allocator/testcases/best_fit.txt
run_log worst_fit  tests/allocator/testcases/worst_fit.txt
run_log buddy      tests/allocator/testcases/buddy.txt
run_log cache_direct tests/cache/testcases/cache_direct.txt
run_log vm_basic tests/virtual_memory/testcases/vm_basic.txt
run_log vm_replacement tests/virtual_memory/testcases/vm_replacement.txt
run_log full_system tests/integration/testcases/full_system.txt
echo "All logs generated in tests/logs/"
