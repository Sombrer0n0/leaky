import leaky
import stim
s = leaky.Simulator(2)
cl = leaky.LeakyPauliChannel(1)
cl.add_transition(0,0,1,1)
#cl.add_transition(0,0,1,1)
ins = leaky.Instruction("X",[0])
circuit=stim.Circuit("""
    X 0
    M 0 1
""")
s.bind_leaky_channel(ins,cl)
print(s.sample_batch(circuit=circuit,shots=1))
print("1")