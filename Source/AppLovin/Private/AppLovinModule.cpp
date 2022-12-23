// Copyright Epic Games, Inc. All Rights Reserved.

#include "AppLovinModule.h"
#include "AppLovinSettings.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Package.h"
#include "ISettingsModule.h"

#include "AppLovinProxyTest.h"

#if PLATFORM_ANDROID
#include "AppLovinProxyAndroid.h"
#elif PLATFORM_IOS
#include "AppLovinProxyIOS.h"
#endif

#define LOCTEXT_NAMESPACE "FAppLovinModule"

void FAppLovinModule::StartupModule()
{
	AppLovinSettings = NewObject<UAppLovinSettings>(GetTransientPackage(), "AppLovinSettings", RF_Standalone);
	AppLovinSettings->AddToRoot();

	// Register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "AppLovin",
			LOCTEXT("RuntimeSettingsName", "AppLovin"),
			LOCTEXT("RuntimeSettingsDescription", "Configure App Lovin plugin"),
			AppLovinSettings);
	}
	
	UClass* ProxyClass;

#if PLATFORM_ANDROID
	ProxyClass = UAppLovinProxyAndroid::StaticClass();
#elif PLATFORM_IOS
    ProxyClass = UAppLovinProxyIOS::StaticClass();
#else
	ProxyClass = UAppLovinProxy::StaticClass();
#endif

#if !UE_BUILD_SHIPPING
	if(WITH_EDITOR || !AppLovinSettings->UseLibraryInDevBuilds)
	{
		ProxyClass = UAppLovinProxyTest::StaticClass();
	}
#endif	

	AppLovinProxy = NewObject<UAppLovinProxy>(GetTransientPackage(), ProxyClass);
	AppLovinProxy->AddToRoot();
}

void FAppLovinModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "AppLovin");
	}

	if (!GExitPurge)
	{
		// If we're in exit purge, this object has already been destroyed
		AppLovinSettings->RemoveFromRoot();
	}
	else
	{
		AppLovinSettings = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAppLovinModule, AppLovin)