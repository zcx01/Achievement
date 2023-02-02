import json
import jinja2
import sys,time,os,re
import numpy as np
sys.path.append("../common")
from send_info import MaiBot

log_lines = []
gnss_msg_id = [1465,42,812,1429,268,266]
process_name_array = ['Timer','CameraCapture', 'Algo', 'Encoder', 'LidarCapture', 'LidarProcess', 'ImuCapture', 'ImuProcess', 'GnssCapture', 'GnssProcess', 'RadarCapture', 'RadarProcess']

camera_fps_samples = {}
algo_last_stamp_samples = {}
encoder_last_stamp_samples = {}
algo_timespan_samples = {}
encoder_timespan_samples = {}
algo_timestamp_samples = {}
encoder_timestamp_samples = {}
algo_resolution_samples = {}
encoder_resolution_samples = {}
camera_drop_frame_samples = {}
sensor_timestamp_samples = {}
sensor_timespan_samples = {}
process_memory_samples = {}
thread_cpu_samples = {}
lidar_status_last_stamp = 0
lidar_packet_last_stamp = 0
imu_last_stamp = 0
gnss_last_stamp = 0

# 对字典按键排序
def sort_by_key(d):
    return dict(sorted(d.items(), key=lambda k: k[0]))

def process_log_data():
    global camera_fps_samples
    global algo_last_stamp_samples
    global encoder_last_stamp_samples
    global algo_timespan_samples
    global encoder_timespan_samples
    global algo_timestamp_samples
    global encoder_timestamp_samples
    global algo_resolution_samples
    global encoder_resolution_samples
    global camera_drop_frame_samples
    global sensor_timestamp_samples
    global sensor_timespan_samples
    global process_memory_samples
    global thread_cpu_samples
    global lidar_status_last_stamp
    global lidar_packet_last_stamp
    global imu_last_stamp
    global gnss_last_stamp

    for line in log_lines:
        reObj = re.match('.*cpp.*\<[0-9]+\>\s([0-9]+).*Sensor([0-9]+)_Out([0-9]+)\s+Frame\s+rate.*\s+([0-9]+[\.]*[0-9]*)', line)
        if reObj:
            stamp_sample = int(reObj.group(1))
            ch_num_str = reObj.group(2)
            ch_num = int(ch_num_str)
            fps_sample = float(reObj.group(4))
            if ch_num_str not in camera_fps_samples:
                camera_fps_samples[ch_num_str] = []
            camera_fps_samples[ch_num_str].append([len(camera_fps_samples[ch_num_str]),fps_sample])

        reObj = re.match('.*Algo.*index:([0-9]+)\s*ImageMetadata\s*Receive\s*sec:([0-9]+),nanosec:([0-9]+).*model:(imx728|isx031).*width:([0-9]+),height:([0-9]+)', line)
        if reObj:
            ch_num_str = reObj.group(1)
            ch_num = int(ch_num_str)
            sec_sample = int(reObj.group(2))
            ns_sample = int(reObj.group(3))
            stamp_sample = int(sec_sample * 1000 + ns_sample / 1000000)
            model_sample = reObj.group(4)
            width_sample = reObj.group(5)
            height_sample = reObj.group(6)
            if ch_num_str not in algo_last_stamp_samples:
                algo_last_stamp_samples[ch_num_str] = stamp_sample
            if ch_num_str not in algo_timespan_samples:
                algo_timespan_samples[ch_num_str] = []
            if(stamp_sample > algo_last_stamp_samples[ch_num_str]):
                algo_timespan_samples[ch_num_str].append([len(algo_timespan_samples[ch_num_str]), stamp_sample - algo_last_stamp_samples[ch_num_str]])
            if ch_num_str not in algo_timestamp_samples:
                algo_timestamp_samples[ch_num_str] = []
            algo_timestamp_samples[ch_num_str].append(stamp_sample)
            print('algo stamp_sample: ', stamp_sample, 'ch: ', ch_num_str)
            algo_resolution_samples[ch_num_str] = width_sample + 'x' + height_sample
            algo_last_stamp_samples[ch_num_str] = stamp_sample
  

        reObj = re.match('.*Encoder.*index:([0-9]+)\s*ImageMetadata\s*Receive\s*sec:([0-9]+),nanosec:([0-9]+).*model:(imx728|isx031).*width:([0-9]+),height:([0-9]+)', line)
        if reObj:
            ch_num_str = reObj.group(1)
            ch_num = int(ch_num_str)
            sec_sample = int(reObj.group(2))
            ns_sample = int(reObj.group(3))
            stamp_sample = int(sec_sample * 1000 + ns_sample / 1000000)
            model_sample = reObj.group(4)
            width_sample = reObj.group(5)
            height_sample = reObj.group(6)
            if ch_num_str not in encoder_last_stamp_samples:
                encoder_last_stamp_samples[ch_num_str] = stamp_sample
            if ch_num_str not in encoder_timespan_samples:
                encoder_timespan_samples[ch_num_str] = []
            if(stamp_sample > encoder_last_stamp_samples[ch_num_str]):
                encoder_timespan_samples[ch_num_str].append([len(encoder_timespan_samples[ch_num_str]), stamp_sample - encoder_last_stamp_samples[ch_num_str]])
            if ch_num_str not in encoder_timestamp_samples:
                encoder_timestamp_samples[ch_num_str] = []
            encoder_timestamp_samples[ch_num_str].append(stamp_sample)
            print('encoder stamp_sample: ', stamp_sample, 'ch: ', ch_num_str)
            encoder_resolution_samples[ch_num_str] = width_sample + 'x' + height_sample
            encoder_last_stamp_samples[ch_num_str] = stamp_sample
  
        reObj = re.match('.*lidar_process.cpp.*get status\s([0-9]+)\.([0-9]+)', line)
        if reObj:
            sec_sample = int(reObj.group(1))
            ns_sample = int(reObj.group(2))
            stamp_sample = int(sec_sample * 1000 + ns_sample / 1000000)
            if lidar_status_last_stamp == 0:
                lidar_status_last_stamp = stamp_sample
            if 'lidar_status' not in sensor_timespan_samples:
                sensor_timespan_samples['lidar_status'] = []
            if 'lidar_status' not in sensor_timestamp_samples:
                sensor_timestamp_samples['lidar_status'] = []
            if(stamp_sample > lidar_status_last_stamp):
                sensor_timespan_samples['lidar_status'].append([len(sensor_timespan_samples['lidar_status']), stamp_sample - lidar_status_last_stamp])
            sensor_timestamp_samples['lidar_status'].append(stamp_sample)
            lidar_status_last_stamp = stamp_sample
        
        reObj = re.match('.*lidar_process.cpp.*get packet\s([0-9]+)\.([0-9]+)', line)
        if reObj:
            sec_sample = int(reObj.group(1))
            ns_sample = int(reObj.group(2))
            stamp_sample = int(sec_sample * 1000 + ns_sample / 1000000)
            if lidar_packet_last_stamp == 0:
                lidar_packet_last_stamp = stamp_sample
            if 'lidar_packet' not in sensor_timespan_samples:
                sensor_timespan_samples['lidar_packet'] = []
            if 'lidar_packet' not in sensor_timestamp_samples:
                sensor_timestamp_samples['lidar_packet'] = []
            if(stamp_sample > lidar_packet_last_stamp):
                sensor_timespan_samples['lidar_packet'].append([len(sensor_timespan_samples['lidar_packet']),stamp_sample - lidar_packet_last_stamp])
            sensor_timestamp_samples['lidar_packet'].append(stamp_sample)
            lidar_packet_last_stamp = stamp_sample

        reObj = re.match('.*ImuCapture.*app index:.*sec:([0-9]+),\snanosec:([0-9]+)', line)
        if reObj:
            sec_sample = int(reObj.group(1))
            ns_sample = int(reObj.group(2))
            stamp_sample = int(sec_sample * 1000 + ns_sample / 1000000)
            if imu_last_stamp == 0:
                imu_last_stamp = stamp_sample
            if 'imu' not in sensor_timespan_samples:
                sensor_timespan_samples['imu'] = []
            if 'imu' not in sensor_timestamp_samples:
                sensor_timestamp_samples['imu'] = []
            if(stamp_sample > imu_last_stamp):
                sensor_timespan_samples['imu'].append([len(sensor_timespan_samples['imu']),stamp_sample - imu_last_stamp])
            sensor_timestamp_samples['imu'].append(stamp_sample)
            imu_last_stamp = stamp_sample
        
        reObj = re.match('.*GnssCapture.*app index:.*sec:([0-9]+),\snanosec:([0-9]+).*msgID:([0-9]+)', line)
        if reObj:
            sec_sample = int(reObj.group(1))
            ns_sample = int(reObj.group(2))
            stamp_sample = int(sec_sample * 1000 + ns_sample / 1000000)
            msgId = int(reObj.group(3))
            # 检查msgId 是否在集合中 否则产生一个测试失败
            if msgId not in gnss_msg_id:
                print('msgId:' + str(msgId) + ' not in gnss_msg_id')
                stamp_sample = 50
            if gnss_last_stamp == 0:
                gnss_last_stamp = stamp_sample
            if 'gnss' not in sensor_timespan_samples:
                sensor_timespan_samples['gnss'] = []
            if 'gnss' not in sensor_timestamp_samples:
                sensor_timestamp_samples['gnss'] = []
            if(stamp_sample > gnss_last_stamp):
                sensor_timespan_samples['gnss'].append([len(sensor_timespan_samples['gnss']), stamp_sample - gnss_last_stamp])
            sensor_timestamp_samples['gnss'].append(stamp_sample)
            gnss_last_stamp = stamp_sample

        reObj = re.match('.*Sensor([0-9]+)\s+Frame\sdrops:\s([0-9]+)', line)
        if reObj:
            ch_num_str = reObj.group(1)
            ch_num = int(ch_num_str)
            drop_sample = float(reObj.group(2))
            if ch_num_str not in camera_drop_frame_samples:
                camera_drop_frame_samples[ch_num_str] = []
            camera_drop_frame_samples[ch_num_str].append(drop_sample)
            print('drop_sample: ', drop_sample)
        
        reObj = re.match('(.*\s[0-9]{2}\s[0-9]{2}:[0-9]{2}:[0-9]{2}\.[0-9]{3}.*stdout\s+[0-9]+)\s+(.*)\s\|(\s+[0-9]+\s\|)+', line)
        if reObj:
            match_line = reObj.group(0).replace(reObj.group(1), '')
            str_array=match_line.split('|')
            process_name=str_array[0].strip()

            if process_name in process_name_array:   
                process_id=str_array[1].strip()
                process_memory_str=str_array[3].strip()
                process_memory=round(int(process_memory_str)/1024, 3)
                print(process_name, str(process_memory) + "MB")
                process_id_str= process_name+'-'+str(process_id)
                if process_id_str not in process_memory_samples:
                    process_memory_samples[process_id_str] = []
                process_memory_samples[process_id_str].append([len(process_memory_samples[process_id_str]), process_memory])

        reObj = re.match('\s+(.*)\s\|(\s+[0-9]+\s\|)+', line)
        if reObj:
            match_line = reObj.group(0)

