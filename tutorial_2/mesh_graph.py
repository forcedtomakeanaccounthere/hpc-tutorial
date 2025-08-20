import matplotlib.pyplot as plt
import pandas as pd

# Replace with your Excel/CSV export
transpose = {
    "injection_rate": [0.001,0.002,0.00289,0.003,0.004,0.005,0.006,0.0065,0.007],
    "latency": [46.7477,48.0048,51.9104,52.6463,55.9598,62.828,72.8325,83.6003,133.808]
}

uniform = {
    "injection_rate": [0.002,0.0037,0.005,0.0058,0.007,0.0084,0.01,0.014,0.018,0.0197],
    "latency": [49.1242,52.6033,54.583,57.7188,60.0628,64.8398,72.3846,87.0083,48.9065,48.7971]
}

plt.figure()
plt.plot(transpose["injection_rate"], transpose["latency"], marker="o", label="Mesh – Transpose")
plt.plot(uniform["injection_rate"], uniform["latency"], marker="s", label="Mesh – Uniform")
plt.xlabel("Injection Rate (packets/cycle/node)")
plt.ylabel("Average Packet Latency (cycles)")
plt.title("8×8 Mesh Topology – Latency vs Offered Load")
plt.legend()
plt.grid(True, alpha=0.3)
plt.show()