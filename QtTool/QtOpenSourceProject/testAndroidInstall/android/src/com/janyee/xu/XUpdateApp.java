package com.janyee.xu;
import android.util.Log;
import android.app.Application;

import com.janyee.xu.update.XUpdateInit;
import com.xuexiang.xhttp2.XHttp;
import com.xuexiang.xhttp2.XHttpSDK;

public class XUpdateApp extends org.qtproject.qt5.android.bindings.QtApplication {

    @Override
    public void onCreate() {
        super.onCreate();
        Log.d("====","更新测试app");

        XHttp.init(this);
        XHttpSDK.setBaseUrl("https://baidu.com/");
        XUpdateInit.init(this);
    }


}

