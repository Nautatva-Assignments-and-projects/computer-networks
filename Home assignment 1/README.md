# Assigment 1
https://www.cse.iitb.ac.in/~mythili/teaching/cs224m_autumn2017/socketpa/index.html

## Problem Description
In this assignment, we will build a simple client-server system. The [client code](./client.c) is given to you. You must write and submit the code for the server. You must use C/C++ for this assignment.

The system you are developing is a simple key-value store. The client takes user input to get/put/delete keys and passes these requests over the server. The server maintains a data structure of key-value pairs in memory and returns a suitable reply to the server. When the request from the client is of the form "put key value", the server must store the key-value pair in its data structures, provided the key does not already exist. Put requests on an existing key must return an error message. When the client sends a request of the form "get key value", the value stored against the key must be returned. If the key is not found, a suitable error message must be returned. The client should be able to issue a delete request (on an existing key) as follows: "del key". For all requests that succeed, the server must either return the value (in case of get), or the string "OK" (in case of put/del). You may assume that all keys and values are integers. When the user inputs "Bye", the server should reply "Goodbye" and close the client connection. Upon receiving this message from the server, your client program terminates.

Below is a sample execution of the client, when the server is running on the local host (hence the special loopback IP address 127.0.0.1).

```
$ gcc client.c -o client
$ ./client 127.0.0.1 5000
Connected to server
Enter request: put 1 2
Server replied: OK
Enter request: put 1 3
Server replied: Key already exists
Enter request put 2 3
Server replied: OK
Enter request: get 1
Server replied: 2
Enter request: del 1
Server replied: OK
Enter request: get 1
Server replied: Key not found
Enter request: del 5
Server replied: Key not found
Enter request: Bye
Server replied: Goodbye
$
```
Note that your server must be able to communicate with multiple active clients at a time, as we will test your code with multiple clients concurrently. This will require you to write your server either using event-driven I/O system calls (like select, epoll), or have multiple threads/processes, one for each client. It may be better for you to write and debug code for a server that handles one client at a time, and then move on to the version with multiple concurrent clients.
When multiple clients talk to the server, the key-value pairs of all clients can be stored in a common data structure, and one client should be able to see the data stored by the other clients.

## Submission Instructions
We will grade your code by running it against multiple clients concurrently, and by reading through the code. All code will be run through a copy detection software, so please do not copy code. Also, make sure your code is well indented and documented.
