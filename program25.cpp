#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    int fd = open("example.txt", O_RDONLY);
    int new_fd = fcntl(fd, F_DUPFD, 0);
    printf("New file descriptor: %d\n", new_fd);
    close(fd);
    close(new_fd);
    fd = open("example.txt", O_RDONLY);
    off_t offset = lseek(fd, 5, SEEK_SET);
    printf("New cursor position: %ld\n", (long)offset);
    close(fd);
    struct stat file_info;
    if (stat("example.txt", &file_info) == 0) {
        printf("File size: %ld bytes\n", (long)file_info.st_size);
        printf("File permissions: %o\n", file_info.st_mode);
    } else {
        perror("stat");
    }
    DIR *dir = opendir(".");
    if (dir) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
    } else {
        perror("opendir");
        return EXIT_FAILURE;
    }

    return 0;
}

