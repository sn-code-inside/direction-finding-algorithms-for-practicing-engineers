function [] = labelSubplot(sub,thetaPeak,phi,mIir,mFir,m)
%labelSubplot(phi,mIir,mFir,m) Summary of this function goes here
%   Detailed explanation goes here
phiPeak = 180*sind(thetaPeak);
subplot(sub); plot(phi,mIir,'-.r',phi,mFir,'.-b');grid;
title(['Beam with ' num2str(m,3) ' Real Coefficients $c_n$'],'interpreter','latex');
ylabel('$J(\varphi)$','interpreter','latex');
xlabel('Phase','interpreter','latex');
tiks = sort([20 60 120 180 round(phiPeak)]);
xticks(tiks);
% latex x-ticks
Ax = gca;
Ax.XAxis.TickLabels = {'$\frac{\pi}{9}$','$\frac{\pi}{3}$','$\varphi_p$', '$\frac{2\pi}{3}$','$\pi$'}; 
Ax.XAxis.TickLabelInterpreter = 'latex';
end