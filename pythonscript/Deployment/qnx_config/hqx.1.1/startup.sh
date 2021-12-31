#! /bin/sh

runusb() {

    case $1 in 
        PRIM)
            ARGS="ioport=0xa600000,irq=165,nousb3,soc=8155"
            STACK_NO="1"
            LUA_PATH="/etc/usblauncher/usb${STACK_NO}.lua"
            DEV_OTG_PATH="/dev/usb${STACK_NO}/io-usb-otg"
            ;;

        SEC)
            ARGS="ioport=0xa800000,irq=170,soc=8155"
            STACK_NO="2"
            LUA_PATH="/etc/usblauncher/usb${STACK_NO}.lua"
            DEV_OTG_PATH="/dev/usb${STACK_NO}/io-usb-otg"
            DEFAULT_USB=1
            ;;
        *)
            echo "runusb: Invalid arguments"
            exit
            ;;
    esac

    on $IO_USB_ON_ARGS $IO_USB_BINARY  -dqcom-xhci $ARGS, -n $DEV_OTG_PATH

    waitfor $DEV_OTG_PATH
    chmod 664 $DEV_OTG_PATH
    if [ $DEFAULT_USB -eq 1 ]; then
        ln -sPf $DEV_OTG_PATH /dev/usb/io-usb-otg
    fi
    waitfor /var/pps
    if [ $SECPOL_ENABLE -eq 1 ]; then
        chown 40:40 /var/pps 
    fi
    on $USBLAUNCHER_OTG_ON_ARGS $USBLAUNCHER_OTG_BINARY -S $STACK_NO -c $LUA_PATH -M /etc/usblauncher/rules.mnt -m /var/pps -n $DEV_OTG_PATH -E -e -0
}

usb() {
    log_launch "io-usb"

    if [ ! -z ${USB2_ENABLE} ]
    then
        runusb SEC
    fi

    if [ ! -z ${USB3_ENABLE} ]
    then
        runusb PRIM
    fi

}
to_bmetrics()
{
        print ${1+"${@}"} > /dev/bmetrics
}

log_launch()
{
        to_bmetrics bootmarker ${1}: launching
}

log_ready()
{
        to_bmetrics bootmarker ${1} ready
}

fde_on(){
    on $FDE_CTL_ON_ARGS $FDE_CTL_BINARY -p userdata basic
    fr=$?
    if [ $fr -eq 0 ] || [ $fr -eq 1 ] ; then
        echo "Setting key for the partition successful $fr";
        return $fr
    else
        echo "Setting key for the partition failed in the beginning exiting inplace FDE operation $fr";
        return 2
    fi
}

fde_on_mount(){
    mount -t qnx6 $DEV_PATH/userdata /var/userdata
    if [ $? -eq 0 ] ; then
        echo "Inplace was already executed succefully";
        return 0
    else
        echo "mount partition failed";
        return 1
    fi
}
fde_off_mount(){
    on $FDE_CTL_ON_ARGS $FDE_CTL_BINARY -p userdata disable
    if [ $? -ne 0 ] ; then
        echo "Not able to disable FDE exiting"
        return 2
    fi
    echo "Disabled FDE going to mount userdata again. if able to mount then do inplace FDE from beginning"
    mount -t qnx6 $DEV_PATH/userdata /var/userdata
    rc=$?
    echo "mount userdata returned $rc"
    if [ $rc -ne 0 ] ; then
        echo "mount userdata failed after disabling FDE $rc"
        return 1
    else
        echo "mount userdata successful after disabling FDE";
        return 0
    fi
}

start_inplace_fde(){
    echo "mounting successful hence Unmount userdata and execute inplace FDE"
    sync && umount -f /var/userdata
    if [ $? -ne 0 ] ; then
        echo "not able to unmount userdata exiting hence"
        return 2
    fi
    echo "Unmounted userdata successfully going to start inplace fde from scratch"
    on $FDE_CTL_ON_ARGS $FDE_CTL_BINARY -p userdata inplace $BACKUP_FILE
    if [ $? -ne 0 ] ; then
        echo "inplace fde failed, needs to format the partition and continue"
        return 1
    else
        echo "inplace fde succeeded";
        return 0
    fi
}

continue_inplace_fde(){
    echo "Starting expecting that previous inplace FDE was interrupted by a power glitch";
    on $FDE_CTL_ON_ARGS $FDE_CTL_BINARY -p userdata inplace $BACKUP_FILE continue
    if [ $? -ne 0 ] ; then
        echo "continue inplace fde failed";
        return 1
    fi
    echo "continue inplace fde succeeded";
    return 0
}
fde_format_partition(){
    on $FDE_CTL_ON_ARGS $FDE_CTL_BINARY -p userdata basic
    if [ $? -ne 0 ] ; then
        echo "not able to set ICE in FDE exiting inplace FDE operation";
        return 2
    fi
    mkqnx6fs $DEV_PATH/userdata -q
    if [ $? -ne 0 ] ; then
        echo " failed to format userdata"
        return 2
    fi
    mount -t qnx6 $DEV_PATH/userdata /var/userdata
    if [ $? -ne 0 ] ; then
        echo " failed to mount userdata"
        return 2
    fi
    return 0
}
fde_setup () {
    on $FDE_CTL_ON_ARGS $FDE_CTL_BINARY $FDE_CTL_ARGS
    rc=$?

    case $rc in
        1)  #First run or user_pass has changed or 'ssd' got busted, seed userdata. 
            echo "$DEV_PATH/userdata's ICE key provisioned, seed the /var directory."
            seed_userdata;
            ;;
        0)  echo "Successfully set the FDE key for $DEV_PATH/userdata"
            ;;
        *)  echo "Failed to set input key for $DEV_PATH/userdata, rc=${rc}"
            return 1;
            ;;
    esac
}

