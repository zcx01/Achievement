export QT_ROOT=$(pwd)/qt
export QT_LICENSE_FILE=${QT_ROOT}/license/.qt-license
export QT_INSTALL_DIR=${QT_ROOT}/prebuilt/
export ANDROID_SDK=${HOME}/Android/Sdk
export ANDROID_NDK=${ANDROID_SDK}/ndk/22.1.7171670

export JAVA_HOME=${HOME}/android-studio/jbr
export PATH=$JAVA_HOME/bin:$PATH

echo ${ANDROID_SDK}
echo ${ANDROID_NDK}
