/* ------------------------------------------------------------
name: "marimba_model"
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
	float fRec5[3];
	float fConst9;
	float fConst10;
	float fConst11;
	float fRec6[3];
	float fConst13;
	float fConst14;
	float fConst15;
	float fRec7[3];
	float fConst17;
	float fConst18;
	float fConst19;
	float fRec8[3];
	float fConst21;
	float fConst22;
	float fConst23;
	float fRec9[3];
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec10[3];
	float fConst29;
	float fConst30;
	float fConst31;
	float fRec11[3];
	float fConst33;
	float fConst34;
	float fConst35;
	float fRec12[3];
	float fConst37;
	float fConst38;
	float fConst39;
	float fRec13[3];
	float fConst41;
	float fConst42;
	float fConst43;
	float fRec14[3];
	float fConst45;
	float fConst46;
	float fConst47;
	float fRec15[3];
	float fConst49;
	float fConst50;
	float fConst51;
	float fRec16[3];
	float fConst53;
	float fConst54;
	float fConst55;
	float fRec17[3];
	float fConst57;
	float fConst58;
	float fConst59;
	float fRec18[3];
	float fConst61;
	float fConst62;
	float fConst63;
	float fRec19[3];
	float fConst65;
	float fConst66;
	float fConst67;
	float fRec20[3];
	float fConst69;
	float fConst70;
	float fConst71;
	float fRec21[3];
	float fConst73;
	float fConst74;
	float fConst75;
	float fRec22[3];
	float fConst77;
	float fConst78;
	float fConst79;
	float fRec23[3];
	float fConst81;
	float fConst82;
	float fConst83;
	float fRec24[3];
	float fConst85;
	float fConst86;
	float fConst87;
	float fRec25[3];
	float fConst89;
	float fConst90;
	float fConst91;
	float fRec26[3];
	float fConst93;
	float fConst94;
	float fConst95;
	float fRec27[3];
	float fConst97;
	float fConst98;
	float fConst99;
	float fRec28[3];
	float fConst101;
	float fConst102;
	float fConst103;
	float fRec29[3];
	float fConst105;
	float fConst106;
	float fConst107;
	float fRec30[3];
	float fConst109;
	float fConst110;
	float fConst111;
	float fRec31[3];
	float fConst113;
	float fConst114;
	float fConst115;
	float fRec32[3];
	float fConst117;
	float fConst118;
	float fConst119;
	float fRec33[3];
	float fConst121;
	float fConst122;
	float fConst123;
	float fRec34[3];
	float fConst125;
	float fConst126;
	float fConst127;
	float fRec35[3];
	float fConst129;
	float fConst130;
	float fConst131;
	float fRec36[3];
	float fConst133;
	float fConst134;
	float fConst135;
	float fRec37[3];
	float fConst137;
	float fConst138;
	float fConst139;
	float fRec38[3];
	float fConst141;
	float fConst142;
	float fConst143;
	float fRec39[3];
	float fConst145;
	float fConst146;
	float fConst147;
	float fRec40[3];
	float fConst149;
	float fConst150;
	float fConst151;
	float fRec41[3];
	float fConst153;
	float fConst154;
	float fConst155;
	float fRec42[3];
	float fConst157;
	float fConst158;
	float fConst159;
	float fRec43[3];
	float fConst161;
	float fConst162;
	float fConst163;
	float fRec44[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fRec45[3];
	float fConst169;
	float fConst170;
	float fConst171;
	float fRec46[3];
	float fConst173;
	float fConst174;
	float fConst175;
	float fRec47[3];
	float fConst177;
	float fConst178;
	float fConst179;
	float fRec48[3];
	float fConst181;
	float fConst182;
	float fConst183;
	float fRec49[3];
	float fConst185;
	float fConst186;
	float fConst187;
	float fRec50[3];
	float fConst189;
	float fConst190;
	float fConst191;
	float fRec51[3];
	float fConst193;
	float fConst194;
	float fConst195;
	float fRec52[3];
	float fConst197;
	float fConst198;
	float fConst199;
	float fRec53[3];
	float fConst201;
	float fConst202;
	float fConst203;
	float fRec54[3];
	float fVec1[2];
	float fRec55[2];
	float fVec2[2048];
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
		m->declare("filename", "marimba_model.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.3.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.7.0");
		m->declare("name", "marimba_model");
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
		return 3;
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
		float fConst8 = std::pow(0.001f, 3.8190633e+09f / fConst0);
		fConst9 = Marimba_faustpower2_f(fConst8);
		fConst10 = 1207.5654f / fConst0;
		fConst11 = 2.0f * fConst8;
		float fConst12 = std::pow(0.001f, 5.3122326e+08f / fConst0);
		fConst13 = Marimba_faustpower2_f(fConst12);
		fConst14 = 1196.1237f / fConst0;
		fConst15 = 2.0f * fConst12;
		float fConst16 = std::pow(0.001f, 2.203328e+07f / fConst0);
		fConst17 = Marimba_faustpower2_f(fConst16);
		fConst18 = 1164.89f / fConst0;
		fConst19 = 2.0f * fConst16;
		float fConst20 = std::pow(0.001f, 4549764.5f / fConst0);
		fConst21 = Marimba_faustpower2_f(fConst20);
		fConst22 = 1140.285f / fConst0;
		fConst23 = 2.0f * fConst20;
		float fConst24 = std::pow(0.001f, 2024133.5f / fConst0);
		fConst25 = Marimba_faustpower2_f(fConst24);
		fConst26 = 1124.2943f / fConst0;
		fConst27 = 2.0f * fConst24;
		float fConst28 = std::pow(0.001f, 630229.4f / fConst0);
		fConst29 = Marimba_faustpower2_f(fConst28);
		fConst30 = 1096.1897f / fConst0;
		fConst31 = 2.0f * fConst28;
		float fConst32 = std::pow(0.001f, 355973.34f / fConst0);
		fConst33 = Marimba_faustpower2_f(fConst32);
		fConst34 = 1079.847f / fConst0;
		fConst35 = 2.0f * fConst32;
		float fConst36 = std::pow(0.001f, 172447.05f / fConst0);
		fConst37 = Marimba_faustpower2_f(fConst36);
		fConst38 = 1056.2349f / fConst0;
		fConst39 = 2.0f * fConst36;
		float fConst40 = std::pow(0.001f, 37577.844f / fConst0);
		fConst41 = Marimba_faustpower2_f(fConst40);
		fConst42 = 993.8931f / fConst0;
		fConst43 = 2.0f * fConst40;
		float fConst44 = std::pow(0.001f, 26985.693f / fConst0);
		fConst45 = Marimba_faustpower2_f(fConst44);
		fConst46 = 977.6448f / fConst0;
		fConst47 = 2.0f * fConst44;
		float fConst48 = std::pow(0.001f, 20142.857f / fConst0);
		fConst49 = Marimba_faustpower2_f(fConst48);
		fConst50 = 962.37036f / fConst0;
		fConst51 = 2.0f * fConst48;
		float fConst52 = std::pow(0.001f, 17675.48f / fConst0);
		fConst53 = Marimba_faustpower2_f(fConst52);
		fConst54 = 955.2515f / fConst0;
		fConst55 = 2.0f * fConst52;
		float fConst56 = std::pow(0.001f, 13265.488f / fConst0);
		fConst57 = Marimba_faustpower2_f(fConst56);
		fConst58 = 938.94666f / fConst0;
		fConst59 = 2.0f * fConst56;
		float fConst60 = std::pow(0.001f, 8048.458f / fConst0);
		fConst61 = Marimba_faustpower2_f(fConst60);
		fConst62 = 908.22815f / fConst0;
		fConst63 = 2.0f * fConst60;
		float fConst64 = std::pow(0.001f, 3034.9124f / fConst0);
		fConst65 = Marimba_faustpower2_f(fConst64);
		fConst66 = 838.6607f / fConst0;
		fConst67 = 2.0f * fConst64;
		float fConst68 = std::pow(0.001f, 2755.6304f / fConst0);
		fConst69 = Marimba_faustpower2_f(fConst68);
		fConst70 = 831.0078f / fConst0;
		fConst71 = 2.0f * fConst68;
		float fConst72 = std::pow(0.001f, 2311.8018f / fConst0);
		fConst73 = Marimba_faustpower2_f(fConst72);
		fConst74 = 816.701f / fConst0;
		fConst75 = 2.0f * fConst72;
		float fConst76 = std::pow(0.001f, 1859.39f / fConst0);
		fConst77 = Marimba_faustpower2_f(fConst76);
		fConst78 = 798.24725f / fConst0;
		fConst79 = 2.0f * fConst76;
		float fConst80 = std::pow(0.001f, 1095.6359f / fConst0);
		fConst81 = Marimba_faustpower2_f(fConst80);
		fConst82 = 749.93585f / fConst0;
		fConst83 = 2.0f * fConst80;
		float fConst84 = std::pow(0.001f, 773.2129f / fConst0);
		fConst85 = Marimba_faustpower2_f(fConst84);
		fConst86 = 715.1899f / fConst0;
		fConst87 = 2.0f * fConst84;
		float fConst88 = std::pow(0.001f, 695.5596f / fConst0);
		fConst89 = Marimba_faustpower2_f(fConst88);
		fConst90 = 704.15027f / fConst0;
		fConst91 = 2.0f * fConst88;
		float fConst92 = std::pow(0.001f, 638.4778f / fConst0);
		fConst93 = Marimba_faustpower2_f(fConst92);
		fConst94 = 695.04596f / fConst0;
		fConst95 = 2.0f * fConst92;
		float fConst96 = std::pow(0.001f, 312.0091f / fConst0);
		fConst97 = Marimba_faustpower2_f(fConst96);
		fConst98 = 612.4893f / fConst0;
		fConst99 = 2.0f * fConst96;
		float fConst100 = std::pow(0.001f, 278.13995f / fConst0);
		fConst101 = Marimba_faustpower2_f(fConst100);
		fConst102 = 598.1052f / fConst0;
		fConst103 = 2.0f * fConst100;
		float fConst104 = std::pow(0.001f, 249.36165f / fConst0);
		fConst105 = Marimba_faustpower2_f(fConst104);
		fConst106 = 584.1232f / fConst0;
		fConst107 = 2.0f * fConst104;
		float fConst108 = std::pow(0.001f, 216.13428f / fConst0);
		fConst109 = Marimba_faustpower2_f(fConst108);
		fConst110 = 565.34845f / fConst0;
		fConst111 = 2.0f * fConst108;
		float fConst112 = std::pow(0.001f, 142.91408f / fConst0);
		fConst113 = Marimba_faustpower2_f(fConst112);
		fConst114 = 507.917f / fConst0;
		fConst115 = 2.0f * fConst112;
		float fConst116 = std::pow(0.001f, 130.3097f / fConst0);
		fConst117 = Marimba_faustpower2_f(fConst116);
		fConst118 = 494.43643f / fConst0;
		fConst119 = 2.0f * fConst116;
		float fConst120 = std::pow(0.001f, 109.456856f / fConst0);
		fConst121 = Marimba_faustpower2_f(fConst120);
		fConst122 = 468.28644f / fConst0;
		fConst123 = 2.0f * fConst120;
		float fConst124 = std::pow(0.001f, 80.89012f / fConst0);
		fConst125 = Marimba_faustpower2_f(fConst124);
		fConst126 = 420.71393f / fConst0;
		fConst127 = 2.0f * fConst124;
		float fConst128 = std::pow(0.001f, 76.06687f / fConst0);
		fConst129 = Marimba_faustpower2_f(fConst128);
		fConst130 = 410.68658f / fConst0;
		fConst131 = 2.0f * fConst128;
		float fConst132 = std::pow(0.001f, 70.99649f / fConst0);
		fConst133 = Marimba_faustpower2_f(fConst132);
		fConst134 = 399.28763f / fConst0;
		fConst135 = 2.0f * fConst132;
		float fConst136 = std::pow(0.001f, 58.4253f / fConst0);
		fConst137 = Marimba_faustpower2_f(fConst136);
		fConst138 = 366.22174f / fConst0;
		fConst139 = 2.0f * fConst136;
		float fConst140 = std::pow(0.001f, 47.439922f / fConst0);
		fConst141 = Marimba_faustpower2_f(fConst140);
		fConst142 = 329.4274f / fConst0;
		fConst143 = 2.0f * fConst140;
		float fConst144 = std::pow(0.001f, 45.175232f / fConst0);
		fConst145 = Marimba_faustpower2_f(fConst144);
		fConst146 = 320.56183f / fConst0;
		fConst147 = 2.0f * fConst144;
		float fConst148 = std::pow(0.001f, 40.26368f / fConst0);
		fConst149 = Marimba_faustpower2_f(fConst148);
		fConst150 = 299.35544f / fConst0;
		fConst151 = 2.0f * fConst148;
		float fConst152 = std::pow(0.001f, 31.381102f / fConst0);
		fConst153 = Marimba_faustpower2_f(fConst152);
		fConst154 = 251.72577f / fConst0;
		fConst155 = 2.0f * fConst152;
		float fConst156 = std::pow(0.001f, 29.263924f / fConst0);
		fConst157 = Marimba_faustpower2_f(fConst156);
		fConst158 = 237.9461f / fConst0;
		fConst159 = 2.0f * fConst156;
		float fConst160 = std::pow(0.001f, 28.536816f / fConst0);
		fConst161 = Marimba_faustpower2_f(fConst160);
		fConst162 = 232.93527f / fConst0;
		fConst163 = 2.0f * fConst160;
		float fConst164 = std::pow(0.001f, 22.269566f / fConst0);
		fConst165 = Marimba_faustpower2_f(fConst164);
		fConst166 = 182.17719f / fConst0;
		fConst167 = 2.0f * fConst164;
		float fConst168 = std::pow(0.001f, 20.48241f / fConst0);
		fConst169 = Marimba_faustpower2_f(fConst168);
		fConst170 = 164.47809f / fConst0;
		fConst171 = 2.0f * fConst168;
		float fConst172 = std::pow(0.001f, 17.630983f / fConst0);
		fConst173 = Marimba_faustpower2_f(fConst172);
		fConst174 = 132.01099f / fConst0;
		fConst175 = 2.0f * fConst172;
		float fConst176 = std::pow(0.001f, 16.365208f / fConst0);
		fConst177 = Marimba_faustpower2_f(fConst176);
		fConst178 = 115.51008f / fConst0;
		fConst179 = 2.0f * fConst176;
		float fConst180 = std::pow(0.001f, 14.533069f / fConst0);
		fConst181 = Marimba_faustpower2_f(fConst180);
		fConst182 = 88.6991f / fConst0;
		fConst183 = 2.0f * fConst180;
		float fConst184 = std::pow(0.001f, 12.802757f / fConst0);
		fConst185 = Marimba_faustpower2_f(fConst184);
		fConst186 = 59.362152f / fConst0;
		fConst187 = 2.0f * fConst184;
		float fConst188 = std::pow(0.001f, 12.337915f / fConst0);
		fConst189 = Marimba_faustpower2_f(fConst188);
		fConst190 = 50.66214f / fConst0;
		fConst191 = 2.0f * fConst188;
		float fConst192 = std::pow(0.001f, 11.038634f / fConst0);
		fConst193 = Marimba_faustpower2_f(fConst192);
		fConst194 = 24.094069f / fConst0;
		fConst195 = 2.0f * fConst192;
		float fConst196 = std::pow(0.001f, 10.890133f / fConst0);
		fConst197 = Marimba_faustpower2_f(fConst196);
		fConst198 = 20.819712f / fConst0;
		fConst199 = 2.0f * fConst196;
		float fConst200 = std::pow(0.001f, 10.259114f / fConst0);
		fConst201 = Marimba_faustpower2_f(fConst200);
		fConst202 = 6.2831855f / fConst0;
		fConst203 = 2.0f * fConst200;
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
		for (int l4 = 0; l4 < 3; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 3; l5 = l5 + 1) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 3; l6 = l6 + 1) {
			fRec7[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 3; l7 = l7 + 1) {
			fRec8[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec9[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec10[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec11[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec12[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec13[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 3; l13 = l13 + 1) {
			fRec14[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec15[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec16[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 3; l16 = l16 + 1) {
			fRec17[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 3; l17 = l17 + 1) {
			fRec18[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 3; l18 = l18 + 1) {
			fRec19[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 3; l19 = l19 + 1) {
			fRec20[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 3; l20 = l20 + 1) {
			fRec21[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 3; l21 = l21 + 1) {
			fRec22[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 3; l22 = l22 + 1) {
			fRec23[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 3; l23 = l23 + 1) {
			fRec24[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 3; l24 = l24 + 1) {
			fRec25[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 3; l25 = l25 + 1) {
			fRec26[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 3; l26 = l26 + 1) {
			fRec27[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 3; l27 = l27 + 1) {
			fRec28[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 3; l28 = l28 + 1) {
			fRec29[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 3; l29 = l29 + 1) {
			fRec30[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 3; l30 = l30 + 1) {
			fRec31[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 3; l31 = l31 + 1) {
			fRec32[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 3; l32 = l32 + 1) {
			fRec33[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 3; l33 = l33 + 1) {
			fRec34[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 3; l34 = l34 + 1) {
			fRec35[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 3; l35 = l35 + 1) {
			fRec36[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec37[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 3; l37 = l37 + 1) {
			fRec38[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 3; l38 = l38 + 1) {
			fRec39[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 3; l39 = l39 + 1) {
			fRec40[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 3; l40 = l40 + 1) {
			fRec41[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 3; l41 = l41 + 1) {
			fRec42[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 3; l42 = l42 + 1) {
			fRec43[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 3; l43 = l43 + 1) {
			fRec44[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 3; l44 = l44 + 1) {
			fRec45[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 3; l45 = l45 + 1) {
			fRec46[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 3; l46 = l46 + 1) {
			fRec47[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 3; l47 = l47 + 1) {
			fRec48[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec49[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 3; l49 = l49 + 1) {
			fRec50[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec51[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec52[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec53[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 3; l53 = l53 + 1) {
			fRec54[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fVec1[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec55[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 2048; l56 = l56 + 1) {
			fVec2[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 2; l57 = l57 + 1) {
			fRec3[l57] = 0.0f;
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
		ui_interface->openVerticalBox("marimba_model");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
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
			float fTemp20 = float(input2[i0]);
			fRec5[0] = fTemp20 + fConst7 * fRec5[1] * std::cos(fConst6 * fTemp1) - fConst5 * fRec5[2];
			fRec6[0] = fTemp20 + fConst11 * fRec6[1] * std::cos(fConst10 * fTemp1) - fConst9 * fRec6[2];
			fRec7[0] = fTemp20 + fConst15 * fRec7[1] * std::cos(fConst14 * fTemp1) - fConst13 * fRec7[2];
			fRec8[0] = fTemp20 + fConst19 * fRec8[1] * std::cos(fConst18 * fTemp1) - fConst17 * fRec8[2];
			fRec9[0] = fTemp20 + fConst23 * fRec9[1] * std::cos(fConst22 * fTemp1) - fConst21 * fRec9[2];
			fRec10[0] = fTemp20 + fConst27 * fRec10[1] * std::cos(fConst26 * fTemp1) - fConst25 * fRec10[2];
			fRec11[0] = fTemp20 + fConst31 * fRec11[1] * std::cos(fConst30 * fTemp1) - fConst29 * fRec11[2];
			fRec12[0] = fTemp20 + fConst35 * fRec12[1] * std::cos(fConst34 * fTemp1) - fConst33 * fRec12[2];
			fRec13[0] = fTemp20 + fConst39 * fRec13[1] * std::cos(fConst38 * fTemp1) - fConst37 * fRec13[2];
			fRec14[0] = fTemp20 + fConst43 * fRec14[1] * std::cos(fConst42 * fTemp1) - fConst41 * fRec14[2];
			fRec15[0] = fTemp20 + fConst47 * fRec15[1] * std::cos(fConst46 * fTemp1) - fConst45 * fRec15[2];
			fRec16[0] = fTemp20 + fConst51 * fRec16[1] * std::cos(fConst50 * fTemp1) - fConst49 * fRec16[2];
			fRec17[0] = fTemp20 + fConst55 * fRec17[1] * std::cos(fConst54 * fTemp1) - fConst53 * fRec17[2];
			fRec18[0] = fTemp20 + fConst59 * fRec18[1] * std::cos(fConst58 * fTemp1) - fConst57 * fRec18[2];
			fRec19[0] = fTemp20 + fConst63 * fRec19[1] * std::cos(fConst62 * fTemp1) - fConst61 * fRec19[2];
			fRec20[0] = fTemp20 + fConst67 * fRec20[1] * std::cos(fConst66 * fTemp1) - fConst65 * fRec20[2];
			fRec21[0] = fTemp20 + fConst71 * fRec21[1] * std::cos(fConst70 * fTemp1) - fConst69 * fRec21[2];
			fRec22[0] = fTemp20 + fConst75 * fRec22[1] * std::cos(fConst74 * fTemp1) - fConst73 * fRec22[2];
			fRec23[0] = fTemp20 + fConst79 * fRec23[1] * std::cos(fConst78 * fTemp1) - fConst77 * fRec23[2];
			fRec24[0] = fTemp20 + fConst83 * fRec24[1] * std::cos(fConst82 * fTemp1) - fConst81 * fRec24[2];
			fRec25[0] = fTemp20 + fConst87 * fRec25[1] * std::cos(fConst86 * fTemp1) - fConst85 * fRec25[2];
			fRec26[0] = fTemp20 + fConst91 * fRec26[1] * std::cos(fConst90 * fTemp1) - fConst89 * fRec26[2];
			fRec27[0] = fTemp20 + fConst95 * fRec27[1] * std::cos(fConst94 * fTemp1) - fConst93 * fRec27[2];
			fRec28[0] = fTemp20 + fConst99 * fRec28[1] * std::cos(fConst98 * fTemp1) - fConst97 * fRec28[2];
			fRec29[0] = fTemp20 + fConst103 * fRec29[1] * std::cos(fConst102 * fTemp1) - fConst101 * fRec29[2];
			fRec30[0] = fTemp20 + fConst107 * fRec30[1] * std::cos(fConst106 * fTemp1) - fConst105 * fRec30[2];
			fRec31[0] = fTemp20 + fConst111 * fRec31[1] * std::cos(fConst110 * fTemp1) - fConst109 * fRec31[2];
			fRec32[0] = fTemp20 + fConst115 * fRec32[1] * std::cos(fConst114 * fTemp1) - fConst113 * fRec32[2];
			fRec33[0] = fTemp20 + fConst119 * fRec33[1] * std::cos(fConst118 * fTemp1) - fConst117 * fRec33[2];
			fRec34[0] = fTemp20 + fConst123 * fRec34[1] * std::cos(fConst122 * fTemp1) - fConst121 * fRec34[2];
			fRec35[0] = fTemp20 + fConst127 * fRec35[1] * std::cos(fConst126 * fTemp1) - fConst125 * fRec35[2];
			fRec36[0] = fTemp20 + fConst131 * fRec36[1] * std::cos(fConst130 * fTemp1) - fConst129 * fRec36[2];
			fRec37[0] = fTemp20 + fConst135 * fRec37[1] * std::cos(fConst134 * fTemp1) - fConst133 * fRec37[2];
			fRec38[0] = fTemp20 + fConst139 * fRec38[1] * std::cos(fConst138 * fTemp1) - fConst137 * fRec38[2];
			fRec39[0] = fTemp20 + fConst143 * fRec39[1] * std::cos(fConst142 * fTemp1) - fConst141 * fRec39[2];
			fRec40[0] = fTemp20 + fConst147 * fRec40[1] * std::cos(fConst146 * fTemp1) - fConst145 * fRec40[2];
			fRec41[0] = fTemp20 + fConst151 * fRec41[1] * std::cos(fConst150 * fTemp1) - fConst149 * fRec41[2];
			fRec42[0] = fTemp20 + fConst155 * fRec42[1] * std::cos(fConst154 * fTemp1) - fConst153 * fRec42[2];
			fRec43[0] = fTemp20 + fConst159 * fRec43[1] * std::cos(fConst158 * fTemp1) - fConst157 * fRec43[2];
			fRec44[0] = fTemp20 + fConst163 * fRec44[1] * std::cos(fConst162 * fTemp1) - fConst161 * fRec44[2];
			fRec45[0] = fTemp20 + fConst167 * fRec45[1] * std::cos(fConst166 * fTemp1) - fConst165 * fRec45[2];
			fRec46[0] = fTemp20 + fConst171 * fRec46[1] * std::cos(fConst170 * fTemp1) - fConst169 * fRec46[2];
			fRec47[0] = fTemp20 + fConst175 * fRec47[1] * std::cos(fConst174 * fTemp1) - fConst173 * fRec47[2];
			fRec48[0] = fTemp20 + fConst179 * fRec48[1] * std::cos(fConst178 * fTemp1) - fConst177 * fRec48[2];
			fRec49[0] = fTemp20 + fConst183 * fRec49[1] * std::cos(fConst182 * fTemp1) - fConst181 * fRec49[2];
			fRec50[0] = fTemp20 + fConst187 * fRec50[1] * std::cos(fConst186 * fTemp1) - fConst185 * fRec50[2];
			fRec51[0] = fTemp20 + fConst191 * fRec51[1] * std::cos(fConst190 * fTemp1) - fConst189 * fRec51[2];
			fRec52[0] = fTemp20 + fConst195 * fRec52[1] * std::cos(fConst194 * fTemp1) - fConst193 * fRec52[2];
			fRec53[0] = fTemp20 + fConst199 * fRec53[1] * std::cos(fConst198 * fTemp1) - fConst197 * fRec53[2];
			fRec54[0] = fTemp20 + fConst203 * fRec54[1] * std::cos(fConst202 * fTemp1) - fConst201 * fRec54[2];
			fVec1[0] = (fRec54[0] - fRec54[2]) * ((fTemp1 < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19, 249))] : 0.0f) + (fRec53[0] - fRec53[2]) * (((3.31356f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 1, 249))] : 0.0f) + (fRec52[0] - fRec52[2]) * (((3.83469f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 2, 249))] : 0.0f) + (fRec51[0] - fRec51[2]) * (((8.06313f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 3, 249))] : 0.0f) + (fRec50[0] - fRec50[2]) * (((9.44778f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 4, 249))] : 0.0f) + (fRec49[0] - fRec49[2]) * (((14.1169f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 5, 249))] : 0.0f) + (fRec48[0] - fRec48[2]) * (((18.384f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 6, 249))] : 0.0f) + (fRec47[0] - fRec47[2]) * (((21.0102f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 7, 249))] : 0.0f) + (fRec46[0] - fRec46[2]) * (((26.1775f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 8, 249))] : 0.0f) + (fRec45[0] - fRec45[2]) * (((28.9944f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 9, 249))] : 0.0f) + (fRec44[0] - fRec44[2]) * (((37.0728f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 10, 249))] : 0.0f) + (fRec43[0] - fRec43[2]) * (((37.8703f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 11, 249))] : 0.0f) + (fRec42[0] - fRec42[2]) * (((40.0634f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 12, 249))] : 0.0f) + (fRec41[0] - fRec41[2]) * (((47.6439f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 13, 249))] : 0.0f) + (fRec40[0] - fRec40[2]) * (((51.019f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 14, 249))] : 0.0f) + (fRec39[0] - fRec39[2]) * (((52.43f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 15, 249))] : 0.0f) + (fRec38[0] - fRec38[2]) * (((58.286f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 16, 249))] : 0.0f) + (fRec37[0] - fRec37[2]) * (((63.5486f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 17, 249))] : 0.0f) + (fRec36[0] - fRec36[2]) * (((65.3628f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 18, 249))] : 0.0f) + (fRec35[0] - fRec35[2]) * (((66.9587f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 19, 249))] : 0.0f) + (fRec34[0] - fRec34[2]) * (((74.5301f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 20, 249))] : 0.0f) + (fRec33[0] - fRec33[2]) * (((78.692f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 21, 249))] : 0.0f) + (fRec32[0] - fRec32[2]) * (((80.8375f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 22, 249))] : 0.0f) + (fRec31[0] - fRec31[2]) * (((89.978f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 23, 249))] : 0.0f) + (fRec30[0] - fRec30[2]) * (((92.9661f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 24, 249))] : 0.0f) + (fRec29[0] - fRec29[2]) * (((95.1914f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 25, 249))] : 0.0f) + (fRec28[0] - fRec28[2]) * (((97.4807f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 26, 249))] : 0.0f) + (fRec27[0] - fRec27[2]) * (((110.62f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 27, 249))] : 0.0f) + (fRec26[0] - fRec26[2]) * (((112.069f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 28, 249))] : 0.0f) + (fRec25[0] - fRec25[2]) * (((113.826f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 29, 249))] : 0.0f) + (fRec24[0] - fRec24[2]) * (((119.356f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 30, 249))] : 0.0f) + (fRec23[0] - fRec23[2]) * (((127.045f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 31, 249))] : 0.0f) + (fRec22[0] - fRec22[2]) * (((129.982f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 32, 249))] : 0.0f) + (fRec21[0] - fRec21[2]) * (((132.259f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 33, 249))] : 0.0f) + (fRec20[0] - fRec20[2]) * (((133.477f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 34, 249))] : 0.0f) + (fRec19[0] - fRec19[2]) * (((144.549f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 35, 249))] : 0.0f) + (fRec18[0] - fRec18[2]) * (((149.438f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 36, 249))] : 0.0f) + (fRec17[0] - fRec17[2]) * (((152.033f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 37, 249))] : 0.0f) + (fRec16[0] - fRec16[2]) * (((153.166f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 38, 249))] : 0.0f) + (fRec15[0] - fRec15[2]) * (((155.597f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 39, 249))] : 0.0f) + (fRec14[0] - fRec14[2]) * (((158.183f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 40, 249))] : 0.0f) + (fRec13[0] - fRec13[2]) * (((168.105f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 41, 249))] : 0.0f) + (fRec12[0] - fRec12[2]) * (((171.863f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 42, 249))] : 0.0f) + (fRec11[0] - fRec11[2]) * (((174.464f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 43, 249))] : 0.0f) + (fRec10[0] - fRec10[2]) * (((178.937f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 44, 249))] : 0.0f) + (fRec9[0] - fRec9[2]) * (((181.482f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 45, 249))] : 0.0f) + (fRec8[0] - fRec8[2]) * (((185.398f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 46, 249))] : 0.0f) + (fRec7[0] - fRec7[2]) * (((190.369f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 47, 249))] : 0.0f) + (fRec6[0] - fRec6[2]) * (((192.19f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 48, 249))] : 0.0f) + (fRec5[0] - fRec5[2]) * (((195.505f * fTemp1) < fConst3) ? ftbl0MarimbaSIG0[std::max<int>(0, std::min<int>(iTemp19 + 49, 249))] : 0.0f);
			fRec55[0] = 0.05f * fRec2[1] + 0.95f * fRec55[1];
			float fTemp21 = 0.99f * fRec55[0] + 0.02f * fVec1[1];
			fVec2[IOTA0 & 2047] = fTemp21;
			fRec3[0] = fTemp18 * (fTemp7 * (fTemp8 * (0.041666668f * fTemp9 * fVec2[(IOTA0 - iTemp17) & 2047] - 0.16666667f * fTemp10 * fVec2[(IOTA0 - iTemp16) & 2047]) + 0.25f * fTemp11 * fVec2[(IOTA0 - iTemp15) & 2047]) - 0.16666667f * fTemp12 * fVec2[(IOTA0 - iTemp14) & 2047]) + 0.041666668f * fTemp13 * fVec2[(IOTA0 - iTemp5) & 2047];
			float fRec1 = fRec3[0];
			output0[i0] = FAUSTFLOAT(fRec1);
			iRec0[1] = iRec0[0];
			fRec4[1] = fRec4[0];
			IOTA0 = IOTA0 + 1;
			fRec2[1] = fRec2[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
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
			fVec1[1] = fVec1[0];
			fRec55[1] = fRec55[0];
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
