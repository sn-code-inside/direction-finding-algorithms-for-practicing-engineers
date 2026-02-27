function [] = label211(muSpk,fs,B,dbyl,doa)
%[] = label211(muSpk,fs,B,dbyl) 
%   Summary of this function goes here
%   Detailed explanation goes here
%{
    Copyright (c) 2025 Dr. Venkata Ranga Rao Kaluri, Visiting Scholar, ICDT
    Department of Computer Science and Engineering,
    The Ohio State University, Columbus, OH, United States
    Contact: kaluri@ieee.org

    This code is provided for academic and illustrative purposes only,
    as part of the book titled "Direction Finding Algorithms for Practicing Engineers,"
    published by Springer Nature.
    The author assumes no responsibility or liability for any outcomes
    resulting from the use of this code.
    All rights reserved. Unauthorized reproduction or distribution is prohibited.
%}
u = B(:,1);
delt = 1/fs; phimax = dbyl*360;
numberOfSamples = length(muSpk); 
phi = linspace(-180,180,numberOfSamples);
indA = find(phi > phimax); e1 = indA(1);
indB = find(phi > -phimax); s1 = indB(1);
phiL = max([phi(s1) phi(e1)]);
phiPeak = phimax*sind(doa);
X =[phiPeak phiPeak]; Y = [0 max(muSpk)];

figure(2);
subplot(211);plot(phi(1:s1),muSpk(1:s1),'.-r', ...
phi(s1:e1),muSpk(s1:e1),'.-b', ...
phi(e1:numberOfSamples),muSpk(e1:numberOfSamples),'.-r', ...
phi(s1), muSpk(s1),'ok',phi(e1), muSpk(e1),'ok',X,Y,'.-r'); 
grid;

xlabel(' $\varphi$ ','interpreter','latex'); 
ylabel('$J(\varphi)$','interpreter','latex');
title('6 ULA g-MUSIC Spectrum for ${\bf{S}}_{k=100}$','interpreter','latex' );
xticks([-150 -100  -41 0 41 100 150]);
xticklabels({'-150^o','-100^o','-41^o','0^o',...
   '41^o','100^o','150^o'});
% arrow for available phase
xa(2) = phi(e1-20);   xa(1) = phi(e1-5);
ya(2) = muSpk(e1-20); ya(1) = muSpk(e1)*3;
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ... 
['$\pm 360(\frac{d}{\lambda})$ = (' num2str(-phiL,2) '$^o$ ' ...
num2str(phiL,2) '$^o$) $\varphi$ range'],...
'Interpreter','latex','color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
% arrow for gFK phase
xa(2) = phiPeak;   xa(1) = -60;
ya(2) = 0.3; ya(1) = 0.3;
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ... 
['gFK $\varphi$ = ' num2str(phiPeak,4) '$^o$ '],...
'Interpreter','latex','color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';



end