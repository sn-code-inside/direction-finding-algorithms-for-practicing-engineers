clc; 
clear all; close all;
r=0.95; thetaPeak = 36; dbyl = 0.5;
phiPeak = 360*dbyl*sind(thetaPeak);
nSamples = 180; 

m=51; 
%% m = 51
[phi,mFir,mIir] = Iir2Fir(thetaPeak,dbyl,r,m);
labelSubplot('321',thetaPeak,phi,mIir,mFir,m);
subtitle(['$\frac{d}{\lambda}$ ' num2str(dbyl) ' $\varphi_p$=' ...
    num2str(180*sind(thetaPeak),3) '$^\circ$ pole $r=$' num2str(r,2)],'interpreter','latex');

% FIR filter
[maxMi indx] = max(mFir);
xa = [phi(indx-4)-30 phi(indx-9)]; 
ya = [mFir(indx-4) mFir(indx-9)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['FIR Filter'],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

%% m = 21
m=11; 
[phi,mFir,mIir] = Iir2Fir(thetaPeak,dbyl,r,m);
labelSubplot('322',thetaPeak,phi,mIir,mFir,m);
subtitle(['DOA at $\theta_p$=' num2str(thetaPeak,3) ...
    '$^\circ$~2\pi\frac{d}{\lambda}$'],...
    'interpreter','latex');

% IIR filter
[maxMi indx] = max(mIir);
xa = [phi(indx-3)-30 phi(indx-3)]; 
ya = [mIir(indx-3) mIir(indx-3)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['IIR Filter'],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';



