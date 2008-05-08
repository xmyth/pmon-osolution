#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream ifs("Z9sL10810.ROM");
ofstream ofs("z9sl10810fw.h");

int main() {
	filebuf *pbuf;
	long size = 0;
	char *buffer;

	ifs.seekg (0, ios::end);
	size = ifs.tellg();
	ifs.seekg(0, ios::beg);

	buffer = new char[size];
	ifs.read(buffer, size);
	
	ofs.fill('0');

	ofs << "unsigned char z9sl10810_rom_data[] = {" << endl;

	for (long i = 0; i < size; i++) {
		int t = (unsigned char) buffer[i];
		ofs << "0x" << hex << setw(2) << t ;
		if (i + 1 != size)
			ofs << ",";
		if ( (i + 1) % 15 == 0)
			ofs << endl;
	}
	ofs << endl << "};" << endl;

}

		
