import React from 'react';
import {requireNativeComponent} from 'react-native';

const RCTAdBanner = requireNativeComponent('RCTAdBanner');

export default class AdBanner extends React.PureComponent {
  render() {
    return <RCTAdBanner />;
  }
}