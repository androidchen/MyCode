/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_easyclient_utils_Installer */

#ifndef _Included_com_easyclient_utils_Installer
#define _Included_com_easyclient_utils_Installer
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_easyclient_utils_Installer
 * Method:    install
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easyclient_utils_Installer_install
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_easyclient_utils_Installer
 * Method:    getProcess
 * Signature: (Ljava/lang/String;)Ljava/lang/Process;
 */
JNIEXPORT jobject JNICALL Java_com_easyclient_utils_Installer_getProcess
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_easyclient_utils_Installer
 * Method:    installToSystem
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_easyclient_utils_Installer_installToSystem
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
