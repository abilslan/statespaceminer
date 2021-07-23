Win32 C program for statespace analysis of synchronous;y updating random Boolean network models, created in Dev-C++ IDE.
This was written some time before I was sold on the importance of commenting (~2012), so the code itself may be less than illuminating. The expected use was for RBN analysis of biological pathways and to assist portability of network models between applications. We used this in the paper:

Bilsland et al (2014), Mathematical model of a telomerase transcriptional regulatory network developed by cell-based screening: analysis of inhibitor effects and telomerase expression mechanisms. PLoS Comput Biol; 10(2):e1003448.

The code wasn't originally published with the paper, although the binary was. I haven't looked at this in years, but it built successfully in codeblocks on 22/7/21. Also included here is the telomerase reverse transctiptase (TERT) transcriptional network that we identified by cell-based screening. It is provided in Pajek format, along with vertex IDs, and was used to produce several of the figures in the paper using node targeting options in the application.

Usage:
- The program is an interactive command-line application.
- The user simply selects actions to perform to initialise and perform RBN analysis from a series of menus.
- From the main menu, choose option 1 (network menu). Initialise a network randomly or loading from file. Accepted network file formats are Pajek .net adjacency matrix representation or Cytoscape format (but see below for comments on Cytoscape parsing).
- From the main menu, choose the menu 3 (rules menu). For simple analysis, threshold rules should be activated. These are simply:

![image](https://user-images.githubusercontent.com/75328354/126550851-d378edb4-3f07-405b-9452-2a52e30d0263.png)


- Where σj(t+1) is the t+1 state of node j, σi(t) is the current state of the node i, ωi,j is the interaction weight between nodes i, j (1 if the interaction is activating, −1 if repressive), and kj is the input-degree of the regulated node j. The threshold variable φ is zero by default.
- However, once rules are activated, the user has the option to control threshold and weight values at the node level if wanted.
- After rule activation, menu 4 (analaysis menu) allows calculation of the network state space and other properties. State space calculation is brute-force but DFS is used to find attractor states and basins of attraction after state space calculation. Other attractor state coherence metrics can also be computed in this menu.
- There are options to read and write out Pajek format network and partition files for further visual analysis.
- An E-Cell model format can also be written out for ODE modelling if real kinetic parameters are known about the network.
- Menu 5 (targeting menu) allows for constitutive knock-out or knock-in of nodes. After recalculation of statespace, effects on attractor states can be observed to model, eg, selective inhibiton.

NOTES:
- The cytoscape parsing functions are in the header file Cytoparser1.h. These were originally intended to allow network models developed in the Metacore/GeneGO pathway analysis platform to be imported and relied on a Cytoscape plugin maintained by GeneGO. However, support for this ended years ago and the plugin was withdrawn. I have not maintained the cytoscape format parser at all and in fact it seems to be throwing an error at the moment but the Pajek parser works.
