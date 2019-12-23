//
// Created by omer on 19/12/2019.
//

#define MAX_CHARS 1024
#define MAX_CLIENTS 1


#include "OpenServerCommand.h"
#include "Lexer.h"
#include "Parser.h"
using namespace std;

OpenServerCommand::OpenServerCommand(string port)  {
  try{
    this->port = stoi(port);
  } catch (const char* e) {
    cout<<e<<endl;
  }
};

int OpenServerCommand::execute() {
  int sockfd=0, client_sock=0, valRead=0;
  char *buffer[MAX_CHARS];
  sockaddr_in address{};

  Parser* parser = new Parser();

  // OPEN SOCKET
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd == -1) {
    cerr<<"Could not create a socket."<<endl;
    return -1;
  }

  address.sin_family = AF_INET; // address is in IPv4
  address.sin_addr.s_addr = INADDR_ANY; // give me any ip alloc'd for my machine
  address.sin_port = htons(this->port); // more info tirgul 6 page 32

  // BIND
  if(bind(sockfd, (struct sockaddr*)&address, sizeof(address)) == -1) {
    cerr<<"Could not bind the socket to an IP"<<endl;
    return -2;
  }


  //TODO make loop run in its own thread - should end when error?
  // should end when user requests?
  while(this->listening == true) {
    // LISTEN
    if(listen(sockfd,MAX_CLIENTS) == -1) {
      sleep(250);
      continue;
    }

    // ACCEPT
    client_sock = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&address);
    if (client_sock == -1) {
      sleep(250);
      continue;
    }

    valRead = read(client_sock,buffer,MAX_CHARS);
    string bufferStr(*buffer);

    for (string str : Lexer::analyzeLine(bufferStr) {
      //TODO implement this: partTake these instructions and do something about it.
    }
  }

  return 0;
}
