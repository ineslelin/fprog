#include <iostream>
#include <cmath>
#include <sstream>

// using namespace std;

struct Quader
{
  int a;
  int b;
  int c;
};

int Volume(Quader const& quader);
int Surface(Quader const& quader);
float Diagonal(Quader const& quader);

std::string FormatResults(int const& V, int const& A, float const& d);
void PrintOutput(std::string const& text);

int main(int argc, char *argv[])
{
  Quader quader = {2, 3, 4};

  int V = 0;
  int A = 0;
  float d = 0;

  V = Volume(quader);
  A = Surface(quader);
  d = Diagonal(quader);

  std::string output = FormatResults(V, A, d);
  PrintOutput(output);
  
  return 0;
}

int Volume(Quader const& quader)
{
  return quader.a * quader.b * quader.c;
}

int Surface(Quader const& quader)
{
  return 2 * (quader.a * quader.b + quader.a * quader.c + quader.b * quader.c);
}

float Diagonal(Quader const& quader)
{
  return sqrt(pow(quader.a, 2) + pow(quader.b, 2) + pow(quader.c, 2));
}

std::string FormatResults(int const& V, int const& A, float const& d)
{
  std::stringstream output;

  output << "Volumen: " << V << " Oberfläche: " << A << " Diagonale: " << d << std::endl;

  return output.str();
}

void PrintOutput(std::string const& text)
{
  std::cout << text;
}