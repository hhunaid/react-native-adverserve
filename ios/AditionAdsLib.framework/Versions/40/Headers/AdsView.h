/*  ————————————————————————————————————————————————————————————————————————  *
 *
 *      AdsView.h
 *      ~~~~~~~~~
 *
 *      View for displaying advertisements
 *
 *      Project:            AditionAdsLib
 *
 *      File encoding:      UTF-8
 *
 *      Created 2011-12-20: Ulrich Singer <ulrich.singer@adition.com>
 *
 *      $Id: AdsView.h 51168 2016-08-04 07:26:12Z sgoeppentin $
 *
 *      Copyright © 2011 The ORMMA.org project authors.  All rights reserved.
 *      Copyright © 2012-2016 ADITION technologies AG.  All rights reserved.
 */

#import <UIKit/UIKit.h>

/*  ————————————————————————————————————————————————————————————————————————  *
 *
 *      Forward Declarations
 */

@class AdsTargeting;

@protocol AdsViewDelegate;              // You implement.


/*  ————————————————————————————————————————————————————————————————————————  *
 *
 *      Global Constants
 */

/**
 *  Error domains.
 */
extern NSString *const                  kAdsErrorDomain_NetworkError;
extern NSString *const                  kAdsErrorDomain_AdServerError;
extern NSString *const                  kAdsErrorDomain_ProtocolError;
extern NSString *const                  kAdsErrorDomain_FileSystemError;
extern NSString *const                  kAdsErrorDomain_DatabaseError;
extern NSString *const                  kAdsErrorDomain_ApplicationError;


/**
 *  Error codes.
 *
 *  Returned by -[NSError code].
 */
enum
{
    // Neutral element.
    kAdsError_NoError                           = 0,

    // Domain = kAdsErrorDomain_NetworkError:
    // These errors might occur while attempting to establish a network connection.

    kAdsNetworkError_CreationFailure            = 0x0101,
    kAdsNetworkError_ConnectionFailure          = 0x0102,
    kAdsNetworkError_AuthenticationFailure      = 0x0103,
    kAdsNetworkError_RequestCancelled           = 0x0104,
    kAdsNetworkError_RequestTimedOut            = 0x0105,
    kAdsNetworkError_WhileBuildingRequest       = 0x0106,
    kAdsNetworkError_WhileApplyingCredentials   = 0x0107,
    kAdsNetworkError_TooMuchRedirection         = 0x0108,
    kAdsNetworkError_UnhandledException         = 0x0109,
    kAdsNetworkError_DecompressionFailure       = 0x010A,

    // Domain = kAdsErrorDomain_AdServerError:
    // An ad request reached the ad server but the server won't play ball for some reason.

    // Targeting criteria didn't yield a banner, possibly
    // because of frequency capping or something similar.
    // This doesn't necessarily mean that you did anything wrong.
    kAdsAdServerError_BannerNotFound            = 0x0201,

    // Domain = kAdsErrorDomain_ProtocolError:
    // A response from the ad server did not conform to the AdSDK communication protocol.
    // If you get one of these, you shoud contact support.

    kAdsProtocolError_ContentType               = 0x0301,
    kAdsProtocolError_DecodingFailure           = 0x0302,
    kAdsProtocolError_MissingField              = 0x0303,
    kAdsProtocolError_InvalidType               = 0x0304,
    kAdsProtocolError_InvalidURL                = 0x0305,
    kAdsProtocolError_Undefined                 = 0x0306,

    // Domain = kAdsErrorDomain_FileSystemError:
    // An error occured during a file system operation.

    kAdsFileSystemError_Generic                 = 0x0401,

    // Domain = kAdsErrorDomain_DatabaseError:
    // An error occured during a database operation.
    // If the error message indicates a reason other than resource
    // restrictions, you should probably contact support.

    kAdsDatabaseError_Generic                   = 0x0501,

    // Domain = kAdsErrorDomain_ApplicationError:
    // Assorted errors while configuring or executing an ad creative.