seed_userdata() {
    echo "All data within /var would be lost"
    mkqnx6fs -i 49152 -b 32768 $DEV_PATH/userdata -q -T media
    if [ $? -ne 0 ] ; then
        echo " failed to format userdata"
        return 1
    fi

    mount -t qnx6 $DEV_PATH/userdata /var
    if [ $? -ne 0 ] ; then
        echo " failed to mount userdata"
        return 1
    fi

    echo "Seed initial directories in /var"
    for adir in /var/ssh         /var/chroot         /var/chroot/sshd         /var/data         /var/pps_persist         /var/run ;
    do
        echo "Creating ${adir}"
        mkdir -p -m 0700 ${adir}
    done
	
	if [ $SECPOL_ENABLE -eq 1 ]; then	
        #add permission for secure build
        #TODO: check why setfacl doesn't work here
        #setfacl -m user:qseecom_daemon:rw /var/data
        #setfacl -m group:qseecom_daemon:rw /var/data
        #setfacl -m other::rw /var/data
        chmod 0766 /var/data
        chown 40:40 /var/pps_persist
	fi

    #All done, sync it up and unmount it.
    sync && umount -f /var
    return 0
}

#TODO: Add a jpeg image to the source along with a readme for inplace FDE algorithm
mount_inplace(){
    DEV_PATH="/dev/disk";
    BACKUP_FILE="/persist/userdata.dat";
    mkdir -p "/var/userdata"
    fde_on
    if [ $? -eq 2 ] ; then
        echo "Complete failure of inplace fde after fde_on failed";
        return 1
    fi
    fde_on_mount
    if [ $? -eq 0 ] ; then
        echo "mount succeeded with FDE enabled";
        return 0
    fi
    fde_off_mount
    fo=$?
    #complete failure if disabling fde (fde_ctl -p userdata disable) fails
    if [ $fo -eq 2 ] ; then
        echo "Complete failure of inplace fde after fde disable";
        return 1
    #able to mount successfully after disabling fde
    elif [ $fo -eq 0 ] ; then
        echo "Starting inplace FDE from beginning partition is not encrypted at all";
        start_inplace_fde
        si=$?
        #unmounting userdata means a complete failure
        if [ $si -eq 2 ] ; then
            echo "Complete failure of inplace fde after inplace fde during first iteration";
            return 1
        #inplace FDE (fde_ctl -p userdata inplace /persist/userdata) failure case
        elif [ $si -eq 1 ] ; then
            echo "Inplace FDE for first time is failed, check for invalid backup file path, going to format the partition";
            fde_format_partition
            if [ $? -eq 2 ] ; then
                echo "Complete failure of inplace fde after fde_format_partition failed";
                return 1
            else
                echo "fde_format_partition succeeded";
                return 0
            fi
        #inplace FDE (fde_ctl -p userdata inplace /persist/userdata) success case
        else
            echo "Inplace FDE for first time is done successfully, now trying to mount";	
            fde_on
            if [ $? -eq 2 ] ; then
                echo "Complete failure of inplace fde as fde_on failed after inplace FDE";
                return 1
            fi
            fde_on_mount
            if [ $? -eq 0 ] ; then
                echo "mounted succefully after inplace FDE";
                return 0
            else
                echo "fde mount failed after inplace FDE, going to format the partition";
                fde_format_partition
                if [ $? -eq 2 ] ; then
                    echo "Complete failure of inplace fde after fde_format_partition failed";
                    return 1
                else
                    echo "fde_format_partition succeeded";
                    return 0
                fi
            fi
        fi
    #able to disable fde but mounting failure - means a partially encrypted partition. So continue inplace.
    else
        echo "Assuming a power glitch occured in previous boot going to continue_inplace_fde";
        continue_inplace_fde
        if [ $? -eq 0 ] ; then
            echo "continue_inplace_fde succeeded going to fde_on_mount";
            fde_on_mount
            if [ $? -eq 0 ] ; then
                echo "Continue Inplace FDE was already executed succefully";
                return 0
            else
                echo "Complete failure of inplace fde - fde_on_mount after continue_inplace failed";
                return 1
            fi
        else
            echo "continue inplace fde failed after inplace FDE";
            fde_format_partition
            if [ $? -eq 2 ] ; then
                echo "Complete failure of inplace fde after fde_format_partition failed in the end";
                return 1
            else
                echo "fde_format_partition succeeded";
                return 0
            fi
        fi
    fi
}