def process_charts_data():
    global camera_fps_samples
    global algo_last_stamp_samples
    global encoder_last_stamp_samples
    global algo_timespan_samples
    global encoder_timespan_samples
    global algo_timestamp_samples
    global encoder_timestamp_samples
    global algo_resolution_samples
    global encoder_resolution_samples
    global camera_drop_frame_samples
    global sensor_timestamp_samples
    global sensor_timespan_samples
    global process_memory_samples
    global thread_cpu_samples
    global lidar_status_last_stamp
    global lidar_packet_last_stamp
    global imu_last_stamp
    global gnss_last_stamp

    # 进程内存数据
    process_memory_series_array = []
    process_memory_legend_array = []
    for ch_key in process_memory_samples:
        process_memory_series = {'symbolSize': 5, 'type':'line', 'name': ch_key, 'data': process_memory_samples[ch_key]}
        process_memory_series_array.append(process_memory_series)
        process_memory_legend_array.append(ch_key)
    process_memory_charts_data = {'title': 'MB','series':process_memory_series_array, 'legend': process_memory_legend_array}

    # 线程CPU数据
    thread_cpu_series_array = []
    thread_cpu_legend_array = []
    for ch_key in thread_cpu_samples:
        thread_cpu_series = {'symbolSize': 5, 'type':'line', 'name': ch_key, 'data': thread_cpu_samples[ch_key]}
        thread_cpu_series_array.append(thread_cpu_series)
        thread_cpu_legend_array.append(ch_key)
    thread_cpu_charts_data = {'title': 'MB','series':thread_cpu_series_array, 'legend': thread_cpu_legend_array}

    # 相机帧率数据
    camera_fps_series_array = []
    camera_fps_legend_array = []
    for ch_key in camera_fps_samples:
        camera_fps_series = {'symbolSize': 5, 'type':'scatter', 'data': camera_fps_samples[ch_key]}
        camera_fps_series_array.append(camera_fps_series)
        camera_fps_legend_array.append(ch_key)
    camera_fps_charts_data = {'title': 'Camera帧率','series':camera_fps_series_array, 'legend': camera_fps_legend_array}
    
    # Algo时间戳
    algo_timespan_series_array = []
    algo_timespan_legend_array = []
    for ch_key in algo_timespan_samples:
        algo_timespan_series = {'symbolSize': 5, 'type':'scatter', 'data': algo_timespan_samples[ch_key]}
        algo_timespan_series_array.append(algo_timespan_series)
        algo_timespan_legend_array.append(ch_key)
    algo_timespan_charts_data = {'title': 'Algo帧间隔ms','series':algo_timespan_series_array,'legend':algo_timespan_legend_array}

    # Encoder时间戳
    encoder_timespan_series_array = []
    encoder_timespan_legend_array = []
    for ch_key in encoder_timespan_samples:
        encoder_timespan_series = {'symbolSize': 5, 'type':'scatter', 'data': encoder_timespan_samples[ch_key]}
        encoder_timespan_series_array.append(encoder_timespan_series)
        encoder_timespan_legend_array.append(ch_key)
    encoder_timespan_charts_data = {'title': 'Encoder帧间隔ms','series':encoder_timespan_series_array,'legend':encoder_timespan_legend_array}

    # lidar_status 时间戳
    lidar_status_timespan_series_array = []
    lidar_status_timespan_series = {'symbolSize': 5, 'type':'scatter', 'data': []}
    if 'lidar_status' in sensor_timespan_samples:
        lidar_status_timespan_series['data'] = sensor_timespan_samples['lidar_status']
    lidar_status_timespan_series_array.append(lidar_status_timespan_series)
    lidar_status_timespan_charts_data = {'title': 'lidar_status帧间隔ms','series':lidar_status_timespan_series_array}


    # lidar_packet 时间戳
    lidar_packet_timespan_series_array = []
    lidar_packet_timespan_series = {'symbolSize': 5, 'type':'scatter', 'data': []}
    if 'lidar_packet' in sensor_timespan_samples:
        lidar_packet_timespan_series['data'] = sensor_timespan_samples['lidar_packet']
    lidar_packet_timespan_series_array.append(lidar_packet_timespan_series)
    lidar_packet_timespan_charts_data = {'title': 'lidar_packet帧间隔ms','series':lidar_packet_timespan_series_array}

    # imu 时间戳
    imu_timespan_series_array = []
    imu_timespan_series = {'symbolSize': 5, 'type':'scatter', 'data': []}
    if 'imu' in sensor_timespan_samples:
        imu_timespan_series['data'] = sensor_timespan_samples['imu']
    imu_timespan_series_array.append(imu_timespan_series)
    imu_timespan_charts_data = {'title': 'imu帧间隔ms','series':imu_timespan_series_array}

    # gnss 时间戳
    gnss_timespan_series_array = []
    gnss_timespan_series = {'symbolSize': 5, 'type':'scatter', 'data': []}
    if 'gnss' in sensor_timespan_samples:
        gnss_timespan_series['data'] = sensor_timespan_samples['gnss']
    gnss_timespan_series_array.append(gnss_timespan_series)
    gnss_timespan_charts_data = {'title': 'gnss帧间隔ms','series':gnss_timespan_series_array}

    charts_data_map = {
        'process_memory_charts_data': process_memory_charts_data,
        'camera_fps_charts_data': camera_fps_charts_data,
        "algo_timespan_charts": algo_timespan_charts_data,
        "encoder_timespan_charts": encoder_timespan_charts_data,
        "lidar_status_timespan_charts": lidar_status_timespan_charts_data,
        "lidar_packet_timespan_charts": lidar_packet_timespan_charts_data,
        "imu_timespan_charts": imu_timespan_charts_data,
        "gnss_timespan_charts": gnss_timespan_charts_data
    }
    return charts_data_map

