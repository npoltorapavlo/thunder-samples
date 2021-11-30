# jsonrpc-high-load

JSONRPC::LinkType performance test

> with high payload (32k)

```shell script
root@pacexi5:/opt# ./jsonrpc-high-load 
token is 'eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2xvY2FsaG9zdA.Tg3rfvW7Cpk4LqkrnD_WhXQDyo9n2nMExaL8e2soICM'
status@org.rdk.VoiceControl errCode: 11, result: '[]', time: 30000928 (timeout 30000 ms)
sendVoiceMessage errCode: 11, result: '{}', time: 30003562 (timeout 30000 ms)
status@org.rdk.VoiceControl errCode: 0, result: '[{"callsign":"org.rdk.VoiceControl","locator":"libWPEFrameworkVoiceControl.so","classname":"VoiceControl","autostart":false,"precondition":["Platform"],"state":"activated","observers":0,"module":"VoiceControl","hash":"engineering_build_for_debug_purpose_only"}]', time: 295878 (timeout 30000 ms)
status@org.rdk.VoiceControl errCode: 0, result: '[{"callsign":"org.rdk.VoiceControl","locator":"libWPEFrameworkVoiceControl.so","classname":"VoiceControl","autostart":false,"precondition":["Platform"],"state":"activated","observers":0,"module":"VoiceControl","hash":"engineering_build_for_debug_purpose_only"}]', time: 3405983 (timeout 30000 ms)
status@org.rdk.VoiceControl errCode: 0, result: '[{"callsign":"org.rdk.VoiceControl","locator":"libWPEFrameworkVoiceControl.so","classname":"VoiceControl","autostart":false,"precondition":["Platform"],"state":"activated","observers":0,"module":"VoiceControl","hash":"engineering_build_for_debug_purpose_only"}]', time: 1742 (timeout 30000 ms)
status@org.rdk.VoiceControl errCode: 0, result: '[{"callsign":"org.rdk.VoiceControl","locator":"libWPEFrameworkVoiceControl.so","classname":"VoiceControl","autostart":false,"precondition":["Platform"],"state":"activated","observers":0,"module":"VoiceControl","hash":"engineering_build_for_debug_purpose_only"}]', time: 2253 (timeout 30000 ms)
status@org.rdk.VoiceControl errCode: 0, result: '[{"callsign":"org.rdk.VoiceControl","locator":"libWPEFrameworkVoiceControl.so","classname":"VoiceControl","autostart":false,"precondition":["Platform"],"state":"activated","observers":0,"module":"VoiceControl","hash":"engineering_build_for_debug_purpose_only"}]', time: 1731 (timeout 30000 ms)
...
```
