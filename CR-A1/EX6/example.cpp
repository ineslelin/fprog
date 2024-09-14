#include <iostream>
#include <cmath>
#include <sstream>

struct Dodecaeder
{
  int a;
};

float Volume(Dodecaeder const& dodecaeder);
float Surface(Dodecaeder const& dodecaeder);
float IncircleRadius(Dodecaeder const& dodecaeder);
float CircumferenceRadius(Dodecaeder const& dodecaeder);

std::string FormatOutput(float const& V, float const& A, float const& ri, float const& ru);
void PrintOutput(std::string const& text);

int main(int argc, char *argv[])
{
  Dodecaeder dodecaeder = { 2 };

  float V = Volume(dodecaeder);
  float A = Surface(dodecaeder);
  float ri = IncircleRadius(dodecaeder);
  float ru = CircumferenceRadius(dodecaeder);

  std::string output = FormatOutput(V, A, ri, ru);
  PrintOutput(output);

  return 0;
}

float Volume(Dodecaeder const& dodecaeder)
{
  return pow(dodecaeder.a, 3) * (15 + 7 * sqrt(5)) / 4.0;
}

float Surface(Dodecaeder const& dodecaeder)
{
  return 3 * pow(dodecaeder.a, 2) * sqrt(5 * (5 + 2 * sqrt(5)));
}

float IncircleRadius(Dodecaeder const& dodecaeder)
{
  return dodecaeder.a * sqrt(10 * (25 + 11 * sqrt(5))) / 20.0;
}

float CircumferenceRadius(Dodecaeder const& dodecaeder)
{
  return dodecaeder.a * sqrt(3) * (1 + sqrt(5)) / 4.0;
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