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
			Bundles.Add("PAGAdSDK", "PAGAdSDK.bundle");
			Bundles.Add("YandexMobileAds", "YandexMobileAdsBundle.bundle");

			List<string> IgnoreFrameworks = new List<string>();
			
			// Ignore some frameworks because of a collision with other plugins. Or by any other reason
			// IgnoreFrameworks.Add("FBLPromises");
			// IgnoreFrameworks.Add("GoogleAppMeasurement");
			// IgnoreFrameworks.Add("GoogleAppMeasurementIdentitySupport");
			// IgnoreFrameworks.Add("GoogleUtilities");
			// IgnoreFrameworks.Add("nanopb");
			// IgnoreFrameworks.Add("YandexMobileMetrica");
			// IgnoreFrameworks.Add("YandexMobileMetricaCrashes");
			// IgnoreFrameworks.Add("FBAudienceNetwork");

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

			string XcodeRoot = Utils.RunLocalProcessAndReturnStdOut("/usr/bin/xcode-select", "--print-path");
			string SwiftStandardLibraryLinkPath = XcodeRoot + "/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/iphoneos";

			// Enable Swift
			PublicSystemLibraryPaths.AddRange(
				new string[] {
					SwiftStandardLibraryLinkPath,
					"/usr/lib/swift"
				}
			);

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
