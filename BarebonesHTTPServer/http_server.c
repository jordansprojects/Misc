#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *msg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 50\n\nIts Arch Linux Time";

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

   for(;;) {
        // Accept incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Send response
        int bytes_sent = 0;
        while (bytes_sent < strlen(msg)) {
            int bytes = send(new_socket, msg + bytes_sent, strlen(msg) - bytes_sent, 0);
            if (bytes == -1) {
                perror("send");
                break;
            }
            bytes_sent += bytes;
       
        printf("Message sent\n");
	}
        // Close connection
        close(new_socket);
    }
    return 0;
}
