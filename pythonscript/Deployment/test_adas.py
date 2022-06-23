from mega_cantools_lib.signal_monitor.signal_monitor import SignalMonitor
import os,time
from threading import Thread

for i in range(1000):
    os.system("sudo ip link set can0 down")
    time.sleep(0.5)
    os.system("sudo ip link set can0 up type can bitrate 500000 sample-point 0.8 dbitrate 2000000 dsample-point 0.85 fd on")
    sim_adas = SignalMonitor(pwd='matrix')
    signals = {'BcmPwrStsFb': 2, 'VCUGearPosn':4, "EspVehSpd":20, "IbBrkPedlStsGb":101}
    t = Thread(target=sim_adas.begin_send_specific_random_message, args=(['GW_31A', 'GW_382'], ),kwargs={'static_signal_value_dic': signals})
    t.setDaemon(True)
    t.start()
    time.sleep(200)
    sim_adas.stop()