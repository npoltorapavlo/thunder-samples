# rpc-test

RPC::CommunicatorClient test

| Arg | Description | Default |
| :-------- | :-------- | :-------- |
| 1 | payload | https://google.com |
| 2 | interface name | SecurityAgent |
| 3 | endpoint | /tmp/SecurityAgent/token |
| 4 | repeat count | 1 |

```shell script
root@pacexi5:~# /opt/rpc-test 
Interface is 0x33c88
CreateToken 0
Token for 'https://google.com' is 'eyJhbGc...'
```
