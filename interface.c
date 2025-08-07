#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vfs.h"

#define MAX_INPUT 256

void run_shell(environment* env) {
    char input[MAX_INPUT];

    while (1) {
        printf("> ");
        if (!fgets(input, MAX_INPUT, stdin)) break;

        // remove newline
        input[strcspn(input, "\n")] = 0;

        // tokenize input
        char* cmd = strtok(input, " ");
        char* arg1 = strtok(NULL, " ");
        char* arg2 = strtok(NULL, "");
        
        if (!cmd) continue;

        if (strcmp(cmd, "mkdir") == 0 && arg1) {
            mkdir_vfs(env, arg1);
        } else if (strcmp(cmd, "touch") == 0 && arg1) {
            touch_vfs(env, arg1);
        } else if (strcmp(cmd, "ls") == 0) {
            ls_vfs(env);
        } else if (strcmp(cmd, "cd") == 0 && arg1) {
            cd_vfs(env, arg1);
        } else if (strcmp(cmd, "pwd") == 0) {
            pwd_vfs(env);
        } else if (strcmp(cmd, "cat") == 0 && arg1) {
            read_vfs(env, arg1);
        } else if (strcmp(cmd, "write") == 0 && arg1 && arg2) {
            write_vfs(env, arg1, arg2);
        } else if (strcmp(cmd, "rm") == 0 && arg1) {
            rm_vfs(env, arg1);
        } else if (strcmp(cmd, "rmdir") == 0 && arg1) {
            rmdir_vfs(env, arg1);
        } else if (strcmp(cmd, "rename") == 0 && arg1 && arg2) {
            rename_vfs(env, arg1, arg2);
        } else if (strcmp(cmd, "tree") == 0) {
            tree_vfs(env, env->pwd, 0);
        } else if (strcmp(cmd, "chmod") == 0 && arg1 && arg2) {
            chmod_vfs(env, arg1, strtol(arg2, NULL, 8)); 
        } else if (strcmp(cmd, "cp") == 0 && arg1 && arg2) {
            cp_vfs(env, arg1, arg2);
        } else if (strcmp(cmd, "mv") == 0 && arg1 && arg2) {
            mv_vfs(env, arg1, arg2);
        } else if (strcmp(cmd, "save") == 0 && arg1) {
            save_vfs(env, arg1);
        } else if (strcmp(cmd, "load") == 0 && arg1) {
            load_vfs(env, arg1);

        } else if (strcmp(cmd, "exit") == 0) {
            break;
        } else {
            printf("Unknown command: %s\n", cmd);
        }
    }
}
