LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := install
LOCAL_SRC_FILES := install.c

LOCAL_LDLIBS := -lm -llog 

include $(BUILD_SHARED_LIBRARY)