#include "figure.hpp"
#include <string>

using namespace std;

int main ( int argc, char *argv[] ){
  try{
      PlotApp ( argc, argv );
  }
  catch (const exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return EXIT_FAILURE;
  }
}
