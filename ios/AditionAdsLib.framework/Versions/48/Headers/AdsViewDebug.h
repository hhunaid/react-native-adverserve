//
//  AdsViewDebug.h
//  AditionAdsLib
//
//  Created by Stephan Göppentin on 15.11.18.
//  Copyright © 2018 ADITION technologies AG. All rights reserved.
//

#include "AdsView.h"

@interface AdsView (Debug)

- (void)forceHttpRequests:(BOOL)inEnable error:(NSError **)outError;

@end
