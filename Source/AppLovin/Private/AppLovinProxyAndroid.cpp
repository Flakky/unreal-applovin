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
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealAppLovin");
	if(!Class) return;
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "showDebugger", "()V", false);
	if(!Method) return;
	
	Env->CallStaticVoidMethod(Class, Method);
	Env->DeleteGlobalRef(Class);
}

void UAppLovinProxyAndroid::ShowRewardedVideo(FString Placement)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALRewardedVideo");
	if(!Class) return;

	jstring PlacementParam = Env->NewStringUTF(TCHAR_TO_UTF8(*Placement));
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "showRewardedVideo", "(Ljava/lang/String;)V", false);
	if(!Method) return;
	
	Env->CallStaticVoidMethod(Class, Method, PlacementParam);

	Env->DeleteLocalRef(PlacementParam);
	Env->DeleteGlobalRef(Class);
}

void UAppLovinProxyAndroid::LoadRewardedVideo(FString Placement)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALRewardedVideo");
	if(!Class) return;

	jstring PlacementParam = Env->NewStringUTF(TCHAR_TO_UTF8(*Placement));
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "loadRewardedVideo", "(Ljava/lang/String;)V", false);
	if(!Method) return;
	
	Env->CallStaticVoidMethod(Class, Method, PlacementParam);

	Env->DeleteLocalRef(PlacementParam);
	Env->DeleteGlobalRef(Class);
}

void UAppLovinProxyAndroid::ShowInterstitial(FString Placement)
{
	UE_LOG(LogTemp, Log, TEXT("Applovin Show interstitial"));
	
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALInterstitial");
	if(!Class) return;

	jstring PlacementParam = Env->NewStringUTF(TCHAR_TO_UTF8(*Placement));
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "showInterstitial", "(Ljava/lang/String;)V", false);
	if(!Method) return;
	
	Env->CallStaticVoidMethod(Class, Method, PlacementParam);

	Env->DeleteLocalRef(PlacementParam);
	Env->DeleteGlobalRef(Class);

	UE_LOG(LogTemp, Log, TEXT("Applovin Shown interstitial"));
}

void UAppLovinProxyAndroid::LoadInterstitial(FString Placement)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALInterstitial");
	if(!Class) return;

	jstring PlacementParam = Env->NewStringUTF(TCHAR_TO_UTF8(*Placement));
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "loadInterstitial", "(Ljava/lang/String;)V", false);
	if(!Method) return;
	
	Env->CallStaticVoidMethod(Class, Method, PlacementParam);

	Env->DeleteLocalRef(PlacementParam);
	Env->DeleteGlobalRef(Class);
}

void UAppLovinProxyAndroid::SetPrivacyHasUserConsent(bool HasUserConsent)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALPrivacy");
	if(!Class) return;
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "setHasUserConsent", "(Z)V", false);
	if(!Method) return;
	
	Env->CallStaticVoidMethod(Class, Method, HasUserConsent);

	Env->DeleteGlobalRef(Class);
}
	
void UAppLovinProxyAndroid::SetPrivacyAgeRestrictedUser(bool IsAgeRestrictedUser)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALPrivacy");
	if(!Class) return;
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "setIsAgeRestrictedUser", "(Z)V", false);
	if(!Method) return;
	
	Env->CallStaticVoidMethod(Class, Method, IsAgeRestrictedUser);
	
	Env->DeleteGlobalRef(Class);
}

void UAppLovinProxyAndroid::SetPrivacyDoNotSell(bool DoNotSell)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALPrivacy");
	if(!Class) return;
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "setDoNotSell", "(Z)V", false);
	if(!Method) return;
	
	Env->CallStaticVoidMethod(Class, Method, DoNotSell);

	Env->DeleteGlobalRef(Class);
}

bool UAppLovinProxyAndroid::DoesUserApplyToGDPR()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return false;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALPrivacy");
	if(!Class) return false;
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "doesUserApplyToGDPR", "()Z", false);
	if(!Method) return false;
	
	jboolean Out = Env->CallStaticBooleanMethod(Class, Method);

	Env->DeleteGlobalRef(Class);

	return (bool)Out;
}

