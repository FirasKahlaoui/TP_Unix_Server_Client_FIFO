# Unix Server-Client FIFO

This project is a simple C client-server application that uses named pipes
(FIFOs) to exchange messages. The client sends a request to the server, and
the server responds with a list of random numbers.

## Requirements

The project requires a C compiler and Bash.

## Manual compilation

From the `src` directory, run:

```bash
cd /root/unix/TP_Unix_Server_Client_FIFO/src
gcc server.c -o server
gcc client.c -o client
```

## Manual execution

Open two terminals in the `src` directory.

In the first terminal, start the server:

```bash
./server
```

In the second terminal, start the client:

```bash
./client
```

The server creates `fifo1` and `fifo2` automatically. Press `Ctrl+C` in the
server terminal to stop it and remove the FIFOs.

Several clients can be started from additional terminals:

```bash
./client
```

## Automated test

From the `src` directory, make the script executable once:

```bash
chmod +x run_test.sh
```

Then run:

```bash
./run_test.sh
```

The script:

1. Removes old FIFOs and client log files.
2. Compiles the server and the client.
3. Starts the server.
4. Waits until `fifo1` and `fifo2` exist.
5. Starts five clients.
6. Stores their output in `client_log_1.txt` through `client_log_5.txt`.
7. Stops the server after all clients finish.

To remove generated files manually:

```bash
rm -f fifo1 fifo2 server client client_log_*.txt
```
