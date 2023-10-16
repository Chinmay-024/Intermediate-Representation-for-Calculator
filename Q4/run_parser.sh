gcc -fdump-tree-original-raw 1.c -o ast
gcc -fdump-tree-gimple-raw 1.c -o gimple
gcc -fdump-tree-cfg-raw 1.c -o cfg
gcc -da 1.c -o rtl