package com.test.uninstall;

import java.io.DataOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.OutputStream;

import com.easyclient.utils.Installer;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class Main extends Activity {
	public static final String TAG = "Main";

	private Installer installer;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		installer = new Installer();

		Button button = (Button) findViewById(R.id.btn);
		button.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// uninstall();
				// testNDKgetProcess();

				testNDKinstallToSystem();
			}
		});

		Button installBtn = (Button) findViewById(R.id.install);
		installBtn.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {

				String sourceApkName = "/sdcard/***.apk";
				File sApk = new File(sourceApkName);
				if (!sApk.exists()) {
					Toast.makeText(Main.this, "安装包不存在", Toast.LENGTH_LONG).show();
					return;
				}

				String systemApk = "/system/app/***.apk";
				StringBuffer command = new StringBuffer();
				command.append("mount -o remount,rw -t yaffs2 /dev/block/mtdblock3 /system ;\n");
				command.append("cat " + sourceApkName + " > " + systemApk + ";\n");
				command.append("mount -o remount,ro -t yaffs2 /dev/block/mtdblock3 /system\n");
				execInstallCmd(command.toString());

			}
		});

	}

	// 从ndk中返回字符串
	private void testNDK() {
		print(installer.install("/system/app/ETPlayer_1.2.2.9.apk"));
	}

	// ndk获得process对象
	private void testNDKgetProcess() {
		Process process = installer.getProcess("su");
		if (process == null) {
			Log.e(TAG, "process is null");
		}
	}

	private void testNDKinstallToSystem() {
		String apkName = "/system/app/ETPlayer_1.2.2.9.apk";
		int result = installer.installToSystem(apkName);
		if (result == 0) {
			Toast.makeText(this, "删除成功", 1000).show();
		}
		else {
			Toast.makeText(this, "删除失败", 1000).show();
		}
	}

	private File[] getSystemApps() {
		File systemApp = new File("/system/app/");
		File[] systemApps = systemApp.listFiles();

		return systemApps;
	}

	private File[] getDataApps() {
		File dataApp = new File("/data/app/");
		File[] dataApps = dataApp.listFiles();

		return dataApps;
	}

	private void printFileInfo(File[] files) {
		if (files == null) {
			System.out.println("error, files is null!");
		}
		for (int i = 0; i < files.length; i++) {
			System.out.println("fileName:" + files[i].getName());
		}
	}

	private void print(String content) {
		System.out.println(content);
	}

	// 卸载
	private void uninstall() {

		// 还要将升级部分删除
		String packageName = "com.easyclient.activity";

		Uri packageURI = Uri.parse("package:" + packageName);
		Intent uninstallIntent = new Intent(Intent.ACTION_DELETE, packageURI);
		uninstallIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		startActivity(uninstallIntent);

		String apkName = "/system/app/***.apk";
		uninstallCommand(apkName);

		System.out.println("uninstall successfully!");
	}

	// 执行卸载命令，删除system程序
	public void uninstallCommand(String apkName) {
		Process process;
		try {
			process = Runtime.getRuntime().exec("su");
			// process = installer.getProcess("su");
			DataOutputStream os = new DataOutputStream(process.getOutputStream());
			os.writeBytes("mount -o remount,rw -t rfs /dev/stl5 /system; \n");
			os.writeBytes("rm -r " + apkName + "; \n");
			os.writeBytes("mount -o remount,ro -t rfs /dev/stl5 /system; \n");
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}

	// 安装apk至system
	public String execInstallCmd(String paramString) {
		String result = "result : ";
		try {
			Process localProcess = Runtime.getRuntime().exec("su ");// 经过Root处理的android系统即有su命令
			OutputStream localOutputStream = localProcess.getOutputStream();
			DataOutputStream localDataOutputStream = new DataOutputStream(localOutputStream);
			String str1 = String.valueOf(paramString);
			String str2 = str1 + "\n";
			localDataOutputStream.writeBytes(str2);
			localDataOutputStream.flush();
			localDataOutputStream.writeBytes("exit\n");
			localDataOutputStream.flush();
			localProcess.waitFor();
			return result;
		}
		catch (Exception localException) {
			localException.printStackTrace();
			return result;
		}
	}
}
