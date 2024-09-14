#include <iostream>
#include <cmath>
#include <sstream>

struct Cube
{
	int a;
};

int Volume(Cube const& cube);
int Surface(Cube const& cube);
float Diagonal(Cube const& cube);
float IncircleRadius(Cube const& cube);
float CircumferenceRadius(Cube const& cube);

std::string FormatOutput(int const& V, int const& A, float const& d, float const& ri, float const& ru);
void PrintOutput(std::string const& text);

int main (int argc, char *argv[])
{
  	Cube cube = { 2 };

	int V = Volume(cube);
	int A = Surface(cube);
	float d = Diagonal(cube);
	float ri = IncircleRadius(cube);
	float ru = CircumferenceRadius(cube);

	std::string output = FormatOutput(V, A, d, ri, ru);
	PrintOutput(output);

  	return 0;
}

int Volume(Cube const& cube)
{
	return pow(cube.a, 3);
}

int Surface(Cube const& cube)
{
	return 6 * pow(cube.a, 2);
}

float Diagonal(Cube const& cube)
{
	return cube.a * sqrt(3);
}

float IncircleRadius(Cube const& cube)
{
	return cube.a / 2;
}

float CircumferenceRadius(Cube const& cube)
{
	return cube.a / 2 * sqrt(3);
}

std::string FormatOutput(int const& V, int const& A, float const& d, float const& ri, float const& ru)
{
	std::stringstream output;

	output << "Volumen: " << V << " Oberfläche: "<< A << " Diagonale: " << d << " Inkreisradius: " << ri << " Umkreisradius: " << ru << std::endl;

	return output.str();
}

void PrintOutput(std::string const& text)
{
	std::cout << text;
}