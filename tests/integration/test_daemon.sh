#!/bin/bash

BIN=./bin/main
FILE_LOG_PID=./config/daemon_pid.txt
FILE_LOG_RUNNING=./logs/log_services_running.log
FILE_LOG_FAILED=./logs/log_services_failed.log
SERVICE_PID=()

cleanup() {
    echo "This is cleaning...!!! ${#SERVICE_PID[@]}"
    for i in "${SERVICE_PID[@]}"; do
        if kill -0 "$i" 2>/dev/null; then
            echo "Killing $i"
            kill "$i"
            wait "$i" 2>/dev/null
        fi
    done

    rm -f "$FILE_LOG_PID" -f "$FILE_LOG_RUNNING" -f "$FILE_LOG_FAILED"
}
trap cleanup EXIT

"$BIN" &

rm -f "$FILE_LOG_PID" -f "$FILE_LOG_RUNNING" -f "$FILE_LOG_FAILED"

sleep 70

if [[ -f "$FILE_LOG_PID" && ( -f "$FILE_LOG_RUNNING" || -f "$FILE_LOG_FAILED" ) ]]; then
    echo "Have file {$FILE_LOG_PID} - {$FILE_LOG_RUNNING} - {$FILE_LOG_FAILED}"
else 
    echo "Not find file logging"
fi
