package com.dudigital.reactnative.adverserve

import android.annotation.SuppressLint
import android.content.Intent
import android.net.Uri
import android.widget.LinearLayout
import com.adition.android.sdk.AdViewListener
import com.adition.android.sdk.AditionErrorCode
import com.adition.android.sdk.AditionView
import com.adition.android.sdk.browser.AditionBrowser
import com.facebook.react.bridge.Arguments
import com.facebook.react.bridge.ReactContext
import com.facebook.react.bridge.WritableMap
import com.facebook.react.uimanager.events.RCTEventEmitter

@SuppressLint("ViewConstructor")
class ReactAdView(private val context: ReactContext): LinearLayout(context) {
    var networkID = ""
        set(value) {
            field = value
            createAdView()
        }
    var contentId = ""
        set(value) {
            field = value
            createAdView()
        }
    var isInline = true
        set(value) {
            field = value
            createAdView()
        }
    var gdprApplies = false
        set(value) {
            field = value
            createAdView()
        }
    private var adView: AditionView? = null
    private val externalBrowser = AditionBrowser { url ->
        val browserIntent = Intent(Intent.ACTION_VIEW, Uri.parse(url))
        context.startActivity(browserIntent)
    }

    companion object {
        const val AD_CLICKED_EVENT = "onAdClicked"
        const val AD_LOADED_EVENT = "onAdLoaded"
        const val BEFORE_AD_SDK_EVENT = "beforeAdSDKEvent"
        const val ON_SDK_EVENT = "onAdSDKEvent"
        const val ON_SDK_ERROR = "onAdSDKError"
        const val ON_AD_FIRED_EVENT = "onAdFiredEvent"
    }

    init {
        createAdView()
    }

    private fun createAdView() {
        if (contentId == "" || networkID == "") {
            return
        }
        if (adView != null) {
            removeView(adView)
            adView = null
        }
        adView = AditionView(context.currentActivity, contentId, networkID, isInline)
        if (gdprApplies) {
            adView?.gdprApplies()
        }
        adView?.execute()
        addView(adView)
        adView?.setBrowser(externalBrowser)
        adView?.adViewListener = object : AdViewListener {
            override fun onAdClicked() {
                sendEvent(AD_CLICKED_EVENT)
            }

            override fun onAdLoaded() {
                sendEvent(AD_LOADED_EVENT)
            }

            override fun beforeAdSDKEvent(eventName: String) {
                val event = Arguments.createMap()
                event.putString("eventName", eventName)
                sendEvent(BEFORE_AD_SDK_EVENT, event)
            }

            override fun onAdSDKEvent(eventName: String, eventPayload: String) {
                val event = Arguments.createMap()
                event.putString("eventName", eventName)
                event.putString("eventPayload", eventPayload)
                sendEvent(ON_SDK_EVENT, event)
            }

            override fun onAdSDKError(aditionErrorCode: AditionErrorCode, message: String) {
                val event = Arguments.createMap()
                event.putInt("errorCode", aditionErrorCode.id)
                event.putString("message", message)
                sendEvent(ON_SDK_ERROR, event)
            }

            override fun onAdFiredEvent(eventName: String, eventPayload: String) {
                val event = Arguments.createMap()
                event.putString("eventName", eventName)
                event.putString("eventPayload", eventPayload)
                sendEvent(ON_AD_FIRED_EVENT, event)
            }
        }
    }

    private fun sendEvent(name: String, event: WritableMap? = null) {
        val context = getContext() as ReactContext
        context.getJSModule(RCTEventEmitter::class.java)?.receiveEvent(
                id,
                name,
                event
        )
    }

    override fun requestLayout() {
        super.requestLayout()
        post {
            measure(MeasureSpec.makeMeasureSpec(width, MeasureSpec.EXACTLY),
                    MeasureSpec.makeMeasureSpec(height, MeasureSpec.EXACTLY))
            layout(left, top, right, bottom)
        }
    }
}