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
function [] = label312(phi,theta,s1,e1,p1,dbyl1)
%[] = label311(phi,theta,s1,e1,p1,dbyl1) Summary of this function goes here
%   Detailed explanation goes here
xlabel(' Phase $\varphi^o$ ','Interpreter','latex');
ylabel(' DOA $\theta^o$ ','Interpreter','latex');

xa(2) = phi(2,s1-10); xa(1) = xa(2)*1.5;
ya(2) = theta(2,s1-10); ya(1) = -ya(2)*0.5;
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ...
 [ '$\frac{d}{\lambda}$ = ' num2str(dbyl1)], ...
 'Interpreter','latex','color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
% vertical lines 1
xa(1) = phi(1,s1); xa(2) = xa(1);
ya(1) = theta(1,s1); ya(2) = 90;
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('line',xaf,yaf);
% vertical lines 2
xa(1) = phi(1,e1); xa(2) = xa(1);
ya(1) = theta(1,e1); ya(2) = 90; mid = (ya(2)+ya(1))/2;
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('line',xaf,yaf);
% arrow for linear part left
xa(2) = phi(1,e1); xa(1) = -15;
ya(2) = mid*2; ya(1) = ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ...
 ['$\theta \approx $ ' num2str(p1(1),2) '$\varphi$'] , ...
 'Interpreter','latex','color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
% arrow for linear part right
xa(2) = phi(1,s1); xa(1) = 40;
ya(2) = mid*2; ya(1) = ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('arrow',xaf,yaf, ...
 'color','blue','LineStyle','-.');
end