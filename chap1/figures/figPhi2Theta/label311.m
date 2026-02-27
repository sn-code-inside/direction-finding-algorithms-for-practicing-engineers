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
function [] = label311(phi,theta,s2,e2,p,dbyl)
%[] = label311(phi,theta,s2,e2,p,dbyl) Summary of this function goes here
%   Detailed explanation goes here
ylabel(' DOA $\theta^o$ ','Interpreter','latex');
title(' Phase to DOA mapping function ','Interpreter','latex');
% text arrow for dbyl = 0.5
xa(2) = phi(1,s2-10); xa(1) = xa(2)*1.1;
ya(2) = theta(1,s2-10); ya(1) = -ya(2)*0.5;
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ...
 ['$\frac{d}{\lambda}$  = ' num2str(dbyl)], ...
 'Interpreter','latex','color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
% vertical lines 1
xa(1) = phi(1,s2); xa(2) = xa(1);
ya(1) = theta(1,s2); ya(2) = 90;
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('line',xaf,yaf);
% vertical lines 2
xa(1) = phi(1,e2); xa(2) = xa(1);
ya(1) = theta(1,e2); ya(2) = 90; mid = (ya(2)+ya(1))/2;
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('line',xaf,yaf);
% arrow for linear part left
xa(2) = phi(1,e2); xa(1) = -15;
ya(2) = mid*2; ya(1) = ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ...
 ['$\theta \approx $ ' num2str(p(1),2) '$\varphi$'] , ...
 'Interpreter','latex','color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
% arrow for linear part right
xa(2) = phi(1,s2); xa(1) = 40;
ya(2) = mid*2; ya(1) = ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('arrow',xaf,yaf, ...
 'color','blue','LineStyle','-.');
end