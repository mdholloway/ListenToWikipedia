/* ------------------------------------------------------------
name: "marimba"
Code generated with Faust 2.70.3 (https://faust.grame.fr)
Compilation options: -a minimal.cpp -lang cpp -ct 1 -cn Marimba -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __Marimba_H__
#define  __Marimba_H__

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
#include "faust/gui/meta.h"
#include "faust/audio/dummy-audio.h"
#include "faust/dsp/one-sample-dsp.h"

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
#define FAUSTCLASS Marimba
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

const static float fMarimbaSIG0Wave0[250] = {1.0f,0.776725f,0.625723f,0.855223f,0.760159f,0.698373f,0.768011f,0.641127f,0.244034f,0.707754f,0.634013f,0.247527f,0.660849f,0.450396f,0.567783f,0.106361f,0.716814f,0.66392f,0.291208f,0.310599f,0.801495f,0.635292f,0.307435f,0.874124f,0.497668f,0.487088f,0.459115f,0.733455f,0.541818f,0.441318f,0.31392f,0.40309f,0.685353f,0.60314f,0.400552f,0.453511f,0.634386f,0.291547f,0.131605f,0.368507f,0.839907f,0.60216f,0.288296f,0.57967f,0.0242493f,0.262746f,0.368588f,0.890284f,0.408963f,0.556072f,0.884427f,0.83211f,0.612015f,0.757176f,0.919477f,1.0f,0.827963f,0.89241f,0.0357408f,0.480789f,0.752872f,0.0546301f,0.235937f,0.362938f,0.444472f,0.101751f,0.703418f,0.453136f,0.316629f,0.490394f,0.982508f,0.551622f,0.602009f,0.666957f,0.77683f,0.905662f,0.0987197f,0.402968f,0.829452f,0.307645f,0.64048f,0.983971f,0.584205f,0.650365f,0.334447f,0.58357f,0.540191f,0.672534f,0.245712f,0.687298f,0.883058f,0.79295f,0.600619f,0.572682f,0.122612f,0.388248f,0.290658f,0.380255f,0.290967f,0.567819f,0.0737721f,0.42099f,0.0786578f,0.393995f,0.268983f,0.260614f,0.494086f,0.238026f,0.0987824f,0.277879f,0.440563f,0.0770212f,0.450591f,0.128137f,0.0368275f,0.128699f,0.329605f,0.374512f,0.36359f,0.272594f,0.379052f,0.305241f,0.0741129f,0.345728f,0.29935f,0.221284f,0.0261391f,0.293202f,0.361885f,0.11433f,0.239005f,0.434156f,0.329583f,0.21946f,0.284175f,0.198555f,0.431976f,0.302985f,1.0f,0.146221f,0.140701f,0.264243f,0.185997f,0.426322f,0.30478f,0.34399f,0.19543f,0.386955f,0.1876f,0.172812f,0.0434115f,0.303761f,0.069454f,0.453943f,0.832451f,0.317817f,0.940601f,1.0f,0.180658f,0.737921f,0.832297f,0.402352f,0.126786f,0.594398f,0.485455f,0.32447f,0.365102f,0.777922f,0.588272f,0.401353f,0.610735f,0.158693f,0.0746072f,0.825099f,0.925459f,0.65377f,0.260792f,0.719384f,0.559908f,0.37259f,0.360035f,0.622939f,0.210271f,0.444595f,0.311286f,0.464309f,0.557231f,0.52408f,0.0701056f,0.320749f,0.19446f,0.727609f,0.522062f,0.394004f,0.235035f,0.395646f,0.494796f,0.517318f,0.109752f,0.692849f,0.00632009f,0.0207583f,0.00306107f,0.0637191f,0.081661f,0.03511f,0.127814f,0.202294f,0.0764145f,0.263127f,0.400199f,0.267278f,0.633385f,1.0f,0.739902f,0.413763f,0.41811f,0.612715f,0.672374f,0.339674f,0.21172f,0.459645f,0.1025f,0.32589f,0.148154f,0.265442f,0.0974305f,0.286438f,0.275213f,0.109111f,0.575089f,0.370283f,0.29411f,0.259826f,0.0648719f,0.583418f,0.282663f,0.182004f,0.117421f,0.417727f,0.16965f,0.24853f,0.122819f,0.185486f,0.0433618f,0.373849f,0.252768f,0.195103f,0.0927835f,0.166543f};
class MarimbaSIG0 {
	
  private:
	
	int fMarimbaSIG0Wave0_idx;
	
  public:
	
	int getNumInputsMarimbaSIG0() {
		return 0;
	}
	int getNumOutputsMarimbaSIG0() {
		return 1;
	}
	
	void instanceInitMarimbaSIG0(int sample_rate) {
		fMarimbaSIG0Wave0_idx = 0;
	}
	
	void fillMarimbaSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			table[i1] = fMarimbaSIG0Wave0[fMarimbaSIG0Wave0_idx];
			fMarimbaSIG0Wave0_idx = (1 + fMarimbaSIG0Wave0_idx) % 250;
		}
	}

};

static MarimbaSIG0* newMarimbaSIG0() { return (MarimbaSIG0*)new MarimbaSIG0(); }
static void deleteMarimbaSIG0(MarimbaSIG0* dsp) { delete dsp; }

static float ftbl0MarimbaSIG0[250];
static float Marimba_faustpower2_f(float value) {
	return value * value;
}

class Marimba : public dsp {
	
 private:
	
	int iRec0[2];
	float fRec4[2];
	int IOTA0;
	float fVec0[2048];
	int fSampleRate;
	float fConst1;
	float fConst2;
	float fRec2[2];
	float fConst3;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fVec1[2];
	int iRec6[2];
	float fConst12;
	float fConst14;
	float fConst16;
	int iRec9[2];
	float fRec8[3];
	float fConst17;
	float fRec7[3];
	float fRec5[3];
	float fConst19;
	float fConst20;
	float fConst21;
	float fRec10[3];
	float fConst23;
	float fConst24;
	float fConst25;
	float fRec11[3];
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec12[3];
	float fConst31;
	float fConst32;
	float fConst33;
	float fRec13[3];
	float fConst35;
	float fConst36;
	float fConst37;
	float fRec14[3];
	float fConst39;
	float fConst40;
	float fConst41;
	float fRec15[3];
	float fConst43;
	float fConst44;
	float fConst45;
	float fRec16[3];
	float fConst47;
	float fConst48;
	float fConst49;
	float fRec17[3];
	float fConst51;
	float fConst52;
	float fConst53;
	float fRec18[3];
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec19[3];
	float fConst59;
	float fConst60;
	float fConst61;
	float fRec20[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec21[3];
	float fConst67;
	float fConst68;
	float fConst69;
	float fRec22[3];
	float fConst71;
	float fConst72;
	float fConst73;
	float fRec23[3];
	float fConst75;
	float fConst76;
	float fConst77;
	float fRec24[3];
	float fConst79;
	float fConst80;
	float fConst81;
	float fRec25[3];
	float fConst83;
	float fConst84;
	float fConst85;
	float fRec26[3];
	float fConst87;
	float fConst88;
	float fConst89;
	float fRec27[3];
	float fConst91;
	float fConst92;
	float fConst93;
	float fRec28[3];
	float fConst95;
	float fConst96;
	float fConst97;
	float fRec29[3];
	float fConst99;
	float fConst100;
	float fConst101;
	float fRec30[3];
	float fConst103;
	float fConst104;
	float fConst105;
	float fRec31[3];
	float fConst107;
	float fConst108;
	float fConst109;
	float fRec32[3];
	float fConst111;
	float fConst112;
	float fConst113;
	float fRec33[3];
	float fConst115;
	float fConst116;
	float fConst117;
	float fRec34[3];
	float fConst119;
	float fConst120;
	float fConst121;
	float fRec35[3];
	float fConst123;
	float fConst124;
	float fConst125;
	float fRec36[3];
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec37[3];
	float fConst131;
	float fConst132;
	float fConst133;
	float fRec38[3];
	float fConst135;
	float fConst136;
	float fConst137;
	float fRec39[3];
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec40[3];
	float fConst143;
	float fConst144;
	float fConst145;
	float fRec41[3];
	float fConst147;
	float fConst148;
	float fConst149;
	float fRec42[3];
	float fConst151;
	float fConst152;
	float fConst153;
	float fRec43[3];
	float fConst155;
	float fConst156;
	float fConst157;
	float fRec44[3];
	float fConst159;
	float fConst160;
	float fConst161;
	float fRec45[3];
	float fConst163;
	float fConst164;
	float fConst165;
	float fRec46[3];
	float fConst167;
	float fConst168;
	float fConst169;
	float fRec47[3];
	float fConst171;
	float fConst172;
	float fConst173;
	float fRec48[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fRec49[3];
	float fConst179;
	float fConst180;
	float fConst181;
	float fRec50[3];
	float fConst183;
	float fConst184;
	float fConst185;
	float fRec51[3];
	float fConst187;
	float fConst188;
	float fConst189;
	float fRec52[3];
	float fConst191;
	float fConst192;
	float fConst193;
	float fRec53[3];
	float fConst195;
	float fConst196;
	float fConst197;
	float fRec54[3];
	float fConst199;
	float fConst200;
	float fConst201;
	float fRec55[3];
	float fConst203;
	float fConst204;
	float fConst205;
	float fRec56[3];
	float fConst207;
	float fConst208;
	float fConst209;
	float fRec57[3];
	float fConst211;
	float fConst212;
	float fConst213;
	float fRec58[3];
	float fVec2[2];
	float fRec59[2];
	float fVec3[2048];
	float fRec3[2];
	
 public:
	Marimba() {}

	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/tabulateNd", "Copyright (C) 2023 Bart Brouns <bart@magnetophon.nl>");
		m->declare("basics.lib/version", "1.12.0");
		m->declare("compile_options", "-a minimal.cpp -lang cpp -ct 1 -cn Marimba -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("delays.lib/fdelay4:author", "Julius O. Smith III");
		m->declare("delays.lib/fdelayltv:author", "Julius O. Smith III");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.1.0");
		m->declare("envelopes.lib/ar:author", "Yann Orlarey, Stéphane Letz");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "1.3.0");
		m->declare("filename", "marimba.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.3.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.7.0");
		m->declare("name", "marimba");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "1.4.0");
		m->declare("physmodels.lib/name", "Faust Physical Models Library");
		m->declare("physmodels.lib/version", "1.1.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.5.0");
	}

	virtual int getNumInputs() {
		return 6;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
		MarimbaSIG0* sig0 = newMarimbaSIG0();
		sig0->instanceInitMarimbaSIG0(sample_rate);
		sig0->fillMarimbaSIG0(250, ftbl0MarimbaSIG0);
		deleteMarimbaSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 0.00882353f * fConst0;
		fConst2 = 0.0014705883f * fConst0;
		fConst3 = 0.5f * fConst0 + -1.0f;
		float fConst4 = std::pow(0.001f, 1.5657384e+14f / fConst0);
		fConst5 = Marimba_faustpower2_f(fConst4);
		fConst6 = 1228.3942f / fConst0;
		fConst7 = 2.0f * fConst4;
		fConst8 = 3.1415927f / fConst0;
		fConst9 = 0.002f * fConst0;
		float fConst10 = std::tan(31.415926f / fConst0);
		float fConst11 = Marimba_faustpower2_f(fConst10);
		fConst12 = 2.0f * (1.0f - 1.0f / fConst11);
		float fConst13 = 1.0f / fConst10;
		fConst14 = (fConst13 + -1.4142135f) / fConst10 + 1.0f;
		float fConst15 = (fConst13 + 1.4142135f) / fConst10 + 1.0f;
		fConst16 = 1.0f / fConst15;
		fConst17 = 1.0f / (fConst11 * fConst15);
		float fConst18 = std::pow(0.001f, 3.8190633e+09f / fConst0);
		fConst19 = Marimba_faustpower2_f(fConst18);
		fConst20 = 1207.5654f / fConst0;
		fConst21 = 2.0f * fConst18;
		float fConst22 = std::pow(0.001f, 5.3122326e+08f / fConst0);
		fConst23 = Marimba_faustpower2_f(fConst22);
		fConst24 = 1196.1237f / fConst0;
		fConst25 = 2.0f * fConst22;
		float fConst26 = std::pow(0.001f, 2.203328e+07f / fConst0);
		fConst27 = Marimba_faustpower2_f(fConst26);
		fConst28 = 1164.89f / fConst0;
		fConst29 = 2.0f * fConst26;
		float fConst30 = std::pow(0.001f, 4549764.5f / fConst0);
		fConst31 = Marimba_faustpower2_f(fConst30);
		fConst32 = 1140.285f / fConst0;
		fConst33 = 2.0f * fConst30;
		float fConst34 = std::pow(0.001f, 2024133.5f / fConst0);
		fConst35 = Marimba_faustpower2_f(fConst34);
		fConst36 = 1124.2943f / fConst0;
		fConst37 = 2.0f * fConst34;
		float fConst38 = std::pow(0.001f, 630229.4f / fConst0);
		fConst39 = Marimba_faustpower2_f(fConst38);
		fConst40 = 1096.1897f / fConst0;
		fConst41 = 2.0f * fConst38;
		float fConst42 = std::pow(0.001f, 355973.34f / fConst0);
		fConst43 = Marimba_faustpower2_f(fConst42);
		fConst44 = 1079.847f / fConst0;
		fConst45 = 2.0f * fConst42;
		float fConst46 = std::pow(0.001f, 172447.05f / fConst0);
		fConst47 = Marimba_faustpower2_f(fConst46);
		fConst48 = 1056.2349f / fConst0;
		fConst49 = 2.0f * fConst46;
		float fConst50 = std::pow(0.001f, 37577.844f / fConst0);
		fConst51 = Marimba_faustpower2_f(fConst50);
		fConst52 = 993.8931f / fConst0;
		fConst53 = 2.0f * fConst50;
		float fConst54 = std::pow(0.001f, 26985.693f / fConst0);
		fConst55 = Marimba_faustpower2_f(fConst54);
		fConst56 = 977.6448f / fConst0;
		fConst57 = 2.0f * fConst54;
		float fConst58 = std::pow(0.001f, 20142.857f / fConst0);
		fConst59 = Marimba_faustpower2_f(fConst58);
		fConst60 = 962.37036f / fConst0;
		fConst61 = 2.0f * fConst58;
		float fConst62 = std::pow(0.001f, 17675.48f / fConst0);
		fConst63 = Marimba_faustpower2_f(fConst62);
		fConst64 = 955.2515f / fConst0;
		fConst65 = 2.0f * fConst62;
		float fConst66 = std::pow(0.001f, 13265.488f / fConst0);
		fConst67 = Marimba_faustpower2_f(fConst66);
		fConst68 = 938.94666f / fConst0;
		fConst69 = 2.0f * fConst66;
		float fConst70 = std::pow(0.001f, 8048.458f / fConst0);
		fConst71 = Marimba_faustpower2_f(fConst70);
		fConst72 = 908.22815f / fConst0;
		fConst73 = 2.0f * fConst70;
		float fConst74 = std::pow(0.001f, 3034.9124f / fConst0);
		fConst75 = Marimba_faustpower2_f(fConst74);
		fConst76 = 838.6607f / fConst0;
		fConst77 = 2.0f * fConst74;
		float fConst78 = std::pow(0.001f, 2755.6304f / fConst0);
		fConst79 = Marimba_faustpower2_f(fConst78);
		fConst80 = 831.0078f / fConst0;
		fConst81 = 2.0f * fConst78;
		float fConst82 = std::pow(0.001f, 2311.8018f / fConst0);
		fConst83 = Marimba_faustpower2_f(fConst82);
		fConst84 = 816.701f / fConst0;
		fConst85 = 2.0f * fConst82;
		float fConst86 = std::pow(0.001f, 1859.39f / fConst0);
		fConst87 = Marimba_faustpower2_f(fConst86);
		fConst88 = 798.24725f / fConst0;
		fConst89 = 2.0f * fConst86;
		float fConst90 = std::pow(0.001f, 1095.6359f / fConst0);
		fConst91 = Marimba_faustpower2_f(fConst90);
		fConst92 = 749.93585f / fConst0;
		fConst93 = 2.0f * fConst90;
		float fConst94 = std::pow(0.001f, 773.2129f / fConst0);
		fConst95 = Marimba_faustpower2_f(fConst94);
		fConst96 = 715.1899f / fConst0;
		fConst97 = 2.0f * fConst94;
		float fConst98 = std::pow(0.001f, 695.5596f / fConst0);
		fConst99 = Marimba_faustpower2_f(fConst98);
		fConst100 = 704.15027f / fConst0;
		fConst101 = 2.0f * fConst98;
		float fConst102 = std::pow(0.001f, 638.4778f / fConst0);
		fConst103 = Marimba_faustpower2_f(fConst102);
		fConst104 = 695.04596f / fConst0;
		fConst105 = 2.0f * fConst102;
		float fConst106 = std::pow(0.001f, 312.0091f / fConst0);
		fConst107 = Marimba_faustpower2_f(fConst106);
		fConst108 = 612.4893f / fConst0;
		fConst109 = 2.0f * fConst106;
		float fConst110 = std::pow(0.001f, 278.13995f / fConst0);
		fConst111 = Marimba_faustpower2_f(fConst110);
		fConst112 = 598.1052f / fConst0;
		fConst113 = 2.0f * fConst110;
		float fConst114 = std::pow(0.001f, 249.36165f / fConst0);
		fConst115 = Marimba_faustpower2_f(fConst114);
		fConst116 = 584.1232f / fConst0;
		fConst117 = 2.0f * fConst114;
		float fConst118 = std::pow(0.001f, 216.13428f / fConst0);
		fConst119 = Marimba_faustpower2_f(fConst118);
		fConst120 = 565.34845f / fConst0;
		fConst121 = 2.0f * fConst118;
		float fConst122 = std::pow(0.001f, 142.91408f / fConst0);
		fConst123 = Marimba_faustpower2_f(fConst122);
		fConst124 = 507.917f / fConst0;
		fConst125 = 2.0f * fConst122;
		float fConst126 = std::pow(0.001f, 130.3097f / fConst0);
		fConst127 = Marimba_faustpower2_f(fConst126);
		fConst128 = 494.43643f / fConst0;
		fConst129 = 2.0f * fConst126;
		float fConst130 = std::pow(0.001f, 109.456856f / fConst0);
		fConst131 = Marimba_faustpower2_f(fConst130);
		fConst132 = 468.28644f / fConst0;
		fConst133 = 2.0f * fConst130;
		float fConst134 = std::pow(0.001f, 80.89012f / fConst0);
		fConst135 = Marimba_faustpower2_f(fConst134);
		fConst136 = 420.71393f / fConst0;
		fConst137 = 2.0f * fConst134;
		float fConst138 = std::pow(0.001f, 76.06687f / fConst0);
		fConst139 = Marimba_faustpower2_f(fConst138);
		fConst140 = 410.68658f / fConst0;
		fConst141 = 2.0f * fConst138;
		float fConst142 = std::pow(0.001f, 70.99649f / fConst0);
		fConst143 = Marimba_faustpower2_f(fConst142);
		fConst144 = 399.28763f / fConst0;
		fConst145 = 2.0f * fConst142;
		float fConst146 = std::pow(0.001f, 58.4253f / fConst0);
		fConst147 = Marimba_faustpower2_f(fConst146);
		fConst148 = 366.22174f / fConst0;
		fConst149 = 2.0f * fConst146;
		float fConst150 = std::pow(0.001f, 47.439922f / fConst0);
		fConst151 = Marimba_faustpower2_f(fConst150);
		fConst152 = 329.4274f / fConst0;
		fConst153 = 2.0f * fConst150;
		float fConst154 = std::pow(0.001f, 45.175232f / fConst0);
		fConst155 = Marimba_faustpower2_f(fConst154);
		fConst156 = 320.56183f / fConst0;
		fConst157 = 2.0f * fConst154;
		float fConst158 = std::pow(0.001f, 40.26368f / fConst0);
		fConst159 = Marimba_faustpower2_f(fConst158);
		fConst160 = 299.35544f / fConst0;
		fConst161 = 2.0f * fConst158;
		float fConst162 = std::pow(0.001f, 31.381102f / fConst0);
		fConst163 = Marimba_faustpower2_f(fConst162);
		fConst164 = 251.72577f / fConst0;
		fConst165 = 2.0f * fConst162;
		float fConst166 = std::pow(0.001f, 29.263924f / fConst0);
		fConst167 = Marimba_faustpower2_f(fConst166);
		fConst168 = 237.9461f / fConst0;
		fConst169 = 2.0f * fConst166;
		float fConst170 = std::pow(0.001f, 28.536816f / fConst0);
		fConst171 = Marimba_faustpower2_f(fConst170);
		fConst172 = 232.93527f / fConst0;
		fConst173 = 2.0f * fConst170;
		float fConst174 = std::pow(0.001f, 22.269566f / fConst0);
		fConst175 = Marimba_faustpower2_f(fConst174);
		fConst176 = 182.17719f / fConst0;
		fConst177 = 2.0f * fConst174;
		float fConst178 = std::pow(0.001f, 20.48241f / fConst0);
		fConst179 = Marimba_faustpower2_f(fConst178);
		fConst180 = 164.47809f / fConst0;
		fConst181 = 2.0f * fConst178;
		float fConst182 = std::pow(0.001f, 17.630983f / fConst0);
		fConst183 = Marimba_faustpower2_f(fConst182);
		fConst184 = 132.01099f / fConst0;
		fConst185 = 2.0f * fConst182;
		float fConst186 = std::pow(0.001f, 16.365208f / fConst0);
		fConst187 = Marimba_faustpower2_f(fConst186);
		fConst188 = 115.51008f / fConst0;
		fConst189 = 2.0f * fConst186;
		float fConst190 = std::pow(0.001f, 14.533069f / fConst0);
		fConst191 = Marimba_faustpower2_f(fConst190);
		fConst192 = 88.6991f / fConst0;
		fConst193 = 2.0f * fConst190;
		float fConst194 = std::pow(0.001f, 12.802757f / fConst0);
		fConst195 = Marimba_faustpower2_f(fConst194);
		fConst196 = 59.362152f / fConst0;
		fConst197 = 2.0f * fConst194;
		float fConst198 = std::pow(0.001f, 12.337915f / fConst0);
		fConst199 = Marimba_faustpower2_f(fConst198);
		fConst200 = 50.66214f / fConst0;
		fConst201 = 2.0f * fConst198;
		float fConst202 = std::pow(0.001f, 11.038634f / fConst0);
		fConst203 = Marimba_faustpower2_f(fConst202);
		fConst204 = 24.094069f / fConst0;
		fConst205 = 2.0f * fConst202;
		float fConst206 = std::pow(0.001f, 10.890133f / fConst0);
		fConst207 = Marimba_faustpower2_f(fConst206);
		fConst208 = 20.819712f / fConst0;
		fConst209 = 2.0f * fConst206;
		float fConst210 = std::pow(0.001f, 10.259114f / fConst0);
		fConst211 = Marimba_faustpower2_f(fConst210);
		fConst212 = 6.2831855f / fConst0;
		fConst213 = 2.0f * fConst210;
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iRec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec4[l1] = 0.0f;
		}
		IOTA0 = 0;
		for (int l2 = 0; l2 < 2048; l2 = l2 + 1) {
			fVec0[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			iRec6[l5] = 0;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			iRec9[l6] = 0;
		}
		for (int l7 = 0; l7 < 3; l7 = l7 + 1) {
			fRec8[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec7[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec5[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec10[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec11[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec12[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 3; l13 = l13 + 1) {
			fRec13[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec14[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec15[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 3; l16 = l16 + 1) {
			fRec16[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 3; l17 = l17 + 1) {
			fRec17[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 3; l18 = l18 + 1) {
			fRec18[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 3; l19 = l19 + 1) {
			fRec19[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 3; l20 = l20 + 1) {
			fRec20[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 3; l21 = l21 + 1) {
			fRec21[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 3; l22 = l22 + 1) {
			fRec22[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 3; l23 = l23 + 1) {
			fRec23[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 3; l24 = l24 + 1) {
			fRec24[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 3; l25 = l25 + 1) {
			fRec25[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 3; l26 = l26 + 1) {
			fRec26[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 3; l27 = l27 + 1) {
			fRec27[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 3; l28 = l28 + 1) {
			fRec28[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 3; l29 = l29 + 1) {
			fRec29[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 3; l30 = l30 + 1) {
			fRec30[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 3; l31 = l31 + 1) {
			fRec31[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 3; l32 = l32 + 1) {
			fRec32[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 3; l33 = l33 + 1) {
			fRec33[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 3; l34 = l34 + 1) {
			fRec34[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 3; l35 = l35 + 1) {
			fRec35[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec36[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 3; l37 = l37 + 1) {
			fRec37[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 3; l38 = l38 + 1) {
			fRec38[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 3; l39 = l39 + 1) {
			fRec39[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 3; l40 = l40 + 1) {
			fRec40[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 3; l41 = l41 + 1) {
			fRec41[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 3; l42 = l42 + 1) {
			fRec42[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 3; l43 = l43 + 1) {
			fRec43[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 3; l44 = l44 + 1) {
			fRec44[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 3; l45 = l45 + 1) {
			fRec45[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 3; l46 = l46 + 1) {
			fRec46[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 3; l47 = l47 + 1) {
			fRec47[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec48[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 3; l49 = l49 + 1) {
			fRec49[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec50[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec51[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec52[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 3; l53 = l53 + 1) {
			fRec53[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 3; l54 = l54 + 1) {
			fRec54[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 3; l55 = l55 + 1) {
			fRec55[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 3; l56 = l56 + 1) {
			fRec56[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 3; l57 = l57 + 1) {
			fRec57[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 3; l58 = l58 + 1) {
			fRec58[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fVec2[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 2; l60 = l60 + 1) {
			fRec59[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2048; l61 = l61 + 1) {
			fVec3[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fRec3[l62] = 0.0f;
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
	
	virtual Marimba* clone() {
		return new Marimba();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("marimba");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* input4 = inputs[4];
		FAUSTFLOAT* input5 = inputs[5];
		FAUSTFLOAT* output0 = outputs[0];
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iRec0[0] = 0;
			fRec4[0] = 0.05f * fRec3[1] + 0.95f * fRec4[1];
			float fTemp0 = 0.99f * fRec4[0] + float(iRec0[1]);
			fVec0[IOTA0 & 2047] = fTemp0;
			float fTemp1 = float(input0[i0]);
			float fTemp2 = fConst2 * (3.4e+02f / fTemp1 + -0.04f);
			float fTemp3 = fTemp2 + -1.499995f;
			int iTemp4 = int(fTemp3);
			int iTemp5 = int(std::min<float>(fConst1, float(std::max<int>(0, iTemp4 + 4))));
			float fTemp6 = std::floor(fTemp3);
			float fTemp7 = fTemp2 + (-3.0f - fTemp6);
			float fTemp8 = fTemp2 + (-2.0f - fTemp6);
			float fTemp9 = fTemp2 + (-1.0f - fTemp6);
			float fTemp10 = fTemp2 - fTemp6;
			float fTemp11 = fTemp10 * fTemp9;
			float fTemp12 = fTemp11 * fTemp8;
			float fTemp13 = fTemp12 * fTemp7;
			int iTemp14 = int(std::min<float>(fConst1, float(std::max<int>(0, iTemp4 + 3))));
			int iTemp15 = int(std::min<float>(fConst1, float(std::max<int>(0, iTemp4 + 2))));
			int iTemp16 = int(std::min<float>(fConst1, float(std::max<int>(0, iTemp4 + 1))));
			int iTemp17 = int(std::min<float>(fConst1, float(std::max<int>(0, iTemp4))));
			float fTemp18 = fTemp2 + (-4.0f - fTemp6);
			fRec2[0] = fTemp18 * (fTemp7 * (fTemp8 * (0.041666668f * fVec0[(IOTA0 - iTemp17) & 2047] * fTemp9 - 0.16666667f * fTemp10 * fVec0[(IOTA0 - iTemp16) & 2047]) + 0.25f * fTemp11 * fVec0[(IOTA0 - iTemp15) & 2047]) - 0.16666667f * fTemp12 * fVec0[(IOTA0 - iTemp14) & 2047]) + 0.041666668f * fTemp13 * fVec0[(IOTA0 - iTemp5) & 2047];
			int iTemp19 = 50 * int(float(input1[i0]));
			float fTemp20 = std::tan(fConst8 * float(input2[i0]));
			float fTemp21 = 1.0f / fTemp20;
			float fTemp22 = (fTemp21 + 1.4142135f) / fTemp20 + 1.0f;
			float fTemp23 = float(input5[i0]);
			fVec1[0] = fTemp23;
			iRec6[0] = (iRec6[1] + (iRec6[1] > 0)) * (fTemp23 <= fVec1[1]) + (fTemp23 > fVec1[1]);
			float fTemp24 = float(iRec6[0]) / std::max<float>(1.0f, fConst9 * float(input3[i0]));
			iRec9[0] = 1103515245 * iRec9[1] + 12345;
			fRec8[0] = 4.656613e-10f * float(iRec9[0]) - fConst16 * (fConst14 * fRec8[2] + fConst12 * fRec8[1]);
			fRec7[0] = fConst17 * (fRec8[2] + (fRec8[0] - 2.0f * fRec8[1])) - (fRec7[2] * ((fTemp21 + -1.4142135f) / fTemp20 + 1.0f) + 2.0f * fRec7[1] * (1.0f - 1.0f / Marimba_faustpower2_f(fTemp20))) / fTemp22;
			float fTemp25 = float(input4[i0]) * (fRec7[2] + fRec7[0] + 2.0f * fRec7[1]) * std::max<float>(0.0f, std::min<float>(fTemp24, 2.0f - fTemp24)) / fTemp22;
			fRec5[0] = fTemp25 + fConst7 * fRec5[1] * std::cos(fConst6 * fTemp1) - fConst5 * fRec5[2];
			fRec10[0] = fTemp25 + fConst21 * fRec10[1] * std::cos(fConst20 * fTemp1) - fConst19 * fRec10[2];
			fRec11[0] = fTemp25 + fConst25 * fRec11[1] * std::cos(fConst24 * fTemp1) - fConst23 * fRec11[2];
			fRec12[0] = fTemp25 + fConst29 * fRec12[1] * std::cos(fConst28 * fTemp1) - fConst27 * fRec12[2];
			fRec13[0] = fTemp25 + fConst33 * fRec13[1] * std::cos(fConst32 * fTemp1) - fConst31 * fRec13[2];
			fRec14[0] = fTemp25 + fConst37 * fRec14[1] * std::cos(fConst36 * fTemp1) - fConst35 * fRec14[2];
			fRec15[0] = fTemp25 + fConst41 * fRec15[1] * std::cos(fConst40 * fTemp1) - fConst39 * fRec15[2];
			fRec16[0] = fTemp25 + fConst45 * fRec16[1] * std::cos(fConst44 * fTemp1) - fConst43 * fRec16[2];
			fRec17[0] = fTemp25 + fConst49 * fRec17[1] * std::cos(fConst48 * fTemp1) - fConst47 * fRec17[2];
			fRec18[0] = fTemp25 + fConst53 * fRec18[1] * std::cos(fConst52 * fTemp1) - fConst51 * fRec18[2];
			fRec19[0] = fTemp25 + fConst57 * fRec19[1] * std::cos(fConst56 * fTemp1) - fConst55 * fRec19[2];
			fRec20[0] = fTemp25 + fConst61 * fRec20[1] * std::cos(fConst60 * fTemp1) - fConst59 * fRec20[2];
			fRec21[0] = fTemp25 + fConst65 * fRec21[1] * std::cos(fConst64 * fTemp1) - fConst63 * fRec21[2];
			fRec22[0] = fTemp25 + fConst69 * fRec22[1] * std::cos(fConst68 * fTemp1) - fConst67 * fRec22[2];
			fRec23[0] = fTemp25 + fConst73 * fRec23[1] * std::cos(fConst72 * fTemp1) - fConst71 * fRec23[2];
			fRec24[0] = fTemp25 + fConst77 * fRec24[1] * std::cos(fConst76 * fTemp1) - fConst75 * fRec24[2];
			fRec25[0] = fTemp25 + fConst81 * fRec25[1] * std::cos(fConst80 * fTemp1) - fConst79 * fRec25[2];
			fRec26[0] = fTemp25 + fConst85 * fRec26[1] * std::cos(fConst84 * fTemp1) - fConst83 * fRec26[2];
			fRec27[0] = fTemp25 + fConst89 * fRec27[1] * std::cos(fConst88 * fTemp1) - fConst87 * fRec27[2];
			fRec28[0] = fTemp25 + fConst93 * fRec28[1] * std::cos(fConst92 * fTemp1) - fConst91 * fRec28[2];
			fRec29[0] = fTemp25 + fConst97 * fRec29[1] * std::cos(fConst96 * fTemp1) - fConst95 * fRec29[2];
			fRec30[0] = fTemp25 + fConst101 * fRec30[1] * std::cos(fConst100 * fTemp1) - fConst99 * fRec30[2];
			fRec31[0] = fTemp25 + fConst105 * fRec31[1] * std::cos(fConst104 * fTemp1) - fConst103 * fRec31[2];
			fRec32[0] = fTemp25 + fConst109 * fRec32[1] * std::cos(fConst108 * fTemp1) - fConst107 * fRec32[2];
			fRec33[0] = fTemp25 + fConst113 * fRec33[1] * std::cos(fConst112 * fTemp1) - fConst111 * fRec33[2];
			fRec34[0] = fTemp25 + fConst117 * fRec34[1] * std::cos(fConst116 * fTemp1) - fConst115 * fRec34[2];
			fRec35[0] = fTemp25 + fConst121 * fRec35[1] * std::cos(fConst120 * fTemp1) - fConst119 * fRec35[2];
			fRec36[0] = fTemp25 + fConst125 * fRec36[1] * std::cos(fConst124 * fTemp1) - fConst123 * fRec36[2];
			fRec37[0] = fTemp25 + fConst129 * fRec37[1] * std::cos(fConst128 * fTemp1) - fConst127 * fRec37[2];
			fRec38[0] = fTemp25 + fConst133 * fRec38[1] * std::cos(fConst132 * fTemp1) - fConst131 * fRec38[2];
			fRec39[0] = fTemp25 + fConst137 * fRec39[1] * std::cos(fConst136 * fTemp1) - fConst135 * fRec39[2];
			fRec40[0] = fTemp25 + fConst141 * fRec40[1] * std::cos(fConst140 * fTemp1) - fConst139 * fRec40[2];
			fRec41[0] = fTemp25 + fConst145 * fRec41[1] * std::cos(fConst144 * fTemp1) - fConst143 * fRec41[2];
			fRec42[0] = fTemp25 + fConst149 * fRec42[1] * std::cos(fConst148 * fTemp1) - fConst147 * fRec42[2];
			fRec43[0] = fTemp25 + fConst153 * fRec43[1] * std::cos(fConst152 * fTemp1) - fConst151 * fRec43[2];
			fRec44[0] = fTemp25 + fConst157 * fRec44[1] * std::cos(fConst156 * fTemp1) - fConst155 * fRec44[2];
			fRec45[0] = fTemp25 + fConst161 * fRec45[1] * std::cos(fConst160 * fTemp1) - fConst159 * fRec45[2];
			fRec46[0] = fTemp25 + fConst165 * fRec46[1] * std::cos(fConst164 * fTemp1) - fConst163 * fRec46[2];
			fRec47[0] = fTemp25 + fConst169 * fRec47[1] * std::cos(fConst168 * fTemp1) - fConst167 * fRec47[2];
			fRec48[0] = fTemp25 + fConst173 * fRec48[1] * std::cos(fConst172 * fTemp1) - fConst171 * fRec48[2];
			fRec49[0] = fTemp25 + fConst177 * fRec49[1] * std::cos(fConst176 * fTemp1) - fConst175 * fRec49[2];
			fRec50[0] = fTemp25 + fConst181 * fRec50[1] * std::cos(fConst180 * fTemp1) - fConst179 * fRec50[2];
			fRec51[0] = fTemp25 + fConst185 * fRec51[1] * std::cos(fConst184 * fTemp1) - fConst183 * fRec51[2];
			fRec52[0] = fTemp25 + fConst189 * fRec52[1] * std::cos(fConst188 * fTemp1) - fConst187 * fRec52[2];
			fRec53[0] = fTemp25 + fConst193 * fRec53[1] * std::cos(fConst192 * fTemp1) - fConst191 * fRec53[2];
			fRec54[0] = fTemp25 + fConst197 * fRec54[1] * std::cos(fConst196 * fTemp1) - fConst195 * fRec54[2];
			fRec55[0] = fTemp25 + fConst201 * fRec55[1] * std::cos(fConst200 * fTemp1) - fConst199 * fRec55[2];
			fRec56[0] = fTemp25 + fConst205 * fRec56[1] * std::cos(fConst204 * fTemp1) - fConst203 * fRec56[2];
			fRec57[0] = fTemp25 + fConst209 * fRec57[1] * std::cos(fConst208 * fTemp1) - fConst207 * fRec57[2];
			fRec58[0] = fTemp25 + fConst213 * fRec58[1] * std::cos(fConst212 * fTemp1) - fConst211 * fRec58[2];
			fVec2[0] = (fRec58[0] - fRec58[2]) * ((fTemp1 < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19, 249))] : 0.0f) + (fRec57[0] - fRec57[2]) * (((3.31356f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 1, 249))] : 0.0f) + (fRec56[0] - fRec56[2]) * (((3.83469f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 2, 249))] : 0.0f) + (fRec55[0] - fRec55[2]) * (((8.06313f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 3, 249))] : 0.0f) + (fRec54[0] - fRec54[2]) * (((9.44778f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 4, 249))] : 0.0f) + (fRec53[0] - fRec53[2]) * (((14.1169f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 5, 249))] : 0.0f) + (fRec52[0] - fRec52[2]) * (((18.384f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 6, 249))] : 0.0f) + (fRec51[0] - fRec51[2]) * (((21.0102f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 7, 249))] : 0.0f) + (fRec50[0] - fRec50[2]) * (((26.1775f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 8, 249))] : 0.0f) + (fRec49[0] - fRec49[2]) * (((28.9944f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 9, 249))] : 0.0f) + (fRec48[0] - fRec48[2]) * (((37.0728f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 10, 249))] : 0.0f) + (fRec47[0] - fRec47[2]) * (((37.8703f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 11, 249))] : 0.0f) + (fRec46[0] - fRec46[2]) * (((40.0634f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 12, 249))] : 0.0f) + (fRec45[0] - fRec45[2]) * (((47.6439f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 13, 249))] : 0.0f) + (fRec44[0] - fRec44[2]) * (((51.019f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 14, 249))] : 0.0f) + (fRec43[0] - fRec43[2]) * (((52.43f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 15, 249))] : 0.0f) + (fRec42[0] - fRec42[2]) * (((58.286f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 16, 249))] : 0.0f) + (fRec41[0] - fRec41[2]) * (((63.5486f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 17, 249))] : 0.0f) + (fRec40[0] - fRec40[2]) * (((65.3628f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 18, 249))] : 0.0f) + (fRec39[0] - fRec39[2]) * (((66.9587f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 19, 249))] : 0.0f) + (fRec38[0] - fRec38[2]) * (((74.5301f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 20, 249))] : 0.0f) + (fRec37[0] - fRec37[2]) * (((78.692f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 21, 249))] : 0.0f) + (fRec36[0] - fRec36[2]) * (((80.8375f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 22, 249))] : 0.0f) + (fRec35[0] - fRec35[2]) * (((89.978f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 23, 249))] : 0.0f) + (fRec34[0] - fRec34[2]) * (((92.9661f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 24, 249))] : 0.0f) + (fRec33[0] - fRec33[2]) * (((95.1914f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 25, 249))] : 0.0f) + (fRec32[0] - fRec32[2]) * (((97.4807f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 26, 249))] : 0.0f) + (fRec31[0] - fRec31[2]) * (((110.62f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 27, 249))] : 0.0f) + (fRec30[0] - fRec30[2]) * (((112.069f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 28, 249))] : 0.0f) + (fRec29[0] - fRec29[2]) * (((113.826f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 29, 249))] : 0.0f) + (fRec28[0] - fRec28[2]) * (((119.356f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 30, 249))] : 0.0f) + (fRec27[0] - fRec27[2]) * (((127.045f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 31, 249))] : 0.0f) + (fRec26[0] - fRec26[2]) * (((129.982f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 32, 249))] : 0.0f) + (fRec25[0] - fRec25[2]) * (((132.259f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 33, 249))] : 0.0f) + (fRec24[0] - fRec24[2]) * (((133.477f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 34, 249))] : 0.0f) + (fRec23[0] - fRec23[2]) * (((144.549f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 35, 249))] : 0.0f) + (fRec22[0] - fRec22[2]) * (((149.438f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 36, 249))] : 0.0f) + (fRec21[0] - fRec21[2]) * (((152.033f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 37, 249))] : 0.0f) + (fRec20[0] - fRec20[2]) * (((153.166f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 38, 249))] : 0.0f) + (fRec19[0] - fRec19[2]) * (((155.597f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 39, 249))] : 0.0f) + (fRec18[0] - fRec18[2]) * (((158.183f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 40, 249))] : 0.0f) + (fRec17[0] - fRec17[2]) * (((168.105f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 41, 249))] : 0.0f) + (fRec16[0] - fRec16[2]) * (((171.863f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 42, 249))] : 0.0f) + (fRec15[0] - fRec15[2]) * (((174.464f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 43, 249))] : 0.0f) + (fRec14[0] - fRec14[2]) * (((178.937f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 44, 249))] : 0.0f) + (fRec13[0] - fRec13[2]) * (((181.482f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 45, 249))] : 0.0f) + (fRec12[0] - fRec12[2]) * (((185.398f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 46, 249))] : 0.0f) + (fRec11[0] - fRec11[2]) * (((190.369f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 47, 249))] : 0.0f) + (fRec10[0] - fRec10[2]) * (((192.19f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 48, 249))] : 0.0f) + (fRec5[0] - fRec5[2]) * (((195.505f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 49, 249))] : 0.0f);
			fRec59[0] = 0.05f * fRec2[1] + 0.95f * fRec59[1];
			float fTemp26 = 0.99f * fRec59[0] + 0.02f * fVec2[1];
			fVec3[IOTA0 & 2047] = fTemp26;
			fRec3[0] = fTemp18 * (fTemp7 * (fTemp8 * (0.041666668f * fTemp9 * fVec3[(IOTA0 - iTemp17) & 2047] - 0.16666667f * fTemp10 * fVec3[(IOTA0 - iTemp16) & 2047]) + 0.25f * fTemp11 * fVec3[(IOTA0 - iTemp15) & 2047]) - 0.16666667f * fTemp12 * fVec3[(IOTA0 - iTemp14) & 2047]) + 0.041666668f * fTemp13 * fVec3[(IOTA0 - iTemp5) & 2047];
			float fRec1 = fRec3[0];
			output0[i0] = FAUSTFLOAT(fRec1);
			iRec0[1] = iRec0[0];
			fRec4[1] = fRec4[0];
			IOTA0 = IOTA0 + 1;
			fRec2[1] = fRec2[0];
			fVec1[1] = fVec1[0];
			iRec6[1] = iRec6[0];
			iRec9[1] = iRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
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
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fVec2[1] = fVec2[0];
			fRec59[1] = fRec59[0];
			fRec3[1] = fRec3[0];
		}
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

/* using namespace std;

int main(int argc, char* argv[])
{
    Marimba DSP;
    cout << "DSP size: " << sizeof(DSP) << " bytes\n";
    
    // Activate the UI, here that only print the control paths
    PrintUI ui;
    DSP.buildUserInterface(&ui);

    // Allocate the audio driver to render 5 buffers of 512 frames
    dummyaudio audio(5);
    audio.init("Test", static_cast<dsp*>(&DSP));
    
    // Render buffers...
    audio.start();
    audio.stop();
} */

/******************* END minimal.cpp ****************/


#endif
