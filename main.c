#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

int is_printable_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) return 0;

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!isprint(ch) && !isspace(ch)) {
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

void print_directory_tree(FILE *output_file, const char *dir_path, int level) {
    DIR *dir = opendir(dir_path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        for (int i = 0; i < level; i++) fprintf(output_file, "  ");
        fprintf(output_file, "|-- %s\n", entry->d_name);

        char new_path[1024];
        snprintf(new_path, sizeof(new_path), "%s/%s", dir_path, entry->d_name);

        struct stat path_stat;
        stat(new_path, &path_stat);

        if (S_ISDIR(path_stat.st_mode)) {
            print_directory_tree(output_file, new_path, level + 1);
        }
    }
    closedir(dir);
}

void concatenate_files(FILE *output_file, const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        char file_path[1024];
        snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);

        struct stat path_stat;
        stat(file_path, &path_stat);

        if (S_ISREG(path_stat.st_mode) && is_printable_file(file_path)) {
            FILE *input_file = fopen(file_path, "r");
            if (input_file) {
                fprintf(output_file, "\n\n-- File: %s --\n", entry->d_name);
                char buffer[1024];
                size_t n;
                while ((n = fread(buffer, 1, sizeof(buffer), input_file)) > 0) {
                    fwrite(buffer, 1, n, output_file);
                }
                fclose(input_file);
            }
        } else if (S_ISDIR(path_stat.st_mode)) {
            concatenate_files(output_file, file_path);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory_path> [output_file]\n", argv[0]);
        return 1;
    }

    const char *dir_path = argv[1];
    FILE *output_file = stdout;

    if (argc >= 3) {
        const char *output_file_path = argv[2];
        output_file = fopen(output_file_path, "w");
        if (!output_file) {
            perror("Error opening output file");
            return 1;
        }
    }

    fprintf(output_file, "Directory Tree:\n");
    print_directory_tree(output_file, dir_path, 0);
    fprintf(output_file, "\nConcatenated Files Content:\n");
    concatenate_files(output_file, dir_path);

    if (output_file != stdout) fclose(output_file);
    else printf("\nFiles have been concatenated to stdout.\n");

    return 0;
}
