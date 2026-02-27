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
function [X,Y] = plotPeaks(muSpk,theta,D,doa)
%[] = plotPeaks(muSpk,theta) Summary of this function goes here
%   Detailed explanation goes here
  [pk ind] = findpeaks(muSpk);
  [pks indx] = sort(pk,'descend'); 
  Pk = pks(1:D); pksInd = ind(indx(1:D));
  X =[doa' doa']; Y =[Pk'*0 1.2*Pk'];
  hold on; plot(theta(pksInd),Pk,'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
end