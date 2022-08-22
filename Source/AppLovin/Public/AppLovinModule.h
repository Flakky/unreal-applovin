// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class UAppLovinSettings;

class UAppLovinProxy;

class FAppLovinModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	UAppLovinSettings* AppLovinSettings;
	
	static inline FAppLovinModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FAppLovinModule>("AppLovin");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("AppLovin");
	}

public:
	
	UAppLovinProxy* AppLovinProxy;
};
