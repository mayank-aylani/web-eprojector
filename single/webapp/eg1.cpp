#include<webearl>
using namespace webe;
/*
Increment-1
void registerRequest()
{
cout<<"function registerRequest invoked on server side";
}
*/


/*
Increment-2
void registerRequest(int dataCount,char *data[])
{
cout<<"function registerRequest invoked on server side";
if(dataCount>0) cout<<"Data in arrived in GET : "<<"\n";
for(int i=0;i<dataCount;++i)
{
cout<<data[i]<<"\n";
}
}
*/


/*
Increment-3
void registerRequest(Request &request,Response &response)
{
string name=request.get("name");
string city=request.get("city");
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<title>Web Projector</title>");
response.write("<meta charset='utf-8'>");
response.write("</head>");
response.write("<body>");
response.write("Hello");
response.write(name);
response.write("<br>");
response.write("Registration completed");
response.write("</body>");
response.write("</html>");
}
*/

int main()
{
WebProjector server(5050);
server.onRequest("/register",registerRequest);
server.start();
return 0;
}