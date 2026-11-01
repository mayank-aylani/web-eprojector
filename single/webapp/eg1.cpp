#include<webearl>
using namespace webe;
int main()
{
WebProjector server(5050);
server.start();
return 0;
}