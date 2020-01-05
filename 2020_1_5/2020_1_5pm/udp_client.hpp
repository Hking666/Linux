#pragma once
#include "udp_server.hpp"
#include "udp_socket.hpp"
class UdpClient
{
    public:
    UdpClient(const std::string& ip , uint16_t port) 
        :server_ip_(ip)
        ,server_port(port)
        ,sock_.CreateSocket();
    {

    }

   ~UdpClient()
   {
        sock_.Close();
   }

   bool Recvfrom(std::string*msg)
   {

       return sock_.RecvFrom(msg);
   }
   
   bool Sendto(const std::string& msg)
   {
       return sock_SendTo(msg,server_ip_,server_port_)
   }
    private:
        UdpSocket sock_;
        std::string server_ip_;
        uint16_t server_port_;

}

