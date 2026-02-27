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
function [] = labelDoa(theta,thetaEst,snr,N,dbyl)
%[] = labelDoa(theta,thetaEst) Summary of this function goes here
%   Detailed explanation goes here
p = polyfit(thetaEst,theta,1);
thetaHat = p(1)*thetaEst + p(2);
ek = (theta-thetaHat); 
sigek = std(ek); muek = mean(ek);
if (abs(muek) < 1e-5) muek = 0; end;
[z,x,y]=pdf_y(ek,40);
subplot(323);plot(thetaHat,ek);grid;
ylabel('Error $e=\theta - \tilde{\theta}$','interpreter','latex');
xlabel('DOA $\hat{\theta}^\circ$ ','interpreter','latex');
s = [' ${\tilde\theta}=$ ' num2str(p(1),4) '$\hat{\theta}+$ ' ... 
    num2str(abs(p(2)),4) ' ($d_\lambda$ ' num2str(dbyl,3) ')'];
title(s,'interpreter','latex');
subplot(324);plot(x,y,'.-r',x,z,'-.b');grid;
ylabel('probability of $e$','interpreter','latex');
xlabel('$\hat\theta - \tilde{\theta}$','interpreter','latex');
title(['$e_{\theta}$ with $\sigma$ ' num2str(sigek,3) ...
    '\% and $\mu$ ' num2str(muek,3) '\%'],'interpreter','latex');
s=['PDF $\mu$ ' num2str(muek,3) ' and $\sigma$ ' num2str(sigek,3)];
title(s,'interpreter','latex');
xticks([-0.5 -sigek muek sigek 0.5]);
xticklabels({'-0.5','-\sigma','\mu','\sigma','0.5'});
%.... Normal Distribution
ind=20; x1m = z(ind);
xa =[x(ind+10) x(ind)]; ya = [0.8*x1m x1m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s = ['$N(\mu,\sigma^2)$'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
end