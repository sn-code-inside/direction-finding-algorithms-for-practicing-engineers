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
function [] = labelPhiFn(phiV,Fn,rmin,rmax,invalid)
%[]=labelPhiFn(phiV,Fn,rmin,rmax) Summary of this function goes here
%   Detailed explanation goes here
subplot(211); plot(phiV,Fn,'+k',360,0.51,'.');grid;
title(['Valid $f_n$ and $\varphi$ Region for ' num2str(rmin,3) ...
    '$< |r| <$' num2str(rmax,3)],'interpreter','latex');
xlabel('Phase Shift $\varphi^o$ ','interpreter','latex');
ylabel('$f_n$ ','interpreter','latex');
xticks([0    45    90   135   180   225   270   315   360]);
yticks([0 0.1 0.2 0.3 0.4 0.5]);
valid = 100 - invalid;
%.... Not Valid
%.... four-element vector of the form [x y w h]
xa =[225 300]; ya = [0.2 0.3];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
box =[xaf(1) yaf(1) xaf(2)-xaf(1) yaf(2)-yaf(1)];
hT = annotation('textbox',box,'String',['$r$ Not Valid '],'color','red','interpreter', 'latex');
hT.BackgroundColor = 'yellow';

%....Valid
%.... four-element vector of the form [x y w h]
xa =[85 175]; ya = [0.1 0.2];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
box =[xaf(1) yaf(1) xaf(2)-xaf(1) yaf(2)-yaf(1)];
hT = annotation('textbox',box,'String',...
    ['$r$ Valid ' num2str(valid,3) '\%'],'interpreter', 'latex');
hT.BackgroundColor = 'yellow';
%....Valid
%.... four-element vector of the form [x y w h]
xa =[20 75]; ya = [0.3 0.4];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
box =[xaf(1) yaf(1) xaf(2)-xaf(1) yaf(2)-yaf(1)];
hT = annotation('textbox',box,'String',['$r$ Valid '],'interpreter', 'latex');
hT.BackgroundColor = 'yellow';
end