mount_userdata(){
    DEV_PATH="/dev/disk";
    #chmod to proide rw permission to uda0 LUN for processes under the user group devb-ufs-service
    #This is specifically done so that during FDE operation the application/service will be able to r/w userdata partition
    chmod 660 /dev/disk/uda0;

    if [ -z $ENABLE_FDE ];  then
        echo "FDE for userdata is disabled";
    elif [ $ENABLE_FDE -eq 0 ]; then
        echo "FDE for userdata is disabled explicitly";
    else 
        fde_setup
        if [ $? -ne 0 ] ; then
          return 1
        fi
    fi

    if [[ ! -e /persist/.var_formatted ]]; then
        echo "First run ever, seed the /var directory."
        seed_userdata;
        touch /persist/.var_formatted && sync;
    fi

    mount -t qnx6 $DEV_PATH/userdata /var
    if [ $? -ne 0 ] ; then
        echo "failed to mount userdata";

        echo "checking $DEV_PATH/userdata";
        chkqnx6fs -vvvv $DEV_PATH/userdata;

        echo "checking super-block 0 $DEV_PATH/userdata";
        chkqnx6fs -S 0 $DEV_PATH/userdata;

        echo "checking super-block 1 $DEV_PATH/userdata";
        chkqnx6fs -S 0 $DEV_PATH/userdata;

        return 1
    fi

    #Symlink /data 
    qln -sfP /var/data /data
}

format_ota_partition() {
    mkqnx6fs /dev/disk/ota -q -T media
    if [ $? -ne 0 ] ; then
        echo "failed to format ota "
        return 1
    fi
}

mount_ota() {
    mkdir -p /ota
    mount -t qnx6 /dev/disk/ota /ota
    if [ $? -ne 0 ] ; then
        echo "failed ot mount ota";
        echo "checking /dev/disk/ota";
        chkqnx6fs -vvv /dev/disk/ota

        echo "mount ota 2nd";
        mount -t qnx6 /dev/disk/ota /ota
        if [ $? -ne 0 ] ; then
            echo "mount ota failed 2, format ota parttion"
            format_ota_partition
            echo "mount ota 3rd"
            mount -t qnx6 /dev/disk/ota /ota
            if [ $? -ne 0 ] ; then
                echo "mount ota failed 3, give up"
                return 1
            fi
        fi
    fi

    chmod 0755 /ota
    mkdir -p /ota/android
    mkdir -p /ota/qnx
    chmod 0776 /ota/android
    chown -R root:1000 /ota/android
}

format_log_partition() {
    mkqnx6fs /dev/disk/log -q -T media
    if [ $? -ne 0 ] ; then
        echo "failed to format log partition"
        return 1
    fi
}

mount_log() {
    mkdir -p /log
    mount -t qnx6 /dev/disk/log /log
    if [ $? -ne 0 ] ; then
        echo "failed ot mount log";
        echo "checking /dev/disk/log";
        chkqnx6fs -vvv /dev/disk/log

        echo "mount log partition 2nd";
        mount -t qnx6 /dev/disk/log /log
        if [ $? -ne 0 ] ; then
            echo "mount  failed 2, format log parttion"
            format_log_partition
            echo "mount log partition 3rd"
            mount -t qnx6 /dev/disk/log /log
            if [ $? -ne 0 ] ; then
                echo "mount log partition failed 3, give up"
                return 1
            fi
        fi
    fi
    chmod 0755 /log
    mkdir -p /log/qlog
    chmod 0776 /log/qlog
    chown -R root:1000 /log/qlog
    qln -sfP /log/qlog /var/log
}

create_syslog () {
    if [ -f /var/log/syslog ]; then
        rm -rf /var/log/syslog
    fi
    touch /var/log/syslog
}

common_early () {
#Add this here , so that we can easily enable slog on boot whe needed
#rm -f /var/third_lastrun.txt
#mv -f /var/slog_second_lastrun.txt /var/slog_third_lastrun.txt
#mv -f /var/slog_lastrun.txt /var/slog_second_lastrun.txt
#mv -f /var/slog_currentrun.txt /var/slog_lastrun.txt
#on -d slog2info -t -w > /var/slog_currentrun.txt

    #on -ae random -t
    on -ae $RANDOM_ON_ARGS $RANDOM_BINARY -t

}

