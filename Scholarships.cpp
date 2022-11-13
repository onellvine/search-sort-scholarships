// Scholarships.cpp
// This program tutorial demonstrates arrays using vectors
// It also demonstrates file I/O techniques with vectors
//  and making arrays of scructures
// The Datafile used in a CSV (Comma Seperated Values) file
//  named Scholarships.csv
// The structor of the data file is:
//  ID, Amount Awarded, Scholarship Type, Length of Scholarship, Date Starts, Last Name, First Name

#include "scholarships.h"


int main()
{
	string sFileLine;				 // a string to read in each line of the file
	vector<string> sParsedLine;      // array to hold the parsed line from file
	vector<Scholarship> scholars;    // Create an array of structures

	// Open input and output files and test to make sure they openned correctly
	ifstream fin;
	ofstream fout;
	OpenFiles(fin, fout);

	while(!fin.eof())
		// Read a line from the file and push onto end ofscholars object array
		scholars.push_back(readFile(sFileLine, sParsedLine, fin));

	int sArraySize = scholars.size();       // Get the size of the array
	for(int i = 0; i < sArraySize; i++)
		writeFile(scholars[i], fout);		// Write a line to the output file

	// Write the summary report to the end of the outut file by calling the
	//  summary function and passing both the array of objects and the 
	//  file handle to the function
	createReportSummary(scholars, fout);

	// Close the original output report to reuse its file handler
	//  and not overwrite the original output report
	fout.close();
	fout.open("ScholarshipsReportByType.dat");
	if(!fout)
	{
		cout << "Output file did not open. Program will exit." << endl;
		exit(0);
	}
	// Ask the user for an ID to search for
	string sIDsearch;
	int pos;
	int search(vector<Scholarship> s, 		//Pass copy of the entire array
			string sLookFor);			// ID to lookfor
	char doAgain;
	do
	{
		// Get the ID to search for
		cout << "\nEnter an ID to see an individual scholarship: ";
		cin  >> sIDsearch;
		
		// Search for the object
		pos = search(scholars, sIDsearch);
		
		// If pos = -1, the code was not found
		if (pos == -1)
			cout << "That code does not exist in the arrary\n";
		else
		{	// The object was found, so use pos to ge the
			// description and price
			createReportHeadings(fout);
			writeFile(scholars); // write a line to the output file
		}
		//  Does the user want to loop up another price?
		cout << "\nLook up another price(Y/N)? ";
		cin  >> doAgain;
	} while (doAgain == 'Y' || doAgain == 'y');
	
	// Ask the user for the specific report
	string sType;
	cout << "What specific type of scholarship would you like a report on?\n";
	cin  >> sType;
	cout << endl;
	for(int i = 0; i < sArraySize; i++)
		writeFile(scholars[i], fout, sType); // Write a line to the output file

	return 0;
}
void OpenFiles(ifstream &in, ofstream &out)  // must be passed in by reference
{
	in.open("Scholarships.csv");
	if(!in)
	{
		cout << "Input file did not open. Program will exit." << endl;
		exit(0);
	}

	out.open("ScholarshipsReport.dat");
	if(!out)
	{
		cout << "Output file did not open. Program will exit." << endl;
		exit(0);
	}

}

Scholarship readFile(string &sLine,           // Pass in by reference to change string in main()
			  vector<string> &sParsed, // Pass in by reference to change array in main()
			  ifstream &fin)           // Also pass in the input file buffer by ref to read from
{										 
	getline(fin,sLine);
	stringstream lineStream(sLine);    // A special string class for pre-output formatting
	string field;
	sParsed.clear();                  // Empty the Parsed Line for reuse
	
    while(getline(lineStream,field,','))  // While there are fields between the ,
    {
        sParsed.push_back(field);        // Push them onto the string array vector
    }
	//  Fill the data elements of a temporary struct of type Scholarship 
	//     from the values in the sParsed line
	Scholarship tempScholar = { sParsed[0], stoi(sParsed[1]), sParsed[2],
		               			sParsed[3], sParsed[4], sParsed[5], sParsed[6]
					   		  };
	// Return a copy of the filled tempScholar struct
	return tempScholar;
}

void writeFile(Scholarship s,    // Pass one element of Scholarship array in by value
			   ofstream &fout)  // Also pass in the output file buffer by ref to write to
{
	static int lineCount = 60;
	if(lineCount == 60) // Ready for next page
	{
		fout << endl; // 
		createReportHeadings(fout);
		lineCount = 0;
	}
	// Output the line from the structure
	fout << s.ID <<  right << setw(10) << addCommas(s.Amount) 
		 << "    " << left <<  setw(12) << s.Type 
		 << setw(10) << s.Length << right << setw(10) << s.DateStarts 
		 << "   " << left <<  setw(15) << s.Fname << s.Lname << endl;
	lineCount++;
}

