clc; clear all;
close all;
%aspectRatio = 0.685;
DOAS =[20, -35, 30];
D = 2; NumOfElements =5;
numberOfPhiSamples = 180;
% look matrix and gold-MUSIC
[muSpk,En,doa,A,eV] = rootMat(D ,NumOfElements,DOAS,numberOfPhiSamples);
doas =[sort(DOAS(1:D))' sort(doa)']';
Jphi = 1./muSpk; 
phi = linspace(-180,180,numberOfPhiSamples);
theta = asind(phi/180);
omega = linspace(-pi,pi,numberOfPhiSamples);

for k=1:NumOfElements-D
e = En(k,:); eC = e.*conj(e); 
    if (k==1)
    m = abs(freqz(e,1,omega)); mE(k,:) = m; r = roots(e)'; else
    m = m + abs(freqz(e,1,omega));
    mE(k,:) = m; r = [r roots(e)'];
    end;
end
B = rootMusic(En); rVn = B(:,2); rAn = B(:,1);
t=-asind(rAn/180); a = B(:,3);



subplot(311); plot(theta,1./m,'o',theta,muSpk,'.-r');grid;
title(num2str(doas,4),'interpreter','latex');
subplot(312); plot(theta,mE,t,rVn,'o');grid;
yticks([0 1 ceil(max(max(mE)))]);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
H = A'*A; H=H/max(max(abs(H)));
[Jn,Jt] = phiSpek(H,En,numberOfPhiSamples,eV);
subplot(313); plot(-theta,Jn');grid;