def process_camera_data():
    global camera_fps_samples
    global algo_last_stamp_samples
    global encoder_last_stamp_samples
    global algo_timespan_samples
    global encoder_timespan_samples
    global algo_timestamp_samples
    global encoder_timestamp_samples
    global algo_resolution_samples
    global encoder_resolution_samples
    global camera_drop_frame_samples
    global sensor_timestamp_samples
    global sensor_timespan_samples
    global process_memory_samples
    global thread_cpu_samples
    global lidar_status_last_stamp
    global lidar_packet_last_stamp
    global imu_last_stamp
    global gnss_last_stamp

    camera_datas={}
    for ch_key in camera_fps_samples:
        ch_index = int(ch_key)
        fps_arry = np.array(camera_fps_samples[ch_key])
        camera_datas[ch_key] = {'chIndex': ch_index,
            'resolution': 'unknown',
            'fpsAvg': round(fps_arry.mean(axis=0)[1],3),
            'fpsMax': round(fps_arry.max(axis=0)[1],3),
            'fpsMin': round(fps_arry.min(axis=0)[1],3),
            'testResult': 'Pass'
        }
        if camera_datas[ch_key]['fpsAvg'] < 9:
            camera_datas[ch_key]['testResult']='Failed'
        if camera_datas[ch_key]['testResult']=='Pass':
            if ch_key in algo_resolution_samples:
                camera_datas[ch_key]['resolution'] = algo_resolution_samples[ch_key]
            if ch_key in encoder_resolution_samples:
                camera_datas[ch_key]['resolution'] = encoder_resolution_samples[ch_key]
            if ch_index == 3:
                if camera_datas[ch_key]['resolution'] == '1920x1080':
                    camera_datas[ch_key]['testResult']='Pass'
            else:
                if camera_datas[ch_key]['resolution'] == '1024x576':
                    camera_datas[ch_key]['testResult']='Pass'
                else:
                    camera_datas[ch_key]['testResult']='Failed'
    return sort_by_key(camera_datas)

