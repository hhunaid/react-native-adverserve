package com.dudigital.reactnative.adverserve

import android.os.Build
import android.webkit.CookieManager
import com.adition.android.sdk.DoNotTrackHelper
import com.adition.android.sdk.OptOutHelper
import com.facebook.react.bridge.*

class AdSDKHelperModule(context: ReactApplicationContext) : ReactContextBaseJavaModule(context) {
    companion object {
        const val MODULE_NAME = "AdSDKHelper"
    }

    override fun getName(): String {
        return MODULE_NAME
    }

    @ReactMethod
    fun optIn(networkId: String) {
        OptOutHelper(networkId).status = 1
    }

    @ReactMethod
    fun optOut(networkId: String) {
        OptOutHelper(networkId).status = 0
    }

    @ReactMethod
    fun getStatus(networkId: String, errorCallback: Callback, successCallback: Callback) {
        val status = OptOutHelper(networkId).status
        if (status == -1) {
            errorCallback.invoke("Couldn't fetch OptOut status")
        } else {
            successCallback.invoke(status)
        }
    }

    @ReactMethod
    fun enableLimitedTracking(isEnabled: Boolean) {
        DoNotTrackHelper(reactApplicationContext).enableLimitedTracking(isEnabled)
    }

    @ReactMethod
    fun isLimitedTrackingEnabled(errorCallback: Callback, successCallback: Callback) {
        successCallback(DoNotTrackHelper(reactApplicationContext).isLimitedTrackingEnabled)
    }

    @ReactMethod
    fun removeAllCookies() {
        if (Build.VERSION.SDK_INT >= 21) {
            CookieManager.getInstance().removeAllCookies(null)
        } else {
            CookieManager.getInstance().removeAllCookie()
        }

    }
}