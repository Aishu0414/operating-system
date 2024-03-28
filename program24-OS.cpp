#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 1024
int main() {
int fd; 
ssize_t bytes_written, bytes_read;
char buffer[BUFFER_SIZE];
const char *file_path = 
fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (fd == -1) {
perror("open");
exit(EXIT_FAILURE);
}
const char *data_to_write = "Hello, world!\n";
bytes_written = write(fd, data_to_write, strlen(data_to_write));
if (bytes_written == -1) {
perror("write");
close(fd);
exit(EXIT_FAILURE);
}
printf("%ld bytes written to the file.\n", bytes_written);
close(fd);
fd = open(file_path, O_RDONLY);
if (fd == -1) {
perror("open");
exit(EXIT_FAILURE);
}
bytes_read = read(fd, buffer, BUFFER_SIZE);
if (bytes_read == -1) {
perror("read");
close(fd);
exit(EXIT_FAILURE);
}
buffer[bytes_read] = '\0';
printf("%ld bytes read from the file: %s\n", bytes_read, buffer);
close(fd);
return 0;
}
 

