
# TODO: Check daemon có được create thành công hay không
while read service; do
    PID=$(pidof $service)
    echo $"$service: ${PID: - NOT running}"
done < watch.conf
# TODO: Check Daemon có chuyển FD stdin, sdinout, sdterr vào file logging chưa
# TODO: Có ngắt kết nối terminal chưa
