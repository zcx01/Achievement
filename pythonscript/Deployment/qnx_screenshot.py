#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
'''
@Project ：changan_instrument 
@File ：qnx_screenshot.py
@Author ：guoming.shen
@Date ：2021/12/9 上午10:01 
'''
import datetime
import logging
import os
import sys

import numpy
import pexpect
from PIL import Image

def qnx_screenshot(serial, image_path):
    #登录android
    p = pexpect.spawn("adb -s %s shell" % serial, encoding='utf-8', logfile=sys.stdout, timeout=30)
    index = p.expect(["bigsur:", pexpect.EOF, pexpect.TIMEOUT])
    if index != 0:
        logging.error("%s is not connected!" % serial)
        p.close(force=True)
        return False, "", "", ""
    else:
        #登录qnx
        p.sendline("telnet 192.168.1.1")
        login_index = p.expect(["login:", pexpect.EOF, pexpect.TIMEOUT])
        if login_index == 0:
            p.sendline("root")
            qnx_index = p.expect(["#", pexpect.EOF, pexpect.TIMEOUT])
            if qnx_index == 0:
                logging.info("login qnx sucessful!")
                #开始截屏
                p.sendline("screenshot -display=1 -file=/var/screen_1.bmp")
                p.expect(["#", pexpect.EOF, pexpect.TIMEOUT])
                p.sendline("screenshot -display=2 -file=/var/screen_2.bmp")
                p.expect(["#", pexpect.EOF, pexpect.TIMEOUT])
                p.sendline("exit")
                logout_index = p.expect(["bigsur:", pexpect.EOF, pexpect.TIMEOUT])
                if logout_index == 0:
                    logging.info("log out qnx sucessful!")
                    #拉取图片到android
                    p.sendline('curl -u root:root -o /sdcard/screen_1.bmp "ftp://192.168.1.1/var/screen_1.bmp"')
                    p.expect(["bigsur:", pexpect.EOF, pexpect.TIMEOUT], timeout=60)
                    p.sendline('curl -u root:root -o /sdcard/screen_2.bmp "ftp://192.168.1.1/var/screen_2.bmp"')
                    p.expect(["bigsur:", pexpect.EOF, pexpect.TIMEOUT], timeout=60)
                    p.close(force=True)
                    #拉取图片到PC
                    img1 = os.path.join(image_path, "screen_1.bmp")
                    img2 = os.path.join(image_path, "screen_2.bmp")
                    img_name = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") + ".bmp"
                    out_img = os.path.join(image_path, img_name)
                    os.system("adb -s %s pull %s %s" % (serial, "/sdcard/screen_1.bmp", img1))
                    os.system("adb -s %s pull %s %s" % (serial, "/sdcard/screen_2.bmp", img2))
                    #合并图片
                    blend_two_images(img1, img2, out_img)
                    os.system(f'rm {img1} {img2}')
                    return True, out_img, img1, img2
                else:
                    logging.error("log out qnx failed!")
                    p.close(force=True)
                    return False, "", "", ""
            else:
                logging.error("login qnx failed!")
                p.close(force=True)
                return False, "", "", ""
        else:
            logging.error("login qnx failed!")
            p.close(force=True)
            return False, "", "", ""



def blend_two_images(img1, img2, output_img, ratio=0.4):
    img1 = Image.open(img1)
    img1 = img1.convert('RGBA')
    img2 = Image.open(img2)
    img2 = img2.convert('RGBA')
    img = Image.blend(img1, img2, ratio)
    img.save(output_img)


if __name__ == "__main__":
    is_ok, screen_shot, screen1, screen_2 = qnx_screenshot(serial="1234567", image_path=".")

