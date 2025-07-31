import("stdfaust.lib");

freq = nentry("freq", 200, 40, 2000, 0.01) : si.smoo;
exPos = nentry("exPos", 0.5, 0, 1, 0.01) : si.smoo;
sharpness = nentry("sharpness", 0.5, 0, 1, 0.01) : si.smoo;
gain = nentry("gain", 0.5, 0, 1, 0.01) : si.smoo;
gate = button("gate") : si.smoo;
exPos2 = nentry("exPos2", 0, 0, 4, 1) : si.smoo;

process = vgroup("marimba", pm.strike(exPos, sharpness, gain, gate) : pm.marimbaModel(freq, exPos2) <: _,_);
