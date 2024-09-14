#include <iostream>
#include <cmath>
#include <sstream>

auto Volume = [](int const& a){ return pow(a, 3) * (15 + 7 * sqrt(5)) / 4.0; };
auto Surface = [](int const& a){ return 3 * pow(a, 2) * sqrt(5 * (5 + 2 * sqrt(5))); };
auto IncircleRadius = [](int const& a){ return a * sqrt(10 * (25 + 11 * sqrt(5))) / 20.0; };
auto CircumferenceRadius = [](int const& a){ return a * sqrt(3) * (1 + sqrt(5)) / 4.0; };

std::string FormatOutput(float const& V, float const& A, float const& ri, float const& ru);
void PrintOutput(std::string const& text);

int main(int argc, char *argv[])
{
  int a = 2;

  float V = Volume(a);
  float A = Surface(a);
  float ri = IncircleRadius(a);
  float ru = CircumferenceRadius(a);

  std::string output = FormatOutput(V, A, ri, ru);
  PrintOutput(output);

  return 0;
}

std::string FormatOutput(float const& V, float const& A, float const& ri, float const& ru)
{
  std::stringstream output;
 
  output << "Volumen: " << V << " Oberfläche: "<< A << " Inkreisradius: " << ri << " Umkreisradius: " << ru << std::endl;

  return output.str();
}

void PrintOutput(std::string const& text)
{
  std::cout << text;
}