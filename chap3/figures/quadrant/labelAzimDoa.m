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
function [] = labelAzimDoa(Phi,phi)
%[] = labelAzimDoa(Phi,phi) Summary of this function goes here
%   Detailed explanation goes here
thetaC = Phi(:,1); 
thetaA = Phi(:,2);
thetaB = Phi(:,3);
subplot(311); plot(phi,thetaC,'.-r',phi,thetaB,'.-b',phi,thetaA,'.-k');grid;
xlabel('Azimuth Angle $\theta^\circ$','interpreter','latex');
ylabel('$\theta_a$,$\theta_b$,$\theta_c$','interpreter','latex');
title(' Three Element DF System','interpreter','latex');
yticks([-90 0 90]);
xticks([-180 -120 -90 -60 0 60 90 120 180]);
%....thetaC
ind=270; x1m = thetaC(ind);
xa =[phi(ind) phi(ind)]; ya = [-15 x1m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s = ['$\theta_c$'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%....thetaA
ind=330; x1m = thetaA(ind);
xa =[phi(ind) phi(ind)]; ya = [-30 x1m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s = ['$\theta_a$'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%....thetaB
ind=210; x1m = thetaB(ind);
xa =[phi(ind) phi(ind)]; ya = [-30 x1m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s = ['$\theta_b$'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
end