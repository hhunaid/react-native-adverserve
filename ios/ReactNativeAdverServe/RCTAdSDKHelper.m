#import "RCTAdSDKHelper.h"
#import <AditionAdsLib/AdsDoNotTrackHelper.h>

@implementation RCTAdSDKHelper {
    AdsOptOutHelper *_helper;
    RCTResponseSenderBlock _callback;
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

RCT_EXPORT_METHOD(getStatus:(NSString *)networkID
                 callback:(RCTResponseSenderBlock)callback){
    _helper = [[AdsOptOutHelper alloc] initForNetwork:networkID withDelegate:self];
    _callback = callback;
    [_helper status];
}

- (void)optOutHelper:(AdsOptOutHelper *)inOptOutHelper gotStatus:(NSInteger)inStatus{
    if (_callback)
        _callback(@[[NSNull null], [NSNumber numberWithInteger:inStatus]]);
    _callback = nil;
    _helper = nil;
}

-(void)optOutHelperFailed:(AdsOptOutHelper *)inOptOutHelper {
    if (_callback)
        _callback(@[@"Couldn't fetch OptOut status"]);
    _callback = nil;
    _helper = nil;
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
