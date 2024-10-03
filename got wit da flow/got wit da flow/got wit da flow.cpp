// got wit da flow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <array>

using namespace std;


#pragma region HeatFlow
class HeatFlow {
public:
	HeatFlow(int, int, float, int, int);
	HeatFlow(int, int, float, int, vector<int>);
	void tick();
	void tick(int);
	void prettyPrint();

private:
	float startingTemp;
	int numSections;
	float K;
	int sourceTemp;
	int sourceLocale;
	vector<float> rod;
	vector<int> sources;
};
HeatFlow::HeatFlow(int startingTemp, int numSections, float K, int sourceTemp, int sourceLocale) {
	this->K = K;
	this->numSections = numSections;
	this->sourceTemp = sourceTemp;
	this->startingTemp = startingTemp;
	this->sourceLocale = sourceLocale;
	
	rod.resize(numSections);
	for (int i = 0;  i < numSections; i++){
		rod[i] = startingTemp;
	}
	rod[sourceLocale] = sourceTemp;
}
HeatFlow::HeatFlow(int startingTemp, int numSections, float K, int sourceTemp, vector<int> sources) {
	this->K = K;
	this->numSections = numSections;
	this->sourceTemp = sourceTemp;
	this->startingTemp = startingTemp;
	this->sources = sources;

	rod.resize(numSections);
	for (int i = 0; i < numSections; i++) {
		rod[i] = startingTemp;
	}
	for (int j = 0; j < numSections; j++) {
		for (int k = 0; k < sources.size(); k++) {
			if (sources[k] == j) {
				rod[j] = sourceTemp;
			}
		}
	}

}
void HeatFlow::tick() {
	bool isNotOne;

	for (int i = 0; i < rod.size(); i++){
		isNotOne = true;
		for (int j = 0; j < sources.size(); j++) {
			if (sources[j] == i) {
				isNotOne = false;
			}
		}

		if (i != sourceLocale && isNotOne) {
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
}
void HeatFlow::tick(int times) {
	for (int i = 0; i < times; i++){
		tick();
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
		
		if (numLength > 5) {
			cout << "|" << rod[i];
		} else if (numLength > 4) {
			cout << "| " << rod[i] << "";
		} else if (numLength > 3) {
			cout << "| " << rod[i] << " ";
		} else if (numLength > 2) {
			cout << "| " << rod[i] << "  ";
		} else if (numLength > 1){
			cout << "|  " << rod[i] << "  ";
		} else {
			cout << "|  " << rod[i] << "   ";
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

	HeatFlow* heatFlow = new HeatFlow(10, 8, 0.1, 100, 0);
	heatFlow->prettyPrint();
	heatFlow->tick();
	heatFlow->prettyPrint();
	heatFlow->tick(2000);
	heatFlow->prettyPrint();

	HeatFlow* heatFlow1 = new HeatFlow(5, 16, 0.01, 1000, 5);
	heatFlow1->prettyPrint();
	heatFlow1->tick();
	heatFlow1->prettyPrint();
	heatFlow1->tick(2000);
	heatFlow1->prettyPrint();

	//you may need to widen your output window for this one to look good
	HeatFlow* heatFlow2 = new HeatFlow(1, 20, 0.001, 100000, 10);
	heatFlow2->prettyPrint();
	heatFlow2->tick();
	heatFlow2->prettyPrint();
	heatFlow2->tick(2000);
	heatFlow2->prettyPrint();
	heatFlow2->tick(20000);
	heatFlow2->prettyPrint();

	HeatFlow* heatFlow2 = new HeatFlow(1, 20, 0.001, 100000, { 2,10 });
	heatFlow2->prettyPrint();
	heatFlow2->tick();
	heatFlow2->prettyPrint();
	heatFlow2->tick(2000);
	heatFlow2->prettyPrint();
	heatFlow2->tick(20000);
	heatFlow2->prettyPrint();

}
