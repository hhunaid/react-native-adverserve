import { NativeModules, Platform } from 'react-native';

const { AdSDKHelper } = NativeModules;

export class OptOutHelper {
  constructor(networkId) {
    this.networkId = networkId;
  }

  optIn() {
    AdSDKHelper.optIn(this.networkId);
  }

  optOut() {
    AdSDKHelper.optOut(this.networkId);
  }

  getStatus(cb) {
    if (Platform.OS === 'ios') {
      AdSDKHelper.getStatus(this.networkId, cb);
    }else{
      AdSDKHelper.getStatus(this.networkId, error => cb(error), res => cb(null, res));
    }
  }
}

export class DoNotTrackHelper {
  static enableLimitedTracking(isEnabled) {
    AdSDKHelper.enableLimitedTracking(isEnabled);
  }

  static isLimitedTrackingEnabled(cb) {
    if (Platform.OS === 'ios') {
      AdSDKHelper.isLimitedTrackingEnabled(cb);
    }else {
      AdSDKHelper.isLimitedTrackingEnabled(error => cb(error), res => cb(null, res));
    }
  }
}

export class CookieManager {
  static removeAllCookies() {
    AdSDKHelper.removeAllCookies();
  }
}
