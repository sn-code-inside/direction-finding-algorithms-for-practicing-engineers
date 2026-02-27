function [] = labelFigMu(doa1,sz,doa,muSpk,dbyL)
%[] = labelFig1(doa1,sz,doa,muSpk,dbyL) Summary of this function goes here
%   Detailed explanation goes here
  figure(1)
  %N = length(s);   ks = 1:N; kw = 1:length(uwav);
    
  doaout = -doa; 
  numberOfSamples = length(muSpk);
  phi = linspace(-180, 180, numberOfSamples);
 
  sth = phi/(360*dbyL);
  ind = find(abs(sth) < 1.0);
  vMuSpk = muSpk(ind);
  theta = -asind(phi(ind)/(360*dbyL));

  % subplot(321); plot(kw,uwav,'.-r');grid;
  % title([wavfile ' ' num2str(k)]);
  % [sxw phiu fw] =Spk(uwav,1);
  % [su phiu f] =Spk(u,1);  [sx phiu f] =Spk(s,1); 
  % [pk ind] = max(sx); fn = ind/N; X=[f(ind) f(ind)]*fs/1000; Y =[pk 0];
  % 
  % subplot(322); plot(fw*fs*2/1000,sxw,'.-b');grid;
  % title(' Voice Spectrum ');
  % xticks([0.9 1 1.1 2 4])
  % xticklabels({'','1Khz','','2','4'})
  % %xlabel(' kHz ');
  % subplot(323); plot(ks,s,'.-r');grid;
  % title(['NB Signal 0.9 to 1.1 KHz;']);
  % subplot(324); plot(f*fs/1000,sx,'.-b',f*fs/1000,su,'-.r',X,Y,'o-k');grid;
  % xticks([0.5 0.9 1.1 1.5])
  % xticklabels({'0.5Khz','','','2Khz'})
  % title(['Peak ' num2str(fs*fn,4) ' Hz']);
  %subplot(312);plot(ks,real(A(1,:)),'.-r',ks,real(A(4,:)),'.-b');grid;
  %title([' phase in the data look matrix ' num2str(sz)]);
%  subplot(313);plot(phi,muSpk,'.-b');grid;
  subplot(313);plot(theta,vMuSpk,'.-b');grid;
  xlabel(' DOA in Degrees ','interpreter','latex'); 
  ylabel(' $J(\theta)$ ','interpreter','latex');
  title(['Est ' num2str(-doa) ' True ' ... 
  num2str(doa1) ' $\frac{d}{\lambda}$ ' num2str(dbyL)],'interpreter','latex');
end