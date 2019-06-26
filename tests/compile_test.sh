make
gcc -o test0 tests/empty.c
gcc -o test1 tests/test_page.c
gcc -o test2 tests/test_free.c
gcc -o test3 tests/test_realloc.c
gcc -o test3bis tests/test_realloc_bis.c
gcc -o test4 tests/test_erreures.c
gcc -o test5 tests/test_show.c -L. -lft_malloc
gcc -o defrag tests/defrag.c -L. -lft_malloc
gcc -o testProtection tests/test_protections.c
