//
//  AdsTagging.h
//  AditionAds
//
//  Created by Stephan Göppentin on 12.04.18.
//  Copyright © 2018 ADITION technologies AG. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 * Tag configuration object
 */
@interface AdsTag : NSObject

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithKey:(NSString *)inKey subkey:(NSString *)inSubkey value:(NSString *)inValue error:(NSError **)error NS_DESIGNATED_INITIALIZER;

@end

@protocol AdsTagSenderDelegate;

/**
 * Tag sending object
 */
@interface AdsTagSender : NSObject

- (instancetype)initWithDelegate:(id<AdsTagSenderDelegate>)inDelegate;

- (BOOL)addTag:(AdsTag *)inTag error:(NSError **)outError;

- (NSError *)submitWithNetworkId:(NSString *)inNetworkId;

@end

@protocol AdsTagSenderDelegate <NSObject>

@optional

- (void)tagSenderSubmittedSuccessfully:(AdsTagSender *)tagSender;

- (void)tagSenderGotError:(AdsTagSender *)tagSender;

@end
