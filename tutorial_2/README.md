# 📊 Mesh vs Torus Topology Analysis & Interpretation

##  Comparison – Mesh vs Torus

| Aspect | Mesh | Torus |
|--------|------|-------|
| **Low-load latency** | Higher (45–60) | Lower (~30) |
| **Saturation threshold** | Very low (~0.007–0.008) | Much higher (~0.09–0.1) |
| **Stability under Uniform traffic** | Poor | Good |
| **Stability under Transpose traffic** | Poor (fails very early) | Better, but still fails sooner than uniform |
| **Overall** | Simpler, but not scalable | More resilient, better for high traffic |

---

## ✅ Final Interpretation

- **Mesh topology** is simple and works fine at **light loads**, but quickly saturates under stress, especially with long-distance traffic like transpose.  
- **Torus topology** is **superior in performance**:
  - Lower base latency  
  - Higher injection rate support  
  - More robust due to additional wrap-around connections  
- However, **both topologies eventually become unstable** when injection rate exceeds their capacity.  
- For **scalability in large NoCs**, **Torus is preferred over Mesh**.