    // Operation was requested in the wrong `loadingStage`.
    kAdsApplicationError_LoadingStage           = 0x0601,
    // The ad developer made an error in AdSDK usage.
    kAdsApplicationError_AdCreative             = 0x0602,
    // Internal AdSDK error.  You should contact support.
    kAdsApplicationError_Internal               = 0x0603,
    // Some arbitrary operating system error.
    kAdsApplicationError_Runtime                = 0x0604,
    // Some arbitrary app developer error.
    kAdsApplicationError_HostApp                = 0x0605

    // You may want to inspect the chain of `NSUnderlyingErrorKey` entries in
    // the `-[NSError userInfo]` dictionaries.
    // In errors related to the file system, you find the file system path at
    // `userInfo[NSFilePathErrorKey]` in one of the underlying errors.  If a
    // file system related error message indicates a reason other than storage
    // restrictions, you should contact support.
};


/*  ————————————————————————————————————————————————————————————————————————  *
 *
 *      Type Definitions
 */

/**
 *  These stages describe the temporal sequence of ad loading.
 */
enum AdsLoadingStage
{
    // Ad loading hasn't begun yet.
    kAdsLoadingStage_PriorToAdRequest,

    // Loading assets from server(s) into local cache.
    kAdsLoadingStage_AdCachingInProgress,

    // Assets loaded into local cache but not yet into WebView.
    kAdsLoadingStage_AdCachingCompleted,

    // Loading locally cached creative into WebView.
    kAdsLoadingStage_AdLoadingInProgress,

    // The WebView has finished loading.
    kAdsLoadingStage_AdLoadingCompleted
};

typedef enum AdsLoadingStage            AdsLoadingStage;


/**
 *  These constants describe an ad's placement type.
 */
enum AdsPlacementType
{
    kAdsPlacementType_Unspecified,
    kAdsPlacementType_Inline,
    kAdsPlacementType_Interstitial
};

typedef enum AdsPlacementType           AdsPlacementType;


/**
 *  These constants describe an ad's visual display state.
 */
enum AdsViewState
{
    kAdsViewState_Default,              // After instantiation.
    kAdsViewState_Resized,              // After `mraid.resize()`.
    kAdsViewState_Expanded,             // After `mraid.expand()`.
    kAdsViewState_Hidden                // After closing an interstitial.
};

typedef enum AdsViewState               AdsViewState;


/**
 *  Runtime Logging Option Flag Bits.
 */
enum AdsLogBitIndex
{
    // Logs dynamic memory management.
    kAdsLogBit_Lifecycle                = 0,

    // Logs network connectivity changes.
    kAdsLogBit_NetStatus                = 1,

    // Logs external network accesses.
    kAdsLogBit_NetAccess                = 2,

    // Logs WebView loads.
    kAdsLogBit_AdWebView                = 3,

    // Logs AdsView layout.
    kAdsLogBit_ViewFrame                = 4,

    // Logs MRAID state transitions.
    kAdsLogBit_ViewState                = 5,

    // Logs JS API ”info” messages from ads.
    kAdsLogBit_AdLogging                = 6,

    // Logs entering & leaving modal state.
    kAdsLogBit_Modality                 = 7,

    // Logs hardware sensor switching.
    kAdsLogBit_Hardware                 = 8,
    
    // Logs debug output from AdServer.
    kAdsLogBit_NoBannerDebug            = 9
};

typedef enum AdsLogBitIndex             AdsLogBitIndex;

static const int kAdsLearningTagMaxAttributeCount = 5;

/*  ————————————————————————————————————————————————————————————————————————  *
 *
 *      Class Definitions
 */

#pragma mark    -

/**
 * External id for the 'Identity Service' feature.
 */
@interface AdsExternalId : NSObject


#pragma mark    —— Public Properties ——

/**
 * The user Id can be stable or unstable. An unstable id means the id will be different if the
 * user is on two different devices. A stable id is an id that is always the same regardless
 * of the device of web client.
 * The user id has to be a string and may not be longer then 32 characters long. If the user
 * id is an empty string then the user id feature is deactivated and the ADITION identity will
 * be used instead and is the default.
 */
@property (atomic, copy, readonly)
NSString                               *userId;

