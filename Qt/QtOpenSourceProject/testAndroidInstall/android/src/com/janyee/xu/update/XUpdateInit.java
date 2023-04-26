/*
 * Copyright (C) 2019 xuexiangjys(xuexiangjys@163.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

package com.janyee.xu.update;

import android.app.Application;
import android.content.Context;

import androidx.annotation.NonNull;

import com.google.gson.Gson;
import org.qtproject.example.BuildConfig;
import com.janyee.xu.CodeMsg;
import com.xuexiang.xupdate.XUpdate;
import com.xuexiang.xupdate.entity.PromptEntity;
import com.xuexiang.xupdate.entity.UpdateEntity;
import com.xuexiang.xupdate.listener.IUpdateParseCallback;
import com.xuexiang.xupdate.proxy.IUpdateParser;
import com.xuexiang.xupdate.proxy.IUpdatePrompter;
import com.xuexiang.xupdate.proxy.IUpdateProxy;
import com.xuexiang.xupdate.utils.UpdateUtils;

import java.util.Map;

import android.util.Log;
/**
 * XUpdate 版本更新 SDK 初始化
 *
 * @author xuexiang
 * @since 2019-06-18 15:51
 */

//解析json
public final class XUpdateInit {

    private XUpdateInit() {
        throw new UnsupportedOperationException("u can't instantiate me...");
    }

    /**
     * 应用版本更新的检查地址
     */
    private static final String KEY_UPDATE_URL = "api/...";

    public static void init(Application application) {
        XUpdate.get()
                .debug(false)
                //默认设置只在wifi下检查版本更新
                .isWifiOnly(false)
                //默认设置使用get请求检查版本
                .isGet(true)
                //默认设置非自动模式，可根据具体使用配置
                .isAutoMode(false)
                //设置默认公共请求参数
                .param("versionCode", UpdateUtils.getVersionCode(application))
                .param("appKey", application.getPackageName())
                //这个必须设置！实现网络请求功能。
                .setIUpdateHttpService(new XHttpUpdateHttpServiceImpl())
                .setIUpdateDownLoader(new CustomUpdateDownloader())
                .setIUpdateParser(new IUpdateParser() {
                    @Override
                    public UpdateEntity parseJson(String json) throws Exception {
                        Log.d("====","获取到版本信息，尝试解析："+json);
                        Log.d("===","本地版本是："+BuildConfig.VERSION_CODE);
                        Gson gson=new Gson();
                        CodeMsg cm= gson.fromJson(json, CodeMsg.class);
                        UpdateEntity entity=new UpdateEntity();
                        if(cm.getCode()==200){
                            entity.setDownloadUrl(cm.getResult().getDownloadUrl());//下载地址
                            entity.setVersionCode(cm.getResult().getClientVersionNumber());//版本号
                            entity.setVersionName(cm.getResult().getVersionName());//版本名字
                            entity.setUpdateContent(cm.getResult().getPromptInfo());//更新内容
                            entity.setIsIgnorable(cm.getResult().getClientVersionNumber()<BuildConfig.VERSION_CODE);//忽律
                            entity.setHasUpdate(cm.getResult().getClientVersionNumber() > BuildConfig.VERSION_CODE);//更新
                        }
                        return entity;
                    }

                    @Override
                    public void parseJson(String json, IUpdateParseCallback callback) throws Exception {

                    }

                    @Override
                    public boolean isAsyncParser() {
                        return false;
                    }
                })
                //这个必须初始化
                .init(application);
    }

    /**
     * 进行版本更新检查
     */
    public static void checkUpdate(Context context, boolean needErrorTip) {
        XUpdate.newBuild(context).updateUrl(KEY_UPDATE_URL).update();
        XUpdate.get().setOnUpdateFailureListener(new CustomUpdateFailureListener(needErrorTip));
    }
}
