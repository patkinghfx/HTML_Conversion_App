//
// Created by patki on 2024-01-24.
//

#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

struct FileException : public exception {
    const char* what() const throw () {
        return "File operation error";
    }
};

string processCppFile(const string& inputFileContent) {
    string contentToProcess = "<PRE>\n";

    for (char c : inputFileContent) {
        if (c == '<') {
            contentToProcess += "&lt;";
        } else if (c == '>') {
            contentToProcess += "&gt;";
        } else {
            contentToProcess += c;
        }
    }

    contentToProcess += "\n</PRE>";
    return contentToProcess;
}

bool isValidFileName(const string& fileName){
    regex validFileNameRegex("^[^\\/:*?\"<>|]+\\.html$");
    return regex_match(fileName, validFileNameRegex);
}

int main(){

    try{

        cout << "Opening OriginalCPP.cpp\n";

        ifstream  fin;

        fin.open("OriginalCPP.cpp");
        if (fin.fail()){
            throw FileException();
        }

        string inputFileContent((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
        fin.close();

        string processedContent = processCppFile(inputFileContent);

        string outputFileName;
        do {
            cout << "Enter the output file name (.html): ";
            cin >> outputFileName;

            if (!isValidFileName(outputFileName)) {
                cerr << "Invalid output file name. Please provide a valid Windows file name with .html extension.\n";
            }
        } while (!isValidFileName(outputFileName));

        ofstream fout(outputFileName);
        if (fout.fail()) {
            throw FileException();
        }

        fout << processedContent;
        fout.close();

        cout << "HTML file successfully created: " << outputFileName << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (...) {
        cerr << "Unknown error occurred." << endl;
    }

    return 0;
}
