# wpeframework-timer

wait Core::TimerType in dtor

>Thunder client subscribes to events w/ interval 5500 ms between attempts. There's a race condition between timer callback and destruction.

| Arg | Description | Default |
| :-------- | :-------- | :-------- |
| 1 | client lifetime, ms | |
| 2 | wait for timer completion | |
| 3 | callsign | |
| 4 | events | |

>Not waiting for timer completion, a thread uses destructed members:
```shell script
root@pacexi5:~# /opt/wpeframework-timer 5500 false "org.rdk.HdmiCecSink" "arcInitiationEvent" "arcTerminationEvent" "shortAudiodesciptorEvent"
token status: 97
[Singleton.h:96](SingletonType)<5186><1>: Singleton constructing LinkType<WPEFramework::Core::JSON::IElement>::CommunicationChannel::ChannelProxy::Administrator
[Singleton.h:96](SingletonType)<5186><1>: Singleton constructing LinkType<WPEFramework::Core::JSON::IElement>::CommunicationChannel::FactoryImpl
Getting status for callSign org.rdk.HdmiCecSink, status: 11
Activating org.rdk.HdmiCecSink
[JSONRPCLink.h:159](Send)<5186><1>: Message: {"jsonrpc":"2.0","id":1,"method":"status@org.rdk.HdmiCecSink"} send
[JSONRPCLink.h:159](Send)<5186><1>: Message: {"jsonrpc":"2.0","id":2,"method":"activate","params":{"callsign":"org.rdk.HdmiCecSink"}} send
Activate with params {"callsign":"org.rdk.HdmiCecSink"}, status: 22, response: {}
Starting the timer
onTimer
onTimer acquired lock
[JSONRPCLink.h:159](Send)<5186><1>: Message: {"jsonrpc":"2.0","id":3,"method":"status@org.rdk.HdmiCecSink"} send
~ThunderClient
Getting status for callSign �, status: 22
Could not subscribe this time, one more attempt in 5500 msec. Plugin is BLOCKED
[JSONRPCLink.h:159](Send)<5186><1>: Message: {"jsonrpc":"2.0","id":4,"method":"status@�"} send
Getting status for callSign �, status: 22
Activating �
[JSONRPCLink.h:159](Send)<5186><1>: Message: {"jsonrpc":"2.0","id":5,"method":"activate","params":{"callsign":"�"}} send
Activate with params {"callsign":"�"}, status: 22, response: {}
```

>Waiting for timer completion:
```shell script
root@pacexi5:~# /opt/wpeframework-timer 5500 true "org.rdk.HdmiCecSink" "arcInitiationEvent" "arcTerminationEvent" "shortAudiodesciptorEvent"
token status: 97
[Singleton.h:96](SingletonType)<7371><1>: Singleton constructing LinkType<WPEFramework::Core::JSON::IElement>::CommunicationChannel::ChannelProxy::Administrator
[Singleton.h:96](SingletonType)<7371><1>: Singleton constructing LinkType<WPEFramework::Core::JSON::IElement>::CommunicationChannel::FactoryImpl
Getting status for callSign org.rdk.HdmiCecSink, status: 11
Activating org.rdk.HdmiCecSink
[JSONRPCLink.h:159](Send)<7371><1>: Message: {"jsonrpc":"2.0","id":1,"method":"status@org.rdk.HdmiCecSink"} send
[JSONRPCLink.h:159](Send)<7371><1>: Message: {"jsonrpc":"2.0","id":2,"method":"activate","params":{"callsign":"org.rdk.HdmiCecSink"}} send
Activate with params {"callsign":"org.rdk.HdmiCecSink"}, status: 22, response: {}
Starting the timer
onTimer
onTimer acquired lock
~ThunderClient
[JSONRPCLink.h:159](Send)<7371><1>: Message: {"jsonrpc":"2.0","id":3,"method":"status@org.rdk.HdmiCecSink"} send
Getting status for callSign org.rdk.HdmiCecSink, status: 22
Could not subscribe this time, one more attempt in 5500 msec. Plugin is BLOCKED
[JSONRPCLink.h:159](Send)<7371><1>: Message: {"jsonrpc":"2.0","id":4,"method":"status@org.rdk.HdmiCecSink"} send
Getting status for callSign org.rdk.HdmiCecSink, status: 22
Activating org.rdk.HdmiCecSink
[JSONRPCLink.h:159](Send)<7371><1>: Message: {"jsonrpc":"2.0","id":5,"method":"activate","params":{"callsign":"org.rdk.HdmiCecSink"}} send
Activate with params {"callsign":"org.rdk.HdmiCecSink"}, status: 22, response: {}
~ThunderClient acquired lock
```

>Not waiting for timer completion, Core::TimerType joins the thread:
```shell script
root@pacexi5:~# /opt/wpeframework-timer 8000 false "org.rdk.System"
token status: 97
[Singleton.h:96](SingletonType)<19485><1>: Singleton constructing LinkType<WPEFramework::Core::JSON::IElement>::CommunicationChannel::ChannelProxy::Administrator
[Singleton.h:96](SingletonType)<19485><1>: Singleton constructing LinkType<WPEFramework::Core::JSON::IElement>::CommunicationChannel::FactoryImpl
Getting status for callSign org.rdk.System, status: 11
Activating org.rdk.System
[JSONRPCLink.h:159](Send)<19485><1>: Message: {"jsonrpc":"2.0","id":1,"method":"status@org.rdk.System"} send
[JSONRPCLink.h:159](Send)<19485><1>: Message: {"jsonrpc":"2.0","id":2,"method":"activate","params":{"callsign":"org.rdk.System"}} send
Activate with params {"callsign":"org.rdk.System"}, status: 0, response: {}
Starting the timer
onTimer
onTimer acquired lock
[JSONRPCLink.h:159](Send)<19485><1>: Message: {"jsonrpc":"2.0","id":3,"method":"status@org.rdk.System"} send
Getting status for callSign org.rdk.System, result: activated
Timer stopped.
Subscription completed.
~ThunderClient
root@pacexi5:~# 
```
