package com.easyclient.utils;

public class Installer {

	public native String install(String apkName);

	public native Process getProcess(String su);

	/*
	 * 0:success
	 * 1:process is null
	 * 2:DataOutputStream is null
	 */
	public native int installToSystem(String apkName);

	static {
		System.loadLibrary("install");
	}
}
