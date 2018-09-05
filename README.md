### TCP Client / Server system for communicating with several simultaneously on the network.


# Client side: 

##### Usage:

```sh
$ ./client <server-ip> <port> <username>
```

##### Connects to the server and declares yourself with the username provided as parameter.


  The client sends messages (text) to the server. and the server send them to all connected users.
  
  The client accepts the following commands typed:

- :help&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;List all available commands
- :quit&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The client leaves and reports it to the server.
- :who&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Asks the server for the list of connected users.


### Todos

 - code documentation


Are you looking for the [server] ?

License
----

MIT


   [server]: <https://github.com/osmankh/tcpserver>
