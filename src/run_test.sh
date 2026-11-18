#!/bin/bash

#clean up any existing FIFO files
rm -f fifo1 fifo2 client_log_*.txt

#compilation of the server and client programs
gcc -o server server.c
gcc -o client client.c

#run the server in the background
./server &
SERVER_PID=$!

while [ ! -p fifo1 ] || [ ! -p fifo2 ]; do
    sleep 0.1
done

read -p "Enter the number of clients: " num 

for ((i=1; i<=num; i++)); do
    ./client > ./clients_logs/client_log_$i.txt 2>&1 &
    client_pids+=("$!")
done

#wait for all clients to finish
for pid in "${client_pids[@]}"; do
    wait "$pid"
done

#kill the server process
kill -SIGINT $SERVER_PID
echo "Server and clients have finished execution."