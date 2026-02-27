clc; clear all;
close all;
wavfile = 'nh2V.wav';
dbyl = 0.5;
ula = 3; doa2 = -30;
doa1 = -85;
MintwoPowerM = 12;
bpf =[100 1500];
indx = 1;
for k=0:110
  [u,s,flag,fs,A,dbyL,uwav,pitch,At] = xTrktNb(wavfile,k,MintwoPowerM,ula,doa1,bpf);
  %...................
  if ( flag > 0 )
 
    doa1 = doa1 + 1.5;
    if ( doa1 > 85.0 ) doa1 = -85.0; end;    
    [muSpk doa En SNR] = gMusik(1,dbyL,A'); sz = size(A);
    doain(indx) = doa1; doaout(indx) = doa(1);
    

%    if (k==20) 
    labelFigAud(k,wavfile,s,u,uwav,bpf,fs);  
    labelFigMu(doa1,sz,doa,muSpk,dbyL);   
%    end;
    pause;
    indx = indx + 1;
  end;
  %........................................................................
end
  figure(2);
  K=1:length(doain);
  subplot(211);plot(doain,doaout,'.r');grid;
  subplot(212);plot(K,doain,'.-r',K,doaout,'ob');grid;
