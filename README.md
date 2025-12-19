📘 Approximation Algorithms

This repository contains implementations of classical approximation algorithms for NP-Hard optimization problems. Written in C++, it serves as a practical codebase for students and developers to understand how theoretical approximation guarantees are realized in practice.

📁 Repository Structure

The project is organized by problem, with each directory containing the implementation for a specific algorithm:

Bin Packing/: Algorithms for the Bin Packing problem.

Knapsack/: Algorithms for the Knapsack problem (0/1 and fractional variants).

Max Cut/: Algorithms for the Maximum Cut problem in graphs.

Metric TSP/: Approximation algorithms for the Metric Traveling Salesperson Problem.

Set Cover/: Implementations for the Set Cover problem.

Steiner Tree/: Algorithms for the Steiner Tree problem in graphs.

Vertex Cover/: Classic algorithms (e.g., greedy, 2-approximation) for the Vertex Cover problem.

🛠️ Technology Stack

Language: C++ (100% of the repository)

Focus: Algorithmic clarity, correctness, and demonstrating approximation ratios.

🚀 Getting Started

Prerequisites

C++ compiler (g++ or compatible)

Basic knowledge of algorithms and data structures

Compilation and Execution

Clone the repository:

git clone [https://github.com/arjunaggarwaliit/Approximation-Algorithms.git](https://github.com/arjunaggarwaliit/Approximation-Algorithms.git)
cd Approximation-Algorithms


Navigate to a specific problem directory:

cd "Vertex Cover"  # or any other algorithm directory


Compile the C++ source files:

g++ -std=c++11 -o algorithm_name main.cpp  # adjust filename as needed


Run the executable:

./algorithm_name


📚 Algorithm Details

Problem

Approximation Ratio

Key Algorithm(s)

Complexity

Bin Packing

Various heuristics

First Fit, Best Fit, FFD

Varies

Knapsack

FPTAS

Dynamic Programming variants

$O(n/\epsilon)$

Max Cut

0.5-approximation

Random assignment, Local search

$O(m+n)$

Metric TSP

1.5-approximation

Christofides algorithm

$O(n^3)$

Set Cover

$\log n$-approximation

Greedy algorithm

$O(mn)$

Steiner Tree

2-approximation

Minimum Spanning Tree based

$O(n^2)$

Vertex Cover

2-approximation

Greedy matching-based

$O(E)$

📊 Sample Usage

Example: Vertex Cover

// Navigate to Vertex Cover directory and compile
cd "Vertex Cover"
g++ -std=c++11 -o vertex_cover vertex_cover.cpp

// Run with sample input
./vertex_cover < input.txt


🧪 Testing

Each implementation includes test cases demonstrating:

Correctness on sample inputs.

Approximation ratio verification.

Performance on different input sizes.

📖 References

Approximation Algorithms by Vijay V. Vazirani

Introduction to Algorithms (CLRS)

Research papers on specific approximation algorithms.

🤝 Contributing

Contributions are welcome! To contribute:

Fork the repository.

Create a feature branch (git checkout -b feature/algorithm-name).

Commit your changes (git commit -m 'Add new algorithm for...').

Push to the branch (git push origin feature/algorithm-name).

Open a Pull Request.
