#include "sxStair.h"

//--------------------------------------------------------------
void sxStair::setup(){

}

//--------------------------------------------------------------
void sxStair::update(){
  _video.update();
}

//--------------------------------------------------------------
void sxStair::draw(int x, int y, int width, int height){
  _video.draw(x, y, width, height);
}

//--------------------------------------------------------------
void sxStair::loadMovie(const string & path){
  setup();
  #ifdef TARGET_LINUX
    _video.setPixelFormat(OF_PIXELS_BGRA);
  #endif
  _video.loadMovie(path);
  _video.setLoopState(OF_LOOP_NONE);
}

//--------------------------------------------------------------
void sxStair::start(){
  _video.firstFrame();
  _video.play();
}

//--------------------------------------------------------------
void sxStair::setId(int id){
  _id = id;
}

//--------------------------------------------------------------
void sxStair::setScore(int score){
  _score = score;
}

