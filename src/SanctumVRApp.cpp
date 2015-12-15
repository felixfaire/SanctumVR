#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SanctumVRApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void SanctumVRApp::setup()
{
}

void SanctumVRApp::mouseDown( MouseEvent event )
{
}

void SanctumVRApp::update()
{
}

void SanctumVRApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( SanctumVRApp, RendererGl )
