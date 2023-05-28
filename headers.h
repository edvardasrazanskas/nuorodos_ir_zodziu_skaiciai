#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

void read_file(string file_name, string &file_contents);
void write_to_file(string &file_name, map<string, pair<int, vector<int>>> &repeated_words, string &all_links);
std::map<std::string, std::pair<int, std::vector<int>>> find_repeated_words(const string &file_content);
void find_all_links(string file_contents, string &all_links);
void print_short_version(map<string, pair<int, vector<int>>> &repeated_words, string &all_links);

#endif