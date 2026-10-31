#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
char response[500];  //5000 is bad, will change it later
char request[500];
WORD ver;
WSADATA wsaData;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int SuccessCode;
int len;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);   //socket library initialized
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
SuccessCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(SuccessCode<0)
{
printf("Unable to bind socket to port 5050\n");
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,10);
printf("Server is ready to accept request on port 5050\n");
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept client connection");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
SuccessCode=recv(clientSocketDescriptor,request,sizeof(request),0);
if(SuccessCode>0)
{
printf("Request arrived\n");
printf("%s\n",request);
}
strcpy(response,"Welcome to earlorithm");
SuccessCode=send(clientSocketDescriptor,response,strlen(response)+1,0);
if(SuccessCode>0)
{
printf("Response sent\n");
}
else
{
printf("Unable to send response\n");
}
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}