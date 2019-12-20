//
// Created by omer on 19/12/2019.
//

#include "OpenServerCommand.h"
#include <string>
#include <thread>
/*NOTE: below includes like in tirgul_6 page 31*/
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;
OpenServerCommand::OpenServerCommand(int port) : port(port) {}
int OpenServerCommand::execute() {
  t(openServer);
  return 0;
}

int OpenServerCommand::openServer() {
  int sockfd, client_sock;
  sockaddr_in address;

  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd == -1) {
    cerr<<"Could not create a socket."<<endl;
    return -1;
  }

  address.sin_family = AF_INET; // address is in IPv4
  address.sin_addr.s_addr = INADDR_ANY; // give me any ip alloc'd for my machine
  address.sin_port = htons(this->port); /* convert our port to value
                                                 that the network understands.*/
  if(bind(sockfd, (struct sockaddr*)&address, sizeof(address)) == -1) {
    cerr<<"Could not bind the socket to an IP"<<endl;
    return -2;
  }

  //TODO figure out how many 'clients' in our listening queue (currently 2).
  if(listen(sockfd, 2) == -1) {
    cerr<<"Error during listening command"<<endl;
  }

  client_sock = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&address);
  //TODO continue connection sequence
  if(client_sock == -1) {
    cerr<<""<<endl;
  }



}
