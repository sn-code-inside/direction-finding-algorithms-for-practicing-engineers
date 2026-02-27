function [] = label211(A,rd)
%label211(A,rd) Summary of this function goes here
%   Detailed explanation goes here
Ar = real(A); Ai = imag(A);
K = 1:rd; fn = linspace(0,1,rd);
subplot(211); plot(K,Ar,K,Ai);
title('Temporal and Spatial Sampled Raw Data','Interpreter','latex');
ylabel('Amplitude','Interpreter','latex');
grid;
% fig number
%text(6,310,'\fbox{a}','Interpreter','latex','BackgroundColor','black','Color','white');
% bf{A}.
xa =[max(K)*1.1 max(K) ]; ya = [ 0 0 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String','$\bf{A}$');
hT.TextBackgroundColor = 'yellow';
% gFK.
xa =[max(K)*0.42 max(K)*0.42 ]; ya = [ -400 -1000 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String','gFK');
hT.TextBackgroundColor = 'yellow';
% Raw Data.
xa =[max(K)*0.73 max(K)*0.73 ]; ya = [ -100 -660 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String','Raw Data');
hT.TextBackgroundColor = 'yellow';
% arrow left.
xa =[max(K)*0.65 max(K)*0.46 ]; ya = [ -120 -300 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('arrow',xaf,yaf);
% kMusic.
xa =[max(K)*0.79 max(K)*0.87 ]; ya = [ -750 -800 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String','$\kappa$MUSIC');
hT.TextBackgroundColor = 'yellow';

% varphi.
xa =[max(K)*0.89 max(K)*0.89 ]; ya = [ -840 -1100 ];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String','$\varphi$');
hT.TextBackgroundColor = 'yellow';
end