
#include "data.h"
data::data(std::string id, float rating, int votes)
{
    this->id = id;
    this->rating = rating;
    this->numVotes = votes;
}

data::data(std::string id, std::string titleType, std::string primaryTitle, std::string originalTitle, std::vector<std::string> genres, bool adult, int  startYear, int endYear, int runtimeMinutes)
{
    this->id = id;
    this->titleType = titleType;
    this->primaryTitle = primaryTitle;
    this->originalTitle = originalTitle;
    this->genres = genres;
    this->isAdult = adult;
    this->startYear = startYear;
    this->endYear = endYear;
    this->runtimeMinutes = runtimeMinutes;
}