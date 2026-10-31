#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct __request
{
char *method;  //get or post
char *resource;
char isClientSideTechnologyResource;
char *mimeType;
}REQUEST;

int extensionEquals(const char *left,const char *right)
{
char a,b;
while(*left && *right)
{
a=*left;
b=*right;
if(a>=65 && a<=90) a+=32;
if(b>=65 && b<=90) b+=32;
if(a!=b) return 0;
left++;
right++;
}
return *left==*right;
}

char * getMIMEType(char *resource)
{
char *mimeType;
mimeType=NULL;
int len=strlen(resource);
if(len<4) return mimeType;
int lastIndexOfDot=len-1;
while(lastIndexOfDot>0 && resource[lastIndexOfDot]!='.') lastIndexOfDot--;
if(lastIndexOfDot==0) return mimeType;
if(extensionEquals(resource+lastIndexOfDot+1,"html"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
if(extensionEquals(resource+lastIndexOfDot+1,"css"))
{
mimeType=(char *)malloc(sizeof(char)*9);
strcpy(mimeType,"text/css");
}
if(extensionEquals(resource+lastIndexOfDot+1,"js"))
{
mimeType=(char *)malloc(sizeof(char)*16);
strcpy(mimeType,"text/javascript");
}
return mimeType;
}

char isClientSideResource(char *resource)
{
return 'Y';  //should be changed
}

REQUEST * parseRequest(char *bytes)
{
char method[11];   //GET,DELETE,POST,...
char resource[1001];
int i,j;
for(i=0;bytes[i]!=' ';i++) method[i]=bytes[i];
method[i]='\0';
i+=2;
for(j=0;bytes[i]!=' ';j++,i++) resource[j]=bytes[i];
resource[j]='\0';
REQUEST *request=(REQUEST *)malloc(sizeof(REQUEST));
request->method=(char *)malloc((sizeof(char)*strlen(method))+1);
strcpy(request->method,method);
if(resource[0]=='\0')
{
request->resource=NULL;
request->isClientSideTechnologyResource='Y';
request->mimeType=NULL;
}
else
{
request->resource=(char *)malloc((sizeof(char)*strlen(resource))+1);
strcpy(request->resource,resource);
request->isClientSideTechnologyResource=isClientSideResource(resource);
request->mimeType=getMIMEType(resource);
}
return request;
}


int main()
{
int i;
char responseBuffer[1025];  //chunk size 1024
char requestBuffer[8193];  //1024*8
int bytesExtracted;
WORD ver;
WSADATA wsaData;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int successCode;
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
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
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
bytesExtracted=recv(clientSocketDescriptor,requestBuffer,8192,0);
if(bytesExtracted<0)
{
//what to do is yet to be decided
}
else if(bytesExtracted==0)
{
//what to do is yet to be decided
}
else
{
requestBuffer[bytesExtracted]='\0';
REQUEST *request=parseRequest(requestBuffer);
if(request->isClientSideTechnologyResource)
{
/*
if request->resource==NULL look for index.html and serve
else look for index.htm and serve
else send back 404
*/
}
else
{
//what to do in case of server side resource is yet to be decided
}
}
strcpy(responseBuffer,"Welcome to earlorithm");
successCode=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer)+1,0);
if(successCode>0)
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