package com.hy.report.api;

/**
 * @Description: javac -h . src/com/hy/report/api/Food.java
 * https://blog.csdn.net/xiaoxiaoyusheng2012/article/details/56672173
 * @Author: Eddie Wei
 * @CreateTime: 2022-08-13
 * @Project: jni_demo
 * @Version: 1.0
 */
public class Food {

    static {
        System.loadLibrary("Calculation");
    }

    // 用于存储C++层的对象指针
    private long mObject;

    public Food(String name, double price) {
        setFoodParam(name, price);
    }

    public native void setFoodParam(String name, double price);
    public native String getName();
    public native double getPrice();
    protected native void finalize();

    public static void main(String[] args) {
        Food f1 = new Food("Bread", 1.99);
        Food f2 = new Food("Milk", 3.99);

        System.out.println(String.format("Food:%s， Price:%f", f1.getName(), f1.getPrice()));
        System.out.println(String.format("Food:%s， Price:%f", f2.getName(), f2.getPrice()));
    }
}
