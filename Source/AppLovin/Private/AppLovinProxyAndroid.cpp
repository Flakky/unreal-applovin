// Copyright Epic Games, Inc. All Rights Reserved.

#if PLATFORM_ANDROID

#include "AppLovinProxyAndroid.h"

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include <android_native_app_glue.h>

#include "Async/Async.h"

UAppLovinProxy* Proxy;

void UAppLovinProxyAndroid::Init()
{
	Proxy = this;
}

void UAppLovinProxyAndroid::ShowDebugger()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	static auto Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_AppLovinShowDebugger", "()V", false);
	
	Env->CallVoidMethod(FJavaWrapper::GameActivityThis, Method);
}

void UAppLovinProxyAndroid::ShowRewardedVideo(FString Placement)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALRewardedVideo");
	if(!Class) return;

	jstring PlacementParam = Env->NewStringUTF(TCHAR_TO_UTF8(*Placement));
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "showRewardedVideo", "(Ljava/lang/String;)V", false);
	
	Env->CallStaticVoidMethod(Class, Method, PlacementParam);

	Env->DeleteLocalRef(PlacementParam);
}

void UAppLovinProxyAndroid::LoadRewardedVideo(FString Placement)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALRewardedVideo");
	if(!Class) return;

	jstring PlacementParam = Env->NewStringUTF(TCHAR_TO_UTF8(*Placement));
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "loadRewardedVideo", "(Ljava/lang/String;)V", false);
	
	Env->CallStaticVoidMethod(Class, Method, PlacementParam);

	Env->DeleteLocalRef(PlacementParam);
}

void UAppLovinProxyAndroid::ShowInterstitial(FString Placement)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALInterstitial");
	if(!Class) return;

	jstring PlacementParam = Env->NewStringUTF(TCHAR_TO_UTF8(*Placement));
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "showInterstitial", "(Ljava/lang/String;)V", false);
	
	Env->CallStaticVoidMethod(Class, Method, PlacementParam);

	Env->DeleteLocalRef(PlacementParam);
	
}

void UAppLovinProxyAndroid::LoadInterstitial(FString Placement)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALInterstitial");
	if(!Class) return;

	jstring PlacementParam = Env->NewStringUTF(TCHAR_TO_UTF8(*Placement));
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "loadInterstitial", "(Ljava/lang/String;)V", false);
	
	Env->CallStaticVoidMethod(Class, Method, PlacementParam);

	Env->DeleteLocalRef(PlacementParam);
	
}

void UAppLovinProxyAndroid::SetPrivacyHasUserConsent(bool HasUserConsent)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALPrivacy");
	if(!Class) return;
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "setHasUserConsent", "(Z)V", false);
	
	Env->CallStaticVoidMethod(Class, Method, HasUserConsent);
}
	
void UAppLovinProxyAndroid::SetPrivacyAgeRestrictedUser(bool IsAgeRestrictedUser)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALPrivacy");
	if(!Class) return;
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "setIsAgeRestrictedUser", "(Z)V", false);
	
	Env->CallStaticVoidMethod(Class, Method, IsAgeRestrictedUser);
}

void UAppLovinProxyAndroid::SetPrivacyDoNotSell(bool DoNotSell)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALPrivacy");
	if(!Class) return;
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "setDoNotSell", "(Z)V", false);
	
	Env->CallStaticVoidMethod(Class, Method, DoNotSell);
}

bool UAppLovinProxyAndroid::DoesUserApplyToGDPR()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return false;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALPrivacy");
	if(!Class) return false;
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "doesUserApplyToGDPR", "()Z", false);
	
	jboolean Out = Env->CallStaticBooleanMethod(Class, Method);

	return (bool)Out;
}

// Rewarded video callbacks

