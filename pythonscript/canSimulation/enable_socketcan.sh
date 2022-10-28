modprobe can
modprobe can_raw
modprobe can_dev
modprobe peak_usb
modprobe pcan
if ifconfig -a |grep can0
then
#  sudo ip link set can0 type can restart-ms 100
#  sudo ifconfig can0 txqueuelen 1000
  sudo ip link set can0 up type can bitrate 500000 sample-point 0.8 dbitrate 2000000 dsample-point 0.85 fd on
fi
if ifconfig -a |grep can1
then
#  sudo ip link set can1 type can restart-ms 100
#  sudo ifconfig can1 txqueuelen 1000
  sudo ip link set can1 up type can bitrate 500000 sample-point 0.8 dbitrate 2000000 dsample-point 0.85 fd on

fi