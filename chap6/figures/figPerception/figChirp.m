clc; clear all;
close all;
kmax = 512; tb = 39; tChp = 128; scale = 0.6;

K=1:kmax;
chp = mod(K,tChp); chy = chp;
ind = find(chp > tb); chp(ind) = chp(ind)*0;
tik = filter([1 -1],1,chp); indx = find(tik < 0);
tiks = filter([1 -1],1,chy); indA = find(tiks < 0);

xtik =sort([indx indA]);
subplot(311);plot(K,chp*scale,'r');grid;
xticks([xtik(1:6)]); xticklabels({'','','','','',''});
yticks([]);
title('Chirping of FMCW Radar','interpreter', 'latex');
ylabel('FMCW Signal','interpreter', 'latex');
xLabel(kmax,indA,indx);
labelChirp(indx,indA,chp,scale);
