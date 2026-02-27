  %Usage Error Parameters Left Hand Side = 0(4) .. Right Hand Side = 0(4) 
  %updated on 11th Jan 2025 @ 9:00am Hyderabad TG
  clc; clear all;
  close all;
  DOAS =[20, -35, 30]; POWS=[1 1 1];
  muSamples = 90;
  snapShots = 128; NumOfElements =6;
  std = 0.1; SamplesPerCycle = 8;
  D = 2;  dbyl = 0.5;
  rcA =[snapShots NumOfElements];
  [A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
  [muSpk doa En eV] = gMusic(D,dbyl,muSamples,A);
  doas =[sort(DOAS(1:D))' sort(doa)']';
  phi = linspace(-180, 180, muSamples);
  theta = asind(phi/180);
  omega = linspace(-pi,pi,muSamples);

for k=1:NumOfElements-D
e = En(k,:); %eC = e.*conj(e); 
    if (k==1)
    m = abs(freqz(e,1,omega)); mE(k,:) = m;else
    m = m + abs(freqz(e,1,omega));
    mE(k,:) = m; 
    end;
end
%  rA = angle(r)*180/pi; rV = abs(r); A = [rA' rV'];
  delr = 0.2;
  B = rootMusic(En,delr); rVn = B(:,2); rAn = B(:,1);
  t=asind(rAn/180);
  subplot(311); plot(phi,m,'o',phi,1./muSpk,'.-r');grid;
  title(num2str(doas,4),'interpreter','latex');
  subplot(312); plot(theta,mE,t,rVn,'o');grid;
  yticks([0 1 ceil(max(max(mE)))]);
  subplot(313); plot(phi,mE,t,rVn,'o');grid;
  yticks([0 1 ceil(max(max(mE)))]);


  