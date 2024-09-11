#include <iostream>
#include <cmath>
#include <sstream>

struct Octaeder
{
  int a;
};

float Volume(Octaeder const& octaeder);
float Surface(Octaeder const& octaeder);
float IncircleRadius(Octaeder const& octaeder);
float CircumferenceRadius(Octaeder const& octaeder);

std::string FormatOutput(float const& V, float const& A, float const& ri, float const& ru);
void PrintOutput(std::string const& text);

int main(int argc, char *argv[])
{
  Octaeder octaeder = { 2 };

  float V = Volume(octaeder);
  float A = Surface(octaeder);
  float ri = IncircleRadius(octaeder);
  float ru = CircumferenceRadius(octaeder);

  std::string output = FormatOutput(V, A, ri, ru);
  PrintOutput(output);

  return 0;
}

float Volume(Octaeder const& octaeder)
{
  return pow(octaeder.a, 3) * sqrt(2) / 3;
}

float Surface(Octaeder const& octaeder)
{
  return 2 * pow(octaeder.a, 2) * sqrt(3);
}

float IncircleRadius(Octaeder const& octaeder)
{
  return octaeder.a * sqrt(6) / 6;
}

float CircumferenceRadius(Octaeder const& octaeder)
{
  return octaeder.a * sqrt(2) / 2;
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