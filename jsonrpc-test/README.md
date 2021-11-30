# jsonrpc-test

JSONRPC::LinkType test

| Arg | Description | Default |
| :-------- | :-------- | :-------- |
| 1 | use token | false | 
| 2 | timeout | |
| 3 | designator | |
| 4 | params | |
| 5 | ... (Arg 2,3,4) | |

JSONRPC::LinkType error codes

| Description | Steps | Error |
| :-------- | :-------- | :-------- |
| Not activated | /opt/jsonrpc-test true \\<br>30000 org.rdk.System.1.getPowerStateBeforeReboot {} | ERROR_UNAVAILABLE<br>2 |
| No token | TIMEFORMAT=%R; time \\<br>/opt/jsonrpc-test false \\<br>30000 org.rdk.System.1.getPowerStateBeforeReboot {} | ERROR_ASYNC_FAILED<br>3<br>0.221 |
| Not permitted | /opt/jsonrpc-test true \\<br>30000 Messenger.acl {} | ERROR_PRIVILIGED_REQUEST<br>4294934692 (-32604) |
| Timeout | /opt/jsonrpc-test true \\<br>100 org.rdk.System.1.getXconfParams {} | ERROR_TIMEDOUT<br>11 |
| Can't activate | cp /etc/WPEFramework/plugins/LocationSync.json /opt/<br>sed -i 's/jsonip.metrological.com/badurl/g' /opt/LocationSync.json<br>mount -o bind /opt/LocationSync.json /etc/WPEFramework/plugins/LocationSync.json<br>systemctl restart wpeframework<br>/opt/jsonrpc-test true \\<br>30000 activate '{"callsign":"LocationSync.1"}' | ERROR_OPENING_FAILED<br>6 |
| No plugin | /opt/jsonrpc-test true \\<br>30000 foo.bar {} | ERROR_BAD_REQUEST<br>4294934693 (-32603) |
| No method | /opt/jsonrpc-test true \\<br>30000 org.rdk.System.1.foo {} | ERROR_UNKNOWN_KEY<br>4294934695 (-32601) |
| Version doesn't exist | /opt/jsonrpc-test true \\<br>30000 org.rdk.System.999.getLastFirmwareFailureReason {} | ERROR_INVALID_SIGNATURE<br>4294934694 (-32602) |
| Wrong version | /opt/jsonrpc-test true \\<br>30000 org.rdk.System.1.getLastFirmwareFailureReason {} | ERROR_UNKNOWN_KEY<br>4294934695 (-32601) |
| Invalid designator | /opt/jsonrpc-test true \\<br>30000 foobar {} | ERROR_UNKNOWN_KEY<br>4294934695 (-32601) |
| Not running | systemctl stop wpeframework<br>/opt/jsonrpc-test true \\<br>30000 org.rdk.System.2.getLastFirmwareFailureReason {} | ERROR_TIMEDOUT<br>11 |
| Method returns error | /opt/jsonrpc-test true \\<br>30000 Messenger.1.send '{"roomid":"","message":""}' | ERROR_UNKNOWN_KEY<br>22 |

Web error codes

| Description | Steps | Code/message |
| :-------- | :-------- | :-------- |
| Not activated | curl -H "Authorization: Bearer $t" -d \\<br>'{"jsonrpc":"2.0","id":"3", "method":"org.rdk.System.1.getPowerStateBeforeReboot"}' \\<br>http://127.0.0.1:9998/jsonrpc | 2<br>"Service is not active" |
| No token | TIMEFORMAT=%R; time \\<br>curl -d \\<br>'{"jsonrpc":"2.0","id":"3", "method":"org.rdk.System.1.getPowerStateBeforeReboot"}' \\<br>http://127.0.0.1:9998/jsonrpc | -32604<br>"Request needs authorization. Missing or invalid token."<br>0.016 |
| Not permitted | curl -H "Authorization: Bearer $t" \\<br>-d '{"jsonrpc":"2.0","id":"3", "method":"Messenger.1.acl"}' \\<br>http://127.0.0.1:9998/jsonrpc | -32604<br>"Request needs authorization. Missing or invalid token." |
| Timeout | - | - |
| Can't activate | curl -H "Authorization: Bearer $t" \\<br>-d '{"jsonrpc":"2.0","id":"3", "method":"Controller.1.activate", "params":{"callsign":"LocationSync.1"}}' \\<br>http://127.0.0.1:9998/jsonrpc | 6<br>"ERROR_OPENING_FAILED" |
| No plugin | curl -H "Authorization: Bearer $t" \\<br>-d '{"jsonrpc":"2.0","id":"3", "method":"foo.bar"}' \\<br>http://127.0.0.1:9998/jsonrpc | -32603<br>"Could not access requested service" |
| No method | curl -H "Authorization: Bearer $t" \\<br>-d '{"jsonrpc":"2.0","id":"3", "method":"org.rdk.System.1.foo"}' \\<br>http://127.0.0.1:9998/jsonrpc | -32601<br>"Unknown method." |
| Version doesn't exist | curl -H "Authorization: Bearer $t" \\<br>-d '{"jsonrpc":"2.0","id":"3", "method":"org.rdk.System.999.getLastFirmwareFailureReason"}' \\<br>http://127.0.0.1:9998/jsonrpc | -32602<br>"Requested version is not supported." |
| Wrong version | curl -H "Authorization: Bearer $t" \\<br>-d '{"jsonrpc":"2.0","id":"3", "method":"org.rdk.System.1.getLastFirmwareFailureReason"}' \\<br>http://127.0.0.1:9998/jsonrpc | -32601<br>"Unknown method." |
| Invalid designator | curl -H "Authorization: Bearer $t" \\<br>-d '{"jsonrpc":"2.0","id":"3", "method":"foobar"}' \\<br>http://127.0.0.1:9998/jsonrpc | -32601<br>"Unknown method." |
| Not running | - | - |
| Method returns error | curl -H "Authorization: Bearer $t" \\<br>-d '{"jsonrpc":"2.0","id":"3", "method":"Messenger.1.send", "params":{"roomid":"","message":""}}' \\<br>http://127.0.0.1:9998/jsonrpc | 22<br>"ERROR_UNKNOWN_KEY" |
