import matplotlib.pyplot as plt

# # Data from running simulator
torus_transpose_rates = [0.001, 0.003, 0.005, 0.007, 0.009, 0.01, 
                         0.04, 0.07, 0.09, 0.095, 0.099, 0.0998, 0.1]
torus_transpose_lat   = [30.0394, 31.0247, 30.7227, 30.7531, 30.8628, 31.0005,
                         32.1259, 34.5074, 62.7312, 158.303, 344.646, 396.453, 417.091]

# unstable after ~0.1
transpose_unstable = [0.2, 0.3]

torus_uniform_rates = [0.02, 0.09, 0.15, 0.17, 0.17998, 0.193, 
                       0.21, 0.23, 0.25, 0.26, 0.268, 0.27, 0.276, 0.28]
torus_uniform_lat   = [31.3806, 31.9951, 33.6559, 34.4804, 34.8958, 35.6452,
                       36.7704, 39.5788, 44.197, 56.9376, 182.322, 302.084, 455.603, 492.498]

# unstable after ~0.29
uniform_unstable = [0.29]

plt.figure(figsize=(9,6))

# Plotting the data
plt.plot(torus_transpose_rates, torus_transpose_lat, marker="o", label="Torus – Transpose")
plt.plot(torus_uniform_rates, torus_uniform_lat, marker="s", label="Torus – Uniform")

# Mark unstable points (just as X markers near top)
plt.scatter(transpose_unstable, [500]*len(transpose_unstable), 
            color="red", marker="x", label="Transpose unstable")
plt.scatter(uniform_unstable, [500]*len(uniform_unstable), 
            color="purple", marker="x", label="Uniform unstable")

plt.xlabel("Injection Rate (packets/cycle/node)")
plt.ylabel("Average Packet Latency (cycles)")
plt.title("8×8 Torus Topology – Latency vs Offered Load")
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()
