clc; clear all;
close all;
v = 343; f = 1000; d=3.8;
lambda = 34.3;
fs = 16000; p = 1; samples = 256;
delt = 1/fs; pSnap = 100;
maxk = 55; blockCt = 1;
D = 1; dbyl = 0.11; phimax = dbyl*360;

for i = 1:15
file =['ula' num2str(i)]; cmd = ['load ' file ];
eval(cmd);
% .................
s = 1; 
    for k=1:maxk
    e = s + 255;    
    x = Data(s:e,:);
    B = hilbert(x);
    [muSpk, doa, En, SNR] = gMusik(D,dbyl,B);
    tgt(p) = doa;  u = B(:,1);
        if ( p == pSnap ) 
        save('del.mat','muSpk','fs','B','dbyl','doa','pSnap')
        doap = doa;
        end
    s = e + 1; p = p + 1;
    end
blocks =1:p-1;
end
load del;
label211(muSpk,fs,B,dbyl,doa,pSnap,blocks,tgt);



