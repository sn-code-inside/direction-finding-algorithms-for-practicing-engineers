% Author: Kaluri V. Ranga Rao
% Visiting Scholar, Department of Computer Science,
% The Ohio State University
%
% Copyright (c) 2025 Kaluri V. Ranga Rao
% All rights reserved.
%
% This code is part of the material for the book:
% "Direction Finding Algorithms for Practicing Engineers,"
% published by Springer Nature.
%
% This material is intended for academic and research purposes only.
clear all; close all; clc;
DOAS = [20, -35, 25];

POWS = [1, 1, 1];
std = 0.5;
D = 3; snapShots = 32;
NumOfElements = 31;
dbyl = 0.5;
SamplesPerCycle = 8;
numberOfRows = 10;
rcA = [snapShots NumOfElements];
[A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
[doas allDoas] = espritDoa(A,D); 
labelPolarEsprit(DOAS,doas,allDoas,rcA,SNR);
LatexFileMatrix('espritDoa.tex','$\theta$ Values',allDoas(:,1:8));



