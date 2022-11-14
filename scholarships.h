#pragma once
// Scholarships.h
// This file contains prototypes of functions used in main program
// This program tutorial demonstrates arrays using vectors
// It also demonstrates file I/O techniques with vectors
//  and making arrays of structures
// The Datafile used in a CSV (Comma Seperated Values) file
//  named Scholarships.csv
// The structor of the data file is:
//  ID, Amount Awarded, Scholarship Type, Length of Scholarship, Date Starts, Last Name, First Name
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

struct Scholarship
{	string ID;
	int    Amount;
	string Type;
	string Length;
	string DateStarts;
	string Lname;
	string Fname;
};

void OpenFiles(ifstream &in, ofstream &out);
Scholarship readFile(string &sLine, vector<string> &sParsed, ifstream &fin);
void writeFile(Scholarship s, ofstream &fout);
void createReportHeadings(ofstream &fout);
string addCommas(int num);
void createReportSummary(vector<Scholarship> sArray, ofstream &fout);
void writeFile(Scholarship s, ofstream &fout, string sType);

int search(vector<Scholarship> s, string sLookFor);
int search(vector<Scholarship> s, int iLookFor, ofstream &fout);
void bubbleSort(vector<Scholarship> &s);