void UAppLovinProxyAndroid::ShowCmpForExistingUser()
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (!Env) return;
	
	jclass Class = FAndroidApplication::FindJavaClassGlobalRef("com/applovin/unreal/UnrealALPrivacy");
	if(!Class) return;
	
	static auto Method = FJavaWrapper::FindStaticMethod(Env, Class, "showCmpForExistingUser", "()V", false);
	if(!Method) return;
	
	Env->CallStaticVoidMethod(Class, Method);

	Env->DeleteGlobalRef(Class);
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
	const FString Error = FJavaHelper::FStringFromParam(jenv, errorMessage);
	AsyncTask(ENamedThreads::GameThread, [jenv, Code, Error]() {
		Proxy->OnRewardedVideoErrorEvent.Broadcast(EAppLovinRewardedErrorEventType::FailedToLoad, Code, Error);
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALRewardedVideo_onRewardedVideoAdShowFailedThunkCpp(JNIEnv* jenv, jobject thiz, jint errorCode, jstring errorMessage)
{
	int Code = (int)errorCode;
	const FString Error = FJavaHelper::FStringFromParam(jenv, errorMessage);
	AsyncTask(ENamedThreads::GameThread, [jenv, Code, Error]() {
		Proxy->OnRewardedVideoErrorEvent.Broadcast(EAppLovinRewardedErrorEventType::FailedToShow, Code, Error);
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
	const FString Error = FJavaHelper::FStringFromParam(jenv, errorMessage);
	AsyncTask(ENamedThreads::GameThread, [Code, Error]() {
		Proxy->OnInterstitialErrorEvent.Broadcast(EAppLovinInterstitialErrorEventType::FailedToLoad, Code, Error);
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALRewardedVideo_onAppLovinRevenueThunkCpp(JNIEnv* jenv, jobject thiz, jdouble revenue, jstring network, jstring unitid, jstring placement, jstring country)
{
	FAppLovinRevenueInfo RevenueInfo;
	RevenueInfo.Revenue = (float)revenue;
	RevenueInfo.Network = FJavaHelper::FStringFromParam(jenv, network);
	RevenueInfo.UnitID = FJavaHelper::FStringFromParam(jenv, unitid);
	RevenueInfo.Placement = FJavaHelper::FStringFromParam(jenv, placement);
	RevenueInfo.Country = FJavaHelper::FStringFromParam(jenv, country);

	UE_LOG(LogTemp, Log, TEXT("AppLovin revenue: %f $ - %s. From %s"), RevenueInfo.Revenue, *RevenueInfo.UnitID, *RevenueInfo.Placement);
	
	AsyncTask(ENamedThreads::GameThread, [RevenueInfo]() {
		Proxy->OnRevenue.Broadcast(RevenueInfo);
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALInterstitial_onAppLovinRevenueThunkCpp(JNIEnv* jenv, jobject thiz, jdouble revenue, jstring network, jstring unitid, jstring placement, jstring country)
{
	FAppLovinRevenueInfo RevenueInfo;
	RevenueInfo.Revenue = (float)revenue;
	RevenueInfo.Network = FJavaHelper::FStringFromParam(jenv, network);
	RevenueInfo.UnitID = FJavaHelper::FStringFromParam(jenv, unitid);
	RevenueInfo.Placement = FJavaHelper::FStringFromParam(jenv, placement);
	RevenueInfo.Country = FJavaHelper::FStringFromParam(jenv, country);

	UE_LOG(LogTemp, Log, TEXT("AppLovin revenue: %f $ - %s. From %s"), RevenueInfo.Revenue, *RevenueInfo.UnitID, *RevenueInfo.Placement);
	
	AsyncTask(ENamedThreads::GameThread, [RevenueInfo]() {
		Proxy->OnRevenue.Broadcast(RevenueInfo);
	});
};

// Privacy callbacks

JNI_METHOD void Java_com_applovin_unreal_UnrealALPrivacy_onCmpCompletedThunkCpp(JNIEnv* jenv, jobject thiz)
{
	AsyncTask(ENamedThreads::GameThread, []()
	{
		Proxy->OnCmpCompleted.Broadcast();
	});
};

JNI_METHOD void Java_com_applovin_unreal_UnrealALPrivacy_onCmpErrorThunkCpp(JNIEnv* jenv, jobject thiz, jint errorCode, jstring errorMessage)
{
	int Code = (int)errorCode;
	const FString Error = FJavaHelper::FStringFromParam(jenv, errorMessage);
	AsyncTask(ENamedThreads::GameThread, [jenv, Code, Error]()
	{
		Proxy->OnCmpError.Broadcast(Code, Error);
	});
};

#endif