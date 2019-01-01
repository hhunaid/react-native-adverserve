package com.dudigital.reactnative.adverserve

import com.facebook.react.uimanager.SimpleViewManager
import com.adition.android.sdk.AditionView
import com.facebook.react.uimanager.ThemedReactContext

class AdBannerManager : SimpleViewManager<AditionView>() {
    companion object {
        const val REACT_CLASS = "RCTAdBanner"
        const val networkID = "3360"
        const val contentId = "4339620"
    }

    override fun createViewInstance(reactContext: ThemedReactContext?): AditionView {
        return AditionView(reactContext, contentId, networkID, true)
    }

    override fun getName(): String {
        return REACT_CLASS
    }

}