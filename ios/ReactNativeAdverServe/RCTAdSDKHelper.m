#import "RCTAdSDKHelper.h"
#import <AditionAdsLib/AdsDoNotTrackHelper.h>

@implementation RCTAdSDKHelper {
    AdsOptOutHelper *_helper;
    RCTPromiseResolveBlock resolver;
    RCTPromiseRejectBlock rejecter;
}

RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(optIn:(NSString *)networkID){
    _helper = [[AdsOptOutHelper alloc] initForNetwork:networkID withDelegate:self];
    [_helper optIn];
}

RCT_EXPORT_METHOD(optOut:(NSString *)networkID){
    _helper = [[AdsOptOutHelper alloc] initForNetwork:networkID withDelegate:self];
    [_helper optOut];
}

RCT_REMAP_METHOD(getStatus,
                 getStatusForNetworkID:(NSString *)networkID
                 resolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject){
    _helper = [[AdsOptOutHelper alloc] initForNetwork:networkID withDelegate:self];
    resolver = resolve;
    rejecter = reject;
    [_helper status];
}

- (void)optOutHelper:(AdsOptOutHelper *)inOptOutHelper gotStatus:(NSInteger)inStatus{
    if (resolver)
        resolver([NSNumber numberWithInteger:inStatus]);
    resolver = nil;
    _helper = nil;
}

-(void)optOutHelperFailed:(AdsOptOutHelper *)inOptOutHelper {
    if (rejecter)
        rejecter(@"Status fetch error", @"Couldn't fetch OptOut status", nil);
    rejecter = nil;
}

RCT_EXPORT_METHOD(enableLimitedTracking:(BOOL)enabled){
    [[AdsDoNotTrackHelper new] enableLimitedTracking: enabled];
}

RCT_EXPORT_METHOD(isLimitedTrackingEnabled:(RCTResponseSenderBlock)callback){
    BOOL isEnabled = [[AdsDoNotTrackHelper new] isLimitedTrackingEnabled];
    callback(@[[NSNull null], [NSNumber numberWithBool:isEnabled]]);
}

RCT_EXPORT_METHOD(removeAllCookies){
    NSArray *cookies = [[NSHTTPCookieStorage sharedHTTPCookieStorage] cookies];
    for (NSHTTPCookie *cookie in cookies) {
        [[NSHTTPCookieStorage sharedHTTPCookieStorage] deleteCookie:cookie];
    }
}
@end
