function [f] = labelFigAud(k,wavfile,s,u,uwav,bpf,fs)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
  figure(1)
  N = length(s);   ks = 1:N; kw = 1:length(uwav);


  subplot(321); plot(1000*kw/(2*fs),uwav,'.-r');grid;
  title([wavfile ' ' num2str(k)],'interpreter','latex');
  xticks([0 50 100 150]);
  xticklabels({'0','50mS','100mS','150'});
  ylabel(' Amplitude ','interpreter','latex');
  %xlabel(' Time in m Seconds ','interpreter','latex');
  [sxw phiu fw] =Spk(uwav,1);
  [su phiu f] =Spk(u,1);  [sx phiu f] =Spk(s,1); 
  [pk ind] = max(sx); fn = ind/N; X=[f(ind) f(ind)]*fs/1000; Y =[pk 0];

  subplot(322); plot(fw*fs*2/1000,sxw,'.-b');grid;
  title(' Voice Spectrum ','interpreter','latex');
  xticks([bpf(1)/1000 bpf(2)/1000 3 4])
  xticklabels({'0.1','1kHz','3kHz','4'})
  ylabel(' Amplitude ','interpreter','latex');
  %xlabel(' kHz ');
  subplot(323); plot(1000*ks/fs,s,'.-r');grid;
  title(['NB Signal ' num2str(fs*fn,4) ' Hz'],'interpreter','latex');
  xticks([0 50 100 150]);
  xticklabels({'0','50mS','100mS','150'});
  %xlabel(' Time in m Seconds ','interpreter','latex');
  subplot(324); plot(f*fs/1000,sx,'.-b',f*fs/1000,su,'-.r',X,Y,'o-k');grid;
  xticks([bpf(1)/1000 0.5 bpf(2)/1000 2]);
  xticklabels({'0.1','0.5kHz','1kHz','2kHz'});
  title(['Pitch Spectrum ' num2str(bpf(1)) ' to ' ... 
      num2str(bpf(2)) ' KHz'],'interpreter','latex');
end