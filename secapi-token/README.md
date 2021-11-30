# secapi-token

secapi jwt token

| Arg | Description | Default |
| :-------- | :-------- | :-------- |
| 1 | payload | "http://google.com" |
| 2 | num of forks | 2 |
| 3 | num of threads | 2 |
| 4 | num of iterations | 5 |

| Build option | Description | Default |
| :-------- | :-------- | :-------- |
| SECAPI_LIB | scapi lib name(s) | sec_api_crypto sec_api_common_crypto |

```shell script
root@pacexi5:~# /opt/secapi-token
starting pid 9171 payload=http://google.com numForks=2 numThreads=2 numIterations=5
ending pid 9171
forked child process pid 9175
root@pacexi5:~# forked child process pid 9174
[pid:9174] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9174] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9175] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9175] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9174] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9174] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9175] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9175] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9174] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9175] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9175] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9174] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9174] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9175] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9174] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9175] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9174] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9175] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
[pid:9174] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
ending pid 9174
[pid:9175] passed. Token : eyJhbGciOiIiLCJ0eXAiOiJKV1QifQ.aHR0cDovL2dvb2dsZS5jb20.GM0OFa6oCrY8oEKBzKOmWhZ9cRXwYpF1pqFkbK8sPRg
ending pid 9175

root@pacexi5:~#
```
