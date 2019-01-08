#if __has_include(<React/RCTBridgeModule.h>)
#import <React/RCTBridgeModule.h>
#else
#import "RCTBridgeModule.h"
#endif

#import <Foundation/Foundation.h>
#import <AditionAdsLib/AdsOptOutHelper.h>

@interface RCTAdSDKHelper : NSObject <RCTBridgeModule, AdsOptOutHelperDelegate>

@end
