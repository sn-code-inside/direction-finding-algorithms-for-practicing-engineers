function [x,y,tw,Jk,t,x1,x2,rkDot,detect] = intWaves(N,Tau,Cycles,nSize,SNR,control)
%[x,y,tw,Jk,t,x1,x2,rkDot,detect] = intWaves(N,Tau,Cycles,nSize,SNR) 
%   Summary of this function goes here
%   Detailed explanation goes here
phiD = 10;
[data tow snr]=synthData(N,Tau,Cycles,nSize,SNR,phiD);
t = data(1,:); x1 = data(2,:); x2 = data(3,:); x3 = data(4,:);
[wData rkDot dir detect] = DetectSigWin(N,data);
tw = wData(1,:); x1w = wData(2,:); x2w = wData(3,:); x3w = wData(4,:);
figure(1);
subplot(311);plot(tw,x1w,'.-r',tw,x2w,'.-b');grid;
[tow shift Jk] = intDelay(N,wData,detect,control);
x = wData(3,:); y = shift;
end
