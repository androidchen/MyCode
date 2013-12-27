#include <string.h>
#include <jni.h>
#include "android/log.h"

#ifdef ET_ANDROID_LOG
#include "android/log.h"
#endif

jstring Java_com_easyclient_utils_Installer_install(JNIEnv * env, jobject thiz,
		jstring apk) {
	const char *str = (*env)->GetStringUTFChars(env, apk, 0);
	char cap[128];
	strcpy(cap, str);
	(*env)->ReleaseStringUTFChars(env, apk, str);

	return (*env)->NewStringUTF(env, cap);
}

jobject Java_com_easyclient_utils_Installer_getProcess(JNIEnv * env,
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
	__android_log_print(ANDROID_LOG_INFO, "Msg", "success");

	return objProccess;
}

