clc; clear all;
close all;
wavfile = 'sr2T.wav';
dbyl = 0.5;
ula = 6; doaIn = 35
doa1 = -85;
MintwoPowerM = 10;
bpf =[100 1000];
waveletWindow = 64;
indx = 1;
for k=0:365
  [u,s,flag,fs,A,dbyL,uwav,pitch,At] = xTrktNb(wavfile,k,MintwoPowerM,ula,doaIn,bpf);
  inDoa(indx) = doaIn; dbyl(indx) = dbyL;

  %...................
  if ( flag > 0 )

    [x,sp,z,pC,bins,pg] = voice2pitch(u,3,k,waveletWindow);
    [sx,phi,f] = Spk(x,1);
    [sxm ind] = max(sx); F0(indx) = f(ind);

    p = real(pC);

    [muSpk doa En SNR] = gMusik(1,dbyL,A'); sz = size(A);
    outDoa(indx) = doa;
    if ( k==82) 
    save('del.mat','wavfile','doaIn','doa','muSpk','dbyL','k');    
    end;
    indx = indx + 1; 
    if (doaIn < -80 ) doaIn = 80; end;
  end;

  %........................................................................
end
kmax = k;
load del;
labelFigMu(wavfile,doaIn,doa,muSpk,dbyL,k,inDoa,outDoa,dbyl,kmax);