/**
 * Whether the user id is stable or not. See userId;
 */
@property (atomic, assign, readonly)
BOOL                                    stable;

/**
 * Whether to use the user data for analytical purposes or not.
 */
@property (atomic, assign, readonly)
BOOL                                    optOut;

#pragma mark    —— Construction ——

- (instancetype)initWithUserId:(NSString *)inUserId stable:(BOOL)inStable optOut:(BOOL)inOptOut
NS_DESIGNATED_INITIALIZER;

#pragma mark    —— Excluded Methods ——

- (instancetype)init NS_UNAVAILABLE;

@end

/**
 * Learning Tag configuration object
 */
@interface AdsLearningTag : NSObject

- (instancetype)initWithAttributes:(NSDictionary *)inAttributes error:(NSError **)outError;

- (void)setAttribute:(NSString *)inAttribute value:(NSString *)inValue error:(NSError **)outError;
// TODO: Fill in properties

@end

/**
 *  A view for displaying ads
 */
@interface AdsView : UIView

#pragma mark    —— Public Properties ——

/**
 *  You assign an instance of a class that conforms to the AdsViewDelegate
 *  protocol.  In most cases, this would be the superview's view controller.
 *
 *  • You MUST assign a valid, non-nil instance.
 */
@property (atomic, assign) IBOutlet
id<AdsViewDelegate>                     delegate;

@property (atomic, assign)
BOOL                                    forceOptOut;

@property (atomic, assign)
BOOL                                    gdprApplies;

/**
 *  You assign values to this object's properties to
 *  supply additional targeting criteria for ad selection.
 */
@property (atomic, retain, readonly)
AdsTargeting                           *targeting;

/**
 * The external id to send with the adrequest. This property is optional.
 */
@property (atomic, retain)
AdsExternalId                           *externalId;

/**
 *  Reflects the ad's visual display state.
 */
@property (atomic, assign, readonly)
AdsViewState                            displayState;

/**
 *  Reflects the ad's progression through the stages of loading.
 */
@property (atomic, assign, readonly)
AdsLoadingStage                         loadingStage;

/**
 *  Tells whether the ad is placed “inline”, inside the app's UI,
 *  or as “interstitial”, blocking the app's workflow until closed.
 */
@property (atomic, assign, readonly)
AdsPlacementType                        placementType;

/**
 *  You set this to YES if the user has to tap a banner before
 *  it may perform `mraid.resize()` or `mraid.expand()`.
 *
 *  • This property is ignored for interstitial ads.
 */
@property (atomic, assign)
BOOL                                    requiresUserInteraction;

#pragma mark    —— Construction ——

/**
 *  Placement-specific initializer for “inline” ads.
 */
- (instancetype)initInlineWithFrame:(CGRect)inFrame delegate:(id<AdsViewDelegate>)inDelegate
NS_DESIGNATED_INITIALIZER;

/**
 *  Placement-specific initializer for “interstitial” ads.
 *
 *  • An interstitial always has full physical screen size.
 */
- (instancetype)initInterstitialWithDelegate:(id<AdsViewDelegate>)inDelegate
NS_DESIGNATED_INITIALIZER;

/**
 *  Placement-specific convenience factory for “inline” ads.
 */
+ (instancetype)inlineAdWithFrame:(CGRect)inFrame delegate:(id<AdsViewDelegate>)inDelegate;

/**
 *  Placement-specific convenience factory for “interstitial” ads.
 *
 *  • An interstitial always has full physical screen size.
 */
+ (instancetype)interstitialAdWithDelegate:(id<AdsViewDelegate>)inDelegate;

#pragma mark    —— Public Methods ——

/**
 *  Retrieves the SDK implementation's CPU architecture and register size.
 */
+ (void)getArchitecture:(NSString **)outArchName andBitCount:(NSNumber **)outBitCount;

/**
 *  Retrieves the platform-specific SDK implementation version number.
 */
+ (NSNumber *)sdkVersionNumber;

/**
 *  Sets the network module's timeout value for all following requests.
 */
+ (void)setNetworkTimeoutSeconds:(NSTimeInterval)inInterval;

