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
clc; clear all;
close all;
theta = 5; sig = 0.1; bins = 50;
n = 1000; x=theta+sig*randn([1 n]);
[Z,X,Y]=pdf_y(x,bins); tmax = 0.1;
t = linspace(0,tmax,n);

xa =[0 tmax+max([max(Y) max(Z)])]; xa(2) = 1.05*xa(2);
ya = [ theta theta ];

subplot(211);
plot(t,x,Y+tmax,X,'bo',Z+tmax,X,'.-k');grid
xticks([t(1) t(400) t(900) 0.1 0.12 0.14 0.16 0.18]);
xticklabels({'0','k = 400','900', '0','0.02','0.04','0.06','0.08'});


%Figure contains an axes object. The axes object contains an object of type line.
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('arrow',xaf,yaf,'color','black','LineStyle','-.');

xa =[0.13 0.13]; ya =[theta+sig theta-sig];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('doublearrow',xaf,yaf,'color','black','LineStyle','-.');

text(0.122,theta+0.1*sig,"2\sigma",AffectAutoLimits="on")


xa =[0.123 Z(bins-10)+tmax]; ya = [theta-2*sig X(bins-10)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','probability density function','color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';

xa =[t(250) t(500)]; ya = [theta-3*sig x(500)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','$\hat\theta_k$','interpreter','latex','color','red','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';




xa =[0 0.16]; ya = [theta+sig theta+sig];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('line',xaf,yaf,'color','red','LineStyle','-.');
xa =[0 0.16]; ya = [theta-sig theta-sig];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('line',xaf,yaf,'color','red','LineStyle','-.');


ylabel('$\hat\theta$','interpreter','latex');
xlabel(' sample number k');

