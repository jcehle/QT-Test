#include "cinder/app/AppBasic.h"
#include "cinder/qtime/QuickTime.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/Timeline.h"
#include "VideoPlayer.h"
#include <iostream>

using namespace ci;
using namespace ci::app;
using namespace std;

VideoPlayer::VideoPlayer()
{
    size = Vec2i::zero();
    position = Vec2i::zero();
    isPlaying = false;
    drawDebug = false;
    debugColor = ColorA( 0.0f, Rand::randFloat(), 0.0f, 0.1f);
    movieAlpha = 1.0f;
}

VideoPlayer::~VideoPlayer()
{
    
}

void VideoPlayer::setSize( Vec2i size )
{
    this->size = size;
}

void VideoPlayer::setPosition( Vec2i position )
{
    this->position = position;
}

void VideoPlayer::playNewMovie()
{
    fs::path moviePath = getOpenFilePath();
    if( !moviePath.empty() )
    {
        
        if( exists( currentMoviePath ) )
        {
            cout << "fade current movie out first..." << endl;
            queuedMoviePath = moviePath;
            return;
        }
        
        cout << "run some sort of validation on the file here.." << endl;
        currentMoviePath = moviePath;
        playMovie();
    }
}

void VideoPlayer::playMovie()
{
    movie = qtime::MovieGl( currentMoviePath );
    movie.setLoop( true, false );
    movie.play();
}

void VideoPlayer::resume()
{
    isPlaying = true;
}

void VideoPlayer::pause()
{
    isPlaying = false;
}

void VideoPlayer::fadeToVal( float newAlpha )
{
    timeline().apply( &movieAlpha, newAlpha, 2.0f, EaseOutSine() );
}


void VideoPlayer::update()
{
    if( movie )
		movieTexture = movie.getTexture();
}

void VideoPlayer::draw()
{
    if( movieTexture )
    {
        gl::color( ColorA( 1.0f, 1.0f, 1.0f, movieAlpha) );
        gl::draw( movieTexture, Rectf( position, position + size ));
    }
    
    if(drawDebug)
    {
        gl::color( debugColor );
        gl::drawSolidRect( Rectf(position, position + size ) );
    }
}



