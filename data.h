#ifndef PICKURFLICK_COP3530_PROJECT_3_DATA_H
#define PICKURFLICK_COP3530_PROJECT_3_DATA_H
#include <iostream>
#include <string>
#include <vector>


class data
{
private:
    // theoretical titleType options: movie, short, tvseries, tvepisode, video, tvSpecial, tvShort, videoGame, musicVideo, podcastSeries
    std::string id, titleType, primaryTitle, originalTitle;
    std::vector<std::string> genres;
    // use -1 for any missing ints
    int rating, startYear, endYear, runtimeMinutes, numVotes;
    // if we don't know (bad data), it will be classified as adult
    bool isAdult;
public:
    data(std::string id, float rating, int votes);
    data(std::string id, std::string titleType, std::string primaryTitle, std::string originalTitle, std::vector<std::string> genres, bool adult, int  startYear, int endYear, int runtimeMinutes);
    void setId(std::string i);
    void setTitleType(std::string titleType);
    void setPrimaryTitle(std::string primaryTitle);
    void setOriginalTitle(std::string originalTitle);
    void setGenres(std::vector<std::string> genres);
    void setIsAdult(bool adult);
    void setStartYear(int startYear);
    void setEndYear(int endYear);
    void setRuntimeMinutes(int runtimeMinutes);
    bool updated();

};


#endif //PICKURFLICK_COP3530_PROJECT_3_DATA_H
