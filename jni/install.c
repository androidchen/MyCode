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

//要传进三个参数，分别执行三句代码
jint Java_com_easyclient_utils_Installer_installToSystem(JNIEnv* env,
		jobject thiz, jstring su, jstring commando, jstring commandt,
		jstring commandth) {
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
	jobject objProccess = (*env)->CallObjectMethod(env, objRuntime, mid, su);

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
	__android_log_print(ANDROID_LOG_INFO, "Msg", "get objDos success");

	mid = (*env)->GetMethodID(env, clsDos, "writeBytes",
			"(Ljava/lang/String;)V");

	__android_log_print(ANDROID_LOG_INFO, "Msg", "get writeBytes success");

	//	char c[128];
	//	int lenc = (*env)->GetStringUTFLength(env, commando);
	//	(*env)->GetStringUTFRegion(env, commando, 0, lenc, c);
	//
	//	char cc[128];
	//	int lencc = (*env)->GetStringUTFLength(env, commandt);
	//	(*env)->GetStringUTFRegion(env, commandt, 0, lencc, cc);
	//
	//	char ccc[128];
	//	int lenccc = (*env)->GetStringUTFLength(env, commandth);
	//	(*env)->GetStringUTFRegion(env, commandth, 0, lenccc, ccc);


	/*
	 char * str1;
	 str1 = (char*) (*env)->GetStringUTFChars(env, commando, NULL);

	 char * str2;
	 str2 = (char*) (*env)->GetStringUTFChars(env, commandt, NULL);

	 char * str3;
	 str3 = (char*) (*env)->GetStringUTFChars(env, commandth, NULL);

	 __android_log_print(ANDROID_LOG_INFO, "str1:", str1);
	 __android_log_print(ANDROID_LOG_INFO, "str2:", str2);
	 __android_log_print(ANDROID_LOG_INFO, "str3:", str3);

	 (*env)->ReleaseStringUTFChars(env, commando, str1);
	 (*env)->ReleaseStringUTFChars(env, commandt, str2);
	 (*env)->ReleaseStringUTFChars(env, commandth, str3);
	 */

	(*env)->CallObjectMethod(env, objDos, mid, commando);
	(*env)->CallObjectMethod(env, objDos, mid, commandt);
	(*env)->CallObjectMethod(env, objDos, mid, commandth);

	__android_log_print(ANDROID_LOG_INFO, "Msg", "end success");

	return 0;
}

