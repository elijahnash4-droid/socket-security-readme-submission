#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

// Function to handle errors
void handle_error(const char *msg) {
    perror(msg); // Print error message to stderr
    exit(EXIT_FAILURE); // Exit the program with a failure status
}

int main() {
    SSL_library_init(); // Initialize the SSL library
    SSL_load_error_strings(); // Load SSL algorithms and error strings
    OpenSSL_add_all_algorithms();
    char buf[1024] = "Hello, secure server!";

    // Create a new SSL context using TLS method
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (ctx == NULL) {
        handle_error("Failed to create SSL context");
    }

    int server = socket(AF_INET, SOCK_STREAM, 0);
    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, server);
    if (server < 0) {
        handle_error("Socket creation failed");
    }

    // Define the server address structure
    struct sockaddr_in addr;
    addr.sin_family = AF_INET; // Use IPv4
    addr.sin_port = htons(4433); // Standard HTTPS port
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr); // Example.com IP address

    // Connect to the server
    if (connect(server, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        handle_error("Connection to the server failed");
    }

    // Perform the TLS handshake
    if (SSL_connect(ssl) <= 0) {
        handle_error("TLS handshake failed");
    }

    // Output the successful connection details
    printf("TLS connection established with %s\n", SSL_get_cipher(ssl));

    SSL_write(ssl, buf, strlen(buf));
    SSL_read(ssl, buf, sizeof(buf));
    printf("Received message: %s\n", buf);

    // Cleanup resources
    SSL_free(ssl); 
    close(server);
    SSL_CTX_free(ctx); 
    ERR_free_strings(); 

    return 0;
}
