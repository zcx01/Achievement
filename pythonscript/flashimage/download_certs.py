# -*- encoding : utf-8 -*-

import json
import copy
import hashlib
import requests
import time
import sys
import os
import collections
import random
import logging
from http.client import HTTPConnection

TLS_CERT_FILE = "CDC.tls.cert"
TLS_KEY_FILE  = "CDC.tls.key"
CDC_CA_FILE   = "CA.CERT"
CDC_CERT      = "CDC.cert"
HOST_NAME     = "tsp-test.gn.i-tetris.com"
APP_ID        = "100220001"
APP_SECRET    = "6f0aa1bD108817e8a3613198127E7BD1"
DEVICE_ID     = "local"
OS            = "MegaOS"
OS_VERSION    = "1.0.0"
APP_VERSION   = "1.0.0"
LANG          = "zh"
REGION        = "cn"
DEVICE_TYPE   = "car"
# VIN           = "MOCKMATRIX"
VIN           = "MATX"
SERIES        = "GN01"
OPERATOR_ID   = "M1"
MODEL_ID      = "15"

def get_sign(sign_str):
    h = hashlib.md5()
    h.update(sign_str.encode('utf8'))
    sign = h.hexdigest()
    return sign

def get_param_str(param):
    param_str = ""
    od = collections.OrderedDict(sorted(param.items()))
    for k, v in od.items():
        param_str = param_str + k + '=' + v + '&'

    return param_str[0:(len(param_str)-1)]

def data_to_param_json(nonce,data_str,timestamp):
    param = {}
    param['jsonBody'] = data_str
    param['app_id'] = APP_ID
    param['nonce'] = nonce
    param['device_id'] = DEVICE_ID
    param['timestamp'] = timestamp
    param['os'] = OS
    param['os_version'] = OS_VERSION
    param['app_version'] = APP_VERSION
    param['device_type'] = DEVICE_TYPE
    # param['lang'] = LANG
    # param['region'] = REGION
    return param

def get_sign_string_json(method, path,data, access_token, timestamp,nonce):
    param = data_to_param_json(nonce, json.dumps(data),timestamp)
    param_str = get_param_str(param)
    sign_str = method + path + '?' + param_str + APP_SECRET
    if access_token is not None:
        sign_str = sign_str + 'Bearer ' + access_token

    # print("sign str %s" % sign_str)
    return sign_str

def get_nonce():
    return ''.join(str(random.choice(range(10))) for _ in range(10))
 
def get_vin():
    return str(int(round(time.time() * 1000)))
    # return ''.join(str(random.choice(range(10))) for _ in range(7))

def get_json_body():
    body={}	
    vehicle_propfile={}
    vehicle_propfile['vin'] = VIN + get_vin()
    vehicle_propfile['model_id'] = MODEL_ID
    vehicle_propfile['series'] = SERIES
    body['operator_id'] = OPERATOR_ID
    body['vehicle_profile'] = vehicle_propfile
    return body
    
def getVid():
    app_id = APP_ID
    nonce = get_nonce()
    device_id = DEVICE_ID
    os = OS
    os_version =  OS_VERSION
    app_version = APP_VERSION
    device_type = DEVICE_TYPE
    now = int(time.time())
    timestamp = str(now)
    data_str= get_json_body()
    path = "/api/1/in/vehicle/mock/new_profile"

    url = ("https://%s" + path) % HOST_NAME

    sign_str = get_sign_string_json('POST', path, data_str,None, timestamp,nonce)
    sign = get_sign(sign_str)

    headers = {'Content-Type':'application/json','KK-Sign':sign}
    params = {'app_id':APP_ID, 'nonce':nonce, 'device_id':DEVICE_ID, 'timestamp':timestamp,'os':os,'os_version':os_version,'app_version':app_version,'device_type':device_type}
        
    r = requests.post(url, params=params, headers=headers,data=json.dumps(data_str))
    r_text = r.text
    response = json.loads(r_text)
    if response['result_code'] != "success":
        print(response)
        print("云端申请车机证书失败！")
        sys.exit(0)
    data = response['data']
    write_cert_files(data)

def write_cert_files(data):
    cdc_tls_cert = data['tls_cdc_cert']
    cdc_tls_key = data['tls_cdc_priv_key']
    cdc_ca = data['cloud_tls_trust_chain']
    cdc_cert = data['cdc_cert']    
				
    write_file(TLS_CERT_FILE, cdc_tls_cert)
    write_file(TLS_KEY_FILE, cdc_tls_key)
    write_file(CDC_CA_FILE, cdc_ca)
    write_file(CDC_CERT,cdc_cert)

def write_file(filename, data):
    with open(filename, 'w') as f:
        f.write(data)

def write_cert(filename):
    os.system("adb -s 1234567 push %s /data/user_de/0/com.mega.cert/cache/" % filename)
    time.sleep(2)
    os.system("adb -s 1234567 shell catls %s /data/user_de/0/com.mega.cert/cache/%s" % (filename, filename))
    time.sleep(2)

def debug_requests_on():
    '''Switches on logging of the requests module.'''
    HTTPConnection.debuglevel = 1

    logging.basicConfig()
    logging.getLogger().setLevel(logging.DEBUG)
    requests_log = logging.getLogger("requests.packages.urllib3")
    requests_log.setLevel(logging.DEBUG)
    requests_log.propagate = True

def import_certs():
    # 车机进入root模式
    os.system("adb -s 1234567 root")
    time.sleep(10)
    getVid()
    # os.system("adb push %s /vendor/bin/" % "catls")
    write_cert(TLS_CERT_FILE)
    write_cert(TLS_KEY_FILE)
    write_cert(CDC_CA_FILE)
    write_cert(CDC_CERT)
        
if __name__ == '__main__':
    #vehicle_id = sys.argv[1]
    #debug_requests_on()
    # 车机进入root模式
    os.system("adb -s 1234567 root")
    time.sleep(10)
    getVid()
    #os.system("adb push %s /vendor/bin/" % "catls")
    write_cert(TLS_CERT_FILE)
    write_cert(TLS_KEY_FILE)
    write_cert(CDC_CA_FILE)
    write_cert(CDC_CERT)