common_late () {
    # Tuning for network throughput performance
    # IPv4
    sysctl -w net.inet.udp.sendspace=92160 net.inet.udp.recvspace=166400
    sysctl -w net.inet.tcp.sendspace=90112 net.inet.tcp.recvspace=1000000
    # IPv6
    sysctl -w net.inet6.udp6.sendspace=92160 net.inet6.udp6.recvspace=166400
    sysctl -w net.inet6.tcp6.sendspace=90112 net.inet6.tcp6.recvspace=1000000
    sysctl -w kern.sbmax=8388608 kern.mbuf.nmbclusters=81920

    #enable if requested gdb
    if [[ -e /var/enable_gdb ]]; then
        pdebug 8888
        echo "Process level ( pdebug ) enabled"
        echo "Run 'qnx attach <ip_addr>:8888' to connect remotely via gdb'"
    else 
        echo "pdebug/gdbserver not enabled by default . touch /var/enable_gdb and reset device to enable gdb debugging"
    fi

    ##  start Analyzer; user responsible for creating/deleting flag
    if [ -e /etc/enable_analyzer ]
    then
        #echo "Info startup.sh: Analyzer enabled by default (/etc/enable_analyzer)"
        # Start Analyzer
        /scripts/analyzer.sh start
    else 
        echo "Analyzer not enabled. touch /etc/enable_analyzer and reset device to enable Analyzer debugging"
        ##  start Analyzer External; user responsible for creating/deleting flag
        if [ -e /etc/enable_analyzer_external ]
        then
            echo "Info startup.sh: Analyzer External enabled by default (/etc/enable_analyzer_external)"
            # Start Analyzer
            /scripts/analyzer.sh start tpm
        else 
            echo "Analyzer External not enabled. touch /etc/enable_analyzer_external and reset device to enable Analyzer External debugging"
        fi
    fi
}

common_onetime () {
    #Enable SSH 
    if [[ ! -e /var/ssh/ssh_host_dsa_key ]] then
        echo "Generate dsa key for ssh only on first boot"
        ssh-keygen -t dsa -b 1024 -f /var/ssh/ssh_host_dsa_key -N ''
        echo "Generate rsa key for ssh only on first boot"
        ssh-keygen -t rsa -b 1024 -f /var/ssh/ssh_host_rsa_key -N ''
    fi
}

common_netdbgservices () {
    
    on -ae $SYSLOGD_ON_ARGS $SYSLOGD_BINARY $SYSLOGD_ARGS

    on -ae $INETD_ON_ARGS $INETD_BINARY $INETD_ARGS

    on -ae $QCONN_ON_ARGS $QCONN_BINARY $QCONN_ARGS
}

common_pps () {
    log_launch "pps"
    #TODO pps progmgr_ability fail, need fix
    if [[ -e /etc/pps_acl.conf ]] then
        if [ $SECPOL_ENABLE -eq 1 ]; then
            on -T pps_t -d /bin/pps -A /etc/pps_acl.conf -m /var/pps -p /var/pps_persist -t 100 -U 40:40
        else
            pps -A /etc/pps_acl.conf -m /var/pps -p /var/pps_persist -t 100
        fi
    else
        if [ $SECPOL_ENABLE -eq 1 ]; then
            on -T pps_t -d /bin/pps -m /var/pps -p /var/pps_persist -t 100 -U 40:40
        else
        pps -m /var/pps -p /var/pps_persist -t 100
        fi
    fi
}

common_hid () {
    log_launch "io-hid"
    io-hid -dusb
}

common_create_if() {
# $1 == interface name

    on $IFCONFIG_ON_ARGS $IFCONFIG_BINARY $1 create
    on $IFUP_ON_ARGS $IFUP_BINARY -p $1 
    on $IFCONFIG_ON_ARGS $IFCONFIG_BINARY $1 up
}

common_add_to_bridge () {
# $1 == bridge name
# $2 == interface name
    brconfig $1 add $2 up
}

common_create_peer_if () {
# $1 == 'system' name from qvm config file
# $2 == host side pathspace's basename.
# $3 == interface name
# $4 == mac address
# $5 == interface name
    if [[ -z $5 ]]; then
	INTERFACE=vp
    else
	INTERFACE=$5
    fi
    mount -T io-pkt -o peer=/dev/qvm/$1/$2,bind=/dev/vdevpeers/$3,mac=$4,name=$INTERFACE /lib/dll/devnp-vdevpeer-net.so
    on $IFUP_ON_ARGS $IFUP_BINARY -p $3
    on $IFCONFIG_ON_ARGS $IFCONFIG_BINARY $3 up
}

launch_ssr_service() {
	waitfor /var/pps
    	#on $SSR_SERVICE_ON_ARGS $SSR_SERVICE_BINARY $SSR_SERVICE_ARGS
	ssr_service -p /var/pps/ssr -s lpass -s modem -s cdsp -t 30 -r 1 &
}


launch_heartbeat() {
	if [[ -e /var/heartbeat ]] then
		echo "Launching Heartbeat ...."
		heartbeat -f -m sys=50.0,start=40.0 -c sys=50.0 &
	fi
}


