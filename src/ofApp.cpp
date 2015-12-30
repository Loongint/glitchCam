#include "ofApp.h"

void ofApp::setup(){
  bgsound.load("1.mp3");
  bgsound.setLoop(true);
  bgsound.play();

    gui.setup();

    gui.add(title.setup(ofToString("         Glitch"), 200, 30));
   
    gui.add(blockGlitch.setup("block", false));
    
    gui.add(linesGlitch.setup("lines", false));
    
    gui.add(disloc.setup("dislocation", false));
    
    gui.add(channelShuffle.setup("channelShuffle", false));
    
    gui.add(texchipS.setup("", .5, 0.0, 1.2));
    gui.add(texchip.setup("texchip",false));
    gui.add(texchipS.setup("", .5, 0.0, 1.2));

    gui.add(pixellate.setup("pixellate", false));
    
    gui.add(noiseS.setup("",.8, 0.0, 1.0));
    gui.add(noise.setup("noise", false));
    gui.add(noiseS.setup("",.8, 0.0, 1.0));

    gui.add(colorFucked.setup("colorFucked", false));
    
    gui.add(tint.setup("tint", false));
    
    gui.add(edgeontop.setup("edge", false));
    
    gui.add(fringeS.setup("", .2, 0.0, 1.0));
    gui.add(fringe.setup("fringe",false));
    gui.add(fringeS.setup("", .2, 0.0, 1.0));
    
    gui.add(gray.setup("gray", false));
    
    gui.add(invertS.setup("", 7.0, 0.0, 10.0));
    gui.add(invert.setup("invert",false));
    gui.add(invertS.setup("", 7.0, 0.0, 10.0));

    gui.add(melting.setup("melting", false));

    gui.add(pattern.setup("pattern", false));
    
    gui.add(slantshiftS.setup("", 0.3, 0.0, 1.0));
    gui.add(slantshift.setup("slant", false));
    gui.add(slantshiftS.setup("", 0.3, 0.0, 1.0));
    
    gui.add(vertnoiseS.setup("",5.0, 0.0, 10.0));
    gui.add(vertnoise.setup("vertnoise",false));
    gui.add(vertnoiseS.setup("",5.0, 0.0, 10.0));
    
    gui.add(vertslideS.setup("",1000.0, 500.0, 4000.0));
    gui.add(vertslide.setup("slide",false));
    gui.add(vertslideS.setup("",900.0, 100.0, 1000.0));
  
  gui.add(frame.setup("frameRate: ", ofToString(ofGetFrameRate())));

  randomize = 1;
  ranrandomize = 0;
  ranranrandomize = 0;

  camWidth = 640;
  camHeight = 480;

  myCam.setDeviceID(0);
  myCam.initGrabber(camWidth,camHeight);
    
    setting.width = ofGetWidth();
    setting.height = ofGetHeight();
    original.allocate(setting);
    
    fx.setup(&original, setting);
    
   
}

void ofApp::update(){
    frame = ofToString(ofGetFrameRate());
    fx.getfxUnit(KSMR_FRAGFX_NOISE)->bEnable		= noise;
    fx.getfxUnit(KSMR_FRAGFX_NOISE)->u_Volume = noiseS;
    
    fx.getfxUnit(KSMR_FRAGFX_EDGEONTOP)->bEnable	= edgeontop;
    fx.getfxUnit(KSMR_FRAGFX_EDGEONTOP)->u_Volume = edgeontopS;
    
    fx.getfxUnit(KSMR_FRAGFX_FRINGE)->bEnable		= fringe;
    fx.getfxUnit(KSMR_FRAGFX_FRINGE)->u_Volume = fringeS;
    
    fx.getfxUnit(KSMR_FRAGFX_INVERT)->bEnable		= invert;
    fx.getfxUnit(KSMR_FRAGFX_INVERT)->u_Volume = invertS;
    
    fx.getfxUnit(KSMR_FRAGFX_SLANTSHIFT)->bEnable	= slantshift;
    fx.getfxUnit(KSMR_FRAGFX_SLANTSHIFT)->u_Volume = slantshiftS;
    
    fx.getfxUnit(KSMR_FRAGFX_TEXCHIP)->bEnable		= texchip;
    fx.getfxUnit(KSMR_FRAGFX_TEXCHIP)->u_Volume = texchipS;
    
    fx.getfxUnit(KSMR_FRAGFX_VERTNOISE)->bEnable = vertnoise;
    fx.getfxUnit(KSMR_FRAGFX_VERTNOISE)->u_Volume = vertnoiseS;
    
    fx.getfxUnit(KSMR_FRAGFX_VERTSLIDE)->bEnable	= vertslide;
    fx.getfxUnit(KSMR_FRAGFX_VERTSLIDE)->u_Volume = ofNoise(ofGetElapsedTimef())*vertslideS;
    
  myCam.update();
  img.setFromPixels(myCam.getPixels());
  img.update();
}

