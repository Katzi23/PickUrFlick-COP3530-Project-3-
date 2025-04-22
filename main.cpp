#include <iostream>
#include <string>
#include <deque>
#include <fstream>
#include <sstream>
#include "data.h"
#include "data.cpp"
#include <unordered_map>

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
    // store everything in a map
    std::unordered_map<std::string, data> items;

    // this is all for ratings:

    // deque to store the data for now
//    std::deque<data> items;

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

        // make a new data object with these values and add to items
        data d(id, rating, votes);
        items.insert({id, d});
//        items.push_back(d);

    }
    file.close();

    // now we have to do it all again for title.basics.tsv:
    // stores:
    // tconst	titleType	primaryTitle	originalTitle	isAdult	startYear	endYear	runtimeMinutes	genres

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

        // it's an adult theme if isAdult != 1, this includes any incorrect data elements,
        // so if we don't know, it will be classified as adult
        bool adult = (isAdult != "1");

        int start = safe_stoi(startYear);
        int end = safe_stoi(endYear);
        int runtime = safe_stoi(runtimeMinutes);

        // make a new data object with these values
        data d2(id, titleType, primaryTitle, originalTitle, genres, adult, start, end, runtime);

        // if it exists in items, add the rest of the data
        auto it = items.find(id);
        if (it != items.end())
        {
            // Update the existing data object to add the "basics" info
            it->second.setTitleType(titleType);
            it->second.setPrimaryTitle(primaryTitle);
            it->second.setOriginalTitle(originalTitle);
            it->second.setGenres(genres);
            it->second.setIsAdult(adult);
            it->second.setStartYear(start);
            it->second.setEndYear(end);
            it->second.setRuntimeMinutes(runtime);
        }
        else
            continue;
            // there is no rating, so ignore it
    }
    file2.close();

    // now remove any items from the first file (title.ratings.tsv) that didn't get updated from the second title.basics.tsv
    for (auto it = items.begin(); it != items.end(); )
    {
        // titleType is only "" if it was not updated, remove it
        if (!it->second.updated())
        {
            // erase returns the next valid iterator
            it = items.erase(it);
        } else {
            ++it;
        }
    }

    return 0;
}
