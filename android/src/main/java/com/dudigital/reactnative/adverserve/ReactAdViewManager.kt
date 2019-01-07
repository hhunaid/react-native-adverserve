package com.dudigital.reactnative.adverserve

import com.facebook.react.common.MapBuilder
import com.facebook.react.uimanager.SimpleViewManager
import com.facebook.react.uimanager.ThemedReactContext
import com.facebook.react.uimanager.annotations.ReactProp

class ReactAdViewManager : SimpleViewManager<ReactAdView>() {
    companion object {
        const val REACT_CLASS = "RCTAdBanner"
        const val CONTENT_ID_PROP = "contentUnitId"
        const val NETWORK_ID_PROP = "networkId"
        const val IS_INLINE_PROP = "isInline"
        const val GDPR_APPLIES_PROP = "gdprApplies"
    }

    override fun createViewInstance(reactContext: ThemedReactContext): ReactAdView {
        return ReactAdView(reactContext)
    }

    override fun getName(): String {
        return REACT_CLASS
    }

    override fun getExportedCustomDirectEventTypeConstants(): MutableMap<String, Any> {
        return MapBuilder.of(
                ReactAdView.AD_CLICKED_EVENT,
                MapBuilder.of("registrationName", ReactAdView.AD_CLICKED_EVENT),
                ReactAdView.AD_LOADED_EVENT,
                MapBuilder.of("registrationName", ReactAdView.AD_LOADED_EVENT),
                ReactAdView.BEFORE_AD_SDK_EVENT,
                MapBuilder.of("registrationName", ReactAdView.BEFORE_AD_SDK_EVENT),
                ReactAdView.ON_SDK_EVENT,
                MapBuilder.of("registrationName", ReactAdView.ON_SDK_EVENT),
                ReactAdView.ON_SDK_ERROR,
                MapBuilder.of("registrationName", ReactAdView.ON_SDK_ERROR),
                ReactAdView.ON_AD_FIRED_EVENT,
                MapBuilder.of("registrationName", ReactAdView.ON_AD_FIRED_EVENT))
    }

    @ReactProp(name = CONTENT_ID_PROP)
    fun setContentId(adView: ReactAdView, contentId: String) {
        adView.contentId = contentId
    }

    @ReactProp(name = NETWORK_ID_PROP)
    fun setNetworkId(adView: ReactAdView, networkID: String) {
        adView.networkID = networkID
    }

    @ReactProp(name = IS_INLINE_PROP)
    fun setIsInline(adView: ReactAdView, isInline: Boolean) {
        adView.isInline = isInline
    }

    @ReactProp(name = GDPR_APPLIES_PROP)
    fun setGdprApplies(adView: ReactAdView, gdprApplies: Boolean) {
        adView.gdprApplies = gdprApplies
    }
}