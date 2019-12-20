//
// Created by omer on 19/12/2019.
//

#include "OpenServerCommand.h"

#include <string>
#include <thread>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
using namespace std;

void startListening(int, sockaddr_in);

int OpenServerCommand::execute() {
  int sockfd, client_sock;
  sockaddr_in address{};

  sockfd = socket(AF_INET,SOCK_STREAM,0);

  // error
  if(sockfd == -1) {
    cerr<<"Could not create a socket."<<endl;
    return -1;
  }

  address.sin_family = AF_INET; // address is in IPv4
  address.sin_addr.s_addr = INADDR_ANY; // give me any ip alloc'd for my machine
  address.sin_port = htons(this->port); // more info tirgul 6 page 32

  //error
  if(bind(sockfd, (struct sockaddr*)&address, sizeof(address)) == -1) {
    cerr<<"Could not bind the socket to an IP"<<endl;
    return -2;
  }

  // Cant run new thread with myThread, so made a new one and moved it.
  // The new thread runs startListening in the back until flag is off.
  thread tmp(startListening, sockfd, address);
  this->myThread = move(tmp);

  // TODO who ends this loop? flag + join() = something is wrong here..
  while(this->listening) {
    this->myThread.join();
  }
  return 0;
}

void startListening(int sockfd, sockaddr_in address) {
  int client_sock;

  //TODO figure out how many 'clients' in our listening queue (currently 2).
  if(listen(sockfd, 2) == -1) {
    cerr<<"Error during listening command"<<endl;
  }

  client_sock = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&address);
  if(client_sock == -1) {
    cerr<<"Error accepting client's connection request"<<endl;
  }

}
