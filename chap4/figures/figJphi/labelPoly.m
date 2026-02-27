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
function [sp sr se] = labelPoly(En,NumOfElements,D,eV)
%[] = labelPoly(En,NumOfElements,D) Summary of this function goes here
%   Detailed explanation goes here
%  xLimits = get(gca,'XLim');  % Get the range of the x axis
%  yLimits = get(gca,'YLim');  % Get the range of the y axis
%  figure(2); subplot(311);xlim([xLimits]); ylim([yLimits]);
  %% steering vector
  sp =' ';
  for p=1:NumOfElements-D
  a=En(p,:); sp = rec2polar(a,sp,p);
  end
  sp =['\framebox{\begin{tabular}{llllll}' sp ' \end{tabular}}'];
  %text(-190,-1.6,sp,'interpreter','latex');
  
  %% roots of steering vector
  sr =' ';
  for p=1:NumOfElements-D
  a=roots(En(p,:));  sr = rootsInpolar(a',sr,p);
  end
  sr =['\framebox{\begin{tabular}{ll}' sr ' \end{tabular}}'];
  %text(-240,-3.2,sr,'interpreter','latex');
  % eigen values of the Hermitian
  se='';
  se = eigenV(eV,se,D);
  %text(-240,-3.2,se,'interpreter','latex');

end