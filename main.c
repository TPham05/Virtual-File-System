#include <stdio.h>
#include <stdlib.h>
#include "vfs.h"
#include "interface.h"

int main() {
    environment env;
    load_vfs(&env, "vfs_save.txt");  // Load saved state if available

    printf("Welcome to the Virtual File System!\n");
    run_shell(&env);

    save_vfs(&env, "vfs_save.txt");  // Save state on exit
    return 0;
}
