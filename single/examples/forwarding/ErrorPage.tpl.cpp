//this file is created by a tool [tpl2c]
#include<webearl>
using namespace webe;
void getErrorPage_TPL(Request &request,Response &response)
{
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<meta charset=\"utf-8\">");
response.write("<head>");
response.write("<title>Web Projector</title>");
response.write("</head>");
response.write("<body>");
response.write("<!--");
response.write("The following will be replaced by the key value map of Request object by server");
response.write("-->");
response.write("<h1>");
response.write(request.getValue("error"));
response.write("</h1>");
response.write("<br>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
}