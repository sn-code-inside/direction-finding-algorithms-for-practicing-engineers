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
function [] = label311xDot(Ek)
%[] = label311xDot(Ek) Summary of this function goes here
%   Detailed explanation goes here
xdotProduct = Ek(3,:);  K =0:length(xdotProduct)-1;
subplot(311);plot(K,xdotProduct,'.-r');grid
title('The Dot Product ${\bf{x}}^T_k \hat{ {\bf{x}} }_k $',...
    'interpreter','latex');
ylabel('${\bf{x}}^T_k \hat{ {\bf{x}} }_k $','interpreter','latex');
xlabel('Iterations $k$','interpreter','latex');
%.... step size
s = ['$\left\{\frac{1}{g_k}\right\} - 1$'];
ind = 2;
  xa = [K(ind+10) K(ind)]; 
  ya = [xdotProduct(ind) xdotProduct(ind)]; 
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',s,'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
% .. convergence parameter 
mu = mean(xdotProduct(25:50));
sig = std(xdotProduct(25:50));
s1 =[' at convergence $\sigma=$ ' num2str(sig,'%2.2e')...
    ' $\mu$ ' num2str(mu,'%2.2e')];
ind = 2;
  xa = [K(ind+10) K(30)]; 
  ya = [xdotProduct(ind) xdotProduct(30)]; 
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',s1,'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
end