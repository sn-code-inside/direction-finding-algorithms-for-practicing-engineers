clc; clear all;
close all;
wavfile = 'sr2T.wav';
dbyl = 0.5;
ula = 6; doa2 = -30;
doa1 = -85; theta = 10;
MintwoPowerM = 10;
bpf =[100 1000];
waveletWindow = 64;
indx = 1;
for k=0:100
  [u,s,flag,fs,A,dbyL,uwav,pitch,At] = xTrktNb(wavfile,k,MintwoPowerM,ula,theta,bpf);
    
  %...................
  if ( flag > 0 )
    [x,sp,z,pC,bins,pg] = voice2pitch(u,3,k,waveletWindow);
    p = real(pC);
    [muSpk doa En SNR] = gMusik(1,dbyL,A'); sz = size(A);
    if ( k==82) 
    labelUlaPhase(At,dbyL,theta);
    pause; 
    end;
  end;
  
end

