package com.applovin.unreal;

import android.app.NativeActivity;

import com.applovin.sdk.AppLovinSdk;
import com.applovin.sdk.AppLovinSdkConfiguration;

import com.applovin.mediation.MaxAd;
import com.applovin.mediation.MaxAdListener;
import com.applovin.mediation.MaxRewardedAdListener;
import com.applovin.mediation.MaxReward;
import com.applovin.mediation.MaxError;
import com.applovin.mediation.ads.MaxRewardedAd;

import android.util.Log;
import java.util.Map;
import java.util.HashMap;
import java.lang.reflect.Method;

public class UnrealALRewardedVideo
{
    private static NativeActivity activity;
    private static Map<String, MaxRewardedAd> RewardedVideoAds;
    
    private native static void onRewardedVideoAdLoadedThunkCpp();
    private native static void onRewardedVideoAdShowedThunkCpp();
    private native static void onRewardedVideoAdClosedThunkCpp();
    private native static void onRewardedVideoAdLoadFailedThunkCpp(int errorCode, String errorMessage);
    private native static void onRewardedVideoAdShowFailedThunkCpp(int errorCode, String errorMessage);
    private native static void onRewardedVideoAdClickedThunkCpp();
    private native static void onRewardedVideoAdRewardedThunkCpp();
    private native static void onRewardedVideoAdStartedThunkCpp();
    private native static void onRewardedVideoAdCompletedThunkCpp();
    
    static public void init(NativeActivity appActivity)
    {
        activity = appActivity;
        
        RewardedVideoAds = new HashMap<String, MaxRewardedAd>();
        
        Log.d("ApplovinLog", "Init Reward Class");
    }
    
    static private void createRewardedVideo(String uintId)
    {
        Log.d("ApplovinLog", "Init AppLovin RewardedVideo");
            
        MaxRewardedAd Ad = MaxRewardedAd.getInstance( uintId, activity);
        
        MaxRewardedAdListener AdListener = new MaxRewardedAdListener(){
        
            @Override
            public void onAdLoaded(final MaxAd maxAd)
            {
                Log.d("ApplovinLog", "Loaded Rewarded ad");
                    
                // Rewarded ad is ready to be shown. RewardedVideoAd.isReady() will now return 'true'
                onRewardedVideoAdLoadedThunkCpp();
            }
                
            @Override
            public void onAdLoadFailed(final String adUnitId, final MaxError error)
            {
                Log.d("ApplovinLog", "Load Rewarded failed: "+error.getCode()+" msg: "+error.getMessage());
                
                // RewardedVideo ad failed to load 
                // We recommend retrying with exponentially higher delays up to a maximum delay (in this case 64 seconds)
                onRewardedVideoAdLoadFailedThunkCpp(error.getCode(), error.getMessage());
                
            }
        
            @Override
            public void onAdDisplayFailed(final MaxAd maxAd, final MaxError error)
            {
                Log.d("ApplovinLog", "Show Rewarded failed: "+error.getCode()+" msg: "+error.getMessage());
                onRewardedVideoAdShowFailedThunkCpp(error.getCode(), error.getMessage());
            }
        
            @Override
            public void onAdDisplayed(final MaxAd maxAd) 
            {
                Log.d("ApplovinLog", "Displayed Rewarded ad");
                onRewardedVideoAdShowedThunkCpp();
            }
        
            @Override
            public void onAdClicked(final MaxAd maxAd) 
            {
                Log.d("ApplovinLog", "Clicked Rewarded ad");
                onRewardedVideoAdClickedThunkCpp();
            }
        
            @Override
            public void onAdHidden(final MaxAd maxAd)
            {
                Log.d("ApplovinLog", "Hide Rewarded ad");
                onRewardedVideoAdClosedThunkCpp();
            }
            
            @Override
            public void onRewardedVideoStarted(final MaxAd maxAd) 
            {
                Log.d("ApplovinLog", "Started Rewarded ad");
                onRewardedVideoAdStartedThunkCpp();
            }
        
            @Override
            public void onRewardedVideoCompleted(final MaxAd maxAd) 
            {
                Log.d("ApplovinLog", "Completed Rewarded ad");
                onRewardedVideoAdCompletedThunkCpp();
            }
        
            @Override
            public void onUserRewarded(final MaxAd maxAd, final MaxReward maxReward)
            {
                Log.d("ApplovinLog", "User Rewarded by ad");
                // Rewarded ad was displayed and user should receive the reward
                onRewardedVideoAdRewardedThunkCpp();
            }
        };
        
        Ad.setListener(AdListener);
        
        RewardedVideoAds.put(uintId, Ad);
        
        Ad.loadAd();
        
    }
    
    static public void loadRewardedVideo(String uintId)
    {
        Log.d("ApplovinLog", "Load RewardedVideo ad " + uintId);
        
        MaxRewardedAd Ad = RewardedVideoAds.get(uintId);
        if(Ad != null){
            Ad.loadAd();
        }
        else{
            createRewardedVideo(uintId);
        }
    }
    
    static public void showRewardedVideo(String uintId)
    {
        Log.d("ApplovinLog", "Show RewardedVideo ad " + uintId);
        MaxRewardedAd Ad = RewardedVideoAds.get(uintId);
        
        if(Ad != null && Ad.isReady()){
            Ad.showAd();
        }
        else {
            Log.d("ApplovinLog", "No RewardedVideo ad or it is not ready! Load it!");
        }
    }
}
