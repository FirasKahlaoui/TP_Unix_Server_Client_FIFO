# Unix Server-Client FIFO

This project is a simple C client-server application that uses named pipes
(FIFOs) to exchange messages. The client sends a request to the server, and
the server responds with a list of random numbers.

## Compile

From the repository root, run:

```bash
gcc src/server.c -o server
gcc src/client.c -o client
```

## Run

Open two terminals in the repository root.

In the first terminal, start the server:

```bash
./server
```

In the second terminal, start the client:

```bash
./client
```

The server creates the named pipes automatically. Press `Ctrl+C` in the
server terminal to stop it and remove the pipes.