/**
 *  Retrieves the network module's timeout value.
 */
+ (NSTimeInterval)networkTimeoutSeconds;

/**
 *  Sets the indicated runtime logging flag bit to the given state.
 *
 *  • You use this method to switch runtime logging in specified components on or off.
 */
+ (BOOL)setLoggingBit:(AdsLogBitIndex)inBitIndex toState:(BOOL)inBitState;

/**
 *  Tells whether the indicated runtime logging flag bit is set to YES.
 */
+ (BOOL)hasLoggingBit:(AdsLogBitIndex)inBitIndex;

/**
 *  Sets the activation status for externally logging SDK errors.
 */
+ (void)activateExternalErrorLog:(BOOL)inLoggingFlag;

/**
 *  Queries the activation status for externally logging SDK errors.
 */
+ (BOOL)isExternalErrorLogActive;

- (BOOL)setBase64ConsentData:(NSString *)consentData;

/**
 *  Sends an ad request for the indicated content unit ID in the given network.
 */
- (BOOL)loadCreativeFromNetwork:(NSString *)inNetworkID withContentUnitID:(NSString *)inContentUnitID error:(NSError **)outError;

/**
 *  Sends an ad request for the indicated learning tag in the given network.
 */
- (BOOL)loadCreativeFromNetwork:(NSString *)inNetworkID withLearningTag:(AdsLearningTag *)inLearningTag error:(NSError **)outError;

/**
 *  Loads an ad creative from a user-defined URL.
 *
 *  • This method is for testing and debugging purposes only.
 *
 *  • If you use this you do so at your own peril.
 */
- (BOOL)requestCreativeFromURL:(NSURL *)inURL error:(NSError **)outError;

/**
 *  Forces the ad to revert to its default state, i.e. closes an expanded or resized display.
 *
 *  • This method has no effect on interstitial ads.
 */
- (void)restoreToDefaultState;

/**
 *  Returns `window.document.querySelectorAll(«selector»).length`,
 *  as the number of DOM elements addressed by the given CSS selector.
 */
- (unsigned int)numberOfElementsWithSelector:(NSString *)inCssSelector;

/**
 *  Returns `window.document.querySelectorAll(«selector»)[«index»].innerHTML.trim()`,
 *  as the HTML contents of the indicated DOM element in the NodeList addressed by
 *  the given CSS selector.
 *
 *  • Returns nil if the selector addresses no elements
 *    or the given index is otherwise out of range.
 */
- (NSString *)htmlOfElementWithSelector:(NSString *)inCssSelector atIndex:(unsigned int)inIndex;

/**
 *  Returns `window.document.querySelectorAll(«selector»)[«index»].innerText.trim()`,
 *  as the text contents of the indicated DOM element in the NodeList addressed by
 *  the given CSS selector.
 *
 *  • Returns nil if the selector addresses no elements
 *    or the given index is otherwise out of range.
 */
- (NSString *)textOfElementWithSelector:(NSString *)inCssSelector atIndex:(unsigned int)inIndex;

/**
 *  Tells the `AdsView` that the user has closed an app-defined browser.  This
 *  method must only be used if your app defines its own browser via the
 *  `-openBrowserForAd:withURL:` delegate method (see below).
 */
- (void)resumeFromAppDefinedBrowser;

/**
 *  Prepares the `AdsView` for a clean shut-down by cancelling any
 *  pending network requests and relinquishing other resources.
 *
 *  • You MUST apply this method right before you release an `AdsView`,
 *    lest your app will suffer from memory leaks.
 *
 *  • Note that this method indicates the end of an AdsView's life cycle.
 *    After you apply this method, you MUST NOT make use of that AdsView
 *    other than releasing it.
 */
- (void)prepareForShutdown;

#pragma mark    —— Excluded Methods ——

- (instancetype)initWithFrame:(CGRect)_ NS_UNAVAILABLE;

- (instancetype)initWithCoder:(NSCoder *)_ NS_UNAVAILABLE;

@end    // AdsView


/*  ————————————————————————————————————————————————————————————————————————  */

#pragma mark    -

