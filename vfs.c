#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vfs.h"

void init_vfs(environment* env) {

    file_node* root = (file_node*)malloc(sizeof(file_node));
    strcpy(root->name, "/");
    root->type = DIR_TYPE;
    root->parent = NULL;
    root->child_count = 0;
    env->root_node = root;
    env->pwd = root;
}

void mkdir_vfs(environment* env, const char* name) {
    if (env->pwd->child_count >= MAX_CHILDREN) {
        printf("Directory full.\n");
        return;
    }

    file_node* dir = (file_node*)malloc(sizeof(file_node));
    strcpy(dir->name, name);
    dir->type = DIR_TYPE;
    dir->parent = env->pwd;
    dir->child_count = 0;

    env->pwd->children[env->pwd->child_count++] = dir;
}

void ls_vfs(environment* env) {
    file_node* current = env->pwd;

    for (int i = 0; i < current->child_count; i++) {
        printf("%s  ", current->children[i]->name);
    }
    printf("\n");
}

void cd_vfs(environment* env, const char* name) {
    file_node* current = env->pwd;

    if (strcmp(name, "..") == 0 && current->parent != NULL) {
        current = current->parent;
        return;
    }

    for (int i = 0; i < current->child_count; i++) {
        file_node* child = env->pwd->children[i];
    if (strcmp(child->name, name) == 0 && child->type == DIR_TYPE) {
        env->pwd = child;
        return;
    }
    }

    printf("Directory not found.\n");
}

void pwd_vfs(environment* env) {
    file_node* current = env->pwd;

    char path[1024] = "";
    while (current != NULL) {
        if (current->parent == NULL) {  
            strcat(path, "/");
        } else {
            char temp[256];
            snprintf(temp, sizeof(temp), "/%s", current->name);
            char new_path[1024] = "";
            strcpy(new_path, temp);
            strcat(new_path, path);
            strcpy(path, new_path);
        }
        current = current->parent;
    }
    printf("%s\n", path);
}

void touch_vfs(environment* env, const char* name) {
    if (env->pwd->child_count >= MAX_CHILDREN) {
        printf("Directory full.\n");
        return;
    }

    file_node* file = (file_node*)malloc(sizeof(file_node));
    strcpy(file->name, name);
    file->type = FILE_TYPE;
    file->parent = env->pwd;
    file->child_count = 0; 

    env->pwd->children[env->pwd->child_count++] = file;
}

void read_vfs(environment* env, const char* name){
    file_node* current = env->pwd;

    for (int i = 0; i < current->child_count; i++){
        file_node* child = current->children[i];

        if(strcmp(child->name, name) == 0){

            if (child->type == DIR_TYPE){
                printf("Error: '%s' is a directory, cannot read.\n", name);
            } else {
                printf("%s\n", child->content);
            }
            return;
        }
    }

    printf("Error: File '%s' not found.\n", name);   
}

void write_vfs(environment* env, const char* name, const char* content){
    file_node* current = env->pwd;

    for (int i = 0 ; i < current->child_count; i++){
        file_node* child = current->children[i];

        if(strcmp(child->name, name) == 0 ){
            if (child->type != FILE_TYPE) {
                printf("Error: '%s' is not a file.\n", name);
                return;
            }

            if(child->has_content){
                size_t current_len = strlen(child->content);
                size_t new_len = strlen(content);

                if (current_len + new_len < CONTENT_SIZE) {
                    strcat(child->content, content);
                } else {
                    printf("Error: Not enough space to append content.\n");
                }

            } else{
                strncpy(child->content,content, CONTENT_SIZE - 1);
                child->content[CONTENT_SIZE - 1] = '\0'; 
                child->has_content = true;
            }
            return;
        }
    }
    printf("Error: File '%s' not found.\n", name);
}

void rm_vfs(environment* env, const char* name){
    file_node* current = env->pwd;

    for (int i = 0; i < current->child_count; i++){
        file_node* child = current->children[i];
        if(strcmp(child->name, name) == 0 ){

            if (child->type != FILE_TYPE) {
                printf("Error: '%s' is not a file.\n", name);
                return;
            }

            free(child);
            
            for (int j = i; j < current->child_count - 1; j++){
                current->children[j] = current->children[j + 1];
            }

            current->children[current->child_count - 1] = NULL; 
            current->child_count--;
            printf("File removed.\n");
            return;
            

        }
    }
    
    printf("Error: File '%s' not found.\n", name);
}    

void rmdir_vfs(environment* env, const char* name){
    file_node* current = env->pwd;

    for (int i = 0; i < current->child_count; i++){
        file_node* child = current->children[i];

        if(strcmp(child->name, name) == 0 && child->type == DIR_TYPE){

            for(int j = 0; j < child->child_count;j++ ){

                current->children[j] = current->children[j+1];
            }

            current->child_count--;
            printf("Directory removed.\n");
            return;
        }
    }
    printf("Directory not found.\n");
}

void rename_vfs(environment* env, const char* old_name, const char* new_name){
    file_node* current = env->pwd;

    for (int i = 0; i < current->child_count; i++){
        file_node* child = current->children[i];

        if (strcmp(child->name, old_name) == 0) {
            
            for (int j = 0; j < current->child_count; j++) {
                if (strcmp(current->children[j]->name, new_name) == 0) {
                    printf("Error: A file with the name '%s' already exists.\n", new_name);
                    return;
                }
            }

            
            strncpy(child->name, new_name, MAX_NAME_LEN);
            child->name[MAX_NAME_LEN - 1] = '\0'; 
            
            return;
        }
    }
    printf("Error: File '%s' not found.\n", old_name);

}

void tree_vfs(environment* env, file_node* dir, int level){
    if (dir == NULL) return;

    
    for (int i = 0; i < level; i++) {
        printf("  ");  
    }

    
    printf("%s\n", dir->name);

    
    if (dir->type == DIR_TYPE) {
        for (int i = 0; i < dir->child_count; i++) {
            tree_vfs(env, dir->children[i], level + 1);
        }
    }
}



void cp_vfs(environment* env, const char* src, const char* dest) {
    
    file_node* source = NULL;
    file_node* current = env->pwd;
    for (int i = 0; i < current->child_count; i++) {
        file_node* child = current->children[i];

        if (strcmp(child->name, src) == 0) {
            source = child;
            break;
        }
    }

    if (!source) {
        printf("cp: Source '%s' not found.\n", src);
        return;
    }

    // Create a new node (copy)
    file_node* copy = malloc(sizeof(file_node));
    if (!copy) {
        printf("cp: Memory allocation failed.\n");
        return;
    }

    memcpy(copy, source, sizeof(file_node)); 
    copy->parent = current;                 
    strcpy(copy->name, dest);                

    // If it's a file, just copy content & metadata
    if (copy->type == FILE_TYPE) {
        current->children[current->child_count++] = copy;
        printf("File '%s' copied to '%s'.\n", src, dest);
    }

    // If it's a directory, reset children (deep copy would require recursion)
    else if (copy->type == DIR_TYPE) {
        copy->child_count = 0;
        printf("Directory '%s' copied to '%s' (empty copy).\n", src, dest);
        current->children[current->child_count++] = copy;
    }
}

void mv_vfs(environment* env, const char* src, const char* dest) {
    
    file_node* source = NULL;
    file_node* current = env->pwd;
    for (int i = 0; i < current->child_count; i++) {
        file_node* child = current->children[i];

        if (strcmp(child->name, src) == 0) {
            source = child;
            break;
        }
    }


    if (!source) {
        printf("mv: Source '%s' not found.\n", src);
        return;
    }

    
    strcpy(source->name, dest);
    printf("Moved/Renamed '%s' to '%s'.\n", src, dest);
}


void save_node(FILE* fp, file_node* node) {
    fprintf(fp, "%d %d %s\n", node->type, node->has_content, node->name);
    if (node->type == FILE_TYPE && node->has_content) {
        fprintf(fp, "%s\n", node->content);
    }
    fprintf(fp, "%d\n", node->child_count);
    for (int i = 0; i < node->child_count; i++) {
        save_node(fp, node->children[i]);
    }
}

void save_vfs(environment* env, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        perror("Failed to save VFS");
        return;
    }
    save_node(fp, env->root_node);
    fclose(fp);
}

file_node* load_node(FILE* fp, file_node* parent) {
    int type, has_content;
    char name[MAX_NAME_LEN];

    if (fscanf(fp, "%d %d %[^\n]\n", &type, &has_content, name) != 3) return NULL;

    file_node* node = malloc(sizeof(file_node));
    strcpy(node->name, name);
    node->type = type;
    node->parent = parent;
    node->child_count = 0;
    node->is_root = (parent == NULL);
    node->has_content = has_content;

    if (type == FILE_TYPE && has_content) {
        fgets(node->content, CONTENT_SIZE, fp);
        node->content[strcspn(node->content, "\n")] = 0; // remove newline
    }

    int count;
    fscanf(fp, "%d\n", &count);
    for (int i = 0; i < count; i++) {
        node->children[node->child_count++] = load_node(fp, node);
    }

    return node;
}

void load_vfs(environment* env, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("No previous VFS found. Starting fresh.\n");
        init_vfs(env);
        return;
    }
    env->root_node = load_node(fp, NULL);
    env->pwd = env->root_node;
    fclose(fp);
}