def process_downstream_timespan(timespan_samples):
    global camera_fps_samples
    global algo_last_stamp_samples
    global encoder_last_stamp_samples
    global algo_timespan_samples
    global encoder_timespan_samples
    global algo_timestamp_samples
    global encoder_timestamp_samples
    global algo_resolution_samples
    global encoder_resolution_samples
    global camera_drop_frame_samples
    global sensor_timestamp_samples
    global sensor_timespan_samples
    global process_memory_samples
    global thread_cpu_samples
    global lidar_status_last_stamp
    global lidar_packet_last_stamp
    global imu_last_stamp
    global gnss_last_stamp

    result_datas={}
    for ch_key in timespan_samples:
        ch_index = int(ch_key)
        result_datas[ch_key]={'chIndex': ch_index,'testResult': 'Pass'}
        timespan_val_array = np.array(timespan_samples[ch_key])
        if timespan_val_array.shape[0] == 0 or timespan_val_array.shape[1] < 2:
            result_datas[ch_key]['testResult'] = 'Failed' 
            return result_datas
        for timespan_val in timespan_val_array[:,1]:
            if abs(timespan_val - 100) > 5:
                result_datas[ch_key]['testResult'] = 'Failed' 
    return sort_by_key(result_datas)

def process_downstream_timestamp(timestamp_samples):
    global camera_fps_samples
    global algo_last_stamp_samples
    global encoder_last_stamp_samples
    global algo_timespan_samples
    global encoder_timespan_samples
    global algo_timestamp_samples
    global encoder_timestamp_samples
    global algo_resolution_samples
    global encoder_resolution_samples
    global camera_drop_frame_samples
    global sensor_timestamp_samples
    global sensor_timespan_samples
    global process_memory_samples
    global thread_cpu_samples
    global lidar_status_last_stamp
    global lidar_packet_last_stamp
    global imu_last_stamp
    global gnss_last_stamp

    result_datas={}
    for ch_key in timestamp_samples:
        ch_index = int(ch_key)
        timestamp_vals=timestamp_samples[ch_key]
        result_datas[ch_key]={'chIndex': ch_index,
            'testResult': 'Pass'
        }
        if len(timestamp_vals) <=0:
           result_datas[ch_key]['testResult'] = 'Failed' 
        for timestamp_val in timestamp_vals:
            if timestamp_val % 100 > 5 and timestamp_val % 100 < 95:
                result_datas[ch_key]['testResult'] = 'Failed' 
    return sort_by_key(result_datas)

