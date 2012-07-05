#ifndef qtDTest_VideoPlayer_h
#define qtDTest_VideoPlayer_h

#include "cinder/app/AppBasic.h"
#include "cinder/qtime/QuickTime.h"
#include "cinder/Timeline.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class VideoPlayer
{
    public:
        VideoPlayer();
        ~VideoPlayer();
    
    void setSize( Vec2i size );
    void setPosition( Vec2i position);
    
    void playNewMovie();
    void resume();
    void pause();
    
    void fadeToVal( float newAlpha );
    
    void update();
    void draw();
    
    
    
    
    protected:
    void playMovie();

    qtime::MovieGl movie;  
    gl::Texture movieTexture;
    Anim<float> movieAlpha;

    
    Vec2i size;
    Vec2i position;
    bool isPlaying;
    
    bool drawDebug;
    ColorA debugColor;
    
    fs::path currentMoviePath;
    fs::path queuedMoviePath;
    
    
};


#endif
