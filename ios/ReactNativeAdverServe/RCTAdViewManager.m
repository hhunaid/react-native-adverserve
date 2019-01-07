//
//  RCTAdViewManager.m
//  ReactNativeAdverServe
//
//  Created by Hunaid Hassan on 07/01/2019.
//  Copyright © 2019 Nezzy Media. All rights reserved.
//

#import "RCTAdViewManager.h"

@implementation RCTAdViewManager

RCT_EXPORT_MODULE()

- (UIView *)view{
    return [RCTAdView new];
}

RCT_EXPORT_VIEW_PROPERTY(contentUnitId, NSString)
RCT_EXPORT_VIEW_PROPERTY(networkId, NSString)
RCT_EXPORT_VIEW_PROPERTY(gdprApplies, BOOL)

RCT_EXPORT_VIEW_PROPERTY(onAdClicked, RCTBubblingEventBlock)
RCT_EXPORT_VIEW_PROPERTY(onAdLoaded, RCTBubblingEventBlock)
RCT_EXPORT_VIEW_PROPERTY(beforeAdSDKEvent, RCTBubblingEventBlock)
RCT_EXPORT_VIEW_PROPERTY(onAdSDKEvent, RCTBubblingEventBlock)
RCT_EXPORT_VIEW_PROPERTY(onAdSDKError, RCTBubblingEventBlock)
RCT_EXPORT_VIEW_PROPERTY(onAdFiredEvent, RCTBubblingEventBlock)

@end
