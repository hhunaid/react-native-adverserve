#if __has_include(<React/RCTBridgeModule.h>)
#import <React/RCTBridgeModule.h>
#import <React/UIView+React.h>
#import <React/RCTLog.h>
#else
#import "RCTBridgeModule.h"
#import "UIView+React.h"
#import "RCTLog.h"
#endif
#import "RCTAdView.h"
#import <AditionAdsLib/AdsView.h>

@implementation RCTAdView {
    AdsView *_inlineAdView;
}

@synthesize contentUnitId, networkId, gdprApplies;

- (void)layoutSubviews{
    if (_inlineAdView == nil) {
        _inlineAdView = [[AdsView alloc] initInlineWithFrame:self.frame delegate:self];
        [self loadAd];
    }
}

- (void)loadAd {
    if (networkId.length == 0 || contentUnitId.length == 0) {
        return;
    }
    _inlineAdView.gdprApplies = gdprApplies;
    [_inlineAdView loadCreativeFromNetwork:networkId withContentUnitID:contentUnitId error:nil];
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-missing-super-calls"
- (void)insertReactSubview:(UIView *)subview atIndex:(NSInteger)atIndex{
    RCTLogError(@"RNDFPBannerView cannot have subviews");
}

- (UIView *)futureSuperviewForAd:(AdsView *)inAdsView{
    return self;
}

- (void)adFinishedCaching:(AdsView *)inAdsView withSuccessOrError:(NSError *)inError{
    [self addSubview:_inlineAdView];
}

- (void)adFinishedLoading:(AdsView *)inAdsView withSuccessOrError:(NSError *)inError{
    if (self.onAdLoaded) {
        self.onAdLoaded(@{});
    }
}

-(void)adFiredEvent:(AdsView *)inAdsView withName:(NSString *)inEventName andInfoText:(NSString *)inInfoText{
    if (self.onAdSDKEvent) {
        self.onAdSDKEvent(@{
                            @"eventname": inEventName,
                            @"eventPayload": inInfoText
                            });
    }
}

-(void)trackAdClickFrom:(AdsView *)inAdsView withURL:(NSURL *)inURL{
    if (self.onAdClicked) {
        self.onAdClicked(@{});
    }
}

- (void)runningAd:(AdsView *)inAdsView encounteredError:(NSError *)inError{
    if (self.onAdSDKError) {
        self.onAdSDKError(@{@"message": inError.localizedDescription});
    }
}

-(void)openBrowserForAd:(AdsView *)inAdsView withURL:(NSURL *)inURL{
    if ([[UIApplication sharedApplication] openURL:inURL]) {
        [_inlineAdView resumeFromAppDefinedBrowser];
    }
}

@end
