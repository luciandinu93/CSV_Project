#include "include/rapidcsv.h"
#include <string>
#include <iostream>
#include <fstream>

typedef long long longNr;

int main() {
	std::ostringstream xmlParser;
	std::ofstream test_file;
	std::string xml_command;
	std::string introduction;
	rapidcsv::Document doc("file.csv");
	
	// configure output file
	test_file.open("test.io");
	
	const std::vector<std::string>& signal_col	= doc.GetRowNames();
	// first values
	const std::vector<std::string>& min1_col = doc.GetColumn<std::string>("min1");
	const std::vector<std::string>& max1_col = doc.GetColumn<std::string>("max1");
	const std::vector<std::string>& value1_col = doc.GetColumn<std::string>("value1");
	// second values
	const std::vector<std::string>& min2_col = doc.GetColumn<std::string>("min2");
	const std::vector<std::string>& max2_col = doc.GetColumn<std::string>("max2");
	const std::vector<std::string>& value2_col = doc.GetColumn<std::string>("value2");
	
	// get the number of rows
	longNr number_of_signals = signal_col.size();
	
	introduction = R"(<note>
  <to>Tove</to>
  <from>Jani</from>
  <heading>Reminder</heading>
  <body>Don't forget me this weekend!</body>
</note>)";

	test_file << introduction << std::endl << std::endl;
	
	for(longNr i = 0; i < number_of_signals; ++i) {
		if(value1_col[i].compare("n.a") != 0) {
			xmlParser << "<order>" << std::endl;
			xmlParser << "<object>" << std::endl;
			xmlParser << "<signal>" << signal_col[i] << "<\\signal>" << std::endl;
			xmlParser << "<value>" << value1_col[i] << "<\\value>" << std::endl;
			xmlParser << "<\\object>" << std::endl;
			xmlParser << "<\\order>" << std::endl;
		} else {
			xmlParser << "<order>" << std::endl;
			xmlParser << "<object>" << std::endl;
			xmlParser << "<signal>" << signal_col[i] << "<\\signal>" << std::endl;
			xmlParser << "<min>" << min1_col[i] << "<\\min>" << std::endl;
			xmlParser << "<max>" << min2_col[i] << "<\\max>" << std::endl;
			xmlParser << "<\\object>" << std::endl;
			xmlParser << "<\\order>" << std::endl;
		}
		
		// copy to string
		xml_command = xmlParser.str();
		
		// clear parser
		xmlParser.str("");
		xmlParser.clear();
		
		// write command to file
		test_file << xml_command << std::endl;
	}
	
	test_file.close();
}