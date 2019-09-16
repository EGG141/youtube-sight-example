# YouTube Sight example

[YouTube Sight](http://tools.tastethecode.com/youtube-sight) is an application that allows you to pull in your actual subscribers count from the YouTube Analytics API after the [change](https://support.google.com/youtube/thread/6543166?msgid=13119244) that YouTube made where the subscribers data on the YouTube Data API was aggregated. 

Since most of the already built subscriber counters used just a single [API library](https://github.com/witnessmenow/arduino-youtube-api) they will no longer work as expected and only show the aggregated subscriber counts. 

The challenge with the YouTube Analytics API is that it can only be authorized through OAuth2 and this is not possible with devices without browser, so YouTube Sight functions as a relay when once you give a consent it provides you with a URL that you can access from Arduino to again display your full subscriber count. 

