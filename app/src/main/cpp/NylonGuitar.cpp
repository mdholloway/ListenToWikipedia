/* ------------------------------------------------------------
name: "nylon_guitar_model"
Code generated with Faust 2.70.3 (https://faust.grame.fr)
Compilation options: -a minimal.cpp -lang cpp -ct 1 -cn NylonGuitar -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __NylonGuitar_H__
#define  __NylonGuitar_H__

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
#define FAUSTCLASS NylonGuitar
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


class NylonGuitar : public dsp {
	
 private:
	
	int iRec10[2];
	int IOTA0;
	int fSampleRate;
	float fConst1;
	float fConst2;
	float fRec22[2];
	float fRec25[2];
	float fRec27[4];
	float fRec28[512];
	float fVec0[2];
	float fVec1[2];
	float fRec26[512];
	float fRec19[2];
	float fRec16[512];
	float fRec18[2];
	float fRec15[4];
	int iRec6[2];
	float fRec2[512];
	float fRec0[2];
	
 public:
	NylonGuitar() {}

	void metadata(Meta* m) { 
		m->declare("compile_options", "-a minimal.cpp -lang cpp -ct 1 -cn NylonGuitar -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("delays.lib/fdelay4:author", "Julius O. Smith III");
		m->declare("delays.lib/fdelayltv:author", "Julius O. Smith III");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.1.0");
		m->declare("filename", "nylon_guitar_model.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.7.0");
		m->declare("name", "nylon_guitar_model");
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
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 0.00882353f * fConst0;
		fConst2 = 0.0014705883f * fConst0;
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iRec10[l0] = 0;
		}
		IOTA0 = 0;
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec22[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec25[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 4; l3 = l3 + 1) {
			fRec27[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 512; l4 = l4 + 1) {
			fRec28[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fVec0[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fVec1[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 512; l7 = l7 + 1) {
			fRec26[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec19[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 512; l9 = l9 + 1) {
			fRec16[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec18[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 4; l11 = l11 + 1) {
			fRec15[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			iRec6[l12] = 0;
		}
		for (int l13 = 0; l13 < 512; l13 = l13 + 1) {
			fRec2[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec0[l14] = 0.0f;
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
	
	virtual NylonGuitar* clone() {
		return new NylonGuitar();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("nylon_guitar_model");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* output0 = outputs[0];
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iRec10[0] = 0;
			int iRec11 = iRec10[1];
			float fRec14 = float(iRec6[1]) - 0.9978437f * (0.7f * fRec15[2] + 0.15f * (fRec15[1] + fRec15[3]));
			float fTemp0 = float(input0[i0]) + -0.11f;
			float fTemp1 = float(input1[i0]);
			float fTemp2 = fConst2 * (1.0f - fTemp1) * fTemp0;
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
			fRec22[0] = fTemp18 * (fTemp7 * (fTemp8 * (0.041666668f * fRec2[(IOTA0 - (iTemp17 + 1)) & 511] * fTemp9 - 0.16666667f * fTemp10 * fRec2[(IOTA0 - (iTemp16 + 1)) & 511]) + 0.25f * fTemp11 * fRec2[(IOTA0 - (iTemp15 + 1)) & 511]) - 0.16666667f * fTemp12 * fRec2[(IOTA0 - (iTemp14 + 1)) & 511]) + 0.041666668f * fTemp13 * fRec2[(IOTA0 - (iTemp5 + 1)) & 511];
			fRec25[0] = 0.6f * fRec22[1] + 0.4f * fRec25[1];
			float fRec23 = fRec25[0];
			fRec27[0] = fRec0[1];
			fRec28[IOTA0 & 511] = -(0.9978437f * (0.7f * fRec27[2] + 0.15f * (fRec27[1] + fRec27[3])));
			float fTemp19 = fConst2 * fTemp1 * fTemp0;
			float fTemp20 = fTemp19 + -1.499995f;
			int iTemp21 = int(fTemp20);
			int iTemp22 = int(std::min<float>(fConst1, float(std::max<int>(0, iTemp21 + 4))));
			float fTemp23 = std::floor(fTemp20);
			float fTemp24 = fTemp19 + (-3.0f - fTemp23);
			float fTemp25 = fTemp19 + (-2.0f - fTemp23);
			float fTemp26 = fTemp19 + (-1.0f - fTemp23);
			float fTemp27 = fTemp19 - fTemp23;
			float fTemp28 = fTemp27 * fTemp26;
			float fTemp29 = fTemp28 * fTemp25;
			float fTemp30 = fTemp29 * fTemp24;
			int iTemp31 = int(std::min<float>(fConst1, float(std::max<int>(0, iTemp21 + 3))));
			int iTemp32 = int(std::min<float>(fConst1, float(std::max<int>(0, iTemp21 + 2))));
			int iTemp33 = int(std::min<float>(fConst1, float(std::max<int>(0, iTemp21 + 1))));
			int iTemp34 = int(std::min<float>(fConst1, float(std::max<int>(0, iTemp21))));
			float fTemp35 = fTemp19 + (-4.0f - fTemp23);
			fVec0[0] = fTemp35 * (fTemp24 * (fTemp25 * (0.041666668f * fRec28[(IOTA0 - (iTemp34 + 2)) & 511] * fTemp26 - 0.16666667f * fTemp27 * fRec28[(IOTA0 - (iTemp33 + 2)) & 511]) + 0.25f * fTemp28 * fRec28[(IOTA0 - (iTemp32 + 2)) & 511]) - 0.16666667f * fTemp29 * fRec28[(IOTA0 - (iTemp31 + 2)) & 511]) + 0.041666668f * fTemp30 * fRec28[(IOTA0 - (iTemp22 + 2)) & 511];
			float fTemp36 = float(input2[i0]);
			fVec1[0] = fTemp36 + fVec0[1];
			fRec26[IOTA0 & 511] = 0.6f * fVec1[1] + 0.4f * fRec26[(IOTA0 - 1) & 511];
			float fRec24 = fTemp18 * (fTemp7 * (fTemp8 * (0.041666668f * fTemp9 * fRec26[(IOTA0 - iTemp17) & 511] - 0.16666667f * fTemp10 * fRec26[(IOTA0 - iTemp16) & 511]) + 0.25f * fTemp11 * fRec26[(IOTA0 - iTemp15) & 511]) - 0.16666667f * fTemp12 * fRec26[(IOTA0 - iTemp14) & 511]) + 0.041666668f * fTemp13 * fRec26[(IOTA0 - iTemp5) & 511];
			fRec19[0] = fRec23;
			float fRec20 = fTemp36 + fRec19[1];
			float fRec21 = fRec24;
			fRec16[IOTA0 & 511] = fRec20;
			float fRec17 = fTemp35 * (fTemp24 * (fTemp25 * (0.041666668f * fTemp26 * fRec16[(IOTA0 - (iTemp34 + 1)) & 511] - 0.16666667f * fTemp27 * fRec16[(IOTA0 - (iTemp33 + 1)) & 511]) + 0.25f * fTemp28 * fRec16[(IOTA0 - (iTemp32 + 1)) & 511]) - 0.16666667f * fTemp29 * fRec16[(IOTA0 - (iTemp31 + 1)) & 511]) + 0.041666668f * fTemp30 * fRec16[(IOTA0 - (iTemp22 + 1)) & 511];
			fRec18[0] = fRec21;
			fRec15[0] = fRec18[1];
			float fRec12 = fRec15[1];
			float fRec13 = fRec15[1];
			iRec6[0] = iRec11;
			float fRec7 = fRec14;
			float fRec8 = fRec12;
			float fRec9 = fRec13;
			fRec2[IOTA0 & 511] = fRec7;
			float fRec3 = fRec17;
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			output0[i0] = FAUSTFLOAT(fRec1);
			iRec10[1] = iRec10[0];
			IOTA0 = IOTA0 + 1;
			fRec22[1] = fRec22[0];
			fRec25[1] = fRec25[0];
			for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
				fRec27[j0] = fRec27[j0 - 1];
			}
			fVec0[1] = fVec0[0];
			fVec1[1] = fVec1[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			for (int j1 = 3; j1 > 0; j1 = j1 - 1) {
				fRec15[j1] = fRec15[j1 - 1];
			}
			iRec6[1] = iRec6[0];
			fRec0[1] = fRec0[0];
		}
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

using namespace std;

int main(int argc, char* argv[])
{
    NylonGuitar DSP;
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
}

/******************* END minimal.cpp ****************/


#endif
