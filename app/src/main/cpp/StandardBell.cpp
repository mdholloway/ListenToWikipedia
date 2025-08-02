/* ------------------------------------------------------------
name: "standardBell"
Code generated with Faust 2.81.2 (https://faust.grame.fr)
Compilation options: -a minimal.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN minimal.cpp ****************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

#include <iostream>

#include "faust/gui/PrintUI.h"
#include "faust/gui/MapUI.h"
#ifdef LAYOUT_UI
#include "faust/gui/LayoutUI.h"
#endif
#include "faust/gui/meta.h"
#include "faust/audio/dummy-audio.h"
#ifdef FIXED_POINT
#include "faust/dsp/fixed-point.h"
#endif

// faust -a minimal.cpp noise.dsp -o noise.cpp && c++ -std=c++11 noise.cpp -o noise && ./noise

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

const static float fmydspSIG0Wave0[350] = {0.691911f,0.622333f,0.548651f,0.463306f,0.826946f,0.749513f,0.2242f,0.642678f,0.760442f,0.326054f,0.276463f,0.359344f,0.18258f,0.686765f,0.457159f,0.839015f,0.845338f,0.372377f,0.306417f,0.147381f,0.359707f,0.653537f,0.27553f,0.401233f,0.435417f,0.251481f,0.190062f,0.773372f,0.315014f,0.228812f,0.521512f,0.411542f,0.720762f,1.0f,0.286502f,0.338938f,0.119995f,0.432289f,0.409677f,0.156272f,0.298871f,0.250786f,0.640776f,0.209431f,0.17001f,0.390014f,0.301698f,0.799413f,0.980581f,0.385f,0.82544f,0.818894f,0.349616f,0.235396f,0.783164f,0.821914f,0.28411f,0.430286f,0.507671f,0.326254f,0.260488f,0.273364f,0.20518f,0.714852f,0.47995f,0.803637f,0.683943f,0.355371f,0.406924f,0.656257f,0.423025f,0.413515f,0.38636f,0.384787f,0.389448f,0.813367f,0.234988f,1.0f,0.311268f,0.350245f,0.403856f,0.646143f,0.500485f,0.833553f,0.431768f,0.467064f,0.298979f,0.487413f,0.514907f,0.369383f,0.106197f,0.494224f,0.816079f,0.535807f,0.379873f,0.380201f,0.606306f,0.516117f,0.748449f,0.556948f,0.587066f,0.584423f,0.394866f,0.341121f,0.433458f,0.455987f,0.361237f,0.42939f,0.122969f,0.133175f,0.505176f,0.513985f,0.0554619f,0.604942f,0.372074f,0.381126f,0.314354f,0.499636f,0.518711f,0.923792f,0.259544f,0.576517f,0.553915f,0.585444f,0.245369f,1.0f,0.117757f,0.977318f,0.652862f,0.509314f,0.14855f,0.506402f,0.180059f,0.356005f,0.38681f,0.279354f,0.205792f,0.551055f,0.689107f,0.445724f,0.306857f,0.324747f,0.603621f,0.394466f,0.288613f,0.264697f,0.60612f,0.20274f,0.267271f,0.925656f,0.439228f,0.425884f,0.626633f,0.547204f,0.230022f,0.225654f,0.392697f,0.493474f,0.149857f,0.0604048f,0.693889f,0.740271f,0.175485f,0.704998f,0.329732f,0.153026f,0.125744f,0.286995f,0.278878f,0.812372f,0.0562174f,0.241479f,0.294525f,0.358834f,0.171047f,0.847604f,0.17228f,0.97521f,0.892073f,0.613987f,0.0659213f,0.301583f,0.0610847f,0.125438f,0.145151f,0.180086f,0.124231f,0.260161f,0.337573f,0.203743f,0.655798f,0.425893f,0.902347f,0.500686f,0.311173f,0.215561f,0.349591f,0.0854218f,0.0805062f,1.0f,0.338652f,0.295396f,0.698314f,0.664972f,0.118983f,0.0881905f,0.31158f,0.391136f,0.151915f,0.239504f,0.685742f,0.884332f,0.288516f,0.768688f,0.274851f,0.0490311f,0.0357865f,0.293303f,0.249461f,0.493771f,0.340984f,0.467623f,0.216631f,0.255235f,0.0988695f,0.46198f,0.147247f,0.640196f,1.0f,0.551938f,0.0453732f,0.189907f,0.0197542f,0.0309217f,0.769837f,0.360418f,0.384041f,0.867434f,0.398948f,0.171848f,0.748652f,0.301957f,0.860611f,0.958674f,0.54903f,0.272753f,0.372753f,0.0180728f,0.0292353f,0.8502f,0.224583f,0.214805f,0.670319f,0.586433f,0.0435142f,0.0388574f,0.144811f,0.157061f,0.155569f,0.418334f,0.673656f,0.749573f,0.337354f,0.747254f,0.255997f,0.0239656f,0.0310719f,0.721087f,0.700616f,0.199051f,0.511844f,0.849485f,0.700682f,0.778658f,0.171289f,0.261973f,0.129228f,0.328597f,0.781821f,0.583813f,0.0806713f,0.416876f,0.0118202f,0.00868563f,1.0f,0.461884f,0.186882f,0.641364f,0.994705f,0.501902f,0.566449f,0.0678845f,0.139737f,0.462582f,0.318656f,0.233947f,0.495941f,0.0314028f,0.0146478f,0.70432f,0.124953f,0.132549f,0.457126f,0.378636f,0.0169362f,0.0195494f,0.204155f,0.294401f,0.271367f,0.730857f,0.459322f,0.433078f,0.325171f,0.734536f,0.416205f,0.012873f,0.0388489f,0.821567f,0.863683f,0.0920531f,0.393972f,0.539544f,0.832052f,0.842732f,0.241144f,0.479558f,0.283092f,0.477845f,0.385473f,0.436587f,0.144308f,0.642395f,0.0215791f,0.00779029f,0.563714f,0.838279f,0.410004f,0.829086f,1.0f,0.630598f,0.0233729f,0.496217f,0.711042f,0.914266f,0.695042f,0.331894f,0.898442f,0.028568f,0.0174966f,0.482846f};
class mydspSIG0 {
	
  private:
	
	int fmydspSIG0Wave0_idx;
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		fmydspSIG0Wave0_idx = 0;
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			table[i1] = fmydspSIG0Wave0[fmydspSIG0Wave0_idx];
			fmydspSIG0Wave0_idx = (1 + fmydspSIG0Wave0_idx) % 350;
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float mydsp_faustpower2_f(float value) {
	return value * value;
}
static float ftbl0mydspSIG0[350];

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int iRec3[2];
	FAUSTFLOAT fButton0;
	float fVec0[2];
	int iRec4[2];
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider1;
	float fRec5[2];
	float fVec1[2];
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec6[2];
	float fRec2[2];
	float fRec1[3];
	FAUSTFLOAT fEntry0;
	float fRec7[2];
	float fConst2;
	float fConst3;
	float fConst4;
	float fRec0[3];
	float fConst5;
	float fConst6;
	float fConst7;
	float fRec8[3];
	float fConst8;
	float fConst9;
	float fConst10;
	float fRec9[3];
	float fConst11;
	float fConst12;
	float fConst13;
	float fRec10[3];
	float fConst14;
	float fConst15;
	float fConst16;
	float fRec11[3];
	float fConst17;
	float fConst18;
	float fConst19;
	float fRec12[3];
	float fConst20;
	float fConst21;
	float fConst22;
	float fRec13[3];
	float fConst23;
	float fConst24;
	float fConst25;
	float fRec14[3];
	float fConst26;
	float fConst27;
	float fConst28;
	float fRec15[3];
	float fConst29;
	float fConst30;
	float fConst31;
	float fRec16[3];
	float fConst32;
	float fConst33;
	float fConst34;
	float fRec17[3];
	float fConst35;
	float fConst36;
	float fConst37;
	float fRec18[3];
	float fConst38;
	float fConst39;
	float fConst40;
	float fRec19[3];
	float fConst41;
	float fConst42;
	float fConst43;
	float fRec20[3];
	float fConst44;
	float fConst45;
	float fConst46;
	float fRec21[3];
	float fConst47;
	float fConst48;
	float fConst49;
	float fRec22[3];
	float fConst50;
	float fConst51;
	float fConst52;
	float fRec23[3];
	float fConst53;
	float fConst54;
	float fConst55;
	float fRec24[3];
	float fConst56;
	float fConst57;
	float fConst58;
	float fRec25[3];
	float fConst59;
	float fConst60;
	float fConst61;
	float fRec26[3];
	float fConst62;
	float fConst63;
	float fConst64;
	float fRec27[3];
	float fConst65;
	float fConst66;
	float fConst67;
	float fRec28[3];
	float fConst68;
	float fConst69;
	float fConst70;
	float fRec29[3];
	float fConst71;
	float fConst72;
	float fConst73;
	float fRec30[3];
	float fConst74;
	float fConst75;
	float fConst76;
	float fRec31[3];
	float fConst77;
	float fConst78;
	float fConst79;
	float fRec32[3];
	float fConst80;
	float fConst81;
	float fConst82;
	float fRec33[3];
	float fConst83;
	float fConst84;
	float fConst85;
	float fRec34[3];
	float fConst86;
	float fConst87;
	float fConst88;
	float fRec35[3];
	float fConst89;
	float fConst90;
	float fConst91;
	float fRec36[3];
	float fConst92;
	float fConst93;
	float fConst94;
	float fRec37[3];
	float fConst95;
	float fConst96;
	float fConst97;
	float fRec38[3];
	float fConst98;
	float fConst99;
	float fConst100;
	float fRec39[3];
	float fConst101;
	float fConst102;
	float fConst103;
	float fRec40[3];
	float fConst104;
	float fConst105;
	float fConst106;
	float fRec41[3];
	float fConst107;
	float fConst108;
	float fConst109;
	float fRec42[3];
	float fConst110;
	float fConst111;
	float fConst112;
	float fRec43[3];
	float fConst113;
	float fConst114;
	float fConst115;
	float fRec44[3];
	float fConst116;
	float fConst117;
	float fConst118;
	float fRec45[3];
	float fConst119;
	float fConst120;
	float fConst121;
	float fRec46[3];
	float fConst122;
	float fConst123;
	float fConst124;
	float fRec47[3];
	float fConst125;
	float fConst126;
	float fConst127;
	float fRec48[3];
	float fConst128;
	float fConst129;
	float fConst130;
	float fRec49[3];
	float fConst131;
	float fConst132;
	float fConst133;
	float fRec50[3];
	float fConst134;
	float fConst135;
	float fConst136;
	float fRec51[3];
	float fConst137;
	float fConst138;
	float fConst139;
	float fRec52[3];
	float fConst140;
	float fConst141;
	float fConst142;
	float fRec53[3];
	float fConst143;
	float fConst144;
	float fConst145;
	float fRec54[3];
	float fConst146;
	float fConst147;
	float fConst148;
	float fRec55[3];
	float fConst149;
	float fConst150;
	float fConst151;
	float fRec56[3];
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/sAndH:author", "Romain Michon");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-a minimal.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("envelopes.lib/ar:author", "Yann Orlarey, Stéphane Letz");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "1.3.0");
		m->declare("filename", "standardBell.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "standardBell");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "1.5.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(350, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 3.1415927f / fConst0;
		fConst2 = std::pow(0.001f, 664.3798f / fConst0);
		fConst3 = 2.0f * std::cos(26313.854f / fConst0) * fConst2;
		fConst4 = mydsp_faustpower2_f(fConst2);
		fConst5 = std::pow(0.001f, 330.5264f / fConst0);
		fConst6 = 2.0f * std::cos(26168.398f / fConst0) * fConst5;
		fConst7 = mydsp_faustpower2_f(fConst5);
		fConst8 = std::pow(0.001f, 133.76732f / fConst0);
		fConst9 = 2.0f * std::cos(25908.148f / fConst0) * fConst8;
		fConst10 = mydsp_faustpower2_f(fConst8);
		fConst11 = std::pow(0.001f, 26.321707f / fConst0);
		fConst12 = 2.0f * std::cos(25122.877f / fConst0) * fConst11;
		fConst13 = mydsp_faustpower2_f(fConst11);
		fConst14 = std::pow(0.001f, 25.141743f / fConst0);
		fConst15 = 2.0f * std::cos(25092.467f / fConst0) * fConst14;
		fConst16 = mydsp_faustpower2_f(fConst14);
		fConst17 = std::pow(0.001f, 6.0577345f / fConst0);
		fConst18 = 2.0f * std::cos(23809.377f / fConst0) * fConst17;
		fConst19 = mydsp_faustpower2_f(fConst17);
		fConst20 = std::pow(0.001f, 5.959083f / fConst0);
		fConst21 = 2.0f * std::cos(23789.898f / fConst0) * fConst20;
		fConst22 = mydsp_faustpower2_f(fConst20);
		fConst23 = std::pow(0.001f, 4.346859f / fConst0);
		fConst24 = 2.0f * std::cos(23389.723f / fConst0) * fConst23;
		fConst25 = mydsp_faustpower2_f(fConst23);
		fConst26 = std::pow(0.001f, 4.275874f / fConst0);
		fConst27 = 2.0f * std::cos(23367.418f / fConst0) * fConst26;
		fConst28 = mydsp_faustpower2_f(fConst26);
		fConst29 = std::pow(0.001f, 3.5721786f / fConst0);
		fConst30 = 2.0f * std::cos(23114.018f / fConst0) * fConst29;
		fConst31 = mydsp_faustpower2_f(fConst29);
		fConst32 = std::pow(0.001f, 2.1705594f / fConst0);
		fConst33 = 2.0f * std::cos(22308.826f / fConst0) * fConst32;
		fConst34 = mydsp_faustpower2_f(fConst32);
		fConst35 = std::pow(0.001f, 2.0903757f / fConst0);
		fConst36 = 2.0f * std::cos(22241.219f / fConst0) * fConst35;
		fConst37 = mydsp_faustpower2_f(fConst35);
		fConst38 = std::pow(0.001f, 1.7896768f / fConst0);
		fConst39 = 2.0f * std::cos(21951.25f / fConst0) * fConst38;
		fConst40 = mydsp_faustpower2_f(fConst38);
		fConst41 = std::pow(0.001f, 1.7453221f / fConst0);
		fConst42 = 2.0f * std::cos(21902.682f / fConst0) * fConst41;
		fConst43 = mydsp_faustpower2_f(fConst41);
		fConst44 = std::pow(0.001f, 1.312705f / fConst0);
		fConst45 = 2.0f * std::cos(21315.832f / fConst0) * fConst44;
		fConst46 = mydsp_faustpower2_f(fConst44);
		fConst47 = std::pow(0.001f, 0.8115767f / fConst0);
		fConst48 = 2.0f * std::cos(20160.04f / fConst0) * fConst47;
		fConst49 = mydsp_faustpower2_f(fConst47);
		fConst50 = std::pow(0.001f, 0.5620478f / fConst0);
		fConst51 = 2.0f * std::cos(19114.393f / fConst0) * fConst50;
		fConst52 = mydsp_faustpower2_f(fConst50);
		fConst53 = std::pow(0.001f, 0.5510875f / fConst0);
		fConst54 = 2.0f * std::cos(19053.885f / fConst0) * fConst53;
		fConst55 = mydsp_faustpower2_f(fConst53);
		fConst56 = std::pow(0.001f, 0.44730455f / fConst0);
		fConst57 = 2.0f * std::cos(18382.652f / fConst0) * fConst56;
		fConst58 = mydsp_faustpower2_f(fConst56);
		fConst59 = std::pow(0.001f, 0.44505778f / fConst0);
		fConst60 = 2.0f * std::cos(18365.75f / fConst0) * fConst59;
		fConst61 = mydsp_faustpower2_f(fConst59);
		fConst62 = std::pow(0.001f, 0.4068938f / fConst0);
		fConst63 = 2.0f * std::cos(18059.068f / fConst0) * fConst62;
		fConst64 = mydsp_faustpower2_f(fConst62);
		fConst65 = std::pow(0.001f, 0.3990936f / fConst0);
		fConst66 = 2.0f * std::cos(17991.398f / fConst0) * fConst65;
		fConst67 = mydsp_faustpower2_f(fConst65);
		fConst68 = std::pow(0.001f, 0.3743582f / fConst0);
		fConst69 = 2.0f * std::cos(17763.947f / fConst0) * fConst68;
		fConst70 = mydsp_faustpower2_f(fConst68);
		fConst71 = std::pow(0.001f, 0.3717643f / fConst0);
		fConst72 = 2.0f * std::cos(17738.877f / fConst0) * fConst71;
		fConst73 = mydsp_faustpower2_f(fConst71);
		fConst74 = std::pow(0.001f, 0.30876094f / fConst0);
		fConst75 = 2.0f * std::cos(17042.889f / fConst0) * fConst74;
		fConst76 = mydsp_faustpower2_f(fConst74);
		fConst77 = std::pow(0.001f, 0.30831742f / fConst0);
		fConst78 = 2.0f * std::cos(17037.297f / fConst0) * fConst77;
		fConst79 = mydsp_faustpower2_f(fConst77);
		fConst80 = std::pow(0.001f, 0.27051228f / fConst0);
		fConst81 = 2.0f * std::cos(16514.725f / fConst0) * fConst80;
		fConst82 = mydsp_faustpower2_f(fConst80);
		fConst83 = std::pow(0.001f, 0.2684097f / fConst0);
		fConst84 = 2.0f * std::cos(16482.68f / fConst0) * fConst83;
		fConst85 = mydsp_faustpower2_f(fConst83);
		fConst86 = std::pow(0.001f, 0.23585056f / fConst0);
		fConst87 = 2.0f * std::cos(15936.797f / fConst0) * fConst86;
		fConst88 = mydsp_faustpower2_f(fConst86);
		fConst89 = std::pow(0.001f, 0.23506209f / fConst0);
		fConst90 = 2.0f * std::cos(15922.283f / fConst0) * fConst89;
		fConst91 = mydsp_faustpower2_f(fConst89);
		fConst92 = std::pow(0.001f, 0.19710599f / fConst0);
		fConst93 = 2.0f * std::cos(15130.916f / fConst0) * fConst92;
		fConst94 = mydsp_faustpower2_f(fConst92);
		fConst95 = std::pow(0.001f, 0.14246607f / fConst0);
		fConst96 = 2.0f * std::cos(13517.645f / fConst0) * fConst95;
		fConst97 = mydsp_faustpower2_f(fConst95);
		fConst98 = std::pow(0.001f, 0.14095205f / fConst0);
		fConst99 = 2.0f * std::cos(13460.907f / fConst0) * fConst98;
		fConst100 = mydsp_faustpower2_f(fConst98);
		fConst101 = std::pow(0.001f, 0.12723906f / fConst0);
		fConst102 = 2.0f * std::cos(12904.908f / fConst0) * fConst101;
		fConst103 = mydsp_faustpower2_f(fConst101);
		fConst104 = std::pow(0.001f, 0.12323294f / fConst0);
		fConst105 = 2.0f * std::cos(12726.403f / fConst0) * fConst104;
		fConst106 = mydsp_faustpower2_f(fConst104);
		fConst107 = std::pow(0.001f, 0.12052324f / fConst0);
		fConst108 = 2.0f * std::cos(12600.991f / fConst0) * fConst107;
		fConst109 = mydsp_faustpower2_f(fConst107);
		fConst110 = std::pow(0.001f, 0.09171629f / fConst0);
		fConst111 = 2.0f * std::cos(10965.7295f / fConst0) * fConst110;
		fConst112 = mydsp_faustpower2_f(fConst110);
		fConst113 = std::pow(0.001f, 0.09169806f / fConst0);
		fConst114 = 2.0f * std::cos(10964.473f / fConst0) * fConst113;
		fConst115 = mydsp_faustpower2_f(fConst113);
		fConst116 = std::pow(0.001f, 0.08883076f / fConst0);
		fConst117 = 2.0f * std::cos(10762.405f / fConst0) * fConst116;
		fConst118 = mydsp_faustpower2_f(fConst116);
		fConst119 = std::pow(0.001f, 0.088295914f / fConst0);
		fConst120 = 2.0f * std::cos(10723.701f / fConst0) * fConst119;
		fConst121 = mydsp_faustpower2_f(fConst119);
		fConst122 = std::pow(0.001f, 0.08246291f / fConst0);
		fConst123 = 2.0f * std::cos(10279.103f / fConst0) * fConst122;
		fConst124 = mydsp_faustpower2_f(fConst122);
		fConst125 = std::pow(0.001f, 0.07680722f / fConst0);
		fConst126 = 2.0f * std::cos(9803.843f / fConst0) * fConst125;
		fConst127 = mydsp_faustpower2_f(fConst125);
		fConst128 = std::pow(0.001f, 0.06364364f / fConst0);
		fConst129 = 2.0f * std::cos(8479.158f / fConst0) * fConst128;
		fConst130 = mydsp_faustpower2_f(fConst128);
		fConst131 = std::pow(0.001f, 0.06360758f / fConst0);
		fConst132 = 2.0f * std::cos(8475.012f / fConst0) * fConst131;
		fConst133 = mydsp_faustpower2_f(fConst131);
		fConst134 = std::pow(0.001f, 0.055557575f / fConst0);
		fConst135 = 2.0f * std::cos(7457.764f / fConst0) * fConst134;
		fConst136 = mydsp_faustpower2_f(fConst134);
		fConst137 = std::pow(0.001f, 0.055299424f / fConst0);
		fConst138 = 2.0f * std::cos(7421.761f / fConst0) * fConst137;
		fConst139 = mydsp_faustpower2_f(fConst137);
		fConst140 = std::pow(0.001f, 0.0453766f / fConst0);
		fConst141 = 2.0f * std::cos(5829.407f / fConst0) * fConst140;
		fConst142 = mydsp_faustpower2_f(fConst140);
		fConst143 = std::pow(0.001f, 0.045276627f / fConst0);
		fConst144 = 2.0f * std::cos(5810.9287f / fConst0) * fConst143;
		fConst145 = mydsp_faustpower2_f(fConst143);
		fConst146 = std::pow(0.001f, 0.03333335f / fConst0);
		fConst147 = 2.0f * std::cos(3080.3315f / fConst0) * fConst146;
		fConst148 = mydsp_faustpower2_f(fConst146);
		fConst149 = std::pow(0.001f, 0.03340854f / fConst0);
		fConst150 = 2.0f * std::cos(3101.6692f / fConst0) * fConst149;
		fConst151 = mydsp_faustpower2_f(fConst149);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.9f);
		fHslider2 = FAUSTFLOAT(0.3f);
		fEntry0 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iRec3[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fVec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iRec4[l2] = 0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec5[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec2[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 3; l7 = l7 + 1) {
			fRec1[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec7[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec0[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec8[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec9[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec10[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 3; l13 = l13 + 1) {
			fRec11[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec12[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec13[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 3; l16 = l16 + 1) {
			fRec14[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 3; l17 = l17 + 1) {
			fRec15[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 3; l18 = l18 + 1) {
			fRec16[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 3; l19 = l19 + 1) {
			fRec17[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 3; l20 = l20 + 1) {
			fRec18[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 3; l21 = l21 + 1) {
			fRec19[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 3; l22 = l22 + 1) {
			fRec20[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 3; l23 = l23 + 1) {
			fRec21[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 3; l24 = l24 + 1) {
			fRec22[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 3; l25 = l25 + 1) {
			fRec23[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 3; l26 = l26 + 1) {
			fRec24[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 3; l27 = l27 + 1) {
			fRec25[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 3; l28 = l28 + 1) {
			fRec26[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 3; l29 = l29 + 1) {
			fRec27[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 3; l30 = l30 + 1) {
			fRec28[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 3; l31 = l31 + 1) {
			fRec29[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 3; l32 = l32 + 1) {
			fRec30[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 3; l33 = l33 + 1) {
			fRec31[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 3; l34 = l34 + 1) {
			fRec32[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 3; l35 = l35 + 1) {
			fRec33[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec34[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 3; l37 = l37 + 1) {
			fRec35[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 3; l38 = l38 + 1) {
			fRec36[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 3; l39 = l39 + 1) {
			fRec37[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 3; l40 = l40 + 1) {
			fRec38[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 3; l41 = l41 + 1) {
			fRec39[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 3; l42 = l42 + 1) {
			fRec40[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 3; l43 = l43 + 1) {
			fRec41[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 3; l44 = l44 + 1) {
			fRec42[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 3; l45 = l45 + 1) {
			fRec43[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 3; l46 = l46 + 1) {
			fRec44[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 3; l47 = l47 + 1) {
			fRec45[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec46[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 3; l49 = l49 + 1) {
			fRec47[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec48[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec49[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec50[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 3; l53 = l53 + 1) {
			fRec51[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 3; l54 = l54 + 1) {
			fRec52[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 3; l55 = l55 + 1) {
			fRec53[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 3; l56 = l56 + 1) {
			fRec54[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 3; l57 = l57 + 1) {
			fRec55[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 3; l58 = l58 + 1) {
			fRec56[l58] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("standardBell");
		ui_interface->addNumEntry("exPos", &fEntry0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("gain", &fHslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addButton("gate", &fButton0);
		ui_interface->addHorizontalSlider("hammerHardness", &fHslider1, FAUSTFLOAT(0.9f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("hammerSize", &fHslider2, FAUSTFLOAT(0.3f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 0.02f * float(fHslider0);
		float fSlow1 = float(fButton0);
		int iSlow2 = int(fSlow1);
		float fSlow3 = float(fHslider1);
		float fSlow4 = float(fHslider2);
		float fSlow5 = float(fEntry0);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iRec3[0] = 1103515245 * iRec3[1] + 12345;
			fVec0[0] = fSlow1;
			iRec4[0] = (iRec4[1] + (iRec4[1] > 0)) * (fSlow1 <= fVec0[1]) + (fSlow1 > fVec0[1]);
			fRec5[0] = ((iSlow2) ? fSlow3 : fRec5[1]);
			float fTemp0 = float(iRec4[0]) / std::max<float>(1.0f, fConst0 * (0.01f * (1.0f - fRec5[0]) + 0.001f));
			float fTemp1 = float(iRec3[0]) * std::max<float>(0.0f, std::min<float>(fTemp0, 2.0f - fTemp0));
			fVec1[0] = fTemp1;
			fRec6[0] = ((iSlow2) ? fSlow4 : fRec6[1]);
			float fTemp2 = std::tan(fConst1 * (9.5e+03f * (1.0f - fRec6[0]) + 5e+02f));
			float fTemp3 = 1.0f / fTemp2;
			fRec2[0] = (4.656613e-10f * (fTemp1 + fVec1[1]) - fRec2[1] * (1.0f - fTemp3)) / (fTemp3 + 1.0f);
			float fTemp4 = (fTemp3 + 1.0f) / fTemp2 + 1.0f;
			fRec1[0] = fRec2[0] - (fRec1[2] * ((fTemp3 + -1.0f) / fTemp2 + 1.0f) + 2.0f * fRec1[1] * (1.0f - 1.0f / mydsp_faustpower2_f(fTemp2))) / fTemp4;
			float fTemp5 = fRec1[2] + fRec1[0] + 2.0f * fRec1[1];
			fRec7[0] = ((iSlow2) ? fSlow5 : fRec7[1]);
			int iTemp6 = 50 * int(fRec7[0]);
			fRec0[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 49, 349))] / fTemp4 + fConst3 * fRec0[1] - fConst4 * fRec0[2];
			fRec8[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 48, 349))] / fTemp4 + fConst6 * fRec8[1] - fConst7 * fRec8[2];
			fRec9[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 47, 349))] / fTemp4 + fConst9 * fRec9[1] - fConst10 * fRec9[2];
			fRec10[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 46, 349))] / fTemp4 + fConst12 * fRec10[1] - fConst13 * fRec10[2];
			fRec11[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 45, 349))] / fTemp4 + fConst15 * fRec11[1] - fConst16 * fRec11[2];
			fRec12[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 44, 349))] / fTemp4 + fConst18 * fRec12[1] - fConst19 * fRec12[2];
			fRec13[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 43, 349))] / fTemp4 + fConst21 * fRec13[1] - fConst22 * fRec13[2];
			fRec14[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 42, 349))] / fTemp4 + fConst24 * fRec14[1] - fConst25 * fRec14[2];
			fRec15[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 41, 349))] / fTemp4 + fConst27 * fRec15[1] - fConst28 * fRec15[2];
			fRec16[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 40, 349))] / fTemp4 + fConst30 * fRec16[1] - fConst31 * fRec16[2];
			fRec17[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 39, 349))] / fTemp4 + fConst33 * fRec17[1] - fConst34 * fRec17[2];
			fRec18[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 38, 349))] / fTemp4 + fConst36 * fRec18[1] - fConst37 * fRec18[2];
			fRec19[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 37, 349))] / fTemp4 + fConst39 * fRec19[1] - fConst40 * fRec19[2];
			fRec20[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 36, 349))] / fTemp4 + fConst42 * fRec20[1] - fConst43 * fRec20[2];
			fRec21[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 35, 349))] / fTemp4 + fConst45 * fRec21[1] - fConst46 * fRec21[2];
			fRec22[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 34, 349))] / fTemp4 + fConst48 * fRec22[1] - fConst49 * fRec22[2];
			fRec23[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 33, 349))] / fTemp4 + fConst51 * fRec23[1] - fConst52 * fRec23[2];
			fRec24[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 32, 349))] / fTemp4 + fConst54 * fRec24[1] - fConst55 * fRec24[2];
			fRec25[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 31, 349))] / fTemp4 + fConst57 * fRec25[1] - fConst58 * fRec25[2];
			fRec26[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 30, 349))] / fTemp4 + fConst60 * fRec26[1] - fConst61 * fRec26[2];
			fRec27[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 29, 349))] / fTemp4 + fConst63 * fRec27[1] - fConst64 * fRec27[2];
			fRec28[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 28, 349))] / fTemp4 + fConst66 * fRec28[1] - fConst67 * fRec28[2];
			fRec29[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 27, 349))] / fTemp4 + fConst69 * fRec29[1] - fConst70 * fRec29[2];
			fRec30[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 26, 349))] / fTemp4 + fConst72 * fRec30[1] - fConst73 * fRec30[2];
			fRec31[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 25, 349))] / fTemp4 + fConst75 * fRec31[1] - fConst76 * fRec31[2];
			fRec32[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 24, 349))] / fTemp4 + fConst78 * fRec32[1] - fConst79 * fRec32[2];
			fRec33[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 23, 349))] / fTemp4 + fConst81 * fRec33[1] - fConst82 * fRec33[2];
			fRec34[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 22, 349))] / fTemp4 + fConst84 * fRec34[1] - fConst85 * fRec34[2];
			fRec35[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 21, 349))] / fTemp4 + fConst87 * fRec35[1] - fConst88 * fRec35[2];
			fRec36[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 20, 349))] / fTemp4 + fConst90 * fRec36[1] - fConst91 * fRec36[2];
			fRec37[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 19, 349))] / fTemp4 + fConst93 * fRec37[1] - fConst94 * fRec37[2];
			fRec38[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 18, 349))] / fTemp4 + fConst96 * fRec38[1] - fConst97 * fRec38[2];
			fRec39[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 17, 349))] / fTemp4 + fConst99 * fRec39[1] - fConst100 * fRec39[2];
			fRec40[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 16, 349))] / fTemp4 + fConst102 * fRec40[1] - fConst103 * fRec40[2];
			fRec41[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 15, 349))] / fTemp4 + fConst105 * fRec41[1] - fConst106 * fRec41[2];
			fRec42[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 14, 349))] / fTemp4 + fConst108 * fRec42[1] - fConst109 * fRec42[2];
			fRec43[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 13, 349))] / fTemp4 + fConst111 * fRec43[1] - fConst112 * fRec43[2];
			fRec44[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 12, 349))] / fTemp4 + fConst114 * fRec44[1] - fConst115 * fRec44[2];
			fRec45[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 11, 349))] / fTemp4 + fConst117 * fRec45[1] - fConst118 * fRec45[2];
			fRec46[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 10, 349))] / fTemp4 + fConst120 * fRec46[1] - fConst121 * fRec46[2];
			fRec47[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 9, 349))] / fTemp4 + fConst123 * fRec47[1] - fConst124 * fRec47[2];
			fRec48[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 8, 349))] / fTemp4 + fConst126 * fRec48[1] - fConst127 * fRec48[2];
			fRec49[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 7, 349))] / fTemp4 + fConst129 * fRec49[1] - fConst130 * fRec49[2];
			fRec50[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 6, 349))] / fTemp4 + fConst132 * fRec50[1] - fConst133 * fRec50[2];
			fRec51[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 5, 349))] / fTemp4 + fConst135 * fRec51[1] - fConst136 * fRec51[2];
			fRec52[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 4, 349))] / fTemp4 + fConst138 * fRec52[1] - fConst139 * fRec52[2];
			fRec53[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 3, 349))] / fTemp4 + fConst141 * fRec53[1] - fConst142 * fRec53[2];
			fRec54[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 2, 349))] / fTemp4 + fConst144 * fRec54[1] - fConst145 * fRec54[2];
			fRec55[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6, 349))] / fTemp4 + fConst147 * fRec55[1] - fConst148 * fRec55[2];
			fRec56[0] = fTemp5 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(iTemp6 + 1, 349))] / fTemp4 + fConst150 * fRec56[1] - fConst151 * fRec56[2];
			float fTemp7 = fSlow0 * (fRec0[0] + fRec8[0] + fRec9[0] + fRec10[0] + fRec11[0] + fRec12[0] + fRec13[0] + fRec14[0] + fRec15[0] + fRec16[0] + fRec17[0] + fRec18[0] + fRec19[0] + fRec20[0] + fRec21[0] + fRec22[0] + fRec23[0] + fRec24[0] + fRec25[0] + fRec26[0] + fRec27[0] + fRec28[0] + fRec29[0] + fRec30[0] + fRec31[0] + fRec32[0] + fRec33[0] + fRec34[0] + fRec35[0] + fRec36[0] + fRec37[0] + fRec38[0] + fRec39[0] + fRec40[0] + fRec41[0] + fRec42[0] + fRec43[0] + fRec44[0] + fRec45[0] + fRec46[0] + fRec47[0] + fRec48[0] + fRec49[0] + fRec50[0] + fRec51[0] + fRec52[0] + fRec53[0] + fRec54[0] + fRec55[0] + fRec56[0] - (fRec55[2] + fRec56[2] + fRec54[2] + fRec53[2] + fRec52[2] + fRec51[2] + fRec50[2] + fRec49[2] + fRec48[2] + fRec47[2] + fRec46[2] + fRec45[2] + fRec44[2] + fRec43[2] + fRec42[2] + fRec41[2] + fRec40[2] + fRec39[2] + fRec38[2] + fRec37[2] + fRec36[2] + fRec35[2] + fRec34[2] + fRec33[2] + fRec32[2] + fRec31[2] + fRec30[2] + fRec29[2] + fRec28[2] + fRec27[2] + fRec26[2] + fRec25[2] + fRec24[2] + fRec23[2] + fRec22[2] + fRec21[2] + fRec20[2] + fRec19[2] + fRec18[2] + fRec17[2] + fRec16[2] + fRec15[2] + fRec14[2] + fRec13[2] + fRec12[2] + fRec11[2] + fRec10[2] + fRec9[2] + fRec8[2] + fRec0[2]));
			output0[i0] = FAUSTFLOAT(fTemp7);
			output1[i0] = FAUSTFLOAT(fTemp7);
			iRec3[1] = iRec3[0];
			fVec0[1] = fVec0[0];
			iRec4[1] = iRec4[0];
			fRec5[1] = fRec5[0];
			fVec1[1] = fVec1[0];
			fRec6[1] = fRec6[0];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec7[1] = fRec7[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
		}
	}

};

/***************************END USER SECTION ***************************/

/******************* END minimal.cpp ****************/


#endif
