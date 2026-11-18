#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void handle_error(const char *msg) {
    perror(msg); // Print error message to stderr
    exit(EXIT_FAILURE); // Exit the program with a failure status
}

int main() {
    SSL_library_init(); // Initialize the SSL library
    SSL_load_error_strings(); // Load SSL algorithms and error strings
    OpenSSL_add_all_algorithms();
    char buf[1024];

    SSL_CTX *ctx = SSL_CTX_new(TLS_server_method());
    if (ctx == NULL) {
        handle_error("Failed to create SSL context");
    }
    
    SSL *ssl = SSL_new(ctx);

    int server_fd, client_fd;
    SSL_set_fd(ssl, client_fd);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        handle_error("Socket creation failed");
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET; // Use IPv4
    addr.sin_port = htons(4433); // Standard HTTPS port
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr); // Example.com IP address

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        handle_error("Bind failed");
    }
    if (listen(server_fd, 3) < 0) {
        handle_error("Listen failed");
    }
    

    printf("Server is listening on port 443...\n");

    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) {
        handle_error("Accept failed");
    }


    if (SSL_accept(ssl) <= 0) {
        handle_error("TLS Handshake");
    }

    printf("TLS handshake successful!\n");

    SSL_read(ssl, buf, sizeof(buf));
    printf("Received message: %s\n", buf);
    SSL_write(ssl, "Hello, secure client!", strlen("Hello, secure client!"));

    // Clean up
    SSL_free(ssl);
    close(client_fd);
    close(server_fd);
    SSL_CTX_free(ctx);
    ERR_free_strings();
    
    return 0;

}