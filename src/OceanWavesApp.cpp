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
	mCam.lookAt(vec3(0, 5, -30), vec3(0));

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
	static float seed = 0.532f;
	static float seed_mult = 0.2432f;
	static float amplitude = 1.5f;
	static float amp_mult = 1.0f;
	static float offset = 41.0f; 
	static float zoff = 450.0f;
	static float frequency = 0.05f;
	static float freq_mult = 1.0f;
	static float speed = 1.5f;
	static float speed_mult = 0.6f;
	static int wave_count = 4;
	static float peak = 0.8f;
	static float peak_offset = 0.2f;

	ImGui::Begin("Ocean Shader");
	if (ImGui::InputFloat("seed", (float*) &seed, 0.01f)) {
		mGlsl->uniform("seed", seed);
	}
	if (ImGui::InputFloat("seed_mult", (float*)&seed_mult, 0.01f)) {
		mGlsl->uniform("seed_mult", seed_mult);
	}
	if (ImGui::DragFloat("near-far offset", &zoff, 0.1f)) {
		mGlsl->uniform("zoff", zoff);
	}
	if (ImGui::DragFloat("up-down offset", &offset, 1.0f)) {
		mGlsl->uniform("offset", offset);
	}
	if (ImGui::DragFloat("amplitude", &amplitude, 0.001f)) {
		mGlsl->uniform("amplitude", amplitude);
	}
	if (ImGui::DragFloat("amp_mult", &amp_mult, 0.001f)) {
		mGlsl->uniform("amp_mult", amp_mult);
	}
	if (ImGui::DragFloat("frequency", &frequency, 0.001f)) {
		mGlsl->uniform("frequency", frequency);
	}
	if (ImGui::DragFloat("freq_mult", &freq_mult, 0.001f)) {
		mGlsl->uniform("freq_mult", freq_mult);
	}
	if (ImGui::DragFloat("speed", &speed, 0.001f)) {
		mGlsl->uniform("speed", speed);
	}
	if (ImGui::DragFloat("speed_mult", &speed_mult, 0.001f)) {
		mGlsl->uniform("speed_mult", speed_mult);
	}
	if (ImGui::DragFloat("peak", &peak, 0.001f)) {
		mGlsl->uniform("peak", peak);
	}
	if (ImGui::DragFloat("peak_offset", &peak_offset, 0.001f)) {
		mGlsl->uniform("peak_offset", peak_offset);
	}
	if (ImGui::InputInt("wave_count", &wave_count, 1)) {
		mGlsl->uniform("wave_count", wave_count);
	}
	if (ImGui::Button("Reset")) {
		seed = 123.2f;
		mGlsl->uniform("seed", seed);
		speed_mult = 12.2f;
		mGlsl->uniform("seed_mult", seed_mult);
		amplitude = 3.08f;
		mGlsl->uniform("amplitude", amplitude);
		amp_mult = 0.22f;
		mGlsl->uniform("amp_mult", amp_mult);
		offset = 30.0f;
		mGlsl->uniform("offset", offset);
		zoff = 466.5f;
		mGlsl->uniform("zoff", zoff);
		frequency = 0.06f;
		mGlsl->uniform("frequency", frequency);
		freq_mult = 3.06f;
		mGlsl->uniform("freq_mult", freq_mult);
		speed = 0.6f;
		mGlsl->uniform("speed", speed);
		speed_mult = 1.94f;
		mGlsl->uniform("speed_mult", speed_mult);
		peak = 1.7f;
		mGlsl->uniform("peak", peak);
		peak_offset = 0.2f;
		mGlsl->uniform("peak_offset", peak_offset);
		wave_count = 32;
		mGlsl->uniform("wave_count", wave_count);
	}
	ImGui::End();
}

CINDER_APP( OceanWavesApp, RendererGl )