void createReportHeadings(ofstream &fout)
{
	fout << "******************************Scholarships Report*****************************\n"
		 << "******************************************************************************\n\n"
		 << "ID      Amount      Type      Length      Starts     First Name     Last Name\n"
		 << "------------------------------------------------------------------------------\n";
}
string addCommas(int num)  // Adds commas to any number for formatted output to report files
{
   string s = to_string(num);  // convert the nuber to string to hold the formatted number
   // insert comma's from right (at implied decimal point) to left
   int sSize = s.size(); // index to last digit
   if (sSize > 3)
      for (int i = (sSize - 3);  i > 0;  i -= 3)
         s.insert(i,",");  // look up the string's insert() method to see how it works
                           //  it is found on page 816 of the textbook or using "help"

   return s;
}
void createReportSummary(vector<Scholarship> sArray,  // Pass by value (copy) the entire array
						ofstream &fout)              // Pass the output file by reference
{
	int total = 0;                          // Accumulator for total amount
	int sArraySize = sArray.size();         // Get the size of the array
	// Accumulators for type totals
	int baseTotal = 0, baskTotal = 0, dTotal = 0, fTotal = 0, gTotal = 0, softTotal = 0,
		swimTotal = 0, tTotal = 0, vTotal = 0;
	
	// Loop through the array to accumulate the total amount of all scholarships
	for(int i = 0; i < sArraySize; i++)
	{
		total += sArray[i].Amount;		// Add the Amount of each scholarship to the total
		string sType = sArray[i].Type; // Get the type of scholarship for this record
		// Add the Type's Amount to the appropriate accumulator
		if(sType == "Baseball") baseTotal += sArray[i].Amount;
		else if(sType == "Basketball") baskTotal += sArray[i].Amount;
		else if(sType == "Diving") dTotal += sArray[i].Amount;
		else if(sType == "Football") fTotal += sArray[i].Amount;
		else if(sType == "Golf") gTotal += sArray[i].Amount;
		else if(sType == "Softball") softTotal += sArray[i].Amount;
		else if(sType == "Swimming") swimTotal += sArray[i].Amount;
		else if(sType == "Track") tTotal += sArray[i].Amount;
		else if(sType == "Volleyball") vTotal += sArray[i].Amount;
	}

	// Write the summary report output line
	fout << "\n\nSummary Report \n" 
		 <<     "--------------\n"
		 << "        Total Number of Scholarships: " 
		 << right << setw(12) << sArraySize << endl
		 << "        Baseball:                    $ " 
		 << setw(11) << addCommas(baseTotal) << endl
		 << "        Basketball:                    " 
		 << setw(11) << addCommas(baskTotal) << endl
		 << "        Diving:                        " 
		 << setw(11) << addCommas(dTotal) << endl
		 << "        Football:                      " 
		 << setw(11) << addCommas(fTotal) << endl
		 << "        Golf:                          " 
		 << setw(11) << addCommas(gTotal) << endl
		 << "        Softball:                      " 
		 << setw(11) << addCommas(softTotal) << endl
		 << "        Swimming:                      " 
		 << setw(11) << addCommas(swimTotal) << endl
		 << "        Track:                         " 
		 << setw(11) << addCommas(tTotal) << endl
		 << "        Volleyball:                    " 
		 << setw(11) << addCommas(vTotal) << endl
		 << "        ===========================================\n"
		 << "        Total Scholarship Amount:    $ " 
		 << setw(11) << addCommas(total); 
}
// Overloaded function for report of specific type of scholarship
void writeFile(Scholarship s,    // Pass in by value- no need to change string in main()
			   ofstream &fout,  // Also pass in the output file buffer by ref to write to
			   string sType)    // Pass in by value the type of scholarship
{
	static int lineCount = 60;
	if(lineCount == 60) // Ready for next page
	{
		fout << endl; // 
		createReportHeadings(fout);
		lineCount = 0;
	}
	if(sType == s.Type)
	{
		fout << s.ID <<  right << setw(10) << addCommas(s.Amount) 
			 << "    " << left <<  setw(12) << s.Type 
			 << setw(10) << s.Length << right << setw(10) << s.DateStarts 
			 << "   " << left <<  setw(15) << s.Fname << s.Lname << endl;
		lineCount++;
	}
}

/*********************************************************
*								Search					 *
* This function performs a linear search on an array of  *
* Scholarship struct records, using ID as the key field. *
* If the desired code is found, its array subscript is   *
* returned. Otherwise, -1 is returned.					 *
**********************************************************/

int search(vector<Scholarship> s, 		//Pass copy of the entire array
			string sLookFor)			// ID to lookfor
{
	int index = 0;				//Used as a subscript to search array
	int position = -1			//Used to record position of search value
	bool found = false;			//Flag to indicate if the value was found
	
	while (index < s.size() && !found)
	{
		if (s[index].ID == sLookFor)		// If the value is found
		{
			found = true;					// Set the flag
			position = index;				// Record the value's subscript
		}
		index++;							// Go to the next element
	}
	return position;						// Return the position, or -1
} // End search


void createReportHeadings()
{
	cout << "******************************Scholarships Report*****************************\n"
		 << "******************************************************************************\n\n"
		 << "ID      Amount      Type      Length      Starts     First Name     Last Name\n"
		 << "------------------------------------------------------------------------------\n";
}



void writeFile(Scholarship s,    // Pass in by value- no need to change string in main()
			   					 // Also pass in the output file buffer by ref to write to
			   string sType)     // Pass in by value the type of scholarship
{
	static int lineCount = 30;
	if(lineCount == 30) // Ready for next page
	{
		cout << endl; // 
		createReportHeadings(fout);
		lineCount = 0;
	}
	if(sType == s.Type)
	{
		cout << s.ID <<  right << setw(10) << addCommas(s.Amount) 
			 << "    " << left <<  setw(12) << s.Type 
			 << setw(10) << s.Length << right << setw(10) << s.DateStarts 
			 << "   " << left <<  setw(15) << s.Fname << s.Lname << endl;
		lineCount++;
	}
}












