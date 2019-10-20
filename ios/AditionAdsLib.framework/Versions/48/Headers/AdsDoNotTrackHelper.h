//
//  AdsDoNotTrackHelper.h
//  AditionAds
//
//  Created by Stephan Göppentin on 09.05.18.
//  Copyright © 2018 ADITION technologies AG. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AdsDoNotTrackHelper : NSObject

- (void)enableLimitedTracking:(BOOL)inEnable;

- (BOOL)isLimitedTrackingEnabled;

@end
