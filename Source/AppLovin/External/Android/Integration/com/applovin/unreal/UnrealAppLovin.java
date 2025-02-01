package com.applovin.unreal;

import android.app.NativeActivity;
import android.util.Log;
import android.net.Uri;

import com.applovin.sdk.*;

import com.applovin.unreal.UnrealALRewardedVideo;
import com.applovin.unreal.UnrealALInterstitial;
import com.applovin.unreal.UnrealALPrivacy;

public class UnrealAppLovin
{
    private static UnrealAppLovin unrealAL;
    private static AppLovinSdk sdk = null;
    private static boolean initialized = false;
    private static NativeActivity activity = null;
    private static UnrealAppLovinInitParams initParams;
    
    private native static void onInitThunkCpp();
    
    static public class UnrealAppLovinInitParams{
        public boolean enableConsentFlow = false;
        public String privacyPolicyURL = "";
        public String termsOfServiceURL = "";
    }
    
    public static void setParams(NativeActivity appActivity, UnrealAppLovinInitParams params)
    {
        initParams = params;
        activity = appActivity;
    }

    public static void init()
    {
        if(initialized) return;
        
        sdk = AppLovinSdk.getInstance(activity);
        
        sdk.setMediationProvider(AppLovinMediationProvider.MAX);
        
        AppLovinSdkSettings settings = new AppLovinSdkSettings(activity);
        settings.getTermsAndPrivacyPolicyFlowSettings().setEnabled(initParams.enableConsentFlow);
        settings.getTermsAndPrivacyPolicyFlowSettings().setPrivacyPolicyUri(Uri.parse(initParams.privacyPolicyURL));
        settings.getTermsAndPrivacyPolicyFlowSettings().setTermsOfServiceUri(Uri.parse(initParams.termsOfServiceURL));
        
        AppLovinSdk.initializeSdk(activity, new AppLovinSdk.SdkInitializationListener() {
            @Override
            public void onSdkInitialized(final AppLovinSdkConfiguration configuration)
            {
                UnrealALRewardedVideo.init(activity, sdk);
                UnrealALInterstitial.init(activity, sdk);
                
                UnrealALPrivacy.init(activity, configuration);
                
                initialized = true;
                
                onInitThunkCpp();
            }
        });
    }
    
    public static void showDebugger(){
        Log.d("ApplovinLog", "Show debugger");
        sdk.showMediationDebugger();
    }
    
}