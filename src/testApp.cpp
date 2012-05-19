#include "testApp.h"
#include "ofxXmlSettings.h"
#include "ofxTweenzor.h"
#define PORT 12045

//--------------------------------------------------------------
void testApp::setup(){
  loadFromXML();
  ofEnableAlphaBlending();
  Tweenzor::init();
  //ofBackground(255, 0, 0);
  _receiver.setup(PORT);

  // loops
  _bgLoop.loadMovie("animations/backgroundlogo_dashboard.mov");
  _bgLoop.setLoopState(OF_LOOP_NORMAL);
  _bgLoop.play();

  #ifdef TARGET_LINUX
    _logoLoop.setPixelFormat(OF_PIXELS_BGRA);
  #endif
  _logoLoop.loadMovie("animations/mots/logoballroom_anime.mov");
  _logoLoop.setLoopState(OF_LOOP_NORMAL);
  _logoLoop.play();

  // load digits
  _digits.resize(10);
  for (unsigned int i = 0; i < 10; i++){
    ofImage *image = new ofImage();
    image->loadImage("graphics/numbers_PNG/" + ofToString(i) + ".png");
    _digits[i] = image;
  }
}

//--------------------------------------------------------------
void testApp::update(){
  Tweenzor::update( ofGetElapsedTimeMillis() );
  checkForOscMessages();
  _bgLoop.update();
  _logoLoop.update();
  for (unsigned int i = 0; i < _stairs.size(); i++){
    _stairs[i]->update();
  }

  // logo loop
  if (ofGetElapsedTimeMillis() - _lastBangTime > 10000
     /*&& !_logoLoop.isPlaying()*/){
    _logoLoop.play();
    _score = 0;
    _easeScore = 0;
  }
}

//--------------------------------------------------------------
void testApp::draw(){
  ofRectangle rect;
  rect.set(0, 0, 600, 450);
  _bgLoop.draw(rect);
  _logoLoop.draw(rect);
  for (unsigned int i = 0; i < _stairs.size(); i++){
    _stairs[i]->draw(rect.x, rect.y, rect.width, rect.height);
  }
  drawScore(_easeScore);
}

//--------------------------------------------------------------
void testApp::drawScore(int score){
  int length = 7;
  //cout << "score: " ;
  for (int i = 0; i < length; i++){
    int digit = (int)(score / (int)pow(10,(length -1 - i))) % 10;
    //cout << digit << endl;
    float ratio = 0.9;
    int digitWidth = 90*ratio;
    int digitHeight = 100*ratio;

    _digits[digit]->draw(i*digitWidth, 450- digitHeight, digitWidth, digitHeight); 
  }
  //cout << endl;
}

//--------------------------------------------------------------
void testApp::checkForOscMessages(){
  while (_receiver.hasWaitingMessages()){
    ofxOscMessage m;
    _receiver.getNextMessage(&m);
    if (m.getAddress() == "/ballroom/bounce/"){
      int stair = m.getArgAsInt32(0);
      cout << "A ball hit stair #" << stair << endl;
      bangStair(stair);
    }
  }
}

//--------------------------------------------------------------
void testApp::bangStair(int stair){
    _stairs[stair]->start();

    _lastBangTime = ofGetElapsedTimeMillis();
    _logoLoop.stop();
    _logoLoop.firstFrame();
    _score = _score + _stairs[stair]->_score;
    Tweenzor::add( &_easeScore, _easeScore, _score, 0.f, 2.0f, EASE_IN_QUINT);
}

//--------------------------------------------------------------
void testApp::loadFromXML(){
  ofxXmlSettings xml;
  string fileName = "settings.xml";

  if (xml.loadFile(fileName)){
    cout << "XML file loaded: " + fileName << endl;
  } else{
    cout << "Unable to find bin/data/" + fileName << endl;
  }
  
  int thereIsStairs = xml.getNumTags("STAIRS");
  if (thereIsStairs > 0){
    xml.pushTag("STAIRS", 0);
    int size = xml.getNumTags("STAIR");
    _stairs.resize(size);
    for (int i = 0; i < size; i++){
      xml.pushTag("STAIR", i);
      sxStair *stair = new sxStair();
      stair->setup();
      fileName = xml.getValue("VIDEO","");
      stair->loadMovie(fileName);
      int id = xml.getValue("ID",-1);
      stair->setId(id);
      int score = xml.getValue("SCORE", 0);
      stair->setScore(score);
      _stairs[id] = stair;
      xml.popTag();
    }
    xml.popTag();
  }
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
  if (key == 'f'){
    ofToggleFullscreen();
  }
  else if (key == '#'){
    bangStair(0);
  }
  else if (key == '1'){
    bangStair(1);
  }
  else if (key == '2'){
    bangStair(2);
  }
  else if (key == '3'){
    bangStair(3);
  }
  else if (key == '4'){
    bangStair(4);
  }
  else if (key == '5'){
    bangStair(5);
  }
  else if (key == '6'){
    bangStair(6);
  }
  else if (key == '7'){
    bangStair(7);
  }
  else if (key == '8'){
    bangStair(8);
  }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
