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

	  CameraPersp         mCam;
	  gl::BatchRef        mRect;
	  gl::GlslProgRef		mGlsl;
};

void OceanWavesApp::setup()
{
	mCam.lookAt(vec3(3, 2, 3), vec3(0));

	mGlsl = gl::GlslProg::create(gl::GlslProg::Format()
		.vertex( loadAsset("render.vert") )
		.fragment( loadAsset("render.frag") ));

	auto plane = geom::Plane().subdivisions(ivec2(30));
	mRect = gl::Batch::create(plane, mGlsl);

	gl::enableDepthWrite();
	gl::enableDepthRead();
}

void OceanWavesApp::draw()
{ 
	gl::clear(Color(0.2f, 0.2f, 0.3f));
	gl::setMatrices(mCam);

	mGlsl->uniform("uCheckSize", 30.0f);
	mRect->draw();
}

CINDER_APP( OceanWavesApp, RendererGl )
