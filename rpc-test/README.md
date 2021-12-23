# rpc-test

RPC::CommunicatorClient test

| Arg | Description | Default |
| :-------- | :-------- | :-------- |
| 1 | payload | https://google.com |
| 2 | interface name | SecurityAgent |
| 3 | endpoint | /tmp/SecurityAgent/token |
| 4 | repeat count | 1 |

> RPC::Communicator is not TCP and the buffer size is 8120

```shell script
# /opt/rpc-test https://google.com SecurityAgent /tmp/SecurityAgent/token 10 
errCode: 0 (0), result: 'eyJhbGci...' [time:0.152598s, params:18b, result:99b]
...
errCode: 0 (0), result: 'eyJhbGci...' [time:0.145045s, params:18b, result:99b]

# /opt/rpc-test "http://www.freakinghugeurl.com/refer.php?count=12&url=Vm0wd2QyUXlVWGxXYTJoV1YwZG9WVll3Wkc5alJ..." SecurityAgent /tmp/SecurityAgent/token 10 
errCode: 0 (0), result: 'eyJhbGci...' [time:0.153237s, params:10918b, result:14633b]
...
errCode: 0 (0), result: 'eyJhbGci...' [time:0.148468s, params:10918b, result:14633b]
```