get_mac_from_syspage() {
# $1 == os indicator, generate different mac addr for different guest
# $2 == interface number
    MAC1=`pidin syspage | sed -n -e "/(nicaddr)/ {n;p;n;n;n;n}" | sed -n -e "s/^.\{17\}//p" | sed -n -e "s/.\{12\}$//p" | sed -n -e "s/ /:/gp"`
    MAC2=`pidin syspage | sed -n -e "/(nicaddr)/ {n;n;n;p;n;n}" | sed -n -e "s/^.\{17\}//p" | sed -n -e "s/.\{12\}$//p" | sed -n -e "s/ /:/gp"`
    MAC3=`pidin syspage | sed -n -e "/(nicaddr)/ {n;n;n;n;n;p}" | sed -n -e "s/^.\{17\}//p" | sed -n -e "s/.\{12\}$//p" | sed -n -e "s/ /:/gp"`
    case $1 in
        vm1)
            MACALL=$MAC2:$MAC1:$MAC3
        ;;
        vm2)
            MACALL=$MAC3:$MAC2:$MAC1
        ;;
        vm3)
            MACALL=$MAC3:$MAC1:$MAC2
        ;;
        *)
            MACALL=$MAC1:$MAC2:$MAC3
        ;;
    esac
    case $2 in
        1)
            MAC=`echo $MACALL | sed -n -e "s/^.\{3\}//gp" | sed -n -e "s/.\{18\}$//gp"`
        ;;
        2)
            MAC=`echo $MACALL | sed -n -e "s/^.\{6\}//gp" | sed -n -e "s/.\{15\}$//gp"`
        ;;
        3)
            MAC=`echo $MACALL | sed -n -e "s/^.\{9\}//gp" | sed -n -e "s/.\{12\}$//gp"`
        ;;
        4)
            MAC=`echo $MACALL | sed -n -e "s/^.\{12\}//gp" | sed -n -e "s/.\{9\}$//gp"`
        ;;
        5)
            MAC=`echo $MACALL | sed -n -e "s/^.\{15\}//gp" | sed -n -e "s/.\{6\}$//gp"`
        ;;
        6)
            MAC=`echo $MACALL | sed -n -e "s/^.\{18\}//gp" | sed -n -e "s/.\{3\}$//gp"`
        ;;
    esac
    MAC=02:$MAC
    echo $MAC
}

dhcp_client_set()
{
# $1 == cookie file to trigger DHCP e.g. /var/dhcp_ntn
# $2 == interface name
    if [ -e /var/$1 ]; then
        export PATH_DHCLIENT_DB=/var/dhclient.leases
        export PATH_DHCLIENT_SCRIPT=/sbin/dhclient-script
        export PATH_DHCLIENT_CONF=/etc/dhclient.conf
        echo "($2): $1 was found -> System is configured to use DHCP"
        if [ $SECPOL_ENABLE -eq 1 ];then
            on -T dhclient_t -u 150:150,0 dhclient -m $2
        else
            dhclient -m $2 
        fi
    fi

}
qseecom () {

        log_launch "qseecom_service"
        on $QSEECOM_SERVICE_ON_ARGS $ASLR_FLAG $QSEECOM_SERVICE_BINARY $QSEECOM_SERVICE_ARGS &
        #modify rpmb device permissions
        if [[ "$uname_m" == *UFS* ]]; then   
        chmod 666 /dev/disk/uda7
        else 
        chmod 666 /dev/disk/rpmb0
        fi
        #modify ssd device permissions
        SSD_DEVICE=`ls -l /dev/disk | grep "ssd" | cut -d'>' -f2`
        chmod 666 $SSD_DEVICE
        log_launch "qseecom_daemon"
        on $QSEECOM_DAEMON_ON_ARGS $ASLR_FLAG $QSEECOM_DAEMON_BINARY $QSEECOM_DAEMON_ARGS
        if [ $SECPOL_ENABLE -eq 1 ]; then
           setfacl -m user:98:w /persist
           setfacl -m group:98:w /persist
        fi
}

io-audio-deva () {
    DEVA_ARGS="skip_device_disable=0,bmetrics_level=medium,log_level=high,platform_id=demo,mib_cgms=0"
    waitfor /dev/audio_service
    log_launch "io-audio"
    on $IOAUDIO_ON_ARGS $IOAUDIO_BINARY -d qc ${DEVA_ARGS}
}

thermal () {
    #FIXME  Move enable_dplmp to QCORE once thermal is verified
#    log_launch "enable_dplmp"
#    echo 'dlexec "" "enable_dplmp" "0" GLOBALSYMS ' > /dev/qcore
    waitfor /dev/dplmp

    log_launch "io-service"
    on $IOSERVICE_ON_ARGS $IOSERVICE_BINARY $IOSERVICE_ARGS

}

modem() {
    log_launch "mis"
    if [ $SECPOL_ENABLE -eq 1 ]; then
        # TODO Remove this line once block devices create with proper permission
        chmod 666 /dev/disk/uda*
        on -T mis_t -u 87:87,21,19,22 -d mis --log_level=5 --config=/etc/modem_cfg
    else
        mis --log_level=5 --config=/etc/modem_cfg &
    fi
}

