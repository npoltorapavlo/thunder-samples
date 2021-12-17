# thunder-samples
Code samples for [Thunder (WPEFramework)](https://github.com/rdkcentral/Thunder)

| Name | Description |
| :-------- | :-------- |
| [wpeframework-test](wpeframework-test) | JSONRPC::LinkType stress test |
| [jsonrpc-test](jsonrpc-test) | JSONRPC::LinkType test |
| [wpeframework-timer](wpeframework-timer) | wait Core::TimerType in dtor |
| [rpc-test](rpc-test) | RPC::CommunicatorClient test |
| [secapi-token](secapi-token) | secapi jwt token |
| [jsonrpc-high-load](jsonrpc-high-load) | JSONRPC::LinkType performance test |

# build
The table below lists ways to build

| Type | Example |
| :-------- | :-------- |
| yocto | `devtool add --autorev thunder-samples "https://github.com/npoltorapavlo/thunder-samples.git;branch=main" && devtool build thunder-samples` |
