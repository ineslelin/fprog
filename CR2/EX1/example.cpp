#include <iostream>
#include <cmath>
#include <sstream>

struct Quader
{
  int a;
  int b;
  int c;
};

auto Volume = [](Quader const& quader) { return quader.a * quader.b * quader.c; };
auto Surface = [](Quader const& quader) { return 2 * (quader.a * quader.b + quader.a * quader.c + quader.b * quader.c); };
auto Diagonal = [](Quader const& quader) { return sqrt(pow(quader.a, 2) + pow(quader.b, 2) + pow(quader.c, 2)); };

std::string FormatResults(int const& V, int const& A, float const& d);
void PrintOutput(std::string const& text);

int main(int argc, char *argv[])
{
  Quader quader = {2, 3, 4};

  auto V = Volume(quader);
  auto A = Surface(quader);
  auto d = Diagonal(quader);

  std::string output = FormatResults(V, A, d);
  PrintOutput(output);
  
  return 0;
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