/**
 *  Targeting criteria for ad selection.
 *
 *  Assignment to all of these properties is optional.
 */
@interface AdsTargeting : NSObject

#pragma mark    —— Public Properties ——

/**
 *  User's selected language.
 *  If your app offers its own language selection, you assign a 2- or
 *  5-character locale code (like “en”, “de”, or “en_GB”) for the user's
 *  language choice.  If you don't assign a value, ad selection will use
 *  the current system language.
 */
@property (nonatomic, copy)             // ^[a-z]{2}(:?_[A-Z]{2})?$
NSString                               *humanLanguage;

/**
 *  Usage tracking group name.
 *
 *  Acts like a namespace for anonymously tracking app usage on an individual
 *  device.  If you assign the same name in several apps, requesting an ad in
 *  one of those apps will generate the same tracking ID on a specific device
 *  (but different IDs on different devices).
 *  The default value is the app's bundle identifier, which will produce
 *  different tracking IDs for each app on the same device.
 *  Since the tracking group name must be unique across all app developers,
 *  it is recommended that you use a reverse DNS naming scheme similar to
 *  your bundle identifier (à la “com.yourdomain.groupname”).
 *  This is about as close as you can get to anonymous user tracking with
 *  scalable granularity across multiple apps.  No personally identifiable
 *  information is ever transmitted.
 */
@property (nonatomic, copy)             // @"com.yourdomain.groupname"
NSString                               *trackingGroupName;

/**
 *  Generic targeting keyword.
 *
 *  An ASCII-encoded text with a maximum length of 255 bytes that narrows
 *  down which ads can be served.  Consult the ADITION user manual to
 *  learn more about keyword targeting.
 */
@property (nonatomic, copy)             //  ⊆ ASCII, < 256 Bytes.
NSString                               *keyword;

#pragma mark    —— Public Methods ——

/**
 *  Sets a single Profile Targeting binding for inclusion in or exclusion from
 *  the ad request URL's “p” query parameter value.
 *
 *  • Applying this method is only valid before you issue the ad request,
 *    i.e. while `AdsView.loadingStage` is `kAdsLoadingStage_PriorToAdLoading`.
 *
 *  • The targeting key must match the RegExp “^[A-Za-z_][A-Za-z0-9_-]{0,59}$”.
 *
 *  • The targeting value must match the RegExp “^[A-Za-z0-9_~.-]{1,255}$”.
 *
 *  • Targeting keys are not case-sensitive.
 *
 *  • The resulting profile assignments can hold a maximum of 100 key/value pairs.
 *
 *  • If you pass a nil argument to the `inValue` parameter, the binding for
 *    the given key is removed from Profile Targeting, if it exists.
 *
 *  • You may pass NULL to the `outError` parameter if you aren't interested
 *    in error diagnosis.
 *
 *  • Returns YES if the operation was successful, otherwise NO.
 */
- (BOOL)bindProfileTargetingKey:(NSString *)inKey withValue:(NSString *)inValue error:(NSError **)outError;

/**
 *  Merges existing Profile Targeting bindings with the given dictionary.
 *
 *  • Applying this method is only valid before you issue the ad request,
 *    i.e. while `AdsView.loadingStage` is `kAdsLoadingStage_PriorToAdLoading`.
 *
 *  • The keys in the dictionary must be NSString instances matching the
 *    RegExp “^[A-Za-z_][A-Za-z0-9_-]{0,59}$”.
 *
 *  • Targeting keys are not case-sensitive.
 *
 *  • The values in the dictionary must be instances of NSString or NSNull.
 *    Value strings must match the RegExp “^[A-Za-z0-9_~.-]{1,255}$”.
 *
 *  • If a value in the given dictionary is NSNull, the binding for its key
 *    is removed from Profile Targeting, if it exists.
 *
 *  • The resulting profile assignments can hold a maximum of 100 key/value pairs.
 *
 *  • You may pass NULL to the `outError` parameter if you aren't interested
 *    in error diagnosis.
 *
 *  • Returns YES if the operation was successful, otherwise NO.
 *
 *  • See also -[AdsTargeting bindProfileTargetingKey:withValue:error:].
 */
