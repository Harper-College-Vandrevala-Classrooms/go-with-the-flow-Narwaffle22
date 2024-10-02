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
	void tick(int);
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
	for (int i = 1; i < rod.size(); i++){
		float leftHeat;
		if (i != 0)
			leftHeat = rod[i - 1];
		else
			leftHeat = startingTemp;
		float rightHeat;
		if (i != rod.size()-1)
			rightHeat = rod[i + 1];
		else
			rightHeat = startingTemp;
		float thisHeat = rod[i];

		rod[i] = thisHeat + K * (rightHeat - 2 * (thisHeat) + leftHeat);
	}
}
void HeatFlow::tick(int times) {
	for (int i = 0; i < times; i++){
		for (int j = 1; j < rod.size() - 1; j++) {
			float leftHeat;
			if (j != 0)
				leftHeat = rod[j - 1];
			else
				leftHeat = startingTemp;
			float rightHeat;
			if (j != rod.size() - 1)
				rightHeat = rod[j + 1];
			else
				rightHeat = startingTemp;
			float thisHeat = rod[j];

			rod[j] = thisHeat + K * (rightHeat - 2 * (thisHeat)+leftHeat);
		}
		//cout << i << "\n";
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

int main(){
	cout << fixed << setprecision(0) << endl;

	HeatFlow* heatFlow = new HeatFlow(10, 8, 0.1, 100);
	heatFlow->prettyPrint();
	heatFlow->tick();
	heatFlow->prettyPrint();
	heatFlow->tick(2000);
	heatFlow->prettyPrint();
}
