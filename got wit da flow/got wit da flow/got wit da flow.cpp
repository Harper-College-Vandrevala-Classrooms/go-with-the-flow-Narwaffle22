// got wit da flow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

#pragma region HeatFlow
class HeatFlow {
public:
	HeatFlow(int, int, float, int);
	void tick();
	void prettyPrint();

private:
	float startingTemp;
	int numSections;
	float K;
	int sourceTemp;
	vector<float> rod;
};
HeatFlow::HeatFlow(int startingTemp, int numSections, float K, int sourceTemp) {
	this->K = K;
	this->numSections = numSections;
	this->sourceTemp = sourceTemp;
	this->startingTemp = startingTemp;
	
	rod.resize(numSections);
	for (int i = 0;  i < numSections; i++){
		rod[i] = startingTemp;
	}
	rod[0] = sourceTemp;
}
void HeatFlow::tick() {
	for (int i = 1; i < rod.size() - 1; i++){
		rod[i] = rod[i] + K * (rod[i + 1] - 2 * (rod[i]) + rod[i - 1]);
	}
}
void HeatFlow::prettyPrint() {
	for (int i = 0; i < rod.size(); i++){
		cout << "+------";
	}
	cout << "+\n";
	for (int i = 0; i < rod.size(); i++) {
		int numLength = log10(rod[i]) + 1;
		if (numLength > 2) {
			cout << "| " << rod[i] << "  ";
		}
		else {
			cout << "|  " << rod[i] << "  ";
		}
		
	}
	cout << "|\n";
	for (int i = 0; i < rod.size(); i++) {
		cout << "+------";
	}
	cout << "+\n\n";
}

#pragma endregion

int main()
{
	cout << fixed << setprecision(0) << endl;

	HeatFlow *heatFlow = new HeatFlow(10, 8, 0.1, 100);
	heatFlow->prettyPrint();
	heatFlow->tick();
	heatFlow->prettyPrint();
}
