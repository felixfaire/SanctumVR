#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/ObjLoader.h"
#include "cinder/CameraUI.h"

#include "SanctumCathedral.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SanctumVRApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    CameraPersp         mCam;
    CameraUi            mCamUi;
    SanctumCathedral    mSanctum;
    
    gl::BatchRef        mSphere;
};

void SanctumVRApp::setup()
{
    mCamUi = CameraUi( &mCam );
    mCamUi.connect( getWindow() );
    mCam.setPerspective( 45.0f, getWindowAspectRatio(), 0.1, 10000 );
    mCam.setEyePoint( vec3( 5.0f, 0.0f, -25.0f ) );
    mCam.lookAt( vec3( 0.0f, 8.0f, 0.0f ) );
    
    mSanctum.setupModel();
    
    mSphere = gl::Batch::create( geom::Sphere().radius( 1.0f ).center( vec3( 0.0f ) ), gl::getStockShader( gl::ShaderDef().color() ) );
    
    gl::enableDepthWrite();
    gl::enableDepthRead();
    gl::enableAlphaBlending();
}

void SanctumVRApp::mouseDown( MouseEvent event )
{
}

void SanctumVRApp::update()
{
}

void SanctumVRApp::draw()
{
	gl::clear( Color( 1.0f, 1.0f, 1.0f ) );
    
    gl::setMatrices( mCam );
    
    mSanctum.draw();

//    gl::color( 0.0f, 0.0f, 0.0f );
//    mSphere->draw();
}

CINDER_APP( SanctumVRApp, RendererGl )