- (BOOL)mergeProfileTargetingWithDictionary:(NSDictionary *)inTargetingMap error:(NSError **)outError;

@end    // AdsTargeting


/*  ————————————————————————————————————————————————————————————————————————  *
 *
 *      Protocol Definitions
 */

#pragma mark    -

/**
 *  AdsView delegate protocol.
 *
 *  You as the app developer implement these methods.
 */
@protocol AdsViewDelegate <NSObject>

@optional

#pragma mark    —— Optional Methods ——

/**
 *  Lets the app developer inform the SDK ahead of time which superview
 *  they will place the given `AdsView` in.  This information is needed
 *  for coordinate computations on `AdsView`s that are not part of a view
 *  hierarchy at the time when ad loading finishes and MRAID state is
 *  initialized.
 *
 *  • The superview chain of the view returned must end in a visible
 *    app window.
 */
- (UIView *)futureSuperviewForAd:(AdsView *)inAdsView;

/**
 *  Lets the app developer update position and size for a generic inline ad.
 *
 *  • You return the desired AdsView frame from this delegate method.
 *
 *  • This method is only invoked for generic inline ads.
 */
- (CGRect)adDefaultFrame:(AdsView *)inAdsView forBannerSize:(CGSize)inBannerSize;

/**
 *  Informs the delegate that the indicated ad is done caching.
 *
 *  • If the caching was successful, the `inError` parameter will have
 *    a `nil` value and the given `AdsView` is ready to load its WebView.
 *
 *  • If the `inError` parameter is `nil`, this method is a good place to
 *    insert the `AdsView` into the app UI or create an `AdsInterstitialController`
 *    for it.
 *
 *  • This method is invoked independently of dynamic context, so you
 *    are free to remove and deallocate the given `AdsView` on error.
 */
- (void)adFinishedCaching:(AdsView *)inAdsView withSuccessOrError:(NSError *)inError;

/**
 *  Asks the delegate whether to load the ad creative into its WebView
 *  before the `AdsView` is inserted into the app UI.
 *
 *  • If you return `NO`, the ad will load its WebView olnly after
 *    the `AdsView` is inserted into the app UI.
 *
 *  • This method is only invoked if you do not implement the
 *    `-adFinishedCaching:withSuccessOrError:` method.
 */
- (BOOL)adShouldLoadWebViewFromCache:(AdsView *)inAdsView;

/**
 *  Tells the delegate that the indicated ad is about to load its WebView.
 */
- (void)adWillLoadWebViewFromCache:(AdsView *)inAdsView;

/**
 *  Informs the delegate that the indicated ad is done loading into its WebView.
 *
 *  • If the loading was successful, the `inError` parameter will have
 *    a `nil` value and the given `AdsView` is ready to be displayed.
 *
 *  • This method is invoked independently of dynamic context, so you
 *    are free to remove and deallocate the given `AdsView` on error.
 */
- (void)adFinishedLoading:(AdsView *)inAdsView withSuccessOrError:(NSError *)inError;

/**
 *  Informs the delegate that user code on the top-level of any <script> nodes
 *  in the creative DOM of the indicated ad has finished running now.
 */
- (void)adWindowDidLoadDOM:(AdsView *)inAdsView;

/**
 *  Tells the delegate that the indicated ad's internal JS code produced
 *  the given error while performing an SDK operation (like one of the
 *  MRAID functionalities).
 */
- (void)runningAd:(AdsView *)inAdsView encounteredError:(NSError *)inError;

/**
 *  Tells the delegate that the indicated ad is about to be displayed.
 */
- (void)adWillShow:(AdsView *)inAdsView;

/**
 *  Tells the delegate that the indicated ad is now being displayed.
 */
- (void)adDidShow:(AdsView *)inAdsView;

/**
 *  Tells the delegate that the indicated ad is about to expand.
 */
- (void)adWillExpand:(AdsView *)inAdsView toFrame:(CGRect)inFrame;

/**
 *  Tells the delegate that the indicated ad is now expanded.
 *
 *  • Note that in the “expanded” state, the AdsView's frame rectangle
 *    continues to represent “default” state coordinates.
 */
