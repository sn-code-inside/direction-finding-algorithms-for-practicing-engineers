    clc; clear all
    close all;
    dbylambda = 0.5;
    N = 180; m = 5; aspectRatio = 0.685;
    K=1:m; thetaQ = 2; A = 2*pi*dbylambda;
    phiQ = A*sin((thetaQ*pi/180));
    b1 = exp(i*K*phiQ);  b2 = exp(-i*K*phiQ);
    Phi = linspace(-pi,pi,N);
    theta = asin(Phi/A)*180/pi; % rehash phase to doa
    location = 80; std = 0.1;
%   phase sepctrum    
    h1 = freqz(b1,1,Phi); m1 = abs(h1); noise1 = std*randn(size(m1)); 
    m1 = m1 + noise1;
    snr1 = 10*log10( var(abs(h1))/var(noise1) );
    J1 = m1/max(m1);
    h2 = freqz(b2,1,Phi); m2 = abs(h2); noise2 = std*randn(size(m2));
    m2 = m2 + noise2;
    snr2 = 10*log10( var(abs(h2))/var(noise2) );
    J2 = m2/max(m2);
    snr = (snr1 + snr2)*0.5;
    figure(1);
    delta = J1-J2;del = delta(59:122);
    delth = theta(59:122);
    delx = linspace(-4.3,4.3,length(del));
    deltaJ = J1-J2; sumJ = J1+J2;
    [pksum lnpk] =findpeaks(-sumJ);
    [pn1 ln1] = findpeaks(pksum); %[pnx indx] = sort(pn,'descend');
    ln = lnpk(ln1);
    indP = find(theta(ln) > 0); s = ln(indP(1));
    indN = find(theta(ln) < 0); e = ln(indN(length(indN)));

    %%
    subplot(322); plot(theta,sumJ,'-.r');grid;
    title(' Squint Beam for Monopulse Radar ','interpreter','latex');
    subtitle(' sum output ','interpreter','latex');
    ylabel('$\sum$','interpreter','latex');
    JkApk = [sumJ(s) sumJ(e)]; thetaPk = [theta(s) theta(e)];
    hold on; plot(thetaPk,JkApk,'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
    xtik = sort([round(thetaPk,1) -80 0 80]);
    xticks(xtik);
    yticks([0 1.5]);
    %%
    subplot(324); plot(theta,deltaJ,delth,0.1632*atan(delx),'-.r');grid;
    title(' Difference output ','interpreter','latex');
    ylabel('$\Delta$','interpreter','latex');
    xticks(xtik);
    yticks([-0.2 0 0.2]);
    xlabel('Angle in Degrees','interpreter','latex');

    %%
    fn = 0.05;  Nt=16; Kt=0:Nt-1;
    uk = randn([1 Nt]); 
    r = 0.95; g =(1-r*r)*0.5; p =2*cos(2*pi*fn);
    mk = filter([1 0 -1]*g,[1 -r*p r*r],uk);
    mk = mk/max(abs(mk)); mk = mk*pi;
    nt = sin(0.01*pi*Kt/Nt);
    phaseNoise = 0.1*nt+0.06*uk;
    thetaA=35; 
    xk = cosd(thetaA)*cos(mk+phaseNoise);
    yk = sind(thetaA)*cos(mk);
    thetaX = atan2(yk,xk); rX = sqrt(xk.*xk + yk.*yk);
    figure(2);
    polarplot(thetaX,rX,'.-b');
    hold on; polarplot(thetaA*pi/180,1,'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
    rticks([0.5 0.9]);
    subtitle(['Adcock Watson Watt' ],...
    "Position",[270,1.25],"HorizontalAlignment",...
    "center",'color','black','interpreter', 'latex');
    thTik = sort([0:45:360 thetaA]);
    thetaticks(thTik);


    




