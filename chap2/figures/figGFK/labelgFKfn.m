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
function [] = labelgFKfn(fn,peak,rcA,S,b,A1,Fn)
%labelgFKfn(fn,peak,rcA,S,A,b,Fn) Summary of this function goes here
%   Detailed explanation goes here
fpk = mean(fn'); fPk =[fpk' fpk'];
Pks =[peak 0*peak];
X = S(:,1); m = abs(X); f = linspace(0,1,rcA(1)); 
% Polar 
theta = -angle(b(1,:)); r = abs(b(1,:));
Theta =[theta' theta'*0]; R =[r' r'*0];
subplot(222);polarplot(Theta',R','-.',theta,r,'o',...
    'MarkerSize',4,'MarkerFaceColor','b');
if (abs(theta(1)) < .001 ) theta(1) = 0; end;
s1 =['$\varphi=$ (' num2str(theta*180/pi,3) ')$^o$'];
title(s1,'interpreter','latex');
thetaticks([0 90 180]);
thetaticklabels({'0','90','180'});
rticks([0.5 1]);
subtitle(['gFK phasors'],"Position",...
       [270,1.4],"HorizontalAlignment",...
       "center",'color','black','interpreter', 'latex')
%............
[a,ind] = max(m); s=ind-15; e = ind+15;
subplot(221); plot(f(s:e),m(s:e),'.-r',fPk(1,:)',Pks(1,:)','-ob');grid;
hold on;
plot(Fn,A1,'o-b','MarkerSize',2,'MarkerFaceColor','b'); hold off;
ylabel('J(f)','interpreter', 'latex');
% FFT Peak
xa = [f(ind+5) f(ind)]; 
ya = [m(ind) m(ind)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','FFT peak','color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
% gFK peak
xa = [f(ind-5) fPk(1,1)]; 
ya = [Pks(1,1)*0.8 Pks(1,1)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','gFK peak','color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';


subplot(413); plot(Fn,A1,'o-r','MarkerSize',4,...
    'MarkerFaceColor','b');grid; hold on;
fftPkF =[f(ind) f(ind)]; fftPk=[0 m(ind)];
plot(fftPkF,fftPk,'o-b',fPk(1,:)',Pks(1,:)','^-b'); hold off;
xlabel('f value around FFT peak','interpreter', 'latex');
ylabel('J(f)','interpreter', 'latex');
% peaks
% FFT Peak
xa = [f(ind)*0.995 f(ind)]; 
ya = [m(ind) m(ind)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','FFT peak','color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%gFK peak
xa = [fPk(1,1)*1.003 fPk(1,1)]; 
ya = [Pks(1,1)*0.8 Pks(1,1)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','gFK peak','color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

end