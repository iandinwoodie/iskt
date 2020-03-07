#include "Client.h"
#include "Server.h"
#include <QCoreApplication>
#include <cstdlib>
#include <exception>
#include <iostream>

int main(int argc, char** argv)
{
  try {
    std::cout << "\n*** Monitoring with iskt ***\n" << std::endl;
    QCoreApplication app(argc, argv);
    Server server(&app);
    server.listen(/*port*/ 8080);

    //Client client(&app);
    //client.connectToHost(/*address*/ "localhost", /*port*/ 8080);
    //client.write("GET /favicon.ico HTTP/1.1\r\n\r\n\r\n\r\n");

    return app.exec();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;

    return EXIT_FAILURE;
  }
}
