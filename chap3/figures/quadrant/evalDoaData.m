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
function [Phi phi] = evalDoaData(thetaMax, kmax)
%[Phi phi] = evalDoaData(thetaMax, kmax) Summary of this function goes here
%  Detailed explanation goes here
phi = linspace(-thetaMax,thetaMax,kmax);
thetaC = azimuth2doa(phi);
thetaA = azimuth2doa(phi+60);
thetaB = azimuth2doa(phi-60);
%Phi =[(thetaA-thetaB)' (thetaB-thetaC)' (thetaC-thetaA)' phi'];
Phi =[thetaC' thetaB' thetaA'];
%labelAzimDoa(Phi,phi);
save("thetadata","Phi","phi");
end