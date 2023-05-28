#include "headers.h"

void print_short_version(map<string, pair<int, vector<int>>> &repeated_words, string &all_links)
{
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

map<string, pair<int, vector<int>>> find_repeated_words(const string &file_content)
{
    string text = remove_special_characters(file_content);

    map<string, pair<int, vector<int>>> wordCount;
    std::stringstream ss(text);
    std::string word, line;

    int line_number = 0;
    while (getline(ss, line))
    {
        std::stringstream ss_line(line);

        while (ss_line >> word)
        {
            // erases all whitespaces from string
            word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
            wordCount[word].first++;
            wordCount[word].second.push_back(line_number);
        }
        line_number++;
    }
    for (auto it = wordCount.begin(); it != wordCount.end();)
    {
        if (it->second.first == 1)
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

/*
    (https?://)? matches the http:// or https:// part of a URL.
    (www\.)? matches the www. part of a URL.
    ([-\w]+) matches one or more alphanumeric characters (a-z, A-Z, 0-9) or hyphens, which is usually the domain name part of the URL.
    Matches 50 different\ domain extensions, like .com, .gov, .io etc.
    ([-\w@:%_\+.~#?&//=]*)? matches optional path, query string, fragment identifiers, etc.
*/


// function which finds most of URLs in string
void find_all_links(string file_contents, string &all_links)
{
    std::regex link_regex(R"((https?:\/\/)?(www\.)?([a-zA-Z0-9\-]+)(\.(com|org|net|gov|io|co|uk|us|ca|au|de|jp|ru|fr|it|nl|se|es|br|pl|in|cn|mx|za|ch|at|be|dk|no|fi|gr|hu|il|kr|pt|ro|tr|cz))([-\/\w@:%_\+.~#?&//=]*)?)");
    smatch matches;
    while (regex_search(file_contents, matches, link_regex))
    {
        // remove dot from the end of the link
        if (matches[0].str().back() == '.')
        {
            string temp = matches[0].str();
            temp.pop_back();
            all_links += temp;
        }
        else{
            all_links += matches[0];
        }
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
    cout << "File read successfully.\n";
}

void write_to_file(string &file_name, map<string, pair<int, vector<int>>> &repeated_words, string &all_links)
{
    ofstream out_file("result_files/" + file_name + "_results.txt");

    out_file << "\nAll links: " << endl;
    out_file << all_links << endl;
    
    // print repeated words and/or links in a cross-reference table
    out_file << "\nRepeated words and/or links in a cross-reference table: " << endl;
    int counter = 0;

    for (const auto &entry : repeated_words)
    {
        out_file << fixed << setw(15) << entry.first << " : " << fixed << setw(4) << entry.second.first << " : ";
        for (const auto &element : entry.second.second)
        {
            out_file << element << " ";
        }
        out_file << endl;
    }

    out_file.close();
}
