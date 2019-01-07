require 'json'
package = JSON.parse(File.read('package.json'))

Pod::Spec.new do |s|
  s.name           = "react-native-adverserve"
  s.version        = package["version"]
  s.summary        = package["description"]
  s.homepage       = "https://www.adition.com/en/"
  s.author         = { "Hunaid Hassan" => "hhunaid@gmail.com" }
  s.ios.deployment_target = '7.0'
  s.license        = "Proprietary"
  s.source_files   = 'ios/ReactNativeAdverServe/*.{h,m}'
  s.source       = { :git => "https://github.com/oblador/react-native-keychain.git", :tag => "v#{s.version}" }
  s.vendored_frameworks = "ios/AditionAdsLib.framework"
  s.frameworks     = "AdSupport", "AssetsLibrary", "EventKit", "MediaPlayer", "MessageUI", "MobileCoreServices", "SystemConfiguration"
  s.library        = "z", "c++"
  s.dependency 'React'
end