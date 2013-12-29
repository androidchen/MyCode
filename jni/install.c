#include <string.h>
#include <jni.h>
#include "android/log.h"

#ifdef ET_ANDROID_LOG
#include "android/log.h"
#endif

jstring Java_com_easyclient_utils_Installer_install(JNIEnv * env, jobject thiz,
		jstring apk) {
	const char *str = (*env)->GetStringUTFChars(env, apk, 0);
	char result[128];
	strcpy(result, str);
	(*env)->ReleaseStringUTFChars(env, apk, str);

	//方法二：不需要释放
	//	char result[128];
	//	int len = (*env)->GetStringUTFLength(env, apk);
	//	(*env)->GetStringUTFRegion(env, apk, 0, len, result);

	return (*env)->NewStringUTF(env, result);
}

jobject Java_com_easyclient_utils_Installer_getProcess(JNIEnv* env,
		jobject thiz, jstring su) {
	jmethodID mid;
	jclass clsRuntime = (*env)->FindClass(env, "java/lang/Runtime");

	//getRuntime方法
	mid = (*env)->GetStaticMethodID(env, clsRuntime, "getRuntime",
			"()Ljava/lang/Runtime;");
	//获得Runtime对象
	jobject objRuntime = (*env)->CallStaticObjectMethod(env, clsRuntime, mid);

	//exec方法
	mid = (*env)->GetMethodID(env, clsRuntime, "exec",
			"(Ljava/lang/String;)Ljava/lang/Process;");

	//获得Process对象
	jobject objProccess = (*env)->CallObjectMethod(env, objRuntime, mid, su);

	if (NULL == objProccess) {
		__android_log_print(ANDROID_LOG_INFO, "Msg", "objProccess is null");
		return NULL;
	}
	__android_log_print(ANDROID_LOG_INFO, "Msg", "get process success");

	return objProccess;
}

/**
 * by chenyoulin
 */
jint Java_com_easyclient_utils_Installer_installToSystem(JNIEnv* env,
		jobject thiz, jstring apkName) {
	jmethodID mid;

	jclass clsRuntime = (*env)->FindClass(env, "java/lang/Runtime");
	//getRuntime方法
	mid = (*env)->GetStaticMethodID(env, clsRuntime, "getRuntime",
			"()Ljava/lang/Runtime;");
	//获得Runtime对象
	jobject objRuntime = (*env)->CallStaticObjectMethod(env, clsRuntime, mid);

	//exec方法
	mid = (*env)->GetMethodID(env, clsRuntime, "exec",
			"(Ljava/lang/String;)Ljava/lang/Process;");

	//获得Process对象,注意参数"su"
	char* suCmd = "su";
	jstring root = (*env)->NewStringUTF(env, suCmd);
	jobject objProccess = (*env)->CallObjectMethod(env, objRuntime, mid, root);

	if (NULL == objProccess) {
		__android_log_print(ANDROID_LOG_INFO, "Msg", "objProccess is null");
		return 1;
	}
	//	__android_log_print(ANDROID_LOG_INFO, "Msg", "get objProccess success");

	jclass clsProcess = (*env)->FindClass(env, "java/lang/Process");
	//getOutputStream方法名
	mid = (*env)->GetMethodID(env, clsProcess, "getOutputStream",
			"()Ljava/io/OutputStream;");
	//获得OutputStream对象，作为获得DataOutputStream对象的参数
	jobject objOs = (*env)->CallObjectMethod(env, objProccess, mid);

	//获得DataOutputStream类，作为参数去获取DataOutputStream对象
	jclass clsDos = (*env)->FindClass(env, "java/io/DataOutputStream");

	//构造器方法获得
	mid = (*env)->GetMethodID(env, clsDos, "<init>",
			"(Ljava/io/OutputStream;)V");

	jobject objDos = (*env)->NewObject(env, clsDos, mid, objOs);
	if (NULL == objDos) {
		__android_log_print(ANDROID_LOG_INFO, "Msg", "objDos is null");
		return 2;
	}
	//	__android_log_print(ANDROID_LOG_INFO, "Msg", "get objDos success");

	mid = (*env)->GetMethodID(env, clsDos, "writeBytes",
			"(Ljava/lang/String;)V");

	//	__android_log_print(ANDROID_LOG_INFO, "Msg", "get writeBytes success");


	//拼接命令，还需要将char转化为jstring
	char uninstallCmd[256];
	char * cmd1 = "mount -o remount,rw -t rfs /dev/stl5 /system; \n";
	char * cmd2_1 = "rm -r ";
	char * str = (char*) (*env)->GetStringUTFChars(env, apkName, NULL);
	char * cmd2_2 = "; \n";
	char * cmd3 = "mount -o remount,ro -t rfs /dev/stl5 /system; \n";

	strcpy(uninstallCmd, cmd1);
	strcat(uninstallCmd, cmd2_1);
	strcat(uninstallCmd, str);
	strcat(uninstallCmd, cmd2_2);
	strcat(uninstallCmd, cmd3);

	jstring strCmd = (*env)->NewStringUTF(env, uninstallCmd);
	__android_log_print(ANDROID_LOG_INFO, "uninstallCmd", uninstallCmd);

	//注意方法的调用，不要使用CallObjectMethod，writeBytes是沒有返回值的方法
	(*env)->CallVoidMethod(env, objDos, mid, strCmd);

	//	__android_log_print(ANDROID_LOG_INFO, "Msg", "uninstall successfully");

	(*env)->ReleaseStringUTFChars(env, apkName, str);

	return 0;
}