def process_sensor_timespan(sensor_key):
    global camera_fps_samples
    global algo_last_stamp_samples
    global encoder_last_stamp_samples
    global algo_timespan_samples
    global encoder_timespan_samples
    global algo_timestamp_samples
    global encoder_timestamp_samples
    global algo_resolution_samples
    global encoder_resolution_samples
    global camera_drop_frame_samples
    global sensor_timestamp_samples
    global sensor_timespan_samples
    global process_memory_samples
    global thread_cpu_samples
    global lidar_status_last_stamp
    global lidar_packet_last_stamp
    global imu_last_stamp
    global gnss_last_stamp

    if sensor_key not in sensor_timespan_samples:
        return 'Failed'
    timespan_val_array = np.array(sensor_timespan_samples[sensor_key])
    if timespan_val_array.shape[0] == 0 or timespan_val_array.shape[1] < 2:
        return 'Failed'
    timespan_vals = timespan_val_array[:,1]
    for timespan_val in timespan_vals:
        if abs(timespan_val - 100) > 5:
            return 'Failed'
    return 'Pass'

def process_sensor_timestamp(sensor_key):
    global camera_fps_samples
    global algo_last_stamp_samples
    global encoder_last_stamp_samples
    global algo_timespan_samples
    global encoder_timespan_samples
    global algo_timestamp_samples
    global encoder_timestamp_samples
    global algo_resolution_samples
    global encoder_resolution_samples
    global camera_drop_frame_samples
    global sensor_timestamp_samples
    global sensor_timespan_samples
    global process_memory_samples
    global thread_cpu_samples
    global lidar_status_last_stamp
    global lidar_packet_last_stamp
    global imu_last_stamp
    global gnss_last_stamp

    if sensor_key not in sensor_timestamp_samples:
        return 'Failed'
    timestamp_vals = sensor_timestamp_samples[sensor_key]
    if len(timestamp_vals) <=0:
        return 'Failed'
    for timestamp_val in timestamp_vals:
        if timestamp_val % 100 > 5 and timestamp_val % 100 < 95:
            return 'Failed'
    return 'Pass'

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Error: input log file(*.log) not specified')
        sys.exit()

    path = os.getcwd().replace("\\", "/")
    temp_path = '/templates/template.html'
    full_path = path+temp_path

    env = jinja2.Environment(loader=jinja2.FileSystemLoader(path))
    temp = env.get_template(temp_path)

    log_lines = []
    with open(sys.argv[1], 'r', encoding='utf8',errors='ignore') as log_file:
        log_content = log_file.read()
        log_lines = log_content.split('\n')
        
    print("lines: ", len(log_lines))
    process_log_data()

    camera_datas=process_camera_data()
    algo_timespan_datas = process_downstream_timespan(algo_timespan_samples)
    encoder_timespan_datas = process_downstream_timespan(encoder_timespan_samples)
    algo_timestamp_datas = process_downstream_timestamp(algo_timestamp_samples)
    encoder_timestamp_datas = process_downstream_timestamp(encoder_timestamp_samples)


    sensor_results_data = {}
    sensor_results_data['lidar_status'] = {}
    sensor_results_data['lidar_packet'] = {}
    sensor_results_data['imu'] = {}
    sensor_results_data['gnss'] = {}

    sensor_results_data['lidar_status']['timespan']=process_sensor_timespan('lidar_status')
    sensor_results_data['lidar_status']['timestamp']=process_sensor_timestamp('lidar_status')
    sensor_results_data['lidar_packet']['timespan']=process_sensor_timespan('lidar_packet')
    sensor_results_data['lidar_packet']['timestamp']=process_sensor_timestamp('lidar_packet')
    sensor_results_data['imu']['timespan']=process_sensor_timespan('imu')
    sensor_results_data['imu']['timestamp']=process_sensor_timestamp('imu')
    sensor_results_data['gnss']['timespan']=process_sensor_timespan('gnss')
    sensor_results_data['gnss']['timestamp']=process_sensor_timestamp('gnss')

    # 渲染HTML Charts
    charts_data = process_charts_data()
    temp_out = temp.render(camera_datas=camera_datas,
    algo_timespan_datas= algo_timespan_datas,
    encoder_timespan_datas=encoder_timespan_datas,
    algo_timestamp_datas=algo_timestamp_datas,
    encoder_timestamp_datas=encoder_timestamp_datas,
    sensor_results_data=sensor_results_data,
    charts_data_map=charts_data)

    # 保存
    full_path2 = path+'/reports/report_build_'+os.getenv('BUILD_NUMBER')+'.html'
    with open(full_path2, 'w', encoding='utf-8') as f:
        f.writelines(temp_out)
        f.close()
    
    bot = MaiBot("C04GGD5S1MW")
    massage = '{job_name} build successful.\n{job_url}\nreport: {reports_url}'.format(
        job_name=os.getenv('JOB_NAME'), job_url=os.getenv('BUILD_URL'), reports_url='http://10.130.16.73:8080/view/tdc/job/tdc_sensor_test/HTML_20Report/')
    print(massage)
    bot.requests_send(massage)