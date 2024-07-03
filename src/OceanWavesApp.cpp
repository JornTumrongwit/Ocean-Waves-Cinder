#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/CinderImGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class OceanWavesApp : public App {
  public:
	  void	setup() override;
	  void	draw() override;
	  void	update() override;
	  void updateParams();
	  OceanWavesApp();

	  CameraPersp         mCam;
	  gl::BatchRef        mRect;
	  gl::GlslProgRef	  mGlsl;
	  float               time;
};

OceanWavesApp::OceanWavesApp() : time(0.0) {
	ImGui::Initialize();
}

void OceanWavesApp::setup()
{
	mCam.lookAt(vec3(0, 10, -30), vec3(0));

	mGlsl = gl::GlslProg::create(gl::GlslProg::Format()
		.vertex( loadAsset("render.vert") )
		.fragment( loadAsset("render.frag") ));

	auto plane = geom::Plane().subdivisions(ivec2(1000)).size(ivec2(1000, 1000));
	mRect = gl::Batch::create(plane, mGlsl);

	gl::enableDepthWrite();
	gl::enableDepthRead();
}

void OceanWavesApp::update()
{
	time += 0.1;
	updateParams();
}

void OceanWavesApp::draw()
{ 
	gl::clear(Color(0.2f, 0.2f, 0.3f));
	gl::setMatrices(mCam);

	mGlsl->uniform("uCheckSize", 30.0f);
	mGlsl->uniform("timepassed", time);
	
	mRect->draw();
}

void OceanWavesApp::updateParams()
{
	static float seed = 12.0f;
	static float amplitude = 1.5f;
	static float amp_mult = 1.0f;
	static float offset = 124.5f; 
	static float zoff = 450.0f;
	static float frequency = 1.6f;
	static float freq_mult = 1.0f;
	static int wave_count = 4;

	ImGui::Begin("Ocean Shader");
	if (ImGui::InputFloat("seed", (float*) &seed, 12.0)) {
		mGlsl->uniform("seed", seed);
	}
	if (ImGui::DragFloat("near-far offset", &zoff, 0.1f, -500.0f, 500.0f)) {
		mGlsl->uniform("zoff", zoff);
	}
	if (ImGui::DragFloat("up-down offset", &offset, 1.0f)) {
		mGlsl->uniform("offset", offset);
	}
	if (ImGui::DragFloat("amplitude", &amplitude, 0.1f)) {
		mGlsl->uniform("amplitude", amplitude);
	}
	if (ImGui::DragFloat("amp_mult", &amp_mult, 0.1f)) {
		mGlsl->uniform("amp_mult", amp_mult);
	}
	if (ImGui::DragFloat("frequency", &frequency, 0.1f)) {
		mGlsl->uniform("frequency", frequency);
	}
	if (ImGui::DragFloat("freq_mult", &freq_mult, 0.1f)) {
		mGlsl->uniform("freq_mult", freq_mult);
	}
	if (ImGui::Button("Reset")) {
		seed = 12.0f;
		mGlsl->uniform("seed", seed);
		amplitude = 1.5f;
		mGlsl->uniform("amplitude", amplitude);
		amp_mult = 1.0f;
		mGlsl->uniform("amp_mult", amp_mult);
		offset = 124.5f;
		mGlsl->uniform("offset", offset);
		zoff = 450.0f;
		mGlsl->uniform("zoff", zoff);
		frequency = 1.6f;
		mGlsl->uniform("frequency", frequency);
		freq_mult = 1.0f;
		mGlsl->uniform("freq_mult", freq_mult);
	}
	ImGui::End();
}

CINDER_APP( OceanWavesApp, RendererGl )
