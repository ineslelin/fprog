#include <iostream>
#include <cmath>
#include <sstream>

struct Tetraeder 
{
  int a;
};

float Volume(Tetraeder const& tetraeder);
float Surface(Tetraeder const& tetraeder);
float IncircleRadius(Tetraeder const& tetraeder);
float CircumferenceRadius(Tetraeder const& tetraeder);

std::string FormatOutput(float const& V, float const& A, float const& ri, float const& ru);
void PrintOutput(std::string const& text);

int main (int argc, char *argv[])
{
  Tetraeder tetraeder = { 2 };

  float V = Volume(tetraeder);
  float A = Surface(tetraeder);
  float ri = IncircleRadius(tetraeder);
  float ru = CircumferenceRadius(tetraeder);

  std::string output = FormatOutput(V, A, ri, ru);
  PrintOutput(output);

  return 0;
}

float Volume(Tetraeder const& tetraeder)
{
  return pow(tetraeder.a, 3) * sqrt(2) / 12;
}

float Surface(Tetraeder const& tetraeder)
{
  return pow(tetraeder.a, 2) * sqrt(3);
}

float IncircleRadius(Tetraeder const& tetraeder)
{
  return tetraeder.a * sqrt(6) / 12;
}

float CircumferenceRadius(Tetraeder const& tetraeder)
{
  return tetraeder.a * sqrt(6) / 4;
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