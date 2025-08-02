import("stdfaust.lib");

freq = nentry("freq",200,40,2000,0.01) : si.smoo;
gain = nentry("gain",1,0,1,0.01) : si.smoo;
gate = button("gate") : si.smoo; 
cutoff = nentry("cutoff[midi:ctrl 1]",5000,40,8000,0.01) : si.smoo;
q = nentry("q[midi:ctrl 2]",5,1,50,0.01) : si.smoo;

process = vgroup("synth", os.sawtooth(freq)*gain*gate : fi.resonlp(cutoff,q,1) : _);