sdcard () {
    log_launch "devb-sdcard" 
    if [ $SECPOL_ENABLE -eq 1 ]; then
        SD_LAUNCH="on -T devb_emmc_t -u 22:22,21 -d"
    else
        SD_LAUNCH=""
    fi
    if [[ "$uname_m" == *Mojave-v1* ]]; then
        ${SD_LAUNCH} /bin/devb-sdmmc-msm8996 blk cache=10M,noatime,ra=128k:128k,automount=@/etc/sdcard.mnt.rules disk name=sda cam quiet,cache,pnp sdmmc verbose=0,bs=dname=compat sdio idx=1,bs=cd=95
    else
        ${SD_LAUNCH} /bin/devb-sdmmc-msm8996 blk cache=10M,noatime,ra=128k:128k,automount=@/etc/sdcard.mnt.rules disk name=sda cam quiet,cache,pnp sdmmc verbose=0,bs=dname=compat sdio idx=1,bs=cd=38
    fi
}

bt-ser() {
    #uart instance for BT
    devc-sermsm8x60 -u5 -S -E -f -b115200 0x07570000
}

powerman () {
    echo 'dlexec "" "idleHookCb_register" "0" GLOBALSYMS ' > /dev/qcore
}

usb-devcfg() {
    echo 'dlexec "devcfg_usb.so" "usb_devcfg_init" "" GLOBALSYMS ' > /dev/qcore
}

camera_server () {
    log_launch "camera_server"
    if [ $SECPOL_ENABLE -eq 1 ];then
	on -T ais_server_t -u 62:62,29,21,AVIN_SERVER_GID -d ais_server &
    else
       ais_server  &
    fi
}

km_be_loader () {
	waitfor /dev/qseecom
	log_launch "km_be"
	on $KM_BE_DAEMON_ON_ARGS $ASLR_FLAG $KM_BE_DAEMON_BINARY $KM_BE_DAEMON_ARGS        
}
# $1 - DIAG BE Preferred Client IP address

qcdiaglsm () {
#    log_launch "qcdiaglsm"    
    
    if [ -e /etc/enable_virt_diag ]
    then
        
        DIAG_LSM_SERVERSOCKET_BINARY="diag_lsm_serversocket"
        if [ $SECPOL_ENABLE -eq 1 ]; then
            DIAG_LSM_SERVERSOCKET_ON_ARGS="-T diag_lsm_serversocket_t -u 710:710 -d"
        else
            DIAG_LSM_SERVERSOCKET_ON_ARGS=""
        fi
    
        if [ -z "$1" ]; then
            DIAG_LSM_SERVERSOCKET_ARGS="-i 192.168.0.2" 
        else
            DIAG_LSM_SERVERSOCKET_ARGS="-i $1"
        fi
        
#        log_launch "diag_lsm_serversocket"
        on -ae $DIAG_LSM_SERVERSOCKET_ON_ARGS $DIAG_LSM_SERVERSOCKET_BINARY $DIAG_LSM_SERVERSOCKET_ARGS&
        
    else 
        echo "DIAG Services not enabled. touch /etc/enable_virt_diag and reset device to enable DIAG LSM server sccket"
    fi
}

start_mcurpc()
{
    #####start SPI RPC#####
    log_launch "spirpc"
    # wait for the SPI device file created by spi_service
    waitfor /dev/spi9
    on -p 40 /usr/bin/spirpc -s 143 -m 148 -p 9 &
}

setup_qt_env() {
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/qt/lib
    export QT_PLUGIN_PATH=/opt/qt/plugins
    export QML2_IMPORT_PATH=/opt/qt/qml
    export FONTCONFIG_FILE=/opt/qt/lib/fontconfig/local.conf
    export QQNX_PHYSICAL_SCREEN_SIZE=1920,720

    export QT_DEBUG_PLUGINS=1
    export QT_LOGGIN_TO_CONSOLE=1

    random -p
    waitfor /dev/random
}
start_factoryservice() 
{
    log_launch "factoryservice"
    factoryservice &
}

start_input_service()
{
    log_launch "input_service"
    waitfor /dev/uartrpc5
    /bin/input_service -p ivi_compositor
}

start_record_service()
{
    log_launch "record_service"
    /bin/record_service
}

start_mcu_hb()
{
    log_launch "mcu_hb"
    mcu_hb 500 &
}
start_mcu_systime()
{
    log_launch "mcu_systime"
    mcu_systime 600 &
}
start_nfsd()
{
    log_launch "nfsd"
    rpcbind
    nfsd -t &
}

start_message_service()
{
    log_launch "message center"
    message_center &
}

start_backlightsrv()
{
    log_launch "backlightsrv"
    backlight_resmgr &
}

start_chime_service()
{
    log_launch "chime service"
    chime_service -d 106
}

start_iceoryx()
{
    log_launch "iceoryx iox-roudi"
    if [ ! -d /var/lock ]; then
        mkdir -m 0644 -p /var/lock;
    fi
    iox-roudi -m off -c /etc/iceoryx/roudi_config.toml &
}

setup_diag_service_pps()
{
    log_launch  "setup diag_service_pps"
    touch  /var/pps/diag_service_pps
}
start_thermalctrl()
{
    log_launch "thermal_ctrl"
    thermal_ctrl &
}



