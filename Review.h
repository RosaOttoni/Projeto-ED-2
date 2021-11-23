#ifndef REVIEW_H_INCLUDED
#define REVIEW_H_INCLUDED

#include <iostream>

using namespace std;

class Review{
    private:
        char review_id[90], review_text[1000], app_version[10], posted_date[20];
        int upvotes;

    public:
        //Construtor
        Review(char* review_id, char* review_text, char* app_version, char* posted_date,int upvotes);

        Review();

        //Destrutor
        ~Review();

        //Getters
        char* getReview_id();
        char* getReview_text();
        char* getApp_version();
        char* getPosted_date();
        int getUpvotes();

        // Setters
        void getReview_id(char* review_id);
        void getReview_text(char* review_text);
        void getApp_version(char* app_version);
        void getPosted_date(char* posted_date);
        void getUpvotes(int upvotes);
};

#endif // REVIEW_H_INCLUDED
