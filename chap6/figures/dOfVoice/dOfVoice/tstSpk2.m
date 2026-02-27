clc; clear all;
close all;
wavfile = 'sr2T.wav';
dbyl = 0.5;
ula = 6; doa2 = -30;
doa1 = -85;
MintwoPowerM = 10;
bpf =[100 1000];
waveletWindow = 64;
pA = zeros([1 512]);
indx = 1;
for k=0:100
  [u,s,flag,fs,A,dbyL,uwav,pitch,At] = xTrktNb(wavfile,k,MintwoPowerM,ula,doa2,bpf);
  %...................
  if ( flag > 0 )
    [x,sp,z,pC,bins,pg] = voice2pitch(u,3,k,waveletWindow); p = real(pC);
    if (length(bins) > 1)
        b = pg(:,2);
        for m = 1:length(u)
        a = p(:,m); g = sum(a)/max(a);   pA(m) = a'*b/g;
        pA(m) = (pA(m)/length(u))*fs;
        end
    end

    [muSpk doa En SNR] = gMusik(1,dbyL,A'); sz = size(A);
    if ( k==82) 
    fn = labelFigAud(k,wavfile,s,u,uwav,bpf,fs);
    labelFigMu(doa2,sz,doa,muSpk,dbyL);
    if (length(bins) > 1) labelPitch(u,sp,pg,fs,wavfile,pA,p,k,fn,bpf); end;
    figure(3);
    kw = 1:length(uwav);
    subplot(211); plot(1000*kw/(2*fs),uwav,'.-r');grid;
    title([wavfile ' ' num2str(k)],'interpreter','latex');
    xticks([0 50 100 128 150]);
    xticklabels({'0','50mS','100mS','128mS','150'});
    ylabel(' Amplitude ','interpreter','latex');
    pause(1); 
    end;

    pich(indx) =mean(pA); doaEst(indx) = doa; 
    indx = indx + 1;
  end;
  
  %........................................................................
end
    labelFigDbyL(doaEst,pich)