JNI_METHOD void Java_com_applovin_unreal_UnrealALRewardedVideo_onRewardedVideoAdLoadedThunkCpp(JNIEnv* jenv, jobject thiz)
{
	AsyncTask(ENamedThreads::GameThread, []()
	{
		Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Loaded);
	});	
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALRewardedVideo_onRewardedVideoAdShowedThunkCpp(JNIEnv* jenv, jobject thiz)
{
	AsyncTask(ENamedThreads::GameThread, []() {
		Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Showed);
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALRewardedVideo_onRewardedVideoAdClosedThunkCpp(JNIEnv* jenv, jobject thiz)
{
	AsyncTask(ENamedThreads::GameThread, []() {
		Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Closed);
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALRewardedVideo_onRewardedVideoAdClickedThunkCpp(JNIEnv* jenv, jobject thiz)
{
	AsyncTask(ENamedThreads::GameThread, []() {
		Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Clicked);
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALRewardedVideo_onRewardedVideoAdRewardedThunkCpp(JNIEnv* jenv, jobject thiz)
{
	AsyncTask(ENamedThreads::GameThread, []() {
		Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Rewarded);
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALRewardedVideo_onRewardedVideoAdStartedThunkCpp(JNIEnv* jenv, jobject thiz)
{
	AsyncTask(ENamedThreads::GameThread, []() {
		Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Started);
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALRewardedVideo_onRewardedVideoAdCompletedThunkCpp(JNIEnv* jenv, jobject thiz)
{
	AsyncTask(ENamedThreads::GameThread, []() {
		Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Completed);
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALRewardedVideo_onRewardedVideoAdLoadFailedThunkCpp(JNIEnv* jenv, jobject thiz, jint errorCode, jstring errorMessage)
{
	int Code = (int)errorCode;
	AsyncTask(ENamedThreads::GameThread, [Code]() {
		Proxy->OnRewardedVideoErrorEvent.Broadcast(EAppLovinRewardedErrorEventType::FailedToLoad, Code, "");
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALRewardedVideo_onRewardedVideoAdShowFailedThunkCpp(JNIEnv* jenv, jobject thiz, jint errorCode, jstring errorMessage)
{
	int Code = (int)errorCode;
	AsyncTask(ENamedThreads::GameThread, [Code]() {
		Proxy->OnRewardedVideoErrorEvent.Broadcast(EAppLovinRewardedErrorEventType::FailedToShow, Code, "");
	});
};

// Interstitial callbacks

JNI_METHOD void Java_com_applovin_unreal_UnrealALInterstitial_onInterstitialAdLoadedThunkCpp(JNIEnv* jenv, jobject thiz)
{
	AsyncTask(ENamedThreads::GameThread, []()
	{
		Proxy->OnInterstitialEvent.Broadcast(EAppLovinInterstitialEventType::Loaded);
	});	
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALInterstitial_onInterstitialAdShowedThunkCpp(JNIEnv* jenv, jobject thiz)
{
	AsyncTask(ENamedThreads::GameThread, []() {
		Proxy->OnInterstitialEvent.Broadcast(EAppLovinInterstitialEventType::Showed);
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALInterstitial_onInterstitialAdClosedThunkCpp(JNIEnv* jenv, jobject thiz)
{
	AsyncTask(ENamedThreads::GameThread, []() {
		Proxy->OnInterstitialEvent.Broadcast(EAppLovinInterstitialEventType::Closed);
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALInterstitial_onInterstitialAdClickedThunkCpp(JNIEnv* jenv, jobject thiz)
{
	AsyncTask(ENamedThreads::GameThread, []() {
		Proxy->OnInterstitialEvent.Broadcast(EAppLovinInterstitialEventType::Clicked);
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALInterstitial_onInterstitialAdLoadFailedThunkCpp(JNIEnv* jenv, jobject thiz, jint errorCode, jstring errorMessage)
{
	int Code = (int)errorCode;
	AsyncTask(ENamedThreads::GameThread, [Code]() {
		Proxy->OnInterstitialErrorEvent.Broadcast(EAppLovinInterstitialErrorEventType::FailedToLoad, Code, "");
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALInterstitial_onInterstitialAdShowFailedThunkCpp(JNIEnv* jenv, jobject thiz, jint errorCode, jstring errorMessage)
{
	int Code = (int)errorCode;
	AsyncTask(ENamedThreads::GameThread, [Code]() {
		Proxy->OnInterstitialErrorEvent.Broadcast(EAppLovinInterstitialErrorEventType::FailedToShow, Code, "");
	});
};


#endif