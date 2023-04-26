package com.janyee.xu;

import android.os.Bundle;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;
import com.janyee.xu.update.XUpdateInit;


import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.view.View;

import android.util.Log;


public class UpdateAty extends org.qtproject.qt5.android.bindings.QtActivity{

//用于开机自动跟新
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d("====","更新测试");
        XUpdateInit.checkUpdate(getApplicationContext(),true);
        Log.d("====","更新测试2");
    }
//调用接口实现更新
    public void updateSoftware(){
        Log.d("====","更新测试");
        XUpdateInit.checkUpdate(getApplicationContext(),true);
        Log.d("====","更新测试2");
    }

}
