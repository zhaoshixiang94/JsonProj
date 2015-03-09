#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;


path main_path_get(){
	path p;
	cin >> p;
	while (!is_directory(p)){
		cout << "ERROR  " << p << " is not valid path"<< endl
			<<"Enter valid path" << endl ;
		cin >> p;
	}
	return p;
} 


void dir_runner(path main_p){
	for (directory_iterator dir_itr(main_p);
		dir_itr != directory_iterator();
		++dir_itr)
	{
		if (is_directory(*dir_itr)) dir_runner(*dir_itr);
		if (is_regular_file(*dir_itr)){
				path p = *dir_itr;
				cout << p.string() << " size : " << file_size(*dir_itr)
				<< " FILENAME : "<< p.filename() << endl;
				}
	}
}

int main(){
	cout << "Enter your path" << endl;
	path main_path = main_path_get();
	dir_runner(main_path);
		cin.get();
	return 0;
}