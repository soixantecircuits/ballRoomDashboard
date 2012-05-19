#pragma once

#include "ofMain.h"

class sxStair{

	public:
		void setup();
		void update();
		void draw(int x, int y, int width, int height);

    void loadMovie(const string & path); 
    void setId(int id);
    void setScore(int score);
    void start();

    ofVideoPlayer _video;
    int _score;
    int _id;
};

