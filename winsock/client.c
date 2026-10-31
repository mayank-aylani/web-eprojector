#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
WORD ver;
WSADATA wsaData;
int clientSocketDescriptor;
int serverSocketDescriptor;
struct sockaddr_in serverSocketInformation;
char request[500];
char response[500];
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(clientSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
strcpy(request,"Hello earlorithm, I want to connect");
send(clientSocketDescriptor,request,strlen(request)+1,0);
recv(clientSocketDescriptor,response,sizeof(response),0);
printf("Response received\n");
printf("%s\n",response);
closesocket(clientSocketDescriptor);
WSACleanup();
return 0;
}