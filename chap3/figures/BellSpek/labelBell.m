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
function [Pk fp t xz] = labelBell(K,Delt,x)
%[Pk fp t xz] = labelBell(K,Delt,x) Summary of this function goes here
%   Detailed explanation goes here
% bell signal
nZ = 1200;
Kz = K(1:nZ); xz = x(1:nZ);
yz = filter(0.1,[1 -0.9],xz.*xz); 
g = max(xz)/max(yz);
yz = yz*g; ind = find(yz > 0.02); ez = yz*0; ez(ind(1)) = 1.5*max(yz);
[sxZ,f] = Spk(xz,Delt); [Pk indx] = max(sxZ); fp = f(indx);
fn = fp*Delt; N = 1/fn;

t = Kz*Delt*1000; torg = Kz(ind(1))*Delt*1000;
subplot(221); plot(t,xz,t,yz,'.-r');grid;
hold on; 
plot([torg torg], [0 ez(ind(1))],'^-k'); 
hold off;
s =['$h(t)=A(t)$' num2str(Pk,2) ...
    '$\sin(2\pi $' num2str(fp,5) '$t + \varphi)$'];
title(s,'interpreter','latex');
xs = round(torg);
xticks([0 xs 300 400 500]);
xlabel(' $t$ in mS ','interpreter','latex'); 
ylabel(' $h(t)$','interpreter','latex');
% Envelop
[pke indxe] = max(yz);
xa = [t(indxe + round(0.25*indxe)) t(indxe)]; 
ya = [pke*1.5 pke];
s =['$A(t)$ Envelope of $h(t)$'];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',s,'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
% Carrier
xa = [t(indxe + round(0.6*indxe)) t(indxe)]; 
ya = [-pke*0.9 0];
s =['$\frac{1}{f_n}$=' num2str(N,3) ' Samples/Cycle'];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',s,'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

subplot(222); plot(f,sxZ);grid
xlabel('Freq in Hz','interpreter','latex'); 
ylabel(' $|H(\omega)|$ ','interpreter','latex');
s = [' DFT of $h(k\delta t)~\delta t=$' num2str(1000*Delt,3) 'mSec'];
title(s,'interpreter','latex')

% FFT peak
xa = [f(indx+round(indx*0.15)) fp]; 
ya = [Pk*0.6 Pk];
s =['$f_p=$' num2str(fp,5) 'Hz ($f_n$=' num2str(fn,4) ')'];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',s,'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
end