#include "Socket.h"
#include <iostream>
#include <string>
#include <time.h>
#include <chrono>

std::string getCurrentTimestamp()
{
using std::chrono::system_clock;
auto currentTime = std::chrono::system_clock::now();
char buffer[80];

auto transformed = currentTime.time_since_epoch().count() / 1000000;

auto millis = transformed % 1000;

std::time_t tt;
tt = system_clock::to_time_t ( currentTime );
auto timeinfo = localtime (&tt);
strftime (buffer,80,"%F %H:%M:%S",timeinfo);
sprintf(buffer, "%s:%03d",buffer,(int)millis);

return std::string(buffer);
}

int main(int argc, int argv[])
{
  while (1)
  {
    std::cout << getCurrentTimestamp() << "\t";  

    try
    {

      ClientSocket client_socket("localhost", 30000);

      std::string reply;

      try
      {
        client_socket << "Test message.";
        client_socket >> reply;
      }
      catch (SocketException &)
      {
      }

      std::cout << "We received this response from the server:\n\"" << reply << "\"\n";
      ;
    }
    catch (SocketException &e)
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }
  }

  return 0;
}
