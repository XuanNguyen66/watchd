#!/bin/bash

BIN=./bin/main

# TODO: Check daemon có được create thành công hay không
while read service; do
    PID=$(pidof $service)
    echo $"$service: ${PID: - NOT running}"
done < watch.conf

echo "[TEST] DAEMON"
$BIN


# TODO: Check Daemon có chuyển FD stdin, sdinout, sdterr vào file logging chưa, có ngắt kết nối terminal chưa
