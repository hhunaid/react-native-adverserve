//
//  AdsOptOutHelper.h
//  AditionAds
//
//  Created by Stephan Göppentin on 04.05.18.
//  Copyright © 2018 ADITION technologies AG. All rights reserved.
//

#import <Foundation/Foundation.h>

static const NSInteger kAdsOptOutError = -1;
static const NSInteger kAdsOptedIn     =  1;
static const NSInteger kAdsOptedOut    =  2;

@protocol AdsOptOutHelperDelegate;

@interface AdsOptOutHelper : NSObject

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initForNetwork:(NSString *)inNetworkID withDelegate:(id<AdsOptOutHelperDelegate>)inDelegate NS_DESIGNATED_INITIALIZER;

- (void)status;

- (void)optIn;

- (void)optOut;

@end

@protocol AdsOptOutHelperDelegate <NSObject>

@optional

- (void)optOutHelperFailed:(AdsOptOutHelper *)inOptOutHelper;

- (void)optOutHelper:(AdsOptOutHelper *)inOptOutHelper gotStatus:(NSInteger)inStatus;

@end
