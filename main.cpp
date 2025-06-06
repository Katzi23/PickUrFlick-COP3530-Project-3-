#include <iostream>
#include <string>
#include <deque>
#include <fstream>
#include <sstream>
#include "data.h"
#include "data.cpp"
#include <unordered_map>
#include "ArrayQ.h"
#include "ArrayQ.cpp"
#include "MaxHeap.h"
#include "MaxHeap.cpp"
#include <limits>


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

float safe_stof(const std::string& s){
    if (s.empty() || s == "\\N" || s == "<unset>"){
        return -1.0f;
    }
    try {
        return std::stof(s);
    } catch (...){
        return -1.0f;
    }
}

//Filter movie list based on the selected categories
bool checkFilter(data* movie, int mov, int year, int beforeOrAfter, int yearData, int minRun, int minRuntime, int maxRun, int maxRuntime, int genre, const std::vector<std::string>& genresWanted) {
    if (year == 1) {
        if (beforeOrAfter == 1 && movie->getStartYear() >= yearData) return false; //check if year is valid
        if (beforeOrAfter == 0 && movie->getStartYear() <= yearData) return false;
    }

    if (minRun == 1 && movie->getRuntimeMinutes() < minRuntime) return false; //Check if runtime is valid
    if (maxRun == 1 && movie->getRuntimeMinutes() > maxRuntime) return false;

    if (genre == 1){ //Check genre based on list of genres wanted and list of genres of movie
        bool genreCheck = false;
        for (const auto& g : movie->getGenres()) {
            for (const auto& want : genresWanted){
                if (g == "Adult"){
                    return false;
                }
                if (g == want) {
                    genreCheck = true;
                    break;
                }
            }
            if (genreCheck) break;
        }

        if (!genreCheck) return false;
    }
    return true;
}

int main()
{
    // store everything in a map
    std::unordered_map<std::string, data*> items;


    // this is all for ratings:

    // open ratings file and make each data object
    std::ifstream file("title.ratings.tsv");
    std::string line;

    // skip the header
    file >> std::noskipws;
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
        float rating = safe_stof(ratingStr);
        int votes = safe_stoi(votesStr);

        // make a new data object with these values and add to items
        data* d = new data(id, rating, votes);
        items.insert({id, d});

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
            it->second->setTitleType(titleType);
            it->second->setPrimaryTitle(primaryTitle);
            it->second->setOriginalTitle(originalTitle);
            it->second->setGenres(genres);
            it->second->setIsAdult(adult);
            it->second->setStartYear(start);
            it->second->setEndYear(end);
            it->second->setRuntimeMinutes(runtime);
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
        if (!it->second->updated())
        {
            // erase returns the next valid iterator
            it = items.erase(it);
        } else {
            ++it;
        }
    }

    // now we can begin actual user interaction
    // first see what option user wants to use
    std::cout<< "Welcome to PickUrFlick! \n Data can be stored in two kinds of priority queues, a max heap or a sorted array implementation. \n To begin, press 1 and then enter if you want to use a max heap, \n or press 0 and then enter if you want to use a sorted array \n";
    int type;
    std::cin >> type;
    MaxHeap heap;
    ArrayQ arr;
    if (type == 1)
    {
        std::cout << "Building the max heap ... \n";
        // build the max heap
        for (auto const& item : items){
            data* movie = item.second;
            if (movie->getVotes() < 25000) continue;
            if (movie->getTitleType() != "movie") continue;
            heap.insert(movie);
        }
    } else {
        std::cout << "Building the sorted array ... \n";
        // build the sorted array
        for (auto const& item : items)
        {
            data *movie = item.second;
            if (movie->getVotes() < 25000) continue;
            if (movie->getTitleType() != "movie") continue;
            arr.insert(movie);
        }
    }

    // create variables to determine what to sort
    // if it's still equal to -1 then the user is not using it to sort

    // if mov == 1 then the user only wants movies, otherwise only shorts
    int mov = -1;



    int year = -1;
    // if beforeOrAfter == 1 then search for before yearData, otherwise after
    int beforeOrAfter;
    int yearData;

    // same storage pattern as above
    int minRun = -1;
    int minRuntime;
    int maxRun = -1;
    int maxRuntime;

    int genre = -1;
    std::string genresStr;
    std::vector<std::string> genresWanted;

    std::cout << "Data structure built! \n Now answer these questions to filter the results: \n";

    std::cout << "Do you want to sort by year? (enter 1 for yes and 0 for no) \n";
    std::cin >> year;
    if (year == 1)
    {
        std::cout << "Do you want to sort before (1) or after (0) a certain year?";
        std::cin >> beforeOrAfter;
        std::cout << "Input the cutoff year numerically (it will be included in the search)";
        std::cin >> yearData;
    }
    std::cout << "Do you want to set a minimum runtime? (enter 1 for yes and 0 for no) \n";
    std::cin >> minRun;
    if (minRun == 1)
    {
        std::cout << "Enter a minimum runtime \n";
        std::cin >> minRuntime;
    }
    std::cout << "Do you want to set a maximum runtime? (enter 1 for yes and 0 for no) \n";
    std::cin >> maxRun;
    if (maxRun == 1)
    {
        std::cout << "Enter a maximum runtime \n";
        std::cin >> maxRuntime;
    }
    std::cout << "Do you want to sort by genre? (enter 1 for yes and 0 for no) \n";
    std::cin >> genre;
    if (genre == 1)
    {
        std::cout << "Here are the available genres: Action, Adventure, Animation, Biography, Comedy, Crime, \n"
                     "Documentary, Drama, Family, Fantasy, Film-Noir, History, Horror, Music, Musical, Mystery, News, \n"
                     "Romance, Sci-Fi, Short, Sport, Thriller, War, Western \n";
        std::cout << "Type what genres you want exactly as they appear above, separated by spaces \n";
        // get the entire line
        // Now, before getline:
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, genresStr);

        // now convert into a list:
        std::istringstream iss(genresStr);
        std::string genre;
        while (iss >> genre)
            genresWanted.push_back(genre);
    }

    std::cout << "Input received! filtering results... \n";

    // now search through the data structure for the top 3 results
    if (type == 1){
        int found = 0;
        std::cout << "Top 3 Results: \n";
        while (!heap.isEmpty() && found < 3){
            data* movie = heap.extractMaxRating();
            if (checkFilter(movie, mov, year, beforeOrAfter, yearData, minRun, minRuntime, maxRun, maxRuntime, genre, genresWanted)){
                std::cout << movie->getPrimaryTitle() << " (" << movie->getStartYear() << "), Rating: " << movie->getRating() << "\n";
                found++;
            }
        }
        if (found == 0){
            std::cout << "No matches found based on your filters. \n";
        }
    } else if (type == 0){
        std::cout << "Top 3 Results: \n";
        int found = 0;
        while (!arr.isEmpty() && found < 3){
            data* movie = arr.extractMax();
            if (checkFilter(movie, mov, year, beforeOrAfter, yearData, minRun, minRuntime, maxRun, maxRuntime, genre, genresWanted)){
                std::cout << movie->getPrimaryTitle() << " (" << movie->getStartYear() << "), Rating: " << movie->getRating() << "\n";
                found++;
            }
        }
        if (found == 0){
            std::cout << "No matches found based on your filters. \n";
        }
    }
    return 0;
}