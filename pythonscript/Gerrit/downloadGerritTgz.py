#!/bin/python
import os
import sys
import argparse
from commonfun import *
from basic_auth import *
import requests
import shutil
import time
from selenium import webdriver
from selenium.webdriver.chrome.options import Options

pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
# headers={"Cookie":"GerritAccount=aUsfprsWMFK5HiIaJY1RHhM2KHQOAilL6a; XSRF_TOKEN=aUsfprtm9B.c6C1tHvjio-KbtDjFvSjOrW"}
'''
下载 chromedriver
https://registry.npmmirror.com/binary.html?path=chromedriver/
'''

def GetCookie(url):
    options = webdriver.ChromeOptions()
    options.add_argument("headless")
    options.add_argument('--no-sandbox')
    options.add_argument('--disable-gpu')
    options.add_argument('--disable-dev-shm-usage')
    driver = webdriver.Chrome(executable_path=pyFileDir+"/chromedriver",options=options)
    driver.get(url)
    driver.find_element("xpath",'/html/body/header/div/div[2]/a[2]').click()
    time.sleep(1)
    driver.find_element("id","f_user").send_keys(basic_auth[0])
    driver.find_element("id",'f_pass').send_keys(basic_auth[1])
    driver.find_element("id",'b_signin').click()
    time.sleep(1)
    driverCookies = driver.get_cookies()
    driverCookieslists=[]
    for driverCookie in driverCookies:
        driverCookieslists.append(f'{driverCookie["name"]}={driverCookie["value"]}')
    driverCookies ="; ".join(driverCookieslists)
    cookies={}
    cookies["Cookie"]=driverCookies
    print(cookies)
    return cookies

def guntargz(file,fileName,path):
    print("解压中 "+file)
    tagName = fileName.split(".")
    if len(tagName) !=0:
        tagName = tagName[0]
    tagName=path+"/"+tagName
    if os.path.exists(tagName):
        shutil.rmtree(tagName)
    os.makedirs(tagName)
    os.system(f"tar -zxvf {file} -C {tagName}")

def DownloadGerritTgz(url,path):
    assert isinstance(url,str)
    # url = "https://git.i-tetris.com/plugins/gitiles/qcom/sa/qnx/mega/prebuilts/bigsur/+/refs/heads/sop/bigsur_hqx.1.2.1_20230130"
    # wget.download(url,"./bigsur_hqx.1.2.1_20230130.tar.gz")
    urls = url.split("/")
    fileName = urls[len(urls)-1]
    file = path+"/"+fileName
    print("下载 "+url)
    headers = GetCookie(url)
    response = requests.get(url,auth=basic_auth,allow_redirects=True,headers=headers)
    content = response.content
    print("写入 "+file)
    with open(file, "wb") as cr:
        cr.write(content)
    guntargz(file,fileName,path)
    print("下载完成")

def WDownload(url,path):
    print("下载 "+url)
    os.system(f"wget {url} --http-user={basic_auth[0]} --http-password={basic_auth[1]}")
    urls = url.split("/")
    fileName = urls[len(urls)-1]
    file = path+"/"+fileName
    guntargz(file,fileName,path)
    print("下载完成")

if __name__ == "__main__":
    parse = argparse.ArgumentParser(description='下载GerritTgz')
    parse.add_argument('-u','--url',help='url',type=str)
    parse.add_argument('-w','--wurl',help='url',type=str)
    parse.add_argument('-p','--path',help='url',type=str,default=".",nargs="?")
    arg = parse.parse_args()
    if '-u' in sys.argv:
        DownloadGerritTgz(arg.url,arg.path)
    elif '-w' in sys.argv:
        WDownload(arg.wurl,arg.path)