import { NativeModules } from 'react-native';

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

  getStatus() {
    return AdSDKHelper.getStatus(this.networkId);
  }
}

export class DoNotTrackHelper {
  static enableLimitedTracking(isEnabled) {
    AdSDKHelper.enableLimitedTracking(isEnabled);
  }

  static isLimitedTrackingEnabled(cb) {
    AdSDKHelper.isLimitedTrackingEnabled(cb);
  }
}

export class CookieManager {
  static removeAllCookies() {
    AdSDKHelper.removeAllCookies();
  }
}
