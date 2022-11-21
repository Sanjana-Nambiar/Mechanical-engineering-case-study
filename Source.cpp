//**************************************************************************//
//** Author: Sanjana Vijayakumar Nambiar                                  **//
//** Date Created: October 23, 2021                                       **//
//** Assignment 2: Flight Simulator Wind Speed                            **//
//** ENGR-UH 1000 Computer Programming for Engineers, NYUAD               **//
//** Problem: Is to develop a software to generate a computer simulation  **//
//** of wind speed for a flight simulator.                                **//
//**************************************************************************//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <istream>
#include <ostream>
#include <cstdlib>

using namespace std;

void generateWindData(double limit, double time[], double wind[], ofstream& out);
void generateStormData(double T, double limit, double time[], double stormMag[], double stormTorF[], ofstream& out);
void generateBurstData(double T, double limit, double time[], double burstMag[], double burstTorF[], ofstream& out);
void finalData(double limit, double time[], double finalSimulation[], double binary_value[], ofstream& finalOut);

int main()
{
	double avSpeed, gust, duration, step_size;
	double pStorm, pBurst;
	double min_storm_amp, max_storm_amp;
	int min_storm_duration, max_storm_duration;
	double min_burst_amp, max_burst_amp;
	int min_burst_duration, max_burst_duration;

	ifstream inFile;
	inFile.open("simulationConfiguration.txt", ios::in);
	if (inFile.fail())
	{
		cerr << "Error! The file simulationConfiguration.txt does not exist\n";
		exit(1);
	}

	ofstream outWind;
	outWind.open("WindSpeedData.txt", ios::out);
	if (outWind.fail())
	{
		cerr << "Error! The output file could not be opened\n";
		exit(1);
	}

	ofstream outStorm;
	outStorm.open("StormData.txt", ios::out);
	if (outStorm.fail())
	{
		cerr << "Error! The output file could not be opened\n";
		exit(1);
	}

	ofstream outBurst;
	outBurst.open("BurstData.txt", ios::out);
	if (outBurst.fail())
	{
		cerr << "Error! The output file could not be opened\n";
		exit(1);
	}

	ofstream out;
	out.open("WindSimulation.txt", ios::out);
	if (out.fail())
	{
		cerr << "Error! The output file could not be opened\n";
		exit(1);
	}

	inFile >> avSpeed >> gust >> duration >> step_size;
	inFile >> pStorm >> min_storm_amp >> max_storm_amp >> min_storm_duration >> max_storm_duration;
	inFile >> pBurst >> min_burst_amp >> max_burst_amp >> min_burst_duration >> max_burst_duration;

	double limit = duration / step_size;
	pStorm = pStorm * 100;
	pBurst = pBurst * 100;

	int a, b;
	a = avSpeed - gust;
	b = avSpeed + gust;

	double arr_time[20000] = { 0 };
	double arr_wind[20000] = { 0 };

	int c = 0;
	srand(time(NULL));
	for (int d = 0; d < duration; d += step_size)
	{
		arr_time[c] = d;
		arr_wind[c] = ((double)rand() / RAND_MAX) * (b - a) + a;
		c++;
	}

	double arr_stormMag[20000] = { 0 };
	double arr_stormTorF[20000] = { 0 };

	double probS;
	double stormT;

	stormT = rand() % (max_storm_duration - min_storm_duration + 1) + min_storm_duration;

	for (int f = 0; f < limit; f++)
	{
		probS = rand() % 100;
		if (probS <= pStorm)
		{
			for (int g = 0; g <= stormT; g += step_size)
			{
				arr_stormMag[f] = (((double)rand() / RAND_MAX) * (max_storm_amp - min_storm_amp) + min_storm_amp);
				arr_stormTorF[f] = 1;
				f++;
			}
			continue;
		}
		else
		{
			arr_stormMag[f] = 0;
			arr_stormTorF[f] = 0;
			f++;
		}
	}

	double arr_BurstMag[20000] = { 0 };
	double arr_burstTorF[20000] = { 0 };

	double probB;
	double burstT;

	burstT = rand() % (max_burst_duration - min_burst_duration + 1) + min_burst_duration;

	for (int i = 0; i < limit; i++)
	{
		if (arr_stormTorF[i] == 1)
		{
			probB = rand() % 100;
			if (probB <= pBurst)
			{
				for (int j = 0; j <= burstT; j += step_size)
				{
					arr_BurstMag[i] = (((double)rand() / RAND_MAX) * (max_burst_amp - min_burst_amp) + min_burst_amp);
					arr_burstTorF[i] = 1;
					i++;
				}
			}
			else
			{
				arr_BurstMag[i] = 0;
				arr_burstTorF[i] = 0;
				i++;
			}
		}
		else
		{
			arr_BurstMag[i] = 0;
			i++;
		}
	}

	double arr_final[20000] = { 0 };
	for (int k = 0; k < 20000; k++)
	{
		arr_final[k] = arr_wind[k] + arr_stormMag[k] + arr_BurstMag[k];
	}

	generateWindData(limit, arr_time, arr_wind, outWind);
	generateStormData(stormT, limit, arr_time, arr_stormMag, arr_stormTorF, outStorm);
	generateBurstData(burstT, limit, arr_time, arr_BurstMag, arr_burstTorF, outBurst);
	finalData(limit, arr_time, arr_final, arr_stormTorF, out);

	cout << " ************************************************* " << endl;
	cout << "        !Wind Simulation is Complete!              " << endl;
	cout << "    Your files with the data has been created      " << endl;
	cout << "                 !Thank You!                       " << endl;
	cout << " ************************************************* " << endl;

	inFile.close();
	outWind.close();
	outStorm.close();
	outBurst.close();
	out.close();
	return (0);
}

void generateWindData(double limit, double time[], double wind[], ofstream& out)
{
	out << setw(20) << left << "Time" << setw(20) << left << "Windspeed" << endl;
	for (int i = 0; i < limit; i++)
	{
		out << setw(20) << left << time[i] << setw(20) << left << wind[i] << endl;
	}
}

void generateStormData(double T, double limit, double time[], double stormMag[], double stormTorF[], ofstream& out)
{
	out << "Duration of the Storm is " << T << endl;
	out << setw(20) << left << "Time" << setw(20) << left << "Storm Magintude" << setw(20) << left << "Storm Probability" << endl;
	for (int i = 0; i < limit; i++)
	{
		out << setw(20) << left << time[i] << setw(20) << left << stormMag[i] << setw(20) << left << stormTorF[i] << endl;
	}
}

void generateBurstData(double T, double limit, double time[], double burstMag[], double burstTorF[], ofstream& out)
{
	out << "Duration of the Microburst is " << T << endl;
	out << setw(20) << left << "Time" << setw(20) << left << "Burst Magnitude" << setw(20) << left << "Burst Probability" << endl;
	for (int i = 0; i < limit; i++)
	{
		out << setw(20) << left << time[i] << setw(20) << left << burstMag[i] << setw(20) << left << burstTorF[i] << endl;
	}
}

void finalData(double limit, double time[], double finalSimulation[], double binary_value[], ofstream& finalOut)
{
	finalOut << setw(20) << left << "Time" << setw(20) << left << "Wind Simulation Data" << setw(20) << left << "Binary Value" << endl;
	for (int i = 0; i < limit; i++)
	{
		finalOut << setw(20) << left << time[i] << setw(20) << left << finalSimulation[i] << setw(20) << left << binary_value[i] <<endl;
	}
}

