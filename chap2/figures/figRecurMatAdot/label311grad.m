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
function [] = label311grad(Ek)
%[] = label311grad(Ek) Summary of this function goes here
%   Detailed explanation goes here
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(2);
gradJkNorm = Ek(2,:); K =0:length(gradJkNorm)-1;
subplot(311);plot(K,gradJkNorm,'.-r');grid
title('Gradient $\nabla J_k = 2e_k {\bf{x}}^T_k $',...
    'interpreter','latex');
ylabel('$|\nabla J_k|$','interpreter','latex');
xlabel('Iterations $k$','interpreter','latex');
%.... norm of gradient
s = ['$|\nabla J_k|$'];
ind = 2;
  xa = [K(ind+10) K(ind)]; 
  ya = [gradJkNorm(ind) gradJkNorm(ind)]; 
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',s,'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
  % .. convergence parameter 
mu = mean(gradJkNorm(25:50));
sig = std(gradJkNorm(25:50));
s1 =[' at convergence $\sigma=$ ' num2str(sig,'%2.2e') ...
    ' $\mu$ ' num2str(mu,'%2.2e')];
ind = 2;
  xa = [K(ind+10) K(30)]; 
  ya = [gradJkNorm(ind) gradJkNorm(30)]; 
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',s1,'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
end