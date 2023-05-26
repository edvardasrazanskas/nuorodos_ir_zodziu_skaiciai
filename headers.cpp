#include "headers.h"

void print_short_version(map<string, int> &repeated_words, string &all_links){
    cout << "Number of different repeated words and/or links found in a file: " << repeated_words.size() << endl;
    cout << "\nLinks found in a file: " << endl;
    if(all_links.size() > 30){
        cout << all_links.substr(0, 30) << "..." << endl;
    } else {
        cout << all_links << endl;
    }
    cout << "\nSee more detailed info in results file." << endl;
}

// function which removes special characters from string
string remove_special_characters(string file_content)
{
    for (int i = 0; i < file_content.size(); i++)
    {
        if (ispunct(file_content[i]))
        {
            file_content.erase(i--, 1);
        }
    }
    return file_content;
}

map<string, int> find_repeated_words(const string &file_content)
{
    string text = remove_special_characters(file_content);

    std::map<std::string, int> wordCount;
    std::stringstream ss(text);
    std::string word;

    while (ss >> word)
    {
        word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
        wordCount[word]++;
    }

    for (auto it = wordCount.begin(); it != wordCount.end();)
    {
        if (it->second == 1)
            it = wordCount.erase(it);
        else
            ++it;
    }

    return wordCount;
}


/*
    (https?://)? matches the http:// or https:// part of a URL.
    (www\.)? matches the www. part of a URL.
    ([-\w]+) matches one or more alphanumeric characters (a-z, A-Z, 0-9) or hyphens, which is usually the domain name part of the URL.
    (\.[a-z\.]{2,6}) matches the domain extension, like .com, .gov, .io etc.
    ([-\w@:%_\+.~#?&//=]*)? matches optional path, query string, fragment identifiers, etc.
*/

// function which finds most of URLs in string
void find_all_links(string file_contents, string &all_links)
{
    regex link_regex(R"((https?://)?(www\.)?([-\w]+)(\.[a-z\.]{2,6})([-\w@:%_\+.~#?&//=]*)?)");
    smatch matches;
    while (regex_search(file_contents, matches, link_regex))
    {
        // cout << matches[0] << endl;
        all_links += matches[0];
        all_links += "\n";
        file_contents = matches.suffix().str();
    }
}

void read_file(string file_name, string &file_contents)
{
    ifstream in_file("source_files/" + file_name + ".txt");
    if (!in_file)
    {
        // handle error
        cerr << "Failed to open file\n";
        system("pause");
        exit(0);
    }

    file_contents = string(istreambuf_iterator<char>(in_file), istreambuf_iterator<char>());
    in_file.close();
}

void write_to_file(string &file_name, map<string, int> &repeated_words, string &all_links)
{
    ofstream out_file("result_files/" + file_name + "_results.txt");

    // print repeated words and/or links in a cross-reference table
    out_file << "\nRepeated words and/or links in a cross-reference table: " << endl;
    int counter = 0;
    for (auto &i : repeated_words)
    {
        out_file << fixed << setw(20) << left << i.first << " " << fixed << setw(5) << left << i.second << " ";
        if (counter % 2 == 1)
        {
            out_file << endl;
        }
        counter++;
    }
    if (counter % 2 == 1)
    {
        out_file << endl;
    }


    out_file << "\nAll links: " << endl;
    out_file << all_links << endl;
    out_file.close();
}