void ofApp::draw(){
    ofSeedRandom(randomize);

    ranrandomize ++;
    if(ranrandomize == (int)ofRandom(3, 7)) {
        randomize ++;
        ranrandomize = 0;
    }

    ranranrandomize ++;
    if(ranranrandomize == 20) {
        blockGlitch = randomBool(.3);
        linesGlitch = randomBool(.3);
        channelShuffle = randomBool(.3);
        disloc = randomBool(.3);
		pixellate = randomBool(.9);
		colorFucked = randomBool(.5);
		tint = randomBool(.5);
		gray = randomBool(.3);
		melting = randomBool(.5);
		pattern = randomBool(.5);
        noise = randomBool(.5);
        edgeontop = randomBool(.5);
        fringe = randomBool(.8);
        invert = randomBool(.9);
        slantshift = randomBool(.5);
        texchip = randomBool(.5);
        vertslide = randomBool(.5);
        vertnoise = randomBool(.5);

        ranranrandomize = 0;
    }
    
    original.begin();{
        ofClear(0,0,0,255);
        
        glitch_1();
        
        glitch_3();
        
        img.draw(0,0,ofGetWidth(),ofGetHeight());
        
        glitch_2();
        
        ofSetColor(255);
        
        glitch_4();
        
    }original.end();
    
    fx.applyFx();
    
    original.draw(0,0);
    
    //gui.draw();
}

void ofApp::keyPressed(int key){
    ofPixels pix2;
    original.readToPixels(pix2);
    ofImage card;
    card.setFromPixels(pix2);
    card.save("1.png");
}

bool ofApp::randomBool(float piu) {
  float biu = ofRandom(0,1);
  if(biu > piu) {
    return true;
  } else {
    return false;
  }
}

void ofApp::glitch_1() {
  if(tint){addTint();}
  if(colorFucked){glitch_colors(int(ofRandom(-40,40)), int(ofRandom(-5,5)));}
  if(gray){glitch_gray();}
}

void ofApp::glitch_2() {
  if(blockGlitch){glitch_block();}
  if(linesGlitch){glitch_lines();}
  if(disloc){glitch_disloc();}
  if(channelShuffle){glitch_channelShuffle();}
}

void ofApp::glitch_3() {
  if(melting){glitch_melt();}
  if(pattern){glitch_pattern();}
}

void ofApp::glitch_4() {
  if(pixellate){glitch_pixel(int(ofRandom(2, 20)));}
}

int ofApp::min(int a, int b) {
  if(a < b) {
    return a;
  } else {
    return b;
  }
}

int ofApp::max(int a, int b) {
  if(a > b) {
    return a;
  } else {
    return b;
  }
}

void ofApp::swapAB(int a, int b) {
  int tmp;
  tmp = a;
  a = b;
  b = tmp;
}
void ofApp::glitch_block() {
  int num = int(ofRandom(5, 20));

  for(int i = 0; i < num; i++) {
    int startX = int(ofRandom(0, ofGetWidth()));
    int startY = int(ofRandom(0, ofGetHeight()));
    int randWidth = int(ofRandom(3, 10));
    int randHeight = int(ofRandom(3, 10));
    int placeX = int(ofRandom(0, ofGetWidth()));
    int placeY = int(ofRandom(0, ofGetWidth()));
    int placeWidth = int(ofRandom(30, 70));
    int placeHeight = int(ofRandom(30, 70));

    img.drawSubsection(placeX, placeY, placeWidth, placeHeight,startX, startY, randWidth, randHeight);
  }

  img.update();
}

