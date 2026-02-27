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
function [] = labelMu211(muDoas,mu,phi,max1,max2,phase)
%[] = labelMu211(muDoas,mu,phi,max1,max2,phase) Summary of this function goes here
%   Detailed explanation goes here
            xa =[phi(95) phi(90)]; ya = [mu(95)+1 mu(90)];
            [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
            hT = annotation('textarrow',xaf,yaf, ...
                'String','Spectrum $J(\varphi)$','color', ...
                'blue','LineStyle','-.','interpreter', 'latex');
            hT.TextBackgroundColor = 'yellow';
            t=text(phi(100)-30,mu(100)+1.8,'MUSIC','interpreter', 'latex');
            t.BackgroundColor ='yellow';
            
            xa =[phase(1)-40 phase(1)]; ya = [max1+0.5 max1];
            [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
            hT = annotation('textarrow',xaf,yaf,'String', ...
                ['$\varphi_1$ = ' num2str(phase(1),4) '$^o$'], ...
                'color','black','LineStyle','-.','interpreter', 'latex');
            hT.TextBackgroundColor = 'yellow';

            xa =[phase(2)+60 phase(2)]; ya = [max2+0.25 max2];
            [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
            hT = annotation('textarrow',xaf,yaf,'String', ...
                ['$\varphi_2$ = ' num2str(phase(2),4) '$^o$'],...
                'color','black','LineStyle','-.','interpreter', 'latex');
            hT.TextBackgroundColor = 'yellow';

            axes('pos',[.085 .65 1.4 .27]);
            imshow('closeDoa.jpg');
end