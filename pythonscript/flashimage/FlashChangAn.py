#coding:UTF-8

import os
import shutil
import logging
import pexpect
import subprocess
logging.basicConfig(format='%(asctime)s %(levelname)s %(message)s', level=logging.INFO)

from matrixtool.cloud_api import *
from matrixtool.device_self_check.adb_device import *
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from downloadimage.DownFromArtifactory import DownloadImage
from downloadimage.UncompressFiles import UncompressFiles
from flashimage.download_certs import *
class FlashChangAn:

    @classmethod
    def flashAndroid(cls, imageDir):

        if not os.path.exists(imageDir):
            logging.error("刷机文件路径 %s 不存在，请检查后重新开始！")
            exit(1)

        deviceInfo = get_device_info()
        if len(deviceInfo) == 0:
            logging.error("adb未获得device信息，退出刷机")
            exit(1)

        setupModel()
        serialIds = []
        for oneDeviceInfo in deviceInfo:
            resultCode, cloudDeviceInfo = searchDeviceInfo(oneDeviceInfo["serial"])
            if cloudDeviceInfo["type"] == "car":
                serialIds.append(oneDeviceInfo["serial"])

        logging.info("扫描出以下待刷机设备：")
        logging.info(serialIds)

        if len(serialIds) == 0:
            logging.error("未获得车机device信息，退出刷机")
            exit(1)

        allSuccess = True
        for oneSerialId in serialIds:

            p = pexpect.spawn("adb -s %s shell" % oneSerialId, encoding='utf-8', logfile=sys.stdout, timeout=30)
            index = p.expect(["bigsur:", pexpect.EOF, pexpect.TIMEOUT])
            if index != 0:
                logging.error("不能连接至车机：%s" % oneSerialId)
                exit(1)
            p.sendline("telnet 192.168.1.1")
            login_index = p.expect(["login:", pexpect.EOF, pexpect.TIMEOUT])
            if login_index != 0:
                logging.error("telnet qunx失败！")
                exit(1)

            logging.info("telnet qunx成功！")
            p.sendline("root")
            root_index = p.expect(["#", pexpect.EOF, pexpect.TIMEOUT])
            if root_index != 0:
                logging.error("切换至root失败！")
                exit(1)

            logging.info("切换至root成功！")
            p.sendline("reset -f")

            time.sleep(5)
            p.close(force=True)

            isFastboot = False
            for i in range(60):
                fastboot_out = subprocess.getoutput("fastboot devices")
                if "fastboot" in fastboot_out:
                    logging.info("设备 " + oneSerialId + " 已进入fastboot模式")
                    logging.info(fastboot_out)
                    isFastboot = True
                    break

                logging.info("设备" + oneSerialId + "未进入fastboot模式，等待1秒后重试")
                time.sleep(1)

            if not isFastboot:
                logging.error("60秒后设备" + oneSerialId + "依旧未进入fastboot模式，退出刷机！")
                continue

            flashFilePath = os.path.join(imageDir.rstrip("/"), "qfi_bin/common/build/fastboot_complete.py")
            flashCommand = "python %s --pf=8155_la --st=ufs" % flashFilePath
            os.system(flashCommand)
            time.sleep(10)
            logging.info("长安车机android刷机完成")
            os.system("fastboot reboot")
            time.sleep(10)
            isSuccess = False
            for j in range(120):
                adb_out = subprocess.getoutput("adb devices")
                if oneSerialId in adb_out:
                    isSuccess = True
                    break

                logging.info("车机重启中...等待1秒")
                time.sleep(1)

            time.sleep(30)

            if isSuccess:
                logging.info("长安车机 %s android刷机成功" % oneSerialId)
            else:
                logging.info("长安车机 %s android刷机失败" % oneSerialId)

            allSuccess = allSuccess and isSuccess

        if not allSuccess:
            exit(1)

    @classmethod
    def flashMcu(cls, imageDir):

        if not os.path.isdir(imageDir):
            logging.error("刷机文件目录 %s 不存在，请检查后重新开始！")
            exit(1)

        allFiles = os.listdir(imageDir)
        aBinName = ""
        bBinName = ""
        for oneFile in allFiles:
            if oneFile.endswith("_a.bin"):
                aBinName = os.path.join(imageDir, oneFile)
            elif oneFile.endswith("_b.bin"):
                bBinName = os.path.join(imageDir, oneFile)

        if aBinName == "":
            logging.error("_a.bin文件缺失，请检查后重新开始！")
            exit(1)
        if bBinName == "":
            logging.error("_b.bin文件缺失，请检查后重新开始！")
            exit(1)

        logging.info("mcu刷机文件：")
        logging.info(aBinName)
        logging.info(bBinName)

        version = "MCU SW version: " + aBinName.split("/")[-1].split("_")[0].strip()

        deviceInfo = get_device_info()
        if len(deviceInfo) == 0:
            logging.error("adb未获得device信息，退出刷机")
            exit(1)

        setupModel()
        serialIds = []
        for oneDeviceInfo in deviceInfo:
            resultCode, cloudDeviceInfo = searchDeviceInfo(oneDeviceInfo["serial"])
            if cloudDeviceInfo["type"] == "car":
                serialIds.append(oneDeviceInfo["serial"])

        logging.info("扫描出以下待刷机设备：")
        logging.info(serialIds)

        if len(serialIds) == 0:
            logging.error("未获得车机device信息，退出刷机")
            exit(1)

        allSuccess = True
        for oneSerialId in serialIds:

            os.system("adb -s %s root" % oneSerialId)
            time.sleep(30)
            os.system("adb -s %s push %s /data" % (oneSerialId,
                                                   os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                                                "mcu_flasher_changan")))
            os.system("adb -s %s push %s /data" % (oneSerialId, aBinName))
            os.system("adb -s %s push %s /data" % (oneSerialId, bBinName))

            p = pexpect.spawn("adb -s %s shell" % oneSerialId, encoding='utf-8', logfile=sys.stdout, timeout=300)
            index = p.expect(["bigsur:", pexpect.EOF, pexpect.TIMEOUT])
            if index != 0:
                logging.error("不能连接至车机：%s" % oneSerialId)
                exit(1)

            p.sendline("curl -u root:root -T /data/mcu_flasher_changan \"ftp://192.168.1.1/data/\"")
            curl_index = p.expect(["100", pexpect.EOF, pexpect.TIMEOUT])
            if curl_index != 0:
                print("上传mcu_flasher_changan文件至qnx失败")
                exit(1)

            binFileName = aBinName.split("/")[-1]
            p.sendline("curl -u root:root -T /data/%s \"ftp://192.168.1.1/data/\"" % binFileName)
            curl_index = p.expect(["100", pexpect.EOF, pexpect.TIMEOUT])
            if curl_index != 0:
                print("上传%s文件至qnx失败" % binFileName)
                exit(1)

            binFileName = bBinName.split("/")[-1]
            p.sendline("curl -u root:root -T /data/%s \"ftp://192.168.1.1/data/\"" % binFileName)
            curl_index = p.expect(["100", pexpect.EOF, pexpect.TIMEOUT])
            if curl_index != 0:
                print("上传%s文件至qnx失败" % binFileName)
                exit(1)

            p.sendline("rm /data/mcu_flasher_changan")
            rm_index = p.expect(["bigsur", pexpect.EOF, pexpect.TIMEOUT])
            if rm_index != 0:
                logging.error("删除/data/mcu_flasher_changan文件失败")

            p.sendline("rm /data/%s" % aBinName.split("/")[-1])
            rm_index = p.expect(["bigsur", pexpect.EOF, pexpect.TIMEOUT])
            if rm_index != 0:
                logging.error("删除/data/%s文件失败" % aBinName.split("/")[-1])

            p.sendline("rm /data/%s" % bBinName.split("/")[-1])
            rm_index = p.expect(["bigsur", pexpect.EOF, pexpect.TIMEOUT])
            if rm_index != 0:
                logging.error("删除/data/%s文件失败" % bBinName.split("/")[-1])

            p.sendline("telnet 192.168.1.1")
            login_index = p.expect(["login:", pexpect.EOF, pexpect.TIMEOUT])
            if login_index != 0:
                logging.error("telnet qunx失败！")
                exit(1)

            logging.info("telnet至qunx成功！")
            p.sendline("root")
            root_index = p.expect(["#", pexpect.EOF, pexpect.TIMEOUT])
            if root_index != 0:
                logging.error("切换至root失败！")
                exit(1)

            logging.info("切换至root成功！")
            p.sendline("cd /data")
            cd_index = p.expect(["#", pexpect.EOF, pexpect.TIMEOUT])
            if cd_index != 0:
                logging.error("cd至/data文件夹失败！")
                exit(1)
            logging.info("cd至/data文件夹成功！")

            p.sendline("chmod 777 mcu_flasher_changan")
            chmod_index = p.expect(["#", pexpect.EOF, pexpect.TIMEOUT])
            if chmod_index != 0:
                logging.error("修改文件mcu_flasher_changan权限失败！")
                exit(1)
            logging.info("修改文件mcu_flasher_changan权限成功！")

            p.sendline("./mcu_flasher_changan -p /data")
            p.sendline("reset")
            out = p.read()
            if "mcu_flasher.flash() return 0" in out:
                logging.info("刷写车机 %s MCU成功！" % oneSerialId)
                allSuccess = allSuccess and True
            else:
                logging.error("刷写车机 %s MCU失败" % oneSerialId)
                allSuccess = allSuccess and False

            p.close(force=True)

            rebootSuccess = False
            for j in range(120):
                adb_out = subprocess.getoutput("adb devices")
                if oneSerialId in adb_out:
                    rebootSuccess = True
                    break

                logging.info("车机重启中...等待1秒")
                time.sleep(1)

            time.sleep(60)
            if rebootSuccess:
                logging.info("长安车机 %s MCU 重启成功" % oneSerialId)
                p = pexpect.spawn("adb -s %s shell" % oneSerialId, encoding='utf-8', logfile=sys.stdout, timeout=300)
                index = p.expect(["bigsur:", pexpect.EOF, pexpect.TIMEOUT])
                if index != 0:
                    logging.error("不能连接至车机：%s" % oneSerialId)
                    exit(1)
                p.sendline("telnet 192.168.1.1")
                login_index = p.expect(["login:", pexpect.EOF, pexpect.TIMEOUT])
                if login_index != 0:
                    logging.error("telnet qunx失败！")
                    exit(1)

                p.sendline("root")
                root_index = p.expect(["#", pexpect.EOF, pexpect.TIMEOUT])
                if root_index != 0:
                    logging.error("切换至root失败！")
                    exit(1)

                p.sendline("rm /data/%s" % aBinName.split("/")[-1])
                rm_index = p.expect(["#", pexpect.EOF, pexpect.TIMEOUT])
                if rm_index != 0:
                    logging.error("qnx删除/data/%s文件失败" % aBinName.split("/")[-1])

                p.sendline("rm /data/%s" % bBinName.split("/")[-1])
                rm_index = p.expect(["#", pexpect.EOF, pexpect.TIMEOUT])
                if rm_index != 0:
                    logging.error("qnx删除/data/%s文件失败" % bBinName.split("/")[-1])

                p.sendline("rm /data/mcu_flasher_changan")
                rm_index = p.expect(["#", pexpect.EOF, pexpect.TIMEOUT])
                if rm_index != 0:
                    logging.error("qnx删除/data/mcu_flasher_changan文件失败")
                p.close(force=True)
            else:
                logging.info("长安车机 %s MCU 重启失败" % oneSerialId)

        if allSuccess:
            logging.info("长安车机MCU刷写成功")
        else:
            logging.error("成安车机刷写失败！")
            exit(1)

    @classmethod
    def deleteImageDir(cls, filePath):
        """
        删除filePath文件或文件夹
        :param filePath: 文件或文件夹路径
        :return:
        """
        if not os.path.exists(filePath):
            logging.info("文件或文件夹%s不存在，退出删除" % filePath)
            return

        if os.path.isfile(filePath):
            os.remove(filePath)
            logging.info("删除文件%s成功！" % filePath)
        elif os.path.isdir(filePath):
            shutil.rmtree(filePath)
            logging.info("删除文件夹%s成功！" % filePath)


