[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/r_JKXvGN)
# Assignment: Enhancing Socket Security with TLS and AES

## Introduction

In this assignment, you will develop a secure network application using TLSv1.2, AES-256 encryption, and SHA-256 hashing techniques. By the end of this assignment, you will understand how to create a socket server and client that securely communicate with each other, ensuring data integrity and confidentiality. This is particularly important in scenarios where sensitive data is transmitted, such as in healthcare applications.

### Starter Files

- Create two new files named `secure_server.c` and `secure_client.c` in your preferred text editor.
- Ensure that you have OpenSSL library installed on your system.

## Requirements

1. Implement a TCP socket server that supports TLSv1.2.
2. Use AES-256 encryption for data transmission.
3. Implement SHA-256 hashing for message integrity.
4. Handle certificate generation, loading, and validation.
5. Demonstrate secure communication between a client and server.

## Steps to Complete the Assignment

**Step 1: Setup Development Environment:**

Ensure OpenSSL libraries are installed on your system to handle AES-256 encryption.

```c
sudo apt-get install libssl-dev
sudo apt-get install openssl
```

**Step 2: Create Self-Signed Certificates**

You will need a self-signed certificate for the server. Use the  OpenSSL commands to create a private key and a certificate

**Step 3: Implement TLS Server**

In `secure_server.c`, implement the following:

1. Initialize the OpenSSL library.
2. Load the server's certificate and private key.
3. Create a TCP socket and listen for incoming connections.
4. Accept connections and establish a TLS session using the loaded certificate.
5. Read messages from the client and respond securely.

**Step 4: Implement TLS Client**

In `secure_client.c`, implement the following:

1. Initialize the OpenSSL library.
2. Create a TCP socket and connect to the server.
3. Load the server's certificate and establish a TLS session.
4. Send a message to the server and read the response.

## Compile, Run and Test the Program:

Before running your code, create the certificates.

**Create Self-Signed Certificates:**

- Generate a private key.

```bash
openssl genrsa -out server.key 2048
```

- Generate a self-signed certificate.

```bash
openssl req -new -x509 -key server.key -out server.crt -days 365 -subj "/CN=localhost"
```

Now open a terminal and compile the code:

```bash
gcc -o secure_server secure_server.c -lssl -lcrypto
gcc -o secure_client secure_client.c -lssl -lcrypto
```

- Run the server in one terminal window:

```bash
./secure_server
```

- Run the client in another terminal window:

```bash
./secure_client
```

**Expected Output**

Server side:

```console
Received: Hello from client!
```

Client side:

```console
Received: Hello from server!
```

## Conclusion

In this assignment, you learned how to implement secure socket programming using TLS, AES-256 encryption, and SHA-256 hashing. You successfully established a secure communication channel between a client and server, ensuring data integrity and confidentiality. This foundational knowledge is essential for developing secure applications that handle sensitive information, particularly in environments where security is paramount.
