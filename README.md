# Circuits Solver

## Project background:

This is practice project to implement knowledge of courses of first semister in `Alexandria University-FOE-CSED` that our `Dr.Hicham Elmongui` suggested.

It implements knowledge of circuits,programming and linear algebra.


## Project target:

Solve any electric circuit knowing its components.

## Features:
- Get voltage of any node in circuit
- Get voltage difference of any two nodes
- Get current of any branch

## Assumtions:
- If no ground then the ground will be in node 1
- No invalid circuits(ground conflicts, battary conflicts..etc)
- No invalid input

## How to use:
- clone repo
- run main.exe
- follow instructions in program

## Technical overview:
- Use nodal analysis to solve the circuit:
I used nodal analysis because it is easier to implement and to solve
- To get super nodes I used dfs to get the tree of battaries and consider it as one node
- After getting equations of nodal analysis solve it using gauss elemination to get the volt of each node
- To get current of a branch if it has resistor then use V/R law
- To get current of a branch if it has battary then go throw all branches take each branch and get its current by kcl of one of its two nodes such that the node all its branches are known current,repeat this process until no more unknown current.



