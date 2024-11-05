# Summary
Algorithmic coding solution leveraging BFS to solve the Jane Street Puzzle for October 2024 \
https://www.janestreet.com/puzzles/knight-moves-6-index/

# Code
Simulation is done using BFS. I start from larger values of A,B, and C to avoid traversing super long paths. If the current sum ever exceeds 2048, we know this path is not valid and we can terminate.
Paths are outputted to a file, leaving the code running will yield many paths. The first valid path should appear within a few seconds. 

# Files
main.cpp is the solver, written in C++ for efficiency
verify.py takes any path and verifies that it is correct. Written in python for simplicity