void ofApp::glitch_lines() {
  int num = int(ofRandom(5, 30));
  for(int i = 0; i < num; i++) {
    int startX = int(ofRandom(0, ofGetWidth()));
    int startY = int(ofRandom(0, ofGetHeight()));
    int randWidth = int(ofRandom(3, 10));
    int randHeight = int(ofRandom(3, 10));
    int placeX = 0;
    int placeY = int(ofRandom(0, ofGetWidth()));
    int placeWidth = ofGetWidth();
    int placeHeight = 2;

    img.drawSubsection(placeX, placeY, placeWidth, placeHeight,startX, startY, randWidth, randHeight);
  }

  img.update();
}

void ofApp::glitch_disloc() {
  int num = (int)ofRandom(1,3);
  for (int i = 0; i <= num; i++) {
    int h = (int)ofRandom(0,camHeight - 100);
    int hh = (int)ofRandom(30, 100);
    int a = (int)ofRandom(camWidth/1.1 ,camWidth);

    float hbiu = h * ofGetHeight() / camHeight;
    float hhbiu = hh * ofGetHeight() / camHeight;
    float abiu = a * ofGetWidth() / camWidth;
    img.drawSubsection(0,hbiu,ofGetWidth() - abiu,hhbiu,a,h,camWidth - a,hh);
    img.drawSubsection(ofGetWidth()-abiu,hbiu,abiu,hhbiu,0,h,a,hh);
  }
  num = (int)ofRandom(1,3);
  for (int i = 0; i <= num; i++) {
    int h = (int)ofRandom(0,camHeight - 100);
    int hh = (int)ofRandom(30, 100);
    int a = (int)ofRandom(10 , 64);

    float hbiu = h * ofGetHeight() / camHeight;
    float hhbiu = hh * ofGetHeight() / camHeight;
    float abiu = a * ofGetWidth() / camWidth;
    img.drawSubsection(0,hbiu,ofGetWidth() - abiu,hhbiu,a,h,camWidth - a,hh);
    img.drawSubsection(ofGetWidth()-abiu,hbiu,abiu,hhbiu,0,h,a,hh);
  }
  img.update();
}

void ofApp::glitch_channelShuffle() {
  int num = int(ofRandom(1, 20));
  for(int x = 0; x < num; x++) {
    int channel = int(ofRandom(0, 2.5));
    int startX = int(ofRandom(0, ofGetWidth()));
    int startY = int(ofRandom(0, ofGetHeight()));
    int randWidth = int(ofRandom(70, 300));
    int randHeight = int(ofRandom(40, 100));
    int randX = int(ofRandom(-100, 100));
    int randY = int(ofRandom(-100, 100));

    if(channel == 0) {
      ofSetColor(255,0,0,70);
    } else if(channel == 1) {
      ofSetColor(0,255,0,70);
    } else {
      ofSetColor(0,0,255,70);
    }
    img.drawSubsection(startX+randX, startY+randY, randWidth, randHeight,startX, startY, randWidth, randHeight);
  }

  img.update();
}

void ofApp::glitch_pixel(int size) {
  for (int x = 0; x < camWidth - size; x += size) {
    for (int y = 0; y < camHeight - size; y += size) {
      ofSetColor(img.getColor(x + size, y + size));
      ofDrawRectangle(x * ofGetWidth() / camWidth, y * ofGetWidth() / camWidth, size * ofGetWidth() / camWidth + 3, size * ofGetWidth() / camWidth+ 3);
    }
  }
}

void ofApp::glitch_colors(int hueShift, int satShift) {
  int biu = (int)ofRandom(0, camHeight);
  int biubiu = (int)ofRandom(biu, camHeight);

  while((biubiu - biu) < 100) {
    biu = (int)ofRandom(0, camHeight);
    biubiu = (int)ofRandom(biu, camHeight);
  }
  for(int x = 0; x < camWidth; x++) {
    for(int y = biu; y < biubiu; y++) {
      ofColor pixel;
      pixel.set(img.getColor(x,y));
      pixel.set(pixel.getHue() + hueShift, pixel.getSaturation() + satShift, pixel.getBrightness());
      img.setColor(x, y, pixel);
    }
  }
  img.update();
}

void ofApp::glitch_gray() {
  int biu = (int)ofRandom(0, camHeight);
  int biubiu = (int)ofRandom(biu, camHeight);

  while((biubiu - biu) < 100) {
    biu = (int)ofRandom(0, camHeight);
    biubiu = (int)ofRandom(biu, camHeight);
  }
  for(int x = 0; x < camWidth; x++) {
    for(int y = biu; y < biubiu; y++) {
      ofColor pixel;
      pixel.set(img.getColor(x,y));
      pixel.set((pixel.r*30 + pixel.g*59 + pixel.b*11 + 50) / 100);
      img.setColor(x, y, pixel);
    }
  }
  img.update();
}

void ofApp::addTint() {
    int rr = int(ofRandom(100));
    int gg = int(ofRandom(100));
    int bb = int(ofRandom(100));

    for(int i = 0; i < camWidth; i++){
      for(int j = 0; j < camHeight; j++){
        ofColor c;
        c.set(img.getColor(i,j));
        c.r += rr;
        if(c.r>255){c.r=255;}
        c.b += bb;
        if(c.b>255){c.b=255;}
        c.g += gg;
        if(c.g>255){c.g=255;}
        img.setColor(i,j,c);
      }
    }
    img.update();
}

void ofApp::glitch_melt() {
  int melts = int(ofRandom(30, 80));
  for(int j = 0; j < melts; j++) {
    int startX = int(ofRandom(0, camWidth));
    int startY = int(ofRandom(0, camHeight));
    int meltLength = int(ofRandom(20, 40));
    int meltWidth = int(ofRandom(3, 5));
    ofColor c = img.getColor(startX, startY);

    while((startX + meltWidth)>camWidth) {
        startX--;
    }
    while((startY + meltLength)>camHeight) {
        startY--;
    }
    for(int i = 0; i < meltLength; i++) {
      for(int k = 0; k < meltWidth; k++) {
        img.setColor(startX+k, startY+i, c);
      }
    }
  }
  img.update();
}

void ofApp::glitch_pattern() {
  int num = int(ofRandom(5, 10));
  for(int count = 0; count < num; count++) {
    int randX = int(ofRandom(0, camWidth));
    int randY = int(ofRandom(0, camHeight));
    int randHeight = int(ofRandom(1, camHeight-randY));
    int randWidth = int(ofRandom(1, camWidth-randX));

    int shifts[randHeight];
    shifts[0] = 0;
    int mostLeft = 0;
    int mostRight = 0;
    for(int i = 1; i < randHeight; i++) {
      int shift = int(ofRandom(-1.5, 1.5));
      shifts[i] = shifts[i-1] + shift;
      if(shifts[i] < mostLeft) { mostLeft = shifts[i]; }
      else if (shifts[i] > mostRight) { mostRight = shifts[i]; }
    }

    int start = int(ofRandom(0, camHeight));
    int stop = int(ofRandom(start, camWidth));

    for(int inY = 0; inY < randHeight; inY++) {
      int offset = (randX +shifts[inY] ) % randWidth;
      int counter = offset;
      for(int x = start; x < stop; x++) {
         ofColor c = img.getColor(randX+(counter), randY+inY);
         if(x<0){x=0;}
         if(x>camWidth){x=camWidth;}
         int tmpy = randY+inY;
         if(tmpy<0){tmpy=0;}
         if(tmpy>camHeight){tmpy=camHeight;}
         img.setColor(x, tmpy, c);
         counter++;
         if (counter > randWidth) { counter = 0; }
      }
    }
  }

  img.update();
}


