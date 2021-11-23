#include "Review.h"
#include <cstring>

using namespace std;



// Construtor

Review::Review(char* review_id, char* review_text, char* app_version, char* posted_date,int upvotes){
    strcpy (this->review_id, review_id);
    strcpy (this->review_text, review_text);
    strcpy (this->app_version, app_version);
    strcpy (this->posted_date, posted_date);
    this->upvotes = upvotes;
}

Review::Review(){
    review_id[0] = '\0';
    review_text[0] = '\0';
    app_version[0] = '\0';
    posted_date[0] = '\0';
    upvotes = 0;
}

// Destrutor
Review::~Review(){}

// Getters
char* Review::getReview_id(){
    return this->review_id;
}

char* Review::getReview_text(){
    return this->review_text;
}

char* Review::getApp_version(){
    return this->app_version;
}

char* Review::getPosted_date(){
    return this->posted_date;
}

int Review::getUpvotes(){
    return this->upvotes;
}

//Setters
void Review::getReview_id(char* review_id){
    strcpy (this->review_id, review_id);
}

void Review::getReview_text(char* review_text){
    strcpy (this->review_text, review_text);
}

void Review::getApp_version(char* app_version){
     strcpy (this->app_version, app_version);
}

void Review::getPosted_date(char* posted_date){
    strcpy (this->posted_date, posted_date);
}
void Review::getUpvotes(int upvotes){
    this->upvotes = upvotes;
}
