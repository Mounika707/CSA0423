#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    // for open, O_RDWR, O_CREAT
#include <unistd.h>   // for read, write, lseek, close
#include <sys/stat.h> // for file permissions

int main() {
    int fd;
    char buffer[100];

    // Open file (POSIX style)
    fd = open("testfile.txt", O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }
    printf("File 'testfile.txt' opened successfully with fd = %d\n", fd);

    // Write to file
    write(fd, "Hello, POSIX I/O system calls!\n", 32);

    // Move file pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // Read from file
    int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0'; // null terminate
    printf("Data read: %s\n", buffer);

    // Close file
    close(fd);

    return 0;
}
