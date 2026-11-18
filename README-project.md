# Secure TCP Socket

## Project Description

Creates a secure connection using TLS to communicate between the server and the client

## Installation 

Step-by-step instructions on how to install and setup this project locally.

```
# clone the repository
git clone https://github.com/atlas-school-classroom/socket-security-with-tls-elijahnash4-droid.git

# Navigate to the project directory
cd socket-security-with-tls-elijahnash4-droid
```

## Usage/Examples
- Open two terminals, make sure they're both in the project directory
- Run `./secure_server` first on one terminal
- Then run `./secure_client` on the second terminal
- input a message to send to server

If done correctly here's an example of how it should look on each terminal

### Server side
```
Server is listening on port 43251
Client connected
Message sent: hi
```

### Client side
```
Connected to the server
Enter message: hi
Response from server: Hello, Client!
```