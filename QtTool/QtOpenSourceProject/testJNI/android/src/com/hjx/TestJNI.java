// package com.hjx;
// import org.qtproject.qt5.android.bindings.QtActivity;

// import java.lang.String;

// public class TestJNI extends org.qtproject.qt5.android.bindings.QtActivity{
//     public static int test() {
//         System.out.println("Hello world!");
//         return 1;
//       }

//     public static int test2(int num){
//         return num + 2;
//        }

//    public static String test3(String s){
//         return (s + ", Hello!");
//        }

//    public  void test4(){
//         System.out.println("21!");
//        }

//    public  String test5(String s){
//         return (s + ", Hi!");
//        }

//     public native static void callBackQt(String topic,String msg);

//     public static String test6(String topic,String msg){
//         System.out.println(topic+msg+"test6");
//         callBackQt("/Speed","100");
//         return "1";
//     }

// }

package com.hjx;

import org.qtproject.qt5.android.bindings.QtActivity;

import android.os.Bundle;
import android.util.ArraySet;
import android.util.Log;

import java.util.Arrays;
import java.util.Set;
import java.lang.String;

import mega.car.MegaCarProperty;

import mega.car.config.CarPropertyProvider;
import mega.car.config.Driving;
import mega.car.hardware.CarPropertyValue;
import mega.car.hardware.property.CarPropertyManager;
import mega.log.MLog;

public class TestJNI extends org.qtproject.qt5.android.bindings.QtActivity {

   public native static void callBackQt(String topic,String msg);

   private static final String TAG = TestJNI.class.getSimpleName();

   private static final int GEAR_ID = CarPropertyProvider.topicToId("DrivingInfo/Gear");
   private static final int SPEED_ID = CarPropertyProvider.topicToId("DrivingInfo/Speed");

   // 需要监听的信号
   private static final Set<Integer> ID_SET = new ArraySet<>(Arrays.asList(
           GEAR_ID,
           SPEED_ID
   ));

   private MegaCarProperty mCarProperty;

   private final CarPropertyManager.CarPropertyEventCallback mCallback =
           new CarPropertyManager.CarPropertyEventCallback() {

       public void onChangeEvent(CarPropertyValue carPropertyValue) {
           // 收到有效信号
           int propertyId = carPropertyValue.getPropertyId();
           Object value = carPropertyValue.getValue();
           if (propertyId == GEAR_ID) {
               callBackQt("DrivingInfo/Gear",String.valueOf(value));
               MLog.d(TAG, "收到档位: " + ((int) value));
           } else if (propertyId == SPEED_ID) {
                callBackQt("DrivingInfo/Speed",String.valueOf(value));
                MLog.d(TAG, "收到速度: " + ((float) value));
           }
       }

       public void onErrorEvent(int id, int area) {
           // 收到无效信号

       }
   };

   public void onCreate() {

       // 获取 MegaCarProperty 实例
       mCarProperty = MegaCarProperty.getInstance(this);

       // 读 int 信号
       int gearId = CarPropertyProvider.topicToId("DrivingInfo/Gear");
       int gear = mCarProperty.getIntProp(gearId);
       MLog.d(TAG, "gear=" + gear);

       CarPropertyValue<?> gearValue = mCarProperty.getPropertyRaw(gearId); // 和 getIntProp 效果一样
       MLog.d(TAG, "gearValue=" + gearValue);
       if (gearValue != null) {
           if (gearValue.getStatus() == CarPropertyValue.STATUS_AVAILABLE) {
               // 有效信号
               int value = (int) gearValue.getValue();
           } else {
               // 无效信号
               String extension = String.valueOf(gearValue.getExtension());
           }
       }

       // 读 Float 信号
       float speed= mCarProperty.getFloatProp(CarPropertyProvider.topicToId("DrivingInfo/Speed"));
       MLog.d(TAG, "speed=" + speed);

       // 发 int 信号
       int faceId = CarPropertyProvider.topicToId("CDC_2D2/CdcCurrAccountFaceID/Set");
       mCarProperty.setIntProp(faceId, 1);
       mCarProperty.setRawProp(new CarPropertyValue<>(faceId, 1)); // 和 setIntProp 效果一样

       // 发 String 信号
       int alSet = CarPropertyProvider.topicToId("ActiveLight/OnOff/Set");
       mCarProperty.setRawProp(new CarPropertyValue<>(faceId, "{\"name\":value}"));

//        mCarProperty.registerCallback(mCallback, ID_SET);
   }

    public void onStart() {
        super.onStart();
        if(mCarProperty!= null)
        {
            // 监听信号
            mCarProperty.registerCallback(mCallback, ID_SET);
        }
    }

   public void onStop() {
       super.onStop();
        if(mCarProperty!= null)
        {
            // 取消监听信号
            mCarProperty.unregisterCallback(mCallback, ID_SET);
        }
   }
}
