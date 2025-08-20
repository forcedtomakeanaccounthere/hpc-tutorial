# import matplotlib.pyplot as plt

# # Data from your Excel sheet ----------------------
# torus_transpose_rates = [0.002, 0.0037, 0.005, 0.0058, 0.007, 0.0084, 0.01, 0.014, 0.018, 0.0197, 0.02, 0.0216, 0.022]
# torus_transpose_lat   = [49.1242, 52.6033, 54.583, 57.7188, 60.0628, 64.8398, 72.3846, 87.0083, 48.9065, 48.7971, 236.459, 377.903, 475.72]

# torus_uniform_rates = [0.001, 0.003, 0.005, 0.007, 0.009, 0.01, 0.04, 0.07, 0.09, 0.095, 0.099, 0.0998, 0.1]
# torus_uniform_lat   = [30.0394, 31.0247, 30.7227, 30.7531, 30.8628, 30.7302, 32.1259, 34.5074, 62.7137, 158.303, 344.646, 396.453, 417.091]

# # -------------------------------------------------

# plt.figure(figsize=(8,6))

# plt.plot(torus_transpose_rates, torus_transpose_lat, marker="o", label="Torus – Transpose")
# plt.plot(torus_uniform_rates, torus_uniform_lat, marker="s", label="Torus – Uniform")

# plt.xlabel("Injection Rate (packets/cycle/node)")
# plt.ylabel("Average Packet Latency (cycles)")
# plt.title("8×8 Torus Topology – Latency vs Offered Load")
# plt.legend()
# plt.grid(True, alpha=0.3)
# plt.tight_layout()
# plt.show()

import matplotlib.pyplot as plt

# Data from your latest table
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

# Plot stable data
plt.plot(torus_transpose_rates, torus_transpose_lat, marker="o", label="Torus – Transpose")
plt.plot(torus_uniform_rates, torus_uniform_lat, marker="s", label="Torus – Uniform")

# Mark unstable points (just as X markers near top)
plt.scatter(transpose_unstable, [500]*len(transpose_unstable), 
            color="red", marker="x", label="Transpose unstable")
plt.scatter(uniform_unstable, [500]*len(uniform_unstable), 
            color="purple", marker="x", label="Uniform unstable")

# Formatting
plt.xlabel("Injection Rate (packets/cycle/node)")
plt.ylabel("Average Packet Latency (cycles)")
plt.title("8×8 Torus Topology – Latency vs Offered Load")
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()