#ifndef FS_H
#define FS_H

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "utils/str_utils.h"
#include "fs/inode.h"
#include "fs/bloc.h"

#define PRINT_LINE printf("LINE %d\n", __LINE__)
#define NO_FILE_ERROR_MESSAGE "File's NULL"
#define BLOC_DELETED_MESSAGE "Bloc's deleted (id == 0)"
#define DIRECTORY_NOT_EMPTY_MESSAGE "Directory's not empty"

#define DISK "rsc/disk"

extern const int INODE_FLAG;
extern const int BLOC_FLAG;

extern const mode_t DEFAULT_PERMISSIONS;
extern const char ROOT[USERNAME_COUNT];
extern const mode_t ROOT_PERMISSIONS;
extern char g_username[USERNAME_COUNT];
extern struct inode g_working_directory;
extern struct file g_filetree;

struct file {
	struct inode i;
	struct bloc b;
	struct file *files;
	int files_count;
};

char *get_filename_for_inode(struct inode *i);
int clean_disk();
int delete_bloc(struct bloc *b);
int delete_inode(struct inode *i);
int overwrite_bloc(struct bloc *new_bloc, unsigned int id);
int overwrite_inode(struct inode *new_inode, unsigned int id);
int print_disk();
int update_bloc(struct bloc *new_bloc);
int update_inode(struct inode *new_inode);
int write_bloc(struct bloc *b);
int write_inode(struct inode *i);
struct bloc add_inode_to_inode(struct inode *dir, struct inode *i);
struct inode get_inode_by_id(unsigned int inode_id);
int get_inodes(struct inode *under_dir, struct inode **inodes);
struct bloc get_bloc_by_id(unsigned int bloc_id);
struct inode create_disk();
struct inode create_root();
unsigned int get_filecount(struct inode *dir);
void inode_count(unsigned int *in_store, unsigned int *deleted);
struct inode get_inode_by_filename(struct inode *under_dir, char *filename);
int remove_inode_from_directory(struct inode *dir, unsigned int id);
void disk_free(unsigned int *blocs_available, unsigned int *inodes_available, size_t *bytes_available);
int create_dotdot_dir(struct inode *parent, struct inode *dir);
int create_dot_dir(struct inode *dir);

struct inode create_regularfile(struct inode *under_dir, char *filename, char *content);
struct inode create_emptyfile(struct inode *under_dir, char *filename, filetype type, const char *mode);
int iwrite(struct inode *i, char *buf, size_t n);
char **list_files(struct inode *dir, int *filecount);
int iread(struct inode *i, char *buf, size_t n);
struct inode iopen(struct inode *under_dir, char *filename, const char *mode);
int move_file(struct inode *from, char *filename, struct inode *to);
int copy_file(struct inode *from, char *filename, struct inode *to);
int unlink_inode(struct inode *from_dir, char *linkname);
int link_inode(struct inode *from_dir, char *filename, struct inode *to_dir, char *linkname);

struct inode create_directory(struct inode *under_dir, char *dirname);
int remove_empty_directory(struct inode *under_dir, char *dirname);
int remove_file(struct inode *under_dir, char *filename, filetype ft);

int remove_int(int **int_array, unsigned int *len, int i);

#endif

