#ifndef __TPL__
#define __TPL__
#include<webearl>
using namespace webe;
void getErrorPage_TPL(Request &request,Response &response);
void registerTPLs(WebProjector *server)
{
server->onRequest("/ErrorPage.tpl",getErrorPage_TPL);
}
#endif 