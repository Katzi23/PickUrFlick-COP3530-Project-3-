#include <iostream>
#include <string>
#include <deque>
#include <fstream>
#include <sstream>
#include "data.h"
#include "data.cpp"

// helper function for checking for bad data when converting to ints
int safe_stoi(const std::string& s)
{
    // if the string is empty, \N, or <unset>, return -1
    if (s.empty() || s == "\\N" || s == "<unset>") return -1;
    // otherwise, try to return the string, but use catch to return -1 if it's invalid or out of range
    try
    {
        return std::stoi(s);
    } catch (const std::invalid_argument& e)
    {
        return -1;
    } catch (const std::out_of_range& e)
    {
        return -1;
    }
}

int main()
{
    // this is all for ratings:

    // deque to store the data for now
    std::deque<data> items;

    // open ratings file and make each data object
    std::ifstream file("title.ratings.tsv");
    std::string line;

    // skip the header
    std::getline(file, line);

    // go through each line of the file
    while (std::getline(file, line))
    {
        // make a string stream from line
        std::istringstream iss(line);
        // make variables to store each value
        std::string id, ratingStr, votesStr;

        // now read up to each tab, and store the values
        std::getline(iss, id, '\t');
        std::getline(iss, ratingStr, '\t');
        std::getline(iss, votesStr, '\t');

        // convert to needed variables
        float rating = std::stof(ratingStr);
        int votes = std::stoi(votesStr);

        // make a new data object with these values and push to items
        data d(id, rating, votes);
        items.push_back(d);

    }
    file.close();

    // now we have to do it all again for title.basics.tsv:
    // stores:
    // tconst	titleType	primaryTitle	originalTitle	isAdult	startYear	endYear	runtimeMinutes	genres

    // deque to store the data for now
    std::deque<data> items2;

    // open ratings file and make each data object
    std::ifstream file2("title.basics.tsv");
    std::string line2;

    // skip the header
    std::getline(file2, line2);

    // go through each line of the file2
    while (std::getline(file2, line2))
    {
        // make a string stream from line2
        std::istringstream iss(line2);
        // make variables to store each value
        std::string id, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genresStr;
        std::vector<std::string> genres;

        // now read up to each tab, and store the values
        std::getline(iss, id, '\t');
        std::getline(iss, titleType, '\t');
        std::getline(iss, primaryTitle, '\t');
        std::getline(iss, originalTitle, '\t');
        std::getline(iss, isAdult, '\t');
        std::getline(iss, startYear, '\t');
        std::getline(iss, endYear, '\t');
        std::getline(iss, runtimeMinutes, '\t');
        std::getline(iss, genresStr, '\t');


        // convert to needed variables

        // go through the genres string, get each genre (they are separated by ,), and add it to genres vector
        if (genresStr != "\\N")
        {
            std::istringstream gss(genresStr);
            std::string genre;
            while (std::getline(gss, genre, ','))
                genres.push_back(genre);
        }

        // it's an adult theme if isAdult != 0, this includes any incorrect data elements,
        // so if we don't know, it will be classified as adult
        bool adult = (isAdult != "0");

        int start = safe_stoi(startYear);
        int end = safe_stoi(endYear);
        int runtime = safe_stoi(runtimeMinutes);

        // make a new data object with these values and push to items2
        data d2(id, titleType, primaryTitle, originalTitle, genres, adult, start, end, runtime);
        items2.push_back(d2);

    }
    file2.close();

    return 0;
}