# react-native-adverserve

React native SDK for Adition

## Installation

### npm

Download an install the library

```npm install react-native-adverserve --save```

Or if you are using yarn

```yarn add react-native-adverserve```

Then run ```react-native link react-native-adverserve``` to link the native parts of the library

In addition to above command you need to follow the last step mentioned in manual instructions for Android

### Android

#### Option: Manual

You can skip this part if ```link``` command works for you

* Edit android/settings.gradle to look like this (without the +):

```diff
  rootProject.name = 'MyApp'

  include ':app'

  + include ':react-native-adverserve'
  + project(':react-native-adverserve').projectDir = new File(rootProject.projectDir, '../node_modules/react-native-adverserve/android')
  ```
  
    * Edit `android/app/build.gradle` (note: **app** folder) to look like this: 
    
    ```diff
    apply plugin: 'com.android.application'
    
    android {
    ...
    }
    
    dependencies {
    implementation fileTree(dir: 'libs', include: ['*.jar'])
    implementation "com.android.support:appcompat-v7:23.0.1"
    implementation "com.facebook.react:react-native:+"  // From node_modules
    + implementation project(':react-native-adverserve')
    }
    ```
  
  * Edit your `MainApplication.java` (deep in `android/app/src/main/java/...`) to look like this (note **two** places to edit):
  
    ```diff
    package com.myapp;
  
    + import com.dudigital.reactnative.adverserve.ReactAdViewPackage;
  
    ....
  
      @Override
      protected List<ReactPackage> getPackages() {
        return Arrays.<ReactPackage>asList(
          new MainReactPackage()
    +   , new ReactAdViewPackage()
        );
      }
  
    }
    ```
    
    * Edit `android/build.gradle` (in Android root) to look like this
    
    ```
    allprojects {
        repositories {
            mavenLocal()
            google()
            jcenter()
            maven {
                // All of React Native (JS, Obj-C sources, Android binaries) is installed from npm
                url "$rootDir/../node_modules/react-native/android"
            }
     +      flatDir {
     +          dirs 'libs'
     +          dirs project(':react-native-adverserve').file('libs')
     +      }
        }
    }
    ```
    
    ### iOS
    
    Recommended way to integrate is [`Cocoapods`](https://cocoapods.org)
    
    #### Option: Cocoapods
    
    * Edit your `Podfile` to look like this
    
    ```
    +   pod 'react-native-adverserve', :path => '../node_modules/react-native-adverserve'
    
    end
    ```
    
    #### Option: Manual
    
    TODO: Add manual instructions
    
    ### Example
    
    ```jsx
    import React, {Component} from 'react';
    import {StyleSheet, View} from 'react-native';
    import AdBanner, {OptOutHelper} from 'react-native-adverserve'
    
    export default class App extends Component<Props> {
      render() {
        return (
          <View style={styles.container}>
            <AdBanner
              style={{width: '90%', backgroundColor: 'red', height: '90%'}}
              networkId={"3360"}
              contentUnitId={"4339620"}
              onAdClicked={() => console.warn('Ad Clicked')}
              onAdLoaded={() => console.warn('Ad Loaded')}
            />
          </View>
        );
      }
    }
    ```
    
### Supported Props
    
   | Prop | Type | Required | 
   | ---- | ---- | -------- |
   | networkId | string | Yes |
   | contentUnitId | string | Yes |
   | isInline | bool | No |
   | gdprApplies | bool | No |
   | onAdClicked | function | No |
   | onAdLoaded | function | No |
   | beforeAdSDKEvent | function | No |
   | onAdSDKEvent | function | No |
   | onAdSDKError | function | No |
   | onAdFiredEvent | function | No |
    
### Other functionalities
    
  Following classes are available `CookieManager`, `DoNotTrackHelper`, `OptOutHelper`
    
### Opt out user

  * Initialize a new instance of `OptOutHelper`
  
   ```
   const networkID = '1234'
   const helper = new OptOutHelper(networkID)
   OptOutHelper.optIn()
   OptOutHelper.optOut()
   OptOutHelper.status(status => console.warn(status))
   ```    
    
### Do not track user

   ```
   DoNotTrackHelper.enableLimitedTracking(true) // or false
   DoNotTrackHelper.isLimitedTrackingEnabled(isEnabled => console.warn(isEnabled)) 
   ```
   
### Clear cookies

  ```
  CookieManager.removeAllCookies()
  ```   