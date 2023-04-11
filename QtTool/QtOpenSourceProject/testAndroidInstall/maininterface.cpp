#include "maininterface.h"
#include "ui_maininterface.h"

#ifdef Q_OS_ANDROID
#include<QAndroidJniEnvironment>
#include<QAndroidJniObject>
#include<QtAndroid>
#endif

MainInterface::MainInterface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainInterface)
{
    ui->setupUi(this);

    connect(ui->updatePushButton, &QAbstractButton::clicked,
            this, [&](){
      // Android自动更新的方法
#ifdef Q_OS_ANDROID
         QAndroidJniEnvironment env;

        m_activity = QtAndroid::androidActivity();
        m_activity.callMethod<void>("updateSoftware");

        if(env->ExceptionCheck()){
            env->ExceptionDescribe();
            env->ExceptionClear();
        }

#endif
    });
}

MainInterface::~MainInterface()
{
    delete ui;
}