#USB2_ENABLE=1
# Not assign ip address to ax0
export ASIX_IPADDR=
start_dhcp()
{
    if [ $SECPOL_ENABLE -eq 1 ];then
        on -T if_up_t -u 51:51 if_up -p -r 100  -m 100 $2 
        dhcp_client_set $1 $2
        on -T pfctl_t -u 152:152,0 pfctl -ef /etc/pf.conf
    else
        if_up -p -r 100  -m 100 $2
        dhcp_client_set $1 $2
        pfctl -ef /etc/pf.conf
    fi
    sysctl -w net.inet.ip.forwarding=1
}

waitfor_if()
{
    log_launch netconfig:if_up-$1 
    if [ $SECPOL_ENABLE -eq 1 ];then
        on -T if_up_t -u 51:51 if_up -p -r 100 -m 20 $1
    else
        if_up -p -r 100 -m 20 $1
    fi
    if [ $? -ne 0 ]; then
        echo "$1 not available, exiting";
        exit 1;
    fi
    log_ready netconfig:if_up-$1
}

uname_m=`uname -m`
. /scripts/platform_variables.sh

common_early;

mount -T io-pkt -o peer=/dev/qvm/la/la_to_host,bind=/dev/vdevpeer/vp0,mac=aaaaaaaaaaaa /lib/dll/devnp-vdevpeer-net.so



    $ON $DEFAULT_ROOT_T dt_patch -i /vm/images/sa8155-vm-la.dtb -o /tmp/la.dtb -p label=pmem_shared_mem,replace=gvm_pmem




qseecom;

km_be_loader;

chmod 660 /dev/disk/uda0;
waitfor /dev/km_be_avb_server
$ON $QVB_SERVICE_ON_ARGS $QVB_SERVICE_BINARY $QVB_SERVICE_ARGS
if [ $SECPOL_ENABLE -eq 1 ]; then
    setfacl -m user:146:w /persist
    setfacl -m group:146:w /persist
fi

# mounting io-pck after VMM Service lauch is casuing vdev issues
mount -T io-pkt /lib64/libdevnp-emac-eth.so

echo "start MCU RPC daemon"
start_mcurpc

# init usb hub chip power
usb_hub_power

#mount_userdata may use QSEECom service functionality
if [ $ENABLE_INPLACE_FDE -eq 1 ]; then
    mount_inplace
else
    mount_userdata
fi

# mount log partition
mount_log

# mount ota partition
mount_ota

echo "start iceoryx"
start_iceoryx

echo "start message service"
start_message_service

log_launch "GVM(s)"
    $ON $VMM_SERVICE_ON_ARGS $VMM_SERVICE_BINARY $VMM_SERVICE_ARGS
    $ON $VMM_LIFECYCLE_ON_ARGS $VMM_LIFECYCLE_BINARY &


create_syslog

$ON $DEFAULT_ROOT_T qnetconfig -b 2 -c /etc/early-net.cfg &

common_netdbgservices;

MTOUCH_720P_TPK_CONF=/etc/system/config/mtouch_lilliput_720p_TPK.conf
CALIB_CONF_720P_TPK_CONF=/etc/system/config/calib_lilliput_tpk.720p
MTOUCH_720P_EGALAX_CONF=/etc/system/config/mtouch_lilliput_720p_eGalax.conf
CALIB_CONF_720P_EGALAX_CONF=/etc/system/config/calib_lilliput_egalax.720p
MTOUCH_720P_SiS_CONF=/etc/system/config/mtouch_lilliput_1080p_SiS.conf
CALIB_CONF_720P_SiS_CONF=/etc/system/config/calib_lilliput_sis.1080p
chmod a+w /etc/system/config

log_launch "pps"
$ON $PPS_ON_ARGS pps -m /var/pps -p /var/pps_persist -t 100
waitfor /var/pps
if [ $SECPOL_ENABLE -eq 1 ];then
    chown 40:40 /var/pps
fi
usb;
common_onetime;


if [ $SECPOL_ENABLE -eq 1 ];then
    on -T ifconfig_t -u 50:50 ifconfig vp0 up
    on -T ifconfig_t -u 50:50 ifconfig bridge0 create
    brconfig bridge0 add vp0 up
else
    ifconfig vp0 up
    ifconfig bridge0 create
    brconfig bridge0 add vp0 up
fi


$ON $SSR_SERVICE_ON_ARGS  ssr_service -p /var/pps/ssr -s lpass -s modem -s cdsp -r 1 -t 300 &
waitfor /dev/ssr
waitfor /dev/pil_service

$ON $CDSP_SERVICE_ON_ARGS  cdsp_service -f /etc/cdsp_cfg &
waitfor /dev/cdsp_service

$ON $IO_HID_ON_ARGS  io-hid -dusb &
waitfor /dev/io-hid/io-hid
chmod 660 /dev/io-hid/io-hid

$ON $DEFAULT_ROOT_T  life_cycle_man_demo &

waitfor /dev/screen


echo test:persistent /pmic/client/wlan 2 > /dev/npa
echo test:persistent /pmic/client/pcie 2 > /dev/npa
echo test:persistent /pmic/client/sensor 2 > /dev/npa

$ON $PRNG_SERVICE_ON_ARGS  $PRNG_SERVICE_BINARY $PRNG_SERVICE_ARGS &
$ON $FDE_BE_ON_ARGS  $FDE_BE_BINARY $FDE_BE_ARGS

if [ $SECPOL_ENABLE -eq 1 ];then
    $ON -T ais_be_server_t -d ais_be_server -U 63:63  &
else
     $ON $DEFAULT_ROOT_T  ais_be_server &
fi

waitfor /dev/audio_service
$ON $IOAUDIO_ON_ARGS io-audio -o sw_mixer_ms=16 -d qc skip_device_disable=0,bmetrics_level=medium,log_level=high,platform_id=demo,mib_cgms=0

        
$ON $NPU_SERVICE_ON_ARGS $NPU_SERVICE_BINARY $NPU_SERVICE_ARGS
waitfor /dev/msm_npu

$ON $IOSERVICE_ON_ARGS  io_service --log_level=7 &
if [ $SECPOL_ENABLE -eq 1 ];then
    on -T ifconfig_t -u 50:50 ifconfig emac0 up
else
    ifconfig emac0 up
fi

if [[ -e /var/stream_test ]]; then
    # enable NAT for emac0
    # all GVMs are assigned as static ip 
    waitfor_if vp0
    if [ $SECPOL_ENABLE -eq 1 ];then
        ifconfig emac0 delete
        on -T ifconfig_t -u 50:50 ifconfig vp0 192.168.1.10 up
        start_dhcp stream_test emac0 &
    else
       ifconfig emac0 delete
       ifconfig vp0 192.168.1.10 up
       start_dhcp stream_test emac0 &
    fi

elif [[ -e /var/dhcp_ntn ]]; then
    # enable NAT for emac0
    # all GVMs are assigned as public ip
    brconfig bridge0 add emac0 up
    start_dhcp dhcp_ntn emac0 & 
else
    if [ $SECPOL_ENABLE -eq 1 ];then
        brconfig bridge0 add emac0 up
        on -T ifconfig_t -u 50:50 ifconfig emac0 192.168.1.1 up
        on -T route_t -u 151:151 route add default 192.168.1.3
    else
        brconfig bridge0 add emac0 up
        ifconfig emac0 192.168.1.1 up
        route add default 192.168.1.3
    fi
fi


route add -net 224.1.1.1 192.168.1.1


$ON $VM_SSR_BE_ON_ARGS  vm_ssr_be &
$ON $DCVS_ON_ARGS dcvs_service -d 30 &

sysctl -qw net.inet6.ip6.ifq.maxlen=1024
sysctl -qw net.inet.ip.ifq.maxlen=1024
sysctl -w net.inet.ip.forwarding=1

##  start Analyzer; user responsible for creating/deleting flag
if [ -e /etc/enable_analyzer ]
then
    #echo "Info startup.sh: Analyzer enabled by default (/etc/enable_analyzer)"
    #Start Analyzer
    /scripts/analyzer.sh start
else 
    echo "Analyzer not enabled. touch /etc/enable_analyzer and reset device to enable Analyzer debugging"
    ##  start Analyzer External; user responsible for creating/deleting flag
    if [ -e /etc/enable_analyzer_external ]
    then
        #echo "Info startup.sh: Analyzer External enabled by default (/etc/enable_analyzer_external)"
        #Start Analyzer
        /scripts/analyzer.sh start tpm
    else 
        echo "Analyzer External not enabled. touch /etc/enable_analyzer_external and reset device to enable Analyzer External debugging"
    fi
fi

echo startup:persistent /pmic/client/usb_hs 2 > /dev/npa

echo "start dlt-log daemon"
/usr/bin/dlt_daemon -d
echo "start dlt-qnx-system daemon"
/usr/bin/dlt_qnx -d

[ ! -d "/var/log/dltlogs" ] && mkdir -m 755 -p "/var/log/dltlogs"
echo "start dlt-receive daemon"
/usr/bin/dlt_receive -d

echo "start chime service"
start_chime_service

echo "setup_qt_env"
setup_qt_env

sleep 3
/bin/slm -V /slm/service_apps.xml

echo "Start Ais Vision Service..."
sleep 2
/bin/slm -V /slm/vision_service.xml


LSM_IPADDR=`cat /etc/hosts | grep 'cdc-android' | awk -F ' ' '{printf $1}'`
qcdiaglsm ${LSM_IPADDR};
echo "qcdiaglsm ip " ${LSM_IPADDR}

slay -R 0xFF qcpe_qhee

echo "Startup complete"

echo "start factoryservice daemon"
start_factoryservice

echo "start input service"
start_input_service

# echo "start record service"
# start_record_service

echo "start nfsd"
start_nfsd

echo "start backlightsrvr"
start_backlightsrv

echo "setup diag_service_pps"
setup_diag_service_pps

echo "start MCU heartbeat service"
start_mcu_hb

echo "start MCU systime service"
start_mcu_systime

echo "start thermal_ctrl"
start_thermalctrl

echo "Startup complete"
