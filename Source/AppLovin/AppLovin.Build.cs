// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.Collections.Generic;
using System.IO;
using Tools.DotNETCommon;
using UnrealBuildTool;

public class AppLovin : ModuleRules
{
	public AppLovin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "UMG" });
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
			);
		
		PrivateIncludePathModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Engine",
				"Settings"
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(PluginPath, "AppLovin_UPL_IOS.xml"));

			Dictionary<string, string> Bundles = new Dictionary<string, string>{};
			
			Bundles.Add("AppLovinSDK", "AppLovinSDKResources.bundle");
			Bundles.Add("PAGAdSDK", "AdsGlobalSDK.bundle");
			Bundles.Add("FBAudienceNetwork", "FBAudienceNetwork.bundle");
			Bundles.Add("IASDKCore", "Fyber_Marketplace_SDK.bundle");
			Bundles.Add("GoogleMobileAds", "GoogleMobileAdsResources.bundle");
			Bundles.Add("IronSource", "IronSourcePrivacyInfo.bundle");
			Bundles.Add("MTGSDK", "MTGSDK.bundle");
			Bundles.Add("UnityAds", "UnityAdsResources.bundle");
			Bundles.Add("UserMessagingPlatform", "UserMessagingPlatformResources.bundle");
			Bundles.Add("VungleAdsSDK", "VungleAds.bundle");

			List<string> IgnoreFrameworks = new List<string>();
			
			// Ignore some frameworks because of a collision with other plugins. Or by any other reason
			IgnoreFrameworks.Add("FBLPromises");
			IgnoreFrameworks.Add("GoogleAppMeasurement");
			IgnoreFrameworks.Add("GoogleAppMeasurementIdentitySupport");
			IgnoreFrameworks.Add("GoogleUtilities");
			IgnoreFrameworks.Add("nanopb");
            IgnoreFrameworks.Add("FBAudienceNetwork");
            IgnoreFrameworks.Add("IronSource");
            IgnoreFrameworks.Add("libIronSourceAdapter");
            IgnoreFrameworks.Add("libByteDanceAdapter");
			
			// We do not need Amazon, Yandex and Smaato yet 
			IgnoreFrameworks.Add("DTBiOSSDK");
			IgnoreFrameworks.Add("libAmazonAdMarketplaceAdapter");
			IgnoreFrameworks.Add("libYandexAdapter");
			IgnoreFrameworks.Add("YandexMobileMetrica");
			IgnoreFrameworks.Add("YandexMobileMetricaCrashes");
			IgnoreFrameworks.Add("YandexMobileAds");
			IgnoreFrameworks.Add("libSmaatoAdapter");
			IgnoreFrameworks.Add("OMSDK_Smaato");
			IgnoreFrameworks.Add("SmaatoSDKBanner");
			IgnoreFrameworks.Add("SmaatoSDKCore");
			IgnoreFrameworks.Add("SmaatoSDKInAppBidding");
			IgnoreFrameworks.Add("SmaatoSDKInterstitial");
			IgnoreFrameworks.Add("SmaatoSDKNative");
			IgnoreFrameworks.Add("SmaatoSDKOpenMeasurement");
			IgnoreFrameworks.Add("SmaatoSDKOutstream");
			IgnoreFrameworks.Add("SmaatoSDKRewardedAds");
			IgnoreFrameworks.Add("SmaatoSDKRichMedia");
			IgnoreFrameworks.Add("SmaatoSDKVideo");

			string FrameworksPath = Path.Combine(ModuleDirectory, "../../ThirdParty/iOS");

			DirectoryInfo directoryInfo = new DirectoryInfo(FrameworksPath);

			// Search for files ending with .embeddedframework.zip
			FileInfo[] files = directoryInfo.GetFiles("*.embeddedframework.zip", SearchOption.AllDirectories);

			// List the found files
			foreach (FileInfo file in files)
			{
				string Framework = file.Name.Split(new string[] { ".embeddedframework.zip" }, StringSplitOptions.None)[0];
				
				if(IgnoreFrameworks.Contains(Framework)) continue;
				
				string bundle;
				
				if (Bundles.TryGetValue(Framework, out bundle))
				{
					PublicAdditionalFrameworks.Add(new Framework(Framework, file.FullName, bundle));
				}
				else
				{
					PublicAdditionalFrameworks.Add(new Framework(Framework, file.FullName));
				}

				Log.TraceInformation("Applovin '"+Framework+"' framework added");
			}

			PublicSystemLibraries.Add("c++");
			PublicSystemLibraries.Add("z");
			PublicSystemLibraries.Add("bz2");
			PublicSystemLibraries.Add("c++abi");
			PublicSystemLibraries.Add("resolv");
			PublicSystemLibraries.Add("sqlite3");
			PublicSystemLibraries.Add("xml2");
			PublicSystemLibraries.Add("iconv");
            
			AddEngineThirdPartyPrivateStaticDependencies( Target, "zlib" );

			PublicFrameworks.AddRange(
			new string[]
			{
				"AdSupport",
				"AudioToolbox",
				"AVFoundation",
				"CFNetwork",
				"CoreGraphics",
				"CoreMedia",
				"CoreMotion",
				"CoreTelephony",
				"MessageUI",
				"SafariServices",
				"StoreKit",
				"SystemConfiguration",
				"UIKit",
				"WebKit"
			});

			// Enable Swift
            string SDKROOT = Utils.RunLocalProcessAndReturnStdOut("/usr/bin/xcrun", "--sdk iphoneos --show-sdk-path");
            PublicSystemLibraryPaths.Add(SDKROOT + "/usr/lib/swift");
            PublicSystemLibraryPaths.Add(SDKROOT + "../../../../../../Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/iphoneos");
            PublicSystemLibraryPaths.Add(SDKROOT + "../../../../../../Toolchains/XcodeDefault.xctoolchain/usr/lib/swift-5.0/iphoneos");
            PublicSystemLibraryPaths.Add(SDKROOT + "../../../../../../Toolchains/XcodeDefault.xctoolchain/usr/lib/swift-5.5/iphoneos");

		}

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Launch"
			});

			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "AppLovin_UPL_Android.xml"));
		}
	}
}
