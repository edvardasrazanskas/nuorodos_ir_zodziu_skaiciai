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
void write_to_file(string &file_name, map<string, int> &repeated_words, string &all_links);
map<string, int> find_repeated_words(const string &text);
void find_all_links(string file_contents, string &all_links);
void print_short_version(map<string, int> &repeated_words, string &all_links);

#endif