#include <iostream>
#include <cmath>
#include <sstream>

struct Ikosaeder
{
  int a;
};

float Volume(Ikosaeder const& ikosaeder);
float Surface(Ikosaeder const& ikosaeder);
float IncircleRadius(Ikosaeder const& ikosaeder);
float CircumferenceRadius(Ikosaeder const& ikosaeder);

std::string FormatOutput(float const& V, float const& A, float const& ri, float const& ru);
void PrintOutput(std::string const& text);

int main(int argc, char *argv[])
{
  Ikosaeder ikosaeder = { 2 };

  float V = Volume(ikosaeder);
  float A = Surface(ikosaeder);
  float ri = IncircleRadius(ikosaeder);
  float ru = CircumferenceRadius(ikosaeder);

  std::string output = FormatOutput(V, A, ri, ru);
  PrintOutput(output);

  return 0;
}

float Volume(Ikosaeder const& ikosaeder)
{
  return 5 * pow(ikosaeder.a, 3) * (3 + sqrt(5)) / 12;
}

float Surface(Ikosaeder const& ikosaeder)
{
  return 5 * pow(ikosaeder.a, 2) * sqrt(3);
}

float IncircleRadius(Ikosaeder const& ikosaeder)
{
  return ikosaeder.a * sqrt(3) * (3 + sqrt(5)) / 12;
}

float CircumferenceRadius(Ikosaeder const& ikosaeder)
{
  return ikosaeder.a / 4.0 * sqrt(2 * (5+sqrt(5)));
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