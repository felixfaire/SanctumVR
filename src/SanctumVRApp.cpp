#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/ObjLoader.h"
#include "cinder/CameraUI.h"

#include "SanctumCathedral.h"

#if CINDER_MSW
    #include "CinderOculus.h"
#endif

using namespace ci;
using namespace ci::app;
using namespace std;

class SanctumVRApp : public App {
  public:
    SanctumVRApp();
    
	void update() override;
	void draw() override;
  private:
    void drawScene();
    
    CameraPersp         mCam;
    CameraUi            mCamUi;
    SanctumCathedral    mSanctum;
    
#if CINDER_MSW
    OculusRiftRef		mRift;
#endif
    
    vec3                mViewerPosition;
};

SanctumVRApp::SanctumVRApp()
    : mViewerPosition( 0, 0, 1 )
{
    mCamUi = CameraUi( &mCam );
    mCamUi.connect( getWindow() );
    mCam.setPerspective( 45.0f, getWindowAspectRatio(), 0.1, 10000 );
    mCam.setEyePoint( vec3( 5.0f, 0.0f, -25.0f ) );
    mCam.lookAt( vec3( 0.0f, 8.0f, 0.0f ) );
    
    mSanctum.setupModel();

    gl::enableDepthWrite();
    gl::enableDepthRead();
    gl::enableAlphaBlending();
    
  #if CINDER_MSW
    try {
        mRift = OculusRift::create();
    }
    catch( const RiftExeption& exc ) {
        CI_LOG_EXCEPTION( "Failed rift initialization.", exc );
    }
  #endif
}


#if CINDER_MSW

void BasicSampleApp::update()
{
    // Move head location
    if( mRift ) {
        auto host = mRift->getHostCamera();
        host.setEyePoint( mViewerPosition + vec3( 0.5f * sin( app::getElapsedSeconds() ), 0, 0 ) );
        host.lookAt( vec3( 0 ) );
        mRift->setHostCamera( host );
    }
    
    // Draw from update due to conflicting WM_PAINT signal emitted by ovr_submitFrame (0.7 SDK).
    gl::clear( Color( 1.0f, 1.0f, 1.0f ) );
    
    if( mRift && ! mRift->isFrameSkipped() ) {
        ScopedRiftBuffer bind{ mRift };
        
        for( auto eye : mRift->getEyes() ) {
            mRift->enableEye( eye );
            
            drawScene();
            
            // Draw positional tracking camera frustum
            CameraPersp positional;
            if( mRift->getPositionalTrackingCamera( &positional ) ) {
                gl::setModelMatrix( mat4() );
                gl::lineWidth( 1.0f );
                gl::drawFrustum( positional );
            }
        }
    }
}

void BasicSampleApp::drawScene()
{
    mSanctum.draw();
}

void BasicSampleApp::draw()
{
    if( ! mRift ) {
        gl::viewport( getWindowSize() );
        gl::setMatrices( mCam );
        
        drawScene();
    }
}



#else // is OSX

void SanctumVRApp::update(){}
void SanctumVRApp::drawScene(){}

void SanctumVRApp::draw()
{
	gl::clear( Color( 1.0f, 1.0f, 1.0f ) );
    
    gl::setMatrices( mCam );
    
    mSanctum.draw();
}
#endif

CINDER_APP( SanctumVRApp, RendererGl )
