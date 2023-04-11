#include "maininterface.h"
#include "ui_maininterface.h"

#ifdef Q_OS_ANDROID
#include<QAndroidJniEnvironment>
#include<QAndroidJniObject>
#include<QtAndroid>
#endif

#include<QDebug>
#include<iostream>



QAndroidJniEnvironment env;
static QString jstringToQString(JNIEnv *en,jstring jstr)
{
    const char* cstr = en->GetStringUTFChars(jstr, 0);
    QString qstr = QString::fromUtf8(cstr);
    en->ReleaseStringUTFChars(jstr, cstr);
    return qstr;
}

static void callBackQt(JNIEnv *en,jobject thiz,jstring topic,jstring  msg)
{
//     qDebug()<<topic.toString() <<msg.toString();
    qDebug()<<jstringToQString(en,topic) <<jstringToQString(en,msg);
}

static const JNINativeMethod gMethods[] = {
     //定义批量注册的数组，是注册的关键部分
     { "callBackQt", "(Ljava/lang/String;Ljava/lang/String;)V", (void*)callBackQt } // func2是在java中声明的native函数名，"()V"是函数的签名，可以通过javah获取。

};

void  RegJni()
{
    const char* kClassName ="com/hjx/TestJNI";
    jclass clazz;
    clazz =env->FindClass(kClassName);
    if (clazz == NULL)
    {
        qDebug()<<"erro   clazz";
        return ;
    }
    qDebug()<<"RegisterNatives   2***********";

    if (env->RegisterNatives(clazz, gMethods, sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK)
    {
        printf("register native method failed!\n");
        return;
    }else{
        qDebug()<<"RegisterNatives   搞定***********";
    }
    env->DeleteLocalRef(clazz);//删除引用避免内存泄漏

}
MainInterface::MainInterface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainInterface)
{
    ui->setupUi(this);

#ifdef Q_OS_ANDROID
    // QAndroidJniEnvironment env;
    RegJni();
    QAndroidJniObject m_activity = QtAndroid::androidActivity();
//    //调用静态方法
//    qDebug()<< m_activity.callStaticMethod<jint>("com/hjx/TestJNI",
//                                                 "test"
//                                                 //,"()V"//方法签名可以省略
//                                                 );

//    jint num = 1;
//    qDebug()<<m_activity.callStaticMethod<jint>("com/hjx/TestJNI",
//                                                "test2",
//                                                "(I)I",
//                                                num);

//    //调用静态类方法
//    QAndroidJniObject obj = QAndroidJniObject::fromString("jiangxueHan");
//    jstring jstr = obj.object<jstring>();
//    QAndroidJniObject s = m_activity.callStaticObjectMethod("com/hjx/TestJNI",
//                                                            "test3",
//                                                            "(Ljava/lang/String;)Ljava/lang/String;",
//                                                            jstr);

//    //调用非静态方法
//    QString qstring = s.toString();
//    qDebug()<<qstring;

//    m_activity.callMethod<void>("test4");

//    //调用非静态类方法
//    s =  m_activity.callObjectMethod("test5",
//                                     "(Ljava/lang/String;)Ljava/lang/String;",
//                                     jstr);
//    qstring = s.toString();
//    qDebug()<<qstring;

//    //调用静态方法
//    m_activity.callStaticObjectMethod("com/hjx/TestJNI",
//                                                 "test6",
//                                                 "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;",
//                                                 jstr,jstr);

    m_activity.callMethod<void>("onCreate");
    m_activity.callMethod<void>("onStart");

    if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
    }

#endif
}

MainInterface::~MainInterface()
{
    delete ui;
}

