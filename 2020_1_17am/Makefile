.PHONY:all
all:server client
cc=g++

client:UdpClient.cpp
	$(cc) -o $@ $^
server:UdpServer.cpp
	$(cc) -o  $@ $^

.PHONY:clean
clean:
	rm -rf client server

