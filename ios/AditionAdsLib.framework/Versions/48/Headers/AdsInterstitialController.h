/*  ————————————————————————————————————————————————————————————————————————  *
 *
 *      AdsInterstitialController.h
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *      View controller for an interstitial ad
 *
 *      Project:            AditionAdsLib
 *
 *      File encoding:      UTF-8
 *
 *      Created 2015-09-01: Ulrich Singer <ulrich.singer@adition.com>
 *
 *      $Id: AdsInterstitialController.h 47721 2016-02-15 09:01:39Z usinger $
 *
 *      Copyright © 2015-2016 ADITION technologies AG.  All rights reserved.
 */

#import <UIKit/UIKit.h>


/*  ————————————————————————————————————————————————————————————————————————  *
 *
 *      Forward Declarations
 */

@class AdsView;


/*  ————————————————————————————————————————————————————————————————————————  *
 *
 *      Class Definitions
 */

#pragma mark    -

@interface AdsInterstitialController : UIViewController

#pragma mark    —— Public Methods ——

/**
 *  Designated initializer.
 *
 *  • You must not replace the presented view after initialization.
 */
- (instancetype)initWithView:(AdsView *)inAdsView
NS_DESIGNATED_INITIALIZER;


/**
 *  Shows this VC by presenting it modally on the app's root view controller.
 *  The Close action will be performed after the modal presentation ends.
 */
- (void)showInterstitialAnimated:(BOOL)inAnimated
                      afterClose:(void(^)(void))inCloseAction;

/**
 *  Shows this VC by presenting it modally on the given view controller.
 *  The Close action will be performed after the modal presentation ends.
 */
- (void)showInterstitialUsingViewController:(UIViewController *)inViewController
                                animated:(BOOL)inAnimated
                              afterClose:(void (^)(void))inCloseAction;

/**
 *  Tells whether this controller is currently being presented
 *  and whether transitions are animated.
 */
- (BOOL)isBeingPresentedAndAnimated:(BOOL *)outAnimated;

/**
 *  You use this method if you need to end the modal presentation
 *  before the user taps the ad's Close indicator.
 */
- (void)hideInterstitialAnimated:(BOOL)inAnimated;

#pragma mark    —— Excluded Methods ——

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithCoder:(NSCoder *)_ NS_UNAVAILABLE;

- (instancetype)initWithNibName:(NSString *)_ bundle:(NSBundle *)_ NS_UNAVAILABLE;

/**
 *  You must not replace the presented view after initialization.
 */
- (void)setView:(UIView *)_ NS_UNAVAILABLE;

@end    // AdsInterstitialController


/*  ————————————————————————————————————————————————————————————————————————  */

/* ~ AdsInterstitialController.h ~ */
