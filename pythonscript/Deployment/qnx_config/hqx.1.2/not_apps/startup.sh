#! /bin/sh

runusb() {

ARGS_TYPED_MEM="memory=/memory/ram/dma"
    case $1 in 
        PRIM)
            ARGS="ioport=0xa600000,irq=165,nousb3,soc=8155"
            STACK_NO="1"
            LUA_PATH="/etc/usblauncher/usb${STACK_NO}.lua"
            DEV_OTG_PATH="/dev/usb${STACK_NO}/io-usb-otg"
            ;;

        SEC)
            ARGS="ioport=0xa800000,irq=170,soc=8155,$ARGS_TYPED_MEM"
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

    on $IO_USB_ON_ARGS $IO_USB_BINARY -t $ARGS_TYPED_MEM -dqcom-xhci $ARGS, -n $DEV_OTG_PATH

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
    mkdir -p /ota/qnx/host
    mkdir -p /ota/qnx/ecu
    chown -R 813:813 /ota/qnx
    chown -R 1000:1000 /ota/android
    chmod 0766 /ota/android
    touch /ota/android/.ota.nfs
    chmod 0644 /ota/android/.ota.nfs
}

format_log_partition() {
    mkqnx6fs /dev/disk/qnx_log -q -T media
    if [ $? -ne 0 ] ; then
        echo "failed to format log partition"
        return 1
    fi
}

mount_log() {
    mkdir -p /log
    mount -t qnx6 /dev/disk/qnx_log /log
    if [ $? -ne 0 ] ; then
        echo "failed ot mount log";
        echo "checking /dev/disk/log";
        chkqnx6fs -vvv /dev/disk/qnx_log

        echo "mount log partition 2nd";
        mount -t qnx6 /dev/disk/qnx_log /log
        if [ $? -ne 0 ] ; then
            echo "mount  failed 2, format log parttion"
            format_log_partition
            echo "mount log partition 3rd"
            mount -t qnx6 /dev/disk/qnx_log /log
            if [ $? -ne 0 ] ; then
                echo "mount log partition failed 3, give up"
                return 1
            fi
        fi
    fi

    chmod 0755 /log
    mkdir -p /log/qlog
    chmod 0777 /log/qlog
    touch /log/qlog/.qlog.nfs
    chmod 0644 /log/qlog/.qlog.nfs
    #Symlink /var/log
    qln -sfP /log/qlog /var/log
}

format_factory_partition() {
    mkqnx6fs /dev/disk/factory -q -T media
    if [ $? -ne 0 ] ; then
        echo "failed to format factory partition"
        return 1
    fi
}

mount_factory() {
    mkdir -p /factory
    mount -t qnx6 /dev/disk/factory /factory
    if [ $? -ne 0 ] ; then
        echo "failed ot mount factory";
        echo "checking /dev/disk/factory";
        chkqnx6fs -vvv /dev/disk/factory

        echo "mount factory partition 2nd";
        mount -t qnx6 /dev/disk/factory /factory
        if [ $? -ne 0 ] ; then
            echo "mount  failed 2, format factory parttion"
            format_factory_partition
            echo "mount factory partition 3rd"
            mount -t qnx6 /dev/disk/factory /factory
            if [ $? -ne 0 ] ; then
                echo "mount factory partition failed 3, give up"
                return 1
            fi
        fi
    fi

   chmod 0755 /factory
}

format_calibration_partition() {
    mkqnx6fs /dev/disk/calibration -q -T media
    if [ $? -ne 0 ] ; then
        echo "failed to format calibration partition"
        return 1
    fi
}

mount_calibration() {
    mkdir -p /cal
    mount -t qnx6 /dev/disk/calibration /cal
    if [ $? -ne 0 ] ; then
        echo "failed ot mount calibration";
        echo "checking /dev/disk/calibration";
        chkqnx6fs -vvv /dev/disk/calibration

        echo "mount calibration partition 2nd";
        mount -t qnx6 /dev/disk/calibration /cal
        if [ $? -ne 0 ] ; then
            echo "mount  failed 2, format calibration parttion"
            format_calibration_partition
            echo "mount calibration partition 3rd"
            mount -t qnx6 /dev/disk/calibration /cal
            if [ $? -ne 0 ] ; then
                echo "mount calibration partition failed 3, give up"
                return 1
            fi
        fi
    fi

   chmod 0755 /cal
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
    
}

