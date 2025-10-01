import matplotlib.pyplot as plt

# Data from your table
sample_size = [10, 100, 10000, 1000000, 10000000, 100000000]
pi_estimate = [3.2000000000, 3.2800000000, 3.1572000000, 
               3.1431400000, 3.1415160000, 3.1416651600]

# Plot
plt.figure(figsize=(8,6))
plt.plot(sample_size, pi_estimate, marker='o', linestyle='-', color='orange', label="Estimated π")
plt.axhline(y=3.1415926536, color='r', linestyle='--', label="True π")

# Log scale for x-axis
plt.xscale("log")
plt.xlabel("Number of Points (log scale)")
plt.ylabel("Estimated π Value")
plt.title("Monte Carlo π Estimation: Number of Points vs π Values")
plt.legend()
plt.grid(True, which="both", linestyle="--", alpha=0.6)

plt.show()