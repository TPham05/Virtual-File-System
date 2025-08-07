#ifndef VFS_H
#define VFS_H

#include <stdbool.h> 
#include <time.h>
#define MAX_NAME_LEN 64
#define MAX_CHILDREN 64
#define CONTENT_SIZE 1024


typedef enum
{
    FILE_TYPE,
    DIR_TYPE
} file_type;

typedef enum { 
    USER_OWNER, 
    USER_GROUP, 
    USER_OTHER 
} user_type;


typedef struct file_node
{
    char name[MAX_NAME_LEN];
    file_type type;
    
    struct file_node* parent;
    struct file_node* children[MAX_CHILDREN];
    int child_count;

    // File-specific
    char content[CONTENT_SIZE];
    
    // Check Flag
    bool is_root;
    bool has_content;

    //File Permissions
    int permissions;

    //File MetaData
    time_t created;
    time_t modified;
    time_t accessed;
    size_t size;

} file_node;

typedef struct 
{
    file_node* root_node;
    file_node* pwd;
} environment;

/** 
 * Initializes a new virtual file system
 * @param env : Pointer to an environment that holds the root and current directory
 */
void init_vfs(environment* env);

/**
 * Creates a new directory in the current directory
 * @param env : The digital environment
 * @param name : The name of the directory
 */
void mkdir_vfs(environment* env, const char* name);

/**
 * List all directory contents
 */
void ls_vfs(environment* env);

/**
 * Change directory
 */
void cd_vfs(environment* env, const char* name);

/**
 * Print working directory
 */
void pwd_vfs(environment* env);

/**
 * Create a file
 */
void touch_vfs(environment* env, const char* name);

/**
 * Read file content
 */
void read_vfs(environment* env, const char* name);

/**
 * Write content to file
 * @param content : The content going into the file
 */
void write_vfs(environment* env, const char* name, const char* content);

/**
 * Remove a file
 */
void rm_vfs(environment* env, const char* name);

/**
 * Remove a directory and file contain in it
 */
void rmdir_vfs(environment* env, const char* name);

/**
 * Rename file or directory
 * @param old_name : The current name of such file or directory
 * @param new_name : The name that needs to be changed to
 */
void rename_vfs(environment* env, const char* old_name, const char* new_name);

/**
 * Print directory tree
 * @param dir : The node the tree is starting from 
 * @param level : Tracks the depth of recursion to determine indentation
 */
void tree_vfs(environment* env, file_node* dir, int level);


/**
 * Copy a file or directory
 * @param src : Source file/directory name
 * @param dest : Destination file/directory name
 */
void cp_vfs(environment* env, const char* src, const char* dest);

/**
 * Move (or rename) a file or directory
 */
void mv_vfs(environment* env, const char* src, const char* dest);

void save_vfs(environment* env, const char* name);
void load_vfs(environment* env, const char* name);


#endif