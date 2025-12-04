#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>   // for open()
#include <unistd.h>  // for read(), write(), lseek(), close()
#include <string.h>

int main() {
    int fd;
    char buffer[100];
    char data[] = "Hello, this is a demo of UNIX file system calls!\n";

    // 1. Create/Open file
    fd = open("demo.txt", O_CREAT | O_RDWR, 0777);
    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }
    printf("File opened successfully with descriptor %d\n", fd);

    // 2. Write data to file
    if (write(fd, data, strlen(data)) < 0) {
        perror("Error writing to file");
        exit(1);
    }
    printf("Data written to file successfully.\n");

    // 3. Reposition file offset to beginning
    lseek(fd, 0, SEEK_SET);

    // 4. Read data from file
    int bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead < 0) {
        perror("Error reading file");
        exit(1);
    }
    buffer[bytesRead] = '\0'; // null terminate string
    printf("Data read from file:\n%s", buffer);

    // 5. Close file
    close(fd);
    printf("File closed successfully.\n");

    return 0;
}