if __name__ == "__main__":

    logging.info("开始刷写长安车机android设备")
    #主线分支
    # artifactoryPath = ["sa8155-hqx", "dailybuild", "dev_hqx.1.1", "bigsur_megaos"]
    # imageKeywords = "bigsur_MEGAOS_BURN-dev"
    #1108分支
    artifactoryPath = ["sa8155-hqx", "dailybuild", "release-bigsur_hqx.1.1_20211108", "bigsur_megaos"]
    # imageKeywords = "bigsur_MEGAOS_C385-EVE_BURN-release-bigsur_hqx"
    imageKeywords = "C385-EV_OS"
    # imageKeywords = "C385-EVE-OS"

    targetFolder = os.path.dirname(os.path.abspath(__file__))
    imageLocalPath = DownloadImage.downloadFromUrl(downloadPath=artifactoryPath, targetFolder=targetFolder,
                                                   keywords=imageKeywords, isLatest=True)

    uncompressObj = UncompressFiles(compressPath=imageLocalPath, targetFolder=targetFolder)
    uncompressImageDir = uncompressObj.uncompressFiles()

    FlashChangAn.flashAndroid(imageDir=uncompressImageDir)
    uncompressImageDir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "uncompress")
    FlashChangAn.deleteImageDir(filePath=uncompressImageDir)
    FlashChangAn.deleteImageDir(filePath=imageLocalPath)

    time.sleep(5)
    logging.info("开始刷写长安车机MCU设备")
    # artifactoryPath = ["kiara-gateway", "dailybuild", "changan_hu", "c385_eve"]
    artifactoryPath = ["kiara-gateway", "dailybuild", "changan_hu", "release-bigsur_hqx.1.1_20211108"]
    imageKeywords = ""
    imageLocalPath = DownloadImage.downloadFromUrl(downloadPath=artifactoryPath, targetFolder=targetFolder,
                                                   keywords=imageKeywords, isLatest=True)

    FlashChangAn.flashMcu(imageDir=imageLocalPath)
    FlashChangAn.deleteImageDir(filePath=imageLocalPath)

    time.sleep(5)
    logging.info("导入证书")
    import_certs()


