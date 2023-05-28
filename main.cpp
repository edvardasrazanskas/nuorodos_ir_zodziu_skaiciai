#include "headers.h"


int main()
{
    string file_name, file_contents, all_links;

    cout << "Enter file name: ";
    cin >> file_name;

    read_file(file_name, file_contents);

    find_all_links(file_contents, all_links);
    std::map<std::string, std::pair<int, std::vector<int>>> repeated_words = find_repeated_words(file_contents);
    
    print_short_version(repeated_words, all_links);
    write_to_file(file_name, repeated_words, all_links);
}