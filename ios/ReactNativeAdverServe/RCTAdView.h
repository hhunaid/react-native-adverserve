#if __has_include(<React/RCTComponent.h>)
#import <React/RCTView.h>
#else
#import "RCTView.h"
#endif
#import <AditionAdsLib/AdsView.h>

@interface RCTAdView : RCTView <AdsViewDelegate>

@property (nonatomic, strong) NSString *contentUnitId;
@property (nonatomic, strong) NSString *networkId;
@property (atomic, assign) BOOL gdprApplies;
@property(setter=setDebugMode:, getter=getDebugMode, atomic, assign) BOOL debugMode;

@property (nonatomic, copy) RCTBubblingEventBlock onAdClicked;
@property (nonatomic, copy) RCTBubblingEventBlock onAdLoaded;
@property (nonatomic, copy) RCTBubblingEventBlock beforeAdSDKEvent;
@property (nonatomic, copy) RCTBubblingEventBlock onAdSDKEvent;
@property (nonatomic, copy) RCTBubblingEventBlock onAdSDKError;
@property (nonatomic, copy) RCTBubblingEventBlock onAdFiredEvent;

@end