common_netdbgservices () {
    
    on -ae $SYSLOGD_ON_ARGS $SYSLOGD_BINARY $SYSLOGD_ARGS

    on -ae $INETD_ON_ARGS $INETD_BINARY $INETD_ARGS

#    on -ae $QCONN_ON_ARGS $QCONN_BINARY $QCONN_ARGS
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

apply_ddr_freq_limits()
{
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

spu_services() {
    log_launch "spcom_service"
    on $SPCOM_SERVICE_ON_ARGS $ASLR_FLAG $SPCOM_SERVICE_BINARY $SPCOM_SERVICE_ARGS &
    waitfor /dev/sp_kernel
    if [ $SECPOL_ENABLE -eq 1 ]; then
       setfacl -m user:143:rw /persist
       setfacl -m group:143:rw /persist
       setfacl -m user:143:rw /persist/secnvm
       setfacl -m group:143:rw /persist/secnvm
    fi
    log_launch "sec_nvm"
    on $SEC_NVM_ON_ARGS $ASLR_FLAG $SEC_NVM_BINARY $SEC_NVM_ARGS &
    log_launch "spdaemon"
    on $SPDAEMON_ON_ARGS $ASLR_FLAG $SPDAEMON_BINARY $SPDAEMON_ARGS &    
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

start_megapm()
{
    #####start mega pm#####
    log_launch "megapm"

    on -T megapm_t -u megapm megapm &
}

start_pm_event_postprocess()
{
    log_launch "start_pm_event_postprocess"

    on -T pm_event_postprocess_t -u pm_event_postprocess -p 40 pm_event_postprocess &
}

start_pm_event_preprocess()
{
    log_launch "start_pm_event_preprocess"

    on -T pm_event_preprocess_t -u pm_event_preprocess -p 40 pm_event_preprocess &
}

start_input_service()
{
    log_launch "input_service"
    waitfor /dev/uartrpc5
    on -T input_service_t -u 815:815,68,819 /bin/input_service -p ivi_compositor
}

start_record_service()
{
    log_launch "record_service"
    on -T record_service_t -u 816:816,819 /bin/record_service
}

start_nfsd()
{
    log_launch "nfsd"
    on -T nfs_t rpcbind
    # /bin/slm -V /slm/nfsd.xml
}

start_message_service()
{
    log_launch "message center"
    # /bin/slm -V /slm/msg_center.xml
}

start_vmm_monitor()
{
    log_launch "vmm_monitor start"
    # /bin/slm -V /slm/vmm_monitor.xml
}

start_backlightsrv()
{
    log_launch "backlightsrv"
    on -T disp_bl_t -u disp_bl backlight_resmgr&
}

start_tempsrv()
{
    log_launch "tempsrv"
    temp_resmgr &
}

setup_diag_service_pps()
{
    log_launch  "setup diag_service_pps"
    touch  /var/pps/diag_service_pps
}

create_syslog () {
    if [ -f /var/log/syslog ]; then
        rm -rf /var/log/syslog
    fi
    touch -m 0666 /var/log/syslog
}

create_icapps_version () {
    if [ ! -f /etc/icapps_version ]; then
        touch -m 0666 /etc/icapps_version
    fi
}

start_iceoryx()
{
    log_launch "iceoryx iox-roudi"
    if [ ! -d /var/lock ]; then
        mkdir -m 0666 -p /var/lock;
    else
        chmod 0666 /var/lock
        rm /var/lock/*.lock
    fi
    on -T iceoryx_t -u iceoryx -p 63 iox-roudi -m off -c /etc/iceoryx/roudi_config.toml 2>/dev/console &
}

start_host_ota()
{
    log_launch "host_otaService"
    # /bin/slm -V /slm/host_update.xml
}

start_chk_luns_consistent()
{
    log_launch "check system slot luns consistent"
    on -T chkslot_t -u chkslot chkslot &
}

start_factoryservice()
{
    log_launch "factoryservice"
    on -T factory_service_t -u factory /bin/factoryservice &
}

start_ecu_ota()
{
    log_launch "ecu_otaService"
    # /bin/slm -V /slm/ecu_update.xml
}

export_slot_info()
{
    log_launch "export current system start slot info to /tmp/slotinfo.txt"
    slotinfo.sh
}

start_health_monitor()
{
    log_launch "health_monitor"
    on -T health_monitor_t -u health_monitor health_monitor -i 60 &
}

start_chime_service()
{
    log_launch "chime_service"
    on -T chime_service_t -u chime /bin/chime_service
}

start_ecu_config_utility()
{
    log_launch "ecu_config_utility"
    on -T ecu_config_utility_t -u 805:805,819 /bin/ecu_config_utility -g
}

start_mcurpc()
{
    #####start SPI RPC#####
    log_launch "spirpc"

    # wait for the SPI device file created by spi_service
    waitfor /dev/spi9
    on -T spirpc_t -p 40 -R 0x04 -u spirpc /usr/bin/spirpc -s 143 -m 148 -p 9 &

    # wait for the UART RPC device file created by uartrpc
    waitfor /dev/uartrpc0
    waitfor /dev/uartrpc1
    waitfor /dev/uartrpc2
    waitfor /dev/uartrpc3
    waitfor /dev/uartrpc4
    waitfor /dev/uartrpc5
    waitfor /dev/uartrpc6
    waitfor /dev/uartrpc7
    # /bin/slm -V /slm/uartrpc_service.xml
}


start_misc_service()
{
    #####start misc_service#####
    log_launch "misc_service"
    on -T misc_service_t -u misc_service misc_service &

}

config_sysctl_network()
{
    # Tuning for network throughput performance
#    sysctl -f /etc/sysctl.conf > /dev/null 2>&1
}

start_dumper()
{
    export COREFILES_DIR=/var/log
    DUMPER_ARGS="-v -d /var/log -N 10 -S -z 9"

    if [ -e $COREFILES_DIR ];then

        for acore in /tmp/*.core*; do
            if [ -f $acore ]; then
                echo "Copying ${acore} to ${COREFILES_DIR}/early_boot_${acore##*/}"
                # If file is already present then skip overwriting it.
                cp -VX ${acore} ${COREFILES_DIR}/early_boot_${acore##*/}
            fi;
        done

        slay -f -v dumper
        if [ $SECPOL_ENABLE -eq 1 ];then
            on -T dumper_t dumper -U dumper ${DUMPER_ARGS}
        else
            dumper ${DUMPER_ARGS}
        fi
    fi
}

config_slog2_verbosity()
{
    waitfor /var/pps/verbose
    echo qseecom_service:n:4 >> /var/pps/verbose
    echo qcpe_service:n:4 >> /var/pps/verbose
    echo qcpe_qhee:n:1 >> /var/pps/verbose
}

rename_slog_files()
{
    base_name=$1

    if [ -e /persist/slog/$base_name.4.log ]; then
        mv -f /persist/slog/$base_name.4.log /persist/slog/$base_name.5.log;
    fi

    if [ -e /persist/slog/$base_name.3.log ]; then
        mv -f /persist/slog/$base_name.3.log /persist/slog/$base_name.4.log;
    fi

    if [ -e /persist/slog/$base_name.2.log ]; then
        mv -f /persist/slog/$base_name.2.log /persist/slog/$base_name.3.log;
    fi

    if [ -e /persist/slog/$base_name.1.log ]; then
        mv -f /persist/slog/$base_name.1.log /persist/slog/$base_name.2.log;
    fi

    if [ -e /persist/slog/$base_name.log ]; then
        mv -f /persist/slog/$base_name.log /persist/slog/$base_name.1.log;
    fi
}

save_log_to_persist()
{
    waitfor /persist

    if [ ! -d /persist/slog ]; then
        mkdir -m 0644 -p /persist/slog;
    fi

    rename_slog_files slog
    slog2info > /persist/slog/slog.log

    rename_slog_files slog_before_reset
    if [ -e /dev/shmem/slogger2phys ]; then
        slog2info -r /dev/shmem/slogger2phys > /persist/slog/slog_before_reset.log
    else
        touch /persist/slog/slog_before_reset.log
    fi

    sync
}

copy_log_to_qlog()
{
    waitfor /var/log

    if [ ! -d /var/log/slog ]; then
        mkdir -m 0644 -p /var/log/slog;
    fi

    cp /persist/slog/*.log /var/log/slog/
}

start_config_vlan()
{
    log_launch "config vlan"

    ifconfig vlan1 create
    ifconfig vlan1 vlan 1 vlanif emac0
    ifconfig vlan1 172.16.1.2 netmask 255.255.255.0 up
    ifconfig vlan1 vlanprio 7
}

start_max20086()
{
    #####start max20086 #####
    log_launch "max20086"
    # wait for the max20086 device file
    on -T max20086_t -u 826:826 -d /usr/bin/max20086
}
start_mcu_hb()
{
    log_launch "mcu_hb"
    on -T mcu_hb_t -u mcu_hb mcu_hb 500 &
}
start_mcu_did()
{
    log_launch "mcu_did"
    on -T mcu_did_t -u mcu_did mcu_did &
}
start_mcu_log()
{
    log_launch "mcu_log"
    on -T mcu_log_t -u mcu_log mcu_log &
}
start_mcu_systime()
{
    log_launch "mcu_systime"
    on -T mcu_systime_t -u mcu_systime mcu_systime 10 &
}
start_thermal_ctrl()
{
    log_launch "thermal_ctrl"
    on -T thermal_ctrl_t -u thermal_ctrl thermal_ctrl &
}

start_mosquitto()
{
    log_launch "mosquitto"

    on -T mosquitto_t -p 10 -u mosquitto /usr/bin/mosquitto -c /etc/mosquitto/mosquitto.conf -d &
}

start_dltlog_app()
{
    log_launch "dltlog"

    if [ ! -d /var/log/dltlogs ]; then
        mkdir -m 0777 -p /var/log/dltlogs;
    fi

    ln -f -s /etc/dlt_logstorage.conf /var/log/dltlogs/dlt_logstorage.conf
    chown 832:832 /var/log/dltlogs

    # /bin/slm -V /slm/dlt_daemon.xml
    # /bin/slm -V /slm/dlt_qnx_system.xml
}


setup_qt_env() {
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/qt/lib
    export QT_PLUGIN_PATH=/opt/qt/plugins
    export QML2_IMPORT_PATH=/opt/qt/qml
    export FONTCONFIG_FILE=/opt/qt/lib/fontconfig/local.conf
    export QQNX_PHYSICAL_SCREEN_SIZE=1920,720

    export QT_DEBUG_PLUGINS=1
    export QT_LOGGIN_TO_CONSOLE=1

    if [ ! -d /var/fontconfig ]; then
        mkdir -m 0666 -p /var/fontconfig;
    fi    
    chown 834:834 /var/fontconfig    

    waitfor /dev/random
}

unpack_resources() {
    if [ ! -d /opt/qt/resources ]; then
        tar -zxvf /opt/qt/resources.tar.gz -C /opt/qt;
        rm /opt/qt/resources.tar.gz;
    fi   
}
start_kbox()
{
    log_launch "gptee"
    on -T kbox_t -p 10 -u 869:869 /bin/gptee &
}


start_ais_vision_server()
{
    #####start ais_vision_server #####
    log_launch "ais_vision_server"
    # wait for the ais_vision_server device file
    #on -T ais_vision_server_t -u ais_vision_server_u ais_vision_server &
    # /bin/slm -V /slm/vision.xml
}
start_ais_dms_server()
{
    #####start ais_dms_server #####
    log_launch "ais_dms_server"
    # wait for the ais_dms_server device file
    on -T ais_dms_server_t -u ais_dms_server_u ais_dms_server &
}
start_display_manager()
{
    log_launch "display_manager"
    on -T display_manager_t -u 865:865,819 /bin/display_manager &
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

[ -f /etc/system/config/display_mapping.json ] || ln -s /etc/system/config/display_mapping_$(uname -m | awk -F '_' '{print $4}').json /etc/system/config/display_mapping.json

echo 'Setting dump mode to mini_rawdump as /etc/enable_mini_rawdump is enabled'
echo mini_rawdump > /dev/pdbg/memorydump/dload/dload_mode

uname_m=`uname -m`
. /scripts/platform_variables.sh

common_early;

waitfor /dev/screen

echo "Starting iceoryx iox-roudi ..."
start_iceoryx

echo "start message service"
start_message_service

echo "start backlightsrvr"
start_backlightsrv

echo "start display_manager"
waitfor /dev/backlight/mode
start_display_manager

echo "start pm_event_postprocess"
start_pm_event_postprocess

echo "start pm_event_preprocess"
start_pm_event_preprocess

# start up ic_qt
echo "setup_qt_env"
setup_qt_env

echo "unpack resources"
unpack_resources

echo "start up ic_qt"
# /bin/slm -V /slm/ic_qt.xml

mount -T io-pkt -o peer=/dev/qvm/la/la_to_host,bind=/dev/vdevpeer/vp0,mac=aaaaaaaaaaaa,mode=0660 /lib/dll/devnp-vdevpeer-net.so






qseecom;

#start kbox 
echo "start kbox service"
#start_kbox
# /bin/slm -V /slm/kbox_service.xml

km_be_loader;

chmod 660 /dev/disk/uda0;
waitfor /dev/km_be_avb_server
$ON -R 0xf0 $QVB_SERVICE_ON_ARGS $QVB_SERVICE_BINARY $QVB_SERVICE_ARGS
if [ $SECPOL_ENABLE -eq 1 ]; then
    setfacl -m user:146:w /persist
    setfacl -m group:146:w /persist
fi

save_log_to_persist

# mounting io-pck after VMM Service lauch is casuing vdev issues
#mount -T io-pkt /lib64/libdevnp-emac-eth.so


# configuring the socket send / recv buffer size
config_sysctl_network

# init usb hub chip power
usb_hub_power

# mount log partition
mount_log

# create file /var/log/syslog
create_syslog

## Enable dump; user responsible for creating/deleting flag
if [ -e /var/enable_fulldump ]; then
    echo 'Setting dump mode to full ramdump as /etc/enable_fulldump is enabled'
    echo full > /dev/pdbg/memorydump/dload/dload_mode
elif [ -e /var/enable_mini_rawdump ]; then
    echo 'Setting dump mode to mini_rawdump as /etc/enable_mini_rawdump is enabled'
    echo mini_rawdump > /dev/pdbg/memorydump/dload/dload_mode
elif [ -e /var/enable_mini_dload ]; then
    echo 'Setting dump mode to mini_dload as /etc/enable_mini_dload is enabled'
    echo mini_dload > /dev/pdbg/memorydump/dload/dload_mode
elif [ -e /var/enable_nodump ]; then
    echo 'Setting dump mode to no ramdump as /etc/enable_nodump is enabled'
    echo nodump > /dev/pdbg/memorydump/dload/dload_mode
else
    echo
fi

echo "start check system slot luns consistent"
start_chk_luns_consistent

# create file /etc/icapps_version
create_icapps_version

log_launch "pps"
$ON $PPS_ON_ARGS pps -m /var/pps -p /var/pps_persist -t 100
waitfor /var/pps
if [ $SECPOL_ENABLE -eq 1 ];then
    chown 40:40 /var/pps
fi

#depend on /var/log
waitfor /log/qlog
mkdir -p /var/log/kernel


waitfor /dev/screen
log_launch "GVM(s)"
	$ON $VMM_SERVICE_ON_ARGS $VMM_SERVICE_BINARY $VMM_SERVICE_ARGS
	$ON $VMM_LIFECYCLE_ON_ARGS $VMM_LIFECYCLE_BINARY $VMM_LIFECYCLE_ARGS &

#$ON $DEFAULT_ROOT_T qnetconfig -b 2 -c /etc/early-net.cfg &
#common_netdbgservices;

echo "start MCU RPC daemon"
start_mcurpc

echo "start MCU log service"
start_mcu_log

echo "start chime_service"
start_chime_service

echo "start MAX20086 daemon"
start_max20086

#mount_userdata may use QSEECom service functionality
if [ $ENABLE_INPLACE_FDE -eq 1 ]; then
    mount_inplace
else
    mount_userdata
fi

export_slot_info


# mount factory partition
mount_factory

# mount calibration partition
mount_calibration

echo "start_dltlog_app"
start_dltlog_app

# copy the saved slog2 log file to qlog directory
copy_log_to_qlog

chmod a+w /etc/system/config

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


$ON $SSR_SERVICE_ON_ARGS  ssr_service -p /var/pps/ssr -s lpass -s modem -s cdsp -s spss -r 1 -t 300 &

waitfor /dev/ssr
waitfor /dev/pil_service

$ON $CDSP_SERVICE_ON_ARGS  cdsp_service -f /etc/cdsp_cfg &


##$ON $LCM_DEMO_ON_ARGS  life_cycle_man_demo &

$ON $MEGA_LIFE_CYCLE_ON_ARGS  mega_life_cycle &

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

echo "start config vlan"
start_config_vlan

LOCAL_IPADDR=192.168.0.1
GATEWAY_IPADDR=192.168.0.3


common_netdbgservices;

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
        on -T ifconfig_t -u 50:50 ifconfig emac0 ${LOCAL_IPADDR} up
        on -T route_t -u 151:151 route add default ${GATEWAY_IPADDR}
    else
        brconfig bridge0 add emac0 up
        ifconfig emac0 ${LOCAL_IPADDR} up
        route add default ${GATEWAY_IPADDR}
    fi
fi

$ON $VM_SSR_BE_ON_ARGS  vm_ssr_be &
$ON $DCVS_ON_ARGS dcvs_service -d 30 &

sysctl -qw net.inet6.ip6.ifq.maxlen=1024
sysctl -qw net.inet.ip.ifq.maxlen=1024
sysctl -w net.inet.ip.forwarding=0

echo "start dumper"
start_dumper

#starting veth ipa backend
veth_ipa_be &

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


echo "start mosquitto"
start_mosquitto

echo "start ic_apps"
# /bin/slm -V /slm/service_apps.xml


LSM_IPADDR=`cat /etc/hosts | grep 'cdc-android' | awk -F ' ' '{printf $1}'`
qcdiaglsm ${LSM_IPADDR};
echo "qcdiaglsm ip " ${LSM_IPADDR}

slay -R 0xFF qcpe_qhee

log_collector &
apply_ddr_freq_limits

if [ -e /var/qgptp_enable ];then
	if [ $SECPOL_ENABLE -eq 1 ];then
		on -T qavb_core_t -u 58:58,37 qavb_core &
		on -T qgptp_t -u 56:56,37 qgptp emac0 -V -INITSYNC -5 -OPERSYNC -1 -INITPDELAY 0 -OPERPDELAY 2  &
		on -T avb_client_t -u 59:59,37 crf_stream -f /etc/qavb_config/crf_talker.ini &
	else
		$ON $DEFAULT_ROOT_T qavb_core &
		$ON $DEFAULT_ROOT_T qgptp emac0 -V -INITSYNC -5 -OPERSYNC -1 -INITPDELAY 0 -OPERPDELAY 2  &
		$ON $DEFAULT_ROOT_T crf_stream -f /etc/qavb_config/crf_talker.ini &
	fi
fi


waitfor /factory/.boot
mkdir -p /factory/ftm
waitfor /cal/.boot
mkdir -p /cal/avm

#mount ota partition
mount_ota

if [ -f /var/devtest.sh ]; then
    /var/devtest.sh
fi

echo "start factoryservice"
start_factoryservice

echo "start input service"
start_input_service

#do not enable this command until production version
echo "start ecu_config_utility"
start_ecu_config_utility

# echo "start record service"
# start_record_service

echo "start nfsd"
waitfor /ota/android
start_nfsd

echo "update timezone info"
timezone.sh

echo "start host ota service"
start_host_ota

echo "start ecu ota service"
start_ecu_ota

echo "setup diag_service_pps"
setup_diag_service_pps

echo "start MCU heartbeat service"
start_mcu_hb

echo "start MCU systime service"
start_mcu_systime

echo "start health monitor service"
start_health_monitor

echo "start thermal_ctrl service"
start_thermal_ctrl

echo "start misc_service"
start_misc_service

echo "start ais_vision_server service"
start_ais_vision_server

echo "start ais_dms_server service"
#start_ais_dms_server

echo "start mcu DID service"
start_mcu_did

### adjust the slog2 verbosiry for some modules ###
config_slog2_verbosity

echo 0 > /dev/pdbg/qcore/power/dynamic_offline_en

echo "start vmm_monitor"
start_vmm_monitor

echo "Startup complete"
