package com.hjx;
import org.qtproject.qt5.android.bindings.QtActivity;

import java.lang.String;

public class TestJNI extends org.qtproject.qt5.android.bindings.QtActivity{
    public static int test() {
        System.out.println("Hello world!");
        return 1;
      }

    public static int test2(int num){
        return num + 2;
       }

   public static String test3(String s){
        return (s + ", Hello!");
       }

   public  void test4(){
        System.out.println("21!");
       }

   public  String test5(String s){
        return (s + ", Hi!");
       }


}
