#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class OceanWavesApp : public App {
  public:
	  void	setup() override;
	  void	draw() override;
	  void	update() override;
	  OceanWavesApp();

	  CameraPersp         mCam;
	  gl::BatchRef        mRect;
	  gl::GlslProgRef	  mGlsl;
	  float               time;
};

OceanWavesApp::OceanWavesApp() : time(0.0) {

}

void OceanWavesApp::setup()
{
	mCam.lookAt(vec3(3, 1, 20), vec3(0));

	mGlsl = gl::GlslProg::create(gl::GlslProg::Format()
		.vertex( loadAsset("render.vert") )
		.fragment( loadAsset("render.frag") ));

	auto plane = geom::Plane().subdivisions(ivec2(300)).size(ivec2(300, 300));
	mRect = gl::Batch::create(plane, mGlsl);

	gl::enableDepthWrite();
	gl::enableDepthRead();
}

void OceanWavesApp::update()
{
	time += 0.1;
}

void OceanWavesApp::draw()
{ 
	gl::clear(Color(0.2f, 0.2f, 0.3f));
	gl::setMatrices(mCam);

	mGlsl->uniform("uCheckSize", 30.0f);
	mGlsl->uniform("timepassed", time);
	mRect->draw();
}

CINDER_APP( OceanWavesApp, RendererGl )
