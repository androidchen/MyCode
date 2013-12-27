package com.easyclient.utils;

public class Installer {

	public native String install(String apkName);

	public native Process getProcess(String su);

	static {
		System.loadLibrary("install");
	}
}
