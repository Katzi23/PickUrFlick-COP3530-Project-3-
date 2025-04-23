
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

void data::setEndYear(int endYear)
{
    this->endYear = endYear;
}

void data::setGenres(std::vector<std::string> genres)
{
    this->genres = genres;
}

void data::setId(std::string i)
{
    this->id = i;
}

void data::setIsAdult(bool adult)
{
    this->isAdult = adult;
}

void data::setOriginalTitle(std::string originalTitle)
{
    this->originalTitle = originalTitle;
}

void data::setPrimaryTitle(std::string primaryTitle)
{
    this->primaryTitle = primaryTitle;
}

void data::setRuntimeMinutes(int runtimeMinutes)
{
    this->runtimeMinutes = runtimeMinutes;
}

void data::setStartYear(int startYear)
{
    this->startYear = startYear;
}

void data::setTitleType(std::string titleType)
{
    this->titleType = titleType;
}

bool data::updated()
{
    return (this->titleType != "");
}

int data::getEndYear() const
{
    return this->endYear;
}

const std::vector<std::string>& data::getGenres() const
{
    return this->genres;
}

const std::string& data::getId() const
{
    return this->id;
}

bool data::getIsAdult() const
{
    return this->isAdult;
}

const std::string& data::getOriginalTitle() const
{
    return this->originalTitle;
}

const std::string& data::getPrimaryTitle() const
{
    return this->primaryTitle;
}

int data::getRuntimeMinutes() const
{
    return this->runtimeMinutes;
}

int data::getStartYear() const
{
    return this->startYear;
}

const std::string& data::getTitleType() const
{
    return this->titleType;
}

float data::getRating() const
{
    return this->rating;
}

int data::getVotes() const {
    return this->numVotes;
}