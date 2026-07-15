#!/bin/bash

BIN=./bin/main
SERVICE_PID=()



cleanup() {
    echo "This is cleaning...!!! ${#SERVICE_PID[@]}"
    for i in "${SERVICE_PIDD[@]}"; do
        if kill -0 "$i" 2>/dev/null; then
            echo "Killing $i"
            kill "$i"
            wait "$i" 2>/dev/null
        fi
    done
}
trap cleanup EXIT

"$BIN" &
SERVICE_PID+=($!)

sleep 70

if [ -f "watch.conf" ]; then
    echo "file tồn tại"
else
    echo "file không tại"
fi


echo "Starting service with: ${SERVICE_PID[@]}"


# TODO: Check Daemon có chuyển FD stdin, sdinout, sdterr vào file logging chưa, có ngắt kết nối terminal chưa
           