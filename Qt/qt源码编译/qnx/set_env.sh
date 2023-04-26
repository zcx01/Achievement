#!/bin/bash

# check the path
check_item=(
    sdk
    CMakeLists.txt
    set_env.sh
    build.sh
)
for item in ${check_item[*]}
do
    if [ ! -e ${item} ]; then
        echo "enter root path and source ./set_env.sh again"
        return
    fi
done

# sudo /etc/init.d/mosquitto restart

# project root path
echo "setup compile environment variables"
export CMAKE_PROJECT_ROOT=$(pwd)

# build path
export CMAKE_BUILD_ROOT=${CMAKE_PROJECT_ROOT}/build

# output path
export CMAKE_OUTPUT_ROOT=${CMAKE_PROJECT_ROOT}/output
export CMAKE_OUTPUT_BINARY=${CMAKE_OUTPUT_ROOT}/binary
export CMAKE_OUTPUT_REPORT=${CMAKE_OUTPUT_ROOT}/report
export CMAKE_REPORT_UNITTEST=${CMAKE_OUTPUT_REPORT}/unit_test

# source code path
export CMAKE_SOURCE_ROOT=${CMAKE_PROJECT_ROOT}/src
export CMAKE_SOURCE_APP=${CMAKE_SOURCE_ROOT}
export CMAKE_SOURCE_LIB=${CMAKE_SOURCE_ROOT}

# apps path
export OUTPUT_BOARD_APPDIR=/opt/apps
export CMAKE_OUTPUT_APPDIR=${CMAKE_OUTPUT_BINARY}${OUTPUT_BOARD_APPDIR}/latest

# tools path
export CMAKE_TOOLS_ROOT=${CMAKE_PROJECT_ROOT}/build_script
export CMAKE_TOOLS_SOURCE=${CMAKE_TOOLS_ROOT}/src

# cmake scripts path
export CMAKE_TEMPLATE_ROOT=${CMAKE_TOOLS_ROOT}/cmake

#cmake common shell tools path
export CMAKE_COMMON_SHELL_TOOLS=${CMAKE_TOOLS_ROOT}/shell

# check input argument
out_type="debug"

compile_flag=""
while [[ $# -gt 0 ]]
do
    key="$1"
    case ${key} in
        release)
            out_type="release"
            shift
            ;;
        test)
            out_type="test"
            shift
            ;;
        *)
            shift
            ;;
    esac
done

# project config path
export PROJ_CONF_DIR=${CMAKE_PROJECT_ROOT}/conf
cfile=${PROJ_CONF_DIR}/g_build_cfg

G_CONFIG_TARGET_SYSTEM=""
G_CONFIG_QNX_TARGET_ARCH=""
QNX_SYSTEM_NAME="QNX"

configs=`sed  -n '/G_CONFIG/ p' ${cfile}`
configs_cflags=`echo ${configs} | sed 's|G_CONFIG|-DG_CONFIG|g'| sed 's|\"|\\\"|g'`
if [ -z "${compile_flag}" ]; then
    compile_flag=${configs_cflags}
else
    compile_flag="${compile_flag} ${configs_cflags}"
fi

if [[ "$compile_flag" == *"G_CONFIG_USE_DLT_LOG=1"* ]];then
    compile_flag="${compile_flag} -DUSE_DLT_LOG"
fi

#echo "----configs = $configs"
export $configs

if [ "${G_CONFIG_TARGET_SYSTEM}" == "$QNX_SYSTEM_NAME" ];then
    sdk_dir=sdk/files/qnx700
    mega_dir=sdk/files/mega
    sdp_env_file=sdk/files/qnx700/qnxsdp-env.sh
    if [ ! -d ${sdk_dir} ]; then
        echo "sdp is not found, need download firstly"
        return
    fi
    if [ ! -n "${G_CONFIG_QNX_TARGET_ARCH}" ]; then
        sdk_env_info=sdk/files/environment-setup-aarch64
    else
        sdk_env_info=sdk/files/environment-setup-${G_CONFIG_QNX_TARGET_ARCH}
        if [ ! -f "${sdk_env_info}" ]; then
            sdk_env_info=sdk/files/environment-setup-aarch64
        fi
    fi
    if [ -f "${sdp_env_file}" ]; then
        source ${sdp_env_file}
    fi
    source ${sdk_env_info}
    export CMAKE_SDK_ROOT=${CMAKE_PROJECT_ROOT}/sdk
    export QNX_TARGET=$(pwd)/${sdk_dir}/target/qnx7
    export MEGA_TARGET=$(pwd)/sdk/files/mega/target
    export IC_PREBUILTS_DIR=$(pwd)/prebuilts/ic
    export COMM_PREBUILTS_DIR=$(pwd)/prebuilts/common/
else
    sdk_file=sdk/sdk-install.sh
    sdk_env_info=sdk/files/environment-setup.txt
    sdk_dir=sdk/work
    sdk_state=${sdk_dir}/sdk_md5

    if [ ! -f ${sdk_file} ] || [ ! -x ${sdk_file} ]; then
        echo "sdk file [${sdk_file}] is not found, need download firstly"
        return
    fi

    output_sdk=0
    if [ ! -d ${sdk_dir} ] || [ ! -f ${sdk_state} ]; then
        output_sdk=1
    else
        old_md5=`cat ${sdk_state} | tr -d '\n'`
        new_md5=`md5sum ${sdk_file} | awk '{print $1}' | tr -d '\n'`
        if [ ! "${old_md5}" == "${new_md5}" ]; then
            output_sdk=1
        fi
    fi

    if [ ${output_sdk} -eq 1 ]; then
        echo "create new sdk files..."
        sudo rm -rf ${sdk_dir}
        mkdir -p ${sdk_dir}
        ./${sdk_file} -d ${sdk_dir} -y
        if [ -d ${sdk_dir}/sysroots ];then
            chmod -R a+rX ${sdk_dir}/sysroots
        fi
        echo $(md5sum ${sdk_file} | awk '{print $1}') > ${sdk_state}

        echo "create new sdk files complete!"
    fi

    source ${sdk_dir}/$(cat ${sdk_env_info})
    export CMAKE_SDK_ROOT=${CMAKE_PROJECT_ROOT}/sdk/work
fi

if [ "${G_CONFIG_QT_SUPPORT}" = "1" ];then
    echo "G_CONFIG_QT_SUPPORT=${G_CONFIG_QT_SUPPORT}"
    export QT_ROOT=$(pwd)/qt
    export QT_LICENSE_FILE=${QT_ROOT}/license/.qt-license
    export QT_INSTALL_DIR=${QT_ROOT}/prebuilt/
fi

# sdk path
export PATH=${CMAKE_PROJECT_ROOT}/build_script:$PATH

echo "G_CONFIG_VEHICLE_MODEL=${G_CONFIG_VEHICLE_MODEL}"
export CMAKE_VEHICLE_TYPE=${G_CONFIG_VEHICLE_MODEL//\"/}

echo "G_CONFIG_QNX_TARGET_ARCH: ${G_CONFIG_QNX_TARGET_ARCH}"

export CMAKE_OUTPUT_TYPE=${out_type}
echo "BUILD TYPE: ${CMAKE_OUTPUT_TYPE}"

export CMAKE_COMPILE_FLAG=${compile_flag}
#echo "compile flag is ${CMAKE_COMPILE_FLAG}"

if [ -z "$ENABLE_UT" ];then
export ENABLE_UT=0
echo "ENABLE_UT=$ENABLE_UT"
fi


