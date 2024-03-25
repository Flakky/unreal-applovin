package com.applovin.unreal;

import android.app.NativeActivity;

import com.applovin.sdk.AppLovinPrivacySettings;
import com.applovin.sdk.AppLovinSdkConfiguration;
import com.applovin.sdk.*;

import android.util.Log;

public class UnrealALPrivacy
{
    private static NativeActivity activity;
    private static AppLovinSdkConfiguration configuration;
    
    private native static void onCmpCompletedThunkCpp();
    private native static void onCmpErrorThunkCpp(int errorCode, String errorMessage);
    
    static public void init(NativeActivity appActivity, AppLovinSdkConfiguration alconfiguration)
    {
        activity = appActivity;
        configuration = alconfiguration;
    }
    
    static public void setHasUserConsent(boolean HasUserConsent)
    {
        AppLovinPrivacySettings.setHasUserConsent( HasUserConsent, activity );
        
        Log.d("ApplovinLog", "Set Has User Content");
    }
    
    static public void setIsAgeRestrictedUser(boolean HasUserConsent)
    {
        AppLovinPrivacySettings.setIsAgeRestrictedUser( HasUserConsent, activity );
        
        Log.d("ApplovinLog", "Set Is Age Restricted User");
    }
    
    static public void setDoNotSell(boolean HasUserConsent)
    {
        AppLovinPrivacySettings.setDoNotSell( HasUserConsent, activity );
        
        Log.d("ApplovinLog", "Set Do Not Sell");
    }
    
    static public boolean doesUserApplyToGDPR()
    {
        return configuration.getConsentDialogState() == AppLovinSdkConfiguration.ConsentDialogState.APPLIES;
    }
    
    public static void showCmpForExistingUser(){
        Log.d("ApplovinLog", "Show Cmp For Existing User");
        
        AppLovinCmpService cmpService = AppLovinSdk.getInstance( activity ).getCmpService();
        
        cmpService.showCmpForExistingUser( activity, new AppLovinCmpService.OnCompletedListener()
        {
            @Override
            public void onCompleted(final AppLovinCmpError error)
            {
                if ( error == null )
                {
                    Log.d("ApplovinLog", "Cmp completed");
                    onCmpCompletedThunkCpp();
                }
                else 
                {
                    Log.w("ApplovinLog", "Cmp error '"+error.getCode()+"': "+error.getMessage());
                    onCmpErrorThunkCpp(error.getCode().getValue(), error.getMessage());
                }
            }
        } );
    }
    
}
