#pragma once

#include "ofMain.h"
#include "sxStair.h"
#include "ofxOsc.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void checkForOscMessages();
		
    void loadFromXML();
    void tada();
    void gameover();
    void startPlaying();
    void bangStair(int stair);
    void drawScore(int score);

    vector<sxStair*> _stairs;
    vector<ofImage*> _digits;
    ofVideoPlayer _bgLoop;
    ofVideoPlayer _logoLoop;
    int _lastBangTime;
    int _score;
    float _easeScore;

    ofxOscReceiver _receiver;
};
