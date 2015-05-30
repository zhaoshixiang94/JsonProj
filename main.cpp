#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include"adler32.h"
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>
//#include "sha256.h"

using namespace std;
using namespace boost::filesystem;
using namespace boost::algorithm;
//using boost::property_tree::ptree;

path main_path_get(){
	path p;
	string s;
	//cin >> p;
	getline(cin, s);
	p = s;
	while (!is_directory(p)){
		cout << "ERROR  " << p << " is not valid path"<< endl
			<<"Enter valid path" << endl ;
		//cin >> p;
		getline(cin, s);
		p = s;
	}
	return p;
} 

//string hash_counter(string file_path){
//	SHA256 sha256;
	unsigned long hash_counter(string file_path) 
{
	string file_text = {};
	ifstream c_file;// for openning file and hash it 
	c_file.open(file_path, ifstream::in);
	while (!c_file.eof()){
		file_text += c_file.get();
	}
	int length = file_text.size();
	char* v = (char*)file_text.c_str();
	unsigned char* str = (unsigned char*)v;
	c_file.close();
	return adler32(str, length);
//	return sha256(file_text);
}

void dir_runner(path main_p, ptree &pt){
	for (directory_iterator dir_itr(main_p);
		dir_itr != directory_iterator();
		++dir_itr)
	{
		if (is_directory(*dir_itr)) dir_runner(*dir_itr,pt);
		if (is_regular_file(*dir_itr)){
				path p = *dir_itr;
				file_output << p.string() << "\t\t" << file_size(*dir_itr/*p*/) << " bt"
				<< "\t\t" << p.filename().string() << "\t\t" << hash_counter(p.string()) << endl;
				}
	}
}

void Start(path main_p) 
{
	ofstream file_output;
	file_output.open("Tsv_MyProject.tsv");
	file_output << "File Path: \t\t\t\t" << "SIZE: \t\t" << "FILE NAME: \t\t" << "FILE HASH: " << endl;
	dir_runner(main_p, file_output);
	file_output.close();
}

int main(){
	cout << "0----For creating a TSV file." << endl;
	cout << "1----For looking for the changes of the olds." << endl;
	int c;
	cin >> c;
	cin.get();
	if (c == 0) { path file_path = file_path_get(); Start(file_path); }
	else directory_scanner();
	cin.get();
	return 0;
}
