#include "tpl.h"  //tpl.h is in working directory
#include<webearl>
using namespace webe;
void getCity(Request &request,Response &response)
{
string cityCodeString=request.get("cityCode");
int cityCode=atoi(cityCodeString.c_str());
if(cityCode==1) request.forward("Ujjain.html");
else if(cityCode==2) request.forward("Indore.html");
else if(cityCode==3) request.forward("Mumbai.html");
else if(cityCode==4) request.forward("Bangalore.html");
else 
{
request.setKeyValue("error","Invalid choice");
//request.forward("errorPage");
/*
on next increment
*/
request.forward("ErrorPage.tpl");
}
}
void enquiry(Request &request,Response &response)
{
string name=request.get("name");
string city=request.get("city");
string address=request.get("address");
string message=request.get("message");
//some logic to save data somewhere, database or file
request.forward("Notify.html");
}
void sendErrorPage(Request &request,Response &response)
{
/*
string errorMessage=request.get("error");
an HTML that displays a page with error message
send HTML using response.write(...);
*/
//next increment, web developer will write this HTML in other file
}
int main()
{
WebProjector server(5050);
server.onRequest("/getCity",getCity);
server.onRequest("/enquiry",enquiry);
server.onRequest("/errorPage",sendErrorPage);
registerTPLs(&server);  //for template, [.tpl.cpp]
server.start();
return 0;
}