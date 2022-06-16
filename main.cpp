#include "include/lib_search.h"
#include <iostream>

int main()
{
    std::string wantedFile;
    std::cout << "<File Finder>\t\t(Search Is Case Sensitive!)" << std::endl;
    std::cout << "Enter a File Name\t(Without File Type!\tExample: 'file1' or 'file 23') > ";
    std::getline(std::cin, wantedFile);
    multisearch(wantedFile);
    return 0;
}
