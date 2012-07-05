#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "VideoPlayer.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class qtDTestApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
    void resize ( ResizeEvent event );
	void update();
	void draw();
    
    VideoPlayer bgVideoPlayer;
    VideoPlayer contentVideoPlayer;
    
    void fadeInBG();
    void fadeOutBG();
    
    Vec2i getContentSize();
    void fadeInContent();
    void fadeOutContent();
    
    params::InterfaceGl debug;
    float currentFrameRate;
    
};

void qtDTestApp::setup()
{
    currentFrameRate = 0.0f;
    setFrameRate( 60.0f );
    
    gl::enableAlphaBlending();
    
    
    debug = params::InterfaceGl("App debug", Vec2i(200, 400) );
    debug.addParam( "FPS: ", &currentFrameRate );
    
    debug.addSeparator();
    debug.addText("BG Video");
    debug.addButton("fade in BG", std::bind( &qtDTestApp::fadeInBG, this) );
    debug.addButton("fade out BG", std::bind( &qtDTestApp::fadeOutBG, this) );
    
    debug.addSeparator();
    debug.addText("Content Video");
    debug.addButton("fade in content", std::bind( &qtDTestApp::fadeInContent, this) );
    debug.addButton("fade out content", std::bind( &qtDTestApp::fadeOutContent, this) );
    
    bgVideoPlayer.setSize( Vec2i(getWindowWidth(), getWindowHeight() ) );
    contentVideoPlayer.setSize( getContentSize() );
}

void qtDTestApp::mouseDown( MouseEvent event )
{
}

void qtDTestApp::keyDown( KeyEvent event)
{
    switch ( event.getCode() ) 
    {
        case KeyEvent::KEY_f:
            setFullScreen( !isFullScreen() );
            break;
            
        case KeyEvent::KEY_1:
            bgVideoPlayer.playNewMovie();
            break;
            
        case KeyEvent::KEY_2:
            contentVideoPlayer.playNewMovie();
            break;
            
        default:
            break;
    }
}

void qtDTestApp::fadeInBG()
{
    bgVideoPlayer.fadeToVal( 1.0f );    
}

void qtDTestApp::fadeOutBG()
{
    bgVideoPlayer.fadeToVal( 0.0f );
}

Vec2i qtDTestApp::getContentSize()
{
    
    int windowHeigt = getWindowHeight();
    if(windowHeigt < 1)
        return Vec2i::zero();
    
    int windowthird = getWindowHeight() / 3;
    return Vec2i( getWindowWidth(), windowthird * 2);
}

void qtDTestApp::fadeInContent()
{
    contentVideoPlayer.fadeToVal( 1.0f );
}

void qtDTestApp::fadeOutContent()
{
    contentVideoPlayer.fadeToVal( 0.0f );
}


void qtDTestApp::resize( ResizeEvent event )
{
    bgVideoPlayer.setSize( event.getSize() );
    contentVideoPlayer.setSize( getContentSize() );
}

void qtDTestApp::update()
{
    currentFrameRate = getAverageFps();
    
    bgVideoPlayer.update();
    contentVideoPlayer.update();
}

void qtDTestApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    bgVideoPlayer.draw();
    contentVideoPlayer.draw();
    
    params::InterfaceGl::draw();
}


CINDER_APP_BASIC( qtDTestApp, RendererGl )
