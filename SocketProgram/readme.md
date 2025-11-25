# C Socket Chat Program

A simple **cross-platform chat program in C** using TCP sockets.  
Supports **Windows** and **Linux**, allowing **server-client communication** over the network.

---

## Features

- Cross-platform: works on **Windows** (`winsock2`) and **Linux** (`sys/socket.h`)  
- Simple **command-line chat** between server and client  
- Graceful handling of connection closure  
- Recognizes `"exit"` command to quit the chat  

---
## How It Works

The program uses **conditional compilation** to separate **server** and **client** logic:

```c
#ifdef SERVER
    // Code for server
#else
    // Code for client
#endif
```
- Server mode: waits for client connection and exchanges messages

- Client mode: connects to server IP and exchanges messages

Compile-time flag -DSERVER determines whether the program acts as server or client.

## Compile & Run

### Linux / GCC

- Server:

```bash
gcc chat.c -o server -DSERVER
./server
```


- Client:

```bash
gcc chat.c -o client
./client
```

### Windows / MinGW

- Server:

```bash
gcc chat.c -o server.exe -DSERVER -lws2_32
server.exe
```

- Client:

```bash
gcc chat.c -o client.exe -lws2_32
client.exe
```

**Note:** On the same machine, use 127.0.0.1 as server IP.