- (void)adDidExpand:(AdsView *)inAdsView toFrame:(CGRect)inFrame;

/**
 *  Tells the delegate that the indicated ad is about to resize.
 */
- (void)adWillResize:(AdsView *)inAdsView toSize:(CGSize)inSize;

/**
 *  Tells the delegate that the indicated ad is now resized.
 */
- (void)adDidResize:(AdsView *)inAdsView toSize:(CGSize)inSize;

/**
 *  Tells the delegate that the indicated ad is about to enter a modal state.
 */
- (void)adWillEnterModalState:(AdsView *)inAdsView;

/**
 *  Tells the delegate that the indicated ad is about to leave a modal state.
 */
- (void)adWillLeaveModalState:(AdsView *)inAdsView;

/**
 *  Tells the delegate that the indicated ad is about to close.
 */
- (void)adWillClose:(AdsView *)inAdsView;

/**
 *  Tells the delegate that the indicated ad is now closed.
 */
- (void)adDidClose:(AdsView *)inAdsView;

/**
 *  Informs the delegate that the indicated ad's JS code has fired
 *  a user-defined event with the given name and info text, using
 *  the `AdSDK.fireEvent()` JS function.
 *
 *  • This method is invoked independently of dynamic context, so you
 *    are free to remove and deallocate the given `AdsView` on error.
 */
- (void)adFiredEvent:(AdsView *)inAdsView withName:(NSString *)inEventName andInfoText:(NSString *)inInfoText;

/**
 *  Tells the delegate that the indicated ad created a new entry
 *  in the device calendar.
 *
 *  • You can use this method to display a message informing the user
 *    that a new entry was inserted into their calendar.
 */
- (void)adCreatedCalendarEntry:(AdsView *)inAdsView;

/**
 *  Lets the delegate handle a tap on the embedded browser's Action button
 *  (the one that looks like UIBarButtonSystemItemAction).  The intended
 *  purpose is to let the user decide what they want to do with the URL:
 *  Open in Safari, mail the link, tweet the link, etc...
 */
- (void)externallyProcessURL:(NSURL *)inURL startingFromView:(UIView *)inView;

/**
 *  Allows the delegate to create a view controller that acts as a browser
 *  for the given URL.  The SDK assumes that you present this browser modally
 *  (using the `-UIViewController presentViewController:animated:completion:`
 *  method).  Therefore, you MUST take the following steps after the user
 *  closes your browser:
 *
 *  • You dismiss the view controller that presents your browser (using the
 *    `-UIViewController dismissViewControllerAnimated:completion:` method).
 *
 *  • You send the `-resumeFromAppDefinedBrowser` message to the given `AdsView`.
 *
 *  • If you don't implement this method, the AdSDK will use a brand-neutral
 *    embedded browser view controller with essential navigation controls.
 */
- (void)openBrowserForAd:(AdsView *)inAdsView withURL:(NSURL *)inURL;

/**
 *  This delegate will be called whenever the user clicks the ad. Parameters are 
 *  the AdsView that was clicked and the URL of the adserver. This will not be called
 *  for magic URLs like sms/callto.
 */
- (void)trackAdClickFrom:(AdsView *)inAdsView withURL:(NSURL *)inURL;

/**
 *  Specify the style of the status bar while the in app browser is shown.
 *  You might implement this method when you want to use a custom background color
 *  for the status bar to get a good contrast between background and contents of
 *  the status bar. The default status bar style `is UIStatusBarStyleLightContent`
 *  which will be used when this method is not implemented.
 */
- (UIStatusBarStyle)preferredStatusBarStyleInBrowserForAd:(AdsView *)inAdsView;

/**
 *  Specify the background color of the status bar while the in app browser is shown.
 *  The default background color is black and will be used if this method is not implemented.
 */
- (UIColor *)preferredStatusBarBackgroundColorInBrowserForAd:(AdsView *)inAdsView;
    
@end    // AdsViewDelegate


/*  ————————————————————————————————————————————————————————————————————————  */

/* ~ AdsView.h ~ */
