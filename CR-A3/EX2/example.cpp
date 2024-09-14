#include <iostream>
#include <cmath>
#include <sstream>

auto Volume = [](int const& a){ return pow(a, 3); };
auto Surface = [](int const& a){ return 6 * pow(a, 2); };
auto Diagonal = [](int const& a){ return a * sqrt(3); };
auto IncircleRadius = [](int const& a){ return a / 2; };
auto CircumferenceRadius = [](int const& a){ return a / 2 * sqrt(3); };

std::string FormatOutput(int const& V, int const& A, float const& d, float const& ri, float const& ru);
void PrintOutput(std::string const& text);

int main (int argc, char *argv[])
{
  	int a = 2;

	auto V = Volume(a);
	auto A = Surface(a);
	auto d = Diagonal(a);
	auto ri = IncircleRadius(a);
	auto ru = CircumferenceRadius(a);

	std::string output = FormatOutput(V, A, d, ri, ru);
	PrintOutput(output);

  	return 0;
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