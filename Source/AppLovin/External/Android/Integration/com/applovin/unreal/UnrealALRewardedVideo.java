package com.applovin.unreal;

import android.app.NativeActivity;

import com.applovin.sdk.AppLovinSdk;
import com.applovin.sdk.AppLovinSdkConfiguration;

import com.applovin.mediation.MaxAd;
import com.applovin.mediation.MaxAdListener;
import com.applovin.mediation.MaxRewardedAdListener;
import com.applovin.mediation.MaxReward;
import com.applovin.mediation.MaxError;
import com.applovin.mediation.MaxAdRevenueListener;
import com.applovin.mediation.ads.MaxRewardedAd;

import android.util.Log;
import java.util.Map;
import java.util.HashMap;
import java.lang.reflect.Method;

public class UnrealALRewardedVideo
{
    private static UnrealALRewardedVideoListener rewardedVideoListener;
    private static AppLovinSdk sdk;
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
    private native static void onAppLovinRevenueThunkCpp(double revenue, String network, String unitId, String placement, String country);
    
    static public void init(NativeActivity appActivity, AppLovinSdk appLovinSDK)
    {
        activity = appActivity;
        sdk = appLovinSDK;
        rewardedVideoListener = new UnrealALRewardedVideoListener();
        
        RewardedVideoAds = new HashMap<String, MaxRewardedAd>();
        
        Log.d("ApplovinLog", "Init Reward Class");
    }
    
    static private void createRewardedVideo(String uintId)
    {
        if(uintId == null) return;
        
        Log.d("ApplovinLog", "Init AppLovin RewardedVideo " + uintId);
            
        MaxRewardedAd Ad = MaxRewardedAd.getInstance( uintId, activity);
        
        Ad.setListener(rewardedVideoListener);
        Ad.setRevenueListener(rewardedVideoListener);
        
        RewardedVideoAds.put(uintId, Ad);
        
        Ad.loadAd();
        
    }
    
    static public void loadRewardedVideo(String uintId)
    {
        if(RewardedVideoAds == null || uintId == null) return;
        
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
        
        if(RewardedVideoAds == null || uintId == null) return;
        
        MaxRewardedAd Ad = RewardedVideoAds.get(uintId);
        
        if(Ad != null && Ad.isReady()){
            Ad.showAd();
        }
        else {
            Log.d("ApplovinLog", "No RewardedVideo ad or it is not ready! Load it!");
        }
    }
    
    private static class UnrealALRewardedVideoListener
        implements MaxRewardedAdListener, MaxAdRevenueListener
    {
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
        
        @Override
        public void onAdRevenuePaid(final MaxAd ad)
        {
            if(ad == null){
                onAppLovinRevenueThunkCpp(0.0, "", "", "", "");
                return;
            }
            
            double revenue = ad.getRevenue(); // In USD
            
            // Miscellaneous data
            String countryCode = sdk.getConfiguration().getCountryCode(); // "US" for the United States, etc - Note: Do not confuse this with currency code which is "USD" in most cases!
            String networkName = ad.getNetworkName(); // Display name of the network that showed the ad (e.g. "AdColony")
            String adUnitId = ad.getAdUnitId(); // The MAX Ad Unit ID
            String placement = ad.getPlacement(); // The placement this ad's postbacks are tied to
            String networkPlacement = ad.getNetworkPlacement(); // The placement ID from the network that showed the ad
            
            Log.d("ApplovinLog", "RewardedVideo revenue: " + revenue + " adunitID: " + adUnitId);
            
            onAppLovinRevenueThunkCpp(revenue, networkName, adUnitId, placement, countryCode);
        }
    }

}
