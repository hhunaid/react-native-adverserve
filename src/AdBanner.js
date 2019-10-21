import React from 'react';
import { requireNativeComponent, View } from 'react-native';
import PropTypes from 'prop-types'

const RCTAdBanner = requireNativeComponent('RCTAdView');

export default class AdBanner extends React.PureComponent {
  static propTypes = {
    contentUnitId: PropTypes.string.isRequired,
    networkId: PropTypes.string.isRequired,
    isInline: PropTypes.bool,
    gdprApplies: PropTypes.bool,
    onAdClicked: PropTypes.func,
    onAdLoaded: PropTypes.func,
    beforeAdSDKEvent: PropTypes.func,
    onAdSDKEvent: PropTypes.func,
    onAdSDKError: PropTypes.func,
    onAdFiredEvent: PropTypes.func,
    debugMode: PropTypes.bool
  };

  static defaultProps = {
    isInline: true,
    gdprApplies: false,
    onAdClicked: () => {},
    onAdLoaded: () => {},
    beforeAdSDKEvent: null,
    onAdSDKEvent: null,
    onAdSDKError: null,
    onAdFiredEvent: null,
    debugMode: false
  };

  state = {
    loaded: false
  }

  _beforeAdSDKEvent = (event) => {
    if (!this.props.beforeAdSDKEvent) {
      return
    }
    const { eventName } = event.nativeEvent;
    this.props.beforeAdSDKEvent(eventName);
  };

  _onAdSDKEvent = (event) => {
    if (!this.props.onAdSDKEvent) {
      return
    }
    const { eventName, eventPayload } = event.nativeEvent;
    this.props.onAdSDKEvent(eventName, eventPayload);
  };

  _onAdSDKError = (event) => {
    if (!this.props.onAdSDKError) {
      return
    }
    const { errorCode, message } = event.nativeEvent;
    this.props.onAdSDKError(errorCode, message)
  };

  _onAdFiredEvent = (event) => {
    if (!this.props.onAdFiredEvent) {
      return
    }
    const { eventName, eventPayload } = event.nativeEvent;
    this.props.onAdSDKEvent(eventName, eventPayload);
  };

  _onAdLoaded = () => {
    this.setState({ loaded: true });
    this.props.onAdLoaded();
  }


  render() {
    const { loaded } = this.state
    return (
      <View style={loaded ? null : { width: 0, height: 0, overflow: 'hidden' }}>
        <RCTAdBanner
          {...this.props}
          beforeAdSDKEvent={this._beforeAdSDKEvent}
          onAdSDKEvent={this._onAdSDKEvent}
          onAdSDKError={this._onAdSDKError}
          onAdFiredEvent={this._onAdFiredEvent}
          onAdLoaded={this._onAdLoaded}
        />
      </View>
    );
  }
}