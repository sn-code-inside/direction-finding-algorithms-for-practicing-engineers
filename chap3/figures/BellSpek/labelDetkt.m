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
function [] = labelDetkt(N,n,y,Delt,delt)
%[] = labelDetkt(y,N,Delt,delt) Summary of this function goes here
%   Detailed explanation goes here
% Detection
T =1:N; ind = 14;
s =round(0.1*n); e = s + 2^ind-1;
x = y(s:e); M = length(x); K=1:M; t=K*Delt;

nZ = 1200;
Kz = K(1:nZ); xz = x(1:nZ);
yz = filter(0.1,[1 -0.9],x.*x); 
g = max(x)/max(yz); threshold = 0.02;
yz = yz*g; ind = find(yz > threshold); ez = yz*0; 
ez(ind) = 1.2*max(yz);
subplot(211); plot(t,ez,'.-r',t,yz,'.b');grid;
xlabel(' $t=k\times\delta t$ in Seconds ','interpreter','latex'); 
title(['Envelop Detection $\sigma_k$ and $w_k$ using threshold ' ...
    num2str(threshold,3)],'interpreter','latex');
ylabel('$\sigma_k$ and $w_k$','interpreter','latex');
yticks([threshold 0.25 0.5]);
yticklabels({['\delta\sigma=' num2str(threshold,2)],'0.25','0.5'});
% energy
xa = [t(6000)*1.3 t(6000)]; 
ya = [0.38 yz(6000)];
s1 =['Envelop $\sigma_k$'];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',s1,'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
% Detection window
xa = [(e-s)*delt*3.2 t(500)]; 
ya = [0.5 ez(500)];
s1 =['Detection Window $w_k$'];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',s1,'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
end