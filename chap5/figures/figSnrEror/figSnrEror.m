clc;
clear all; close All;
load snrFig
subplot(311);plot(sNrAm,sigmaEkAm,'s-r','MarkerSize', 4,'MarkerFaceColor','r');grid
hold on; plot(sNrT,sigmaEkT,'o-b','MarkerSize', 4,'MarkerFaceColor','b'); hold off;
title(['Accuracy of 3-ULA size ' num2str(m,3)],'interpreter', 'latex')
s1 = ['$\frac{d}{\lambda}=$ ' num2str(d_by_lambda,3) ...
    ' $r=$ ' num2str(r,3) ' $f_n=$ ' num2str(fn,3)];
subtitle(s1,'interpreter', 'latex');
xlabel(' Signal to Noise Ratio in dB ','interpreter', 'latex')
ylabel(' $\sigma$ of $\hat\theta^\circ$ ','interpreter', 'latex');
legend(' NB Signal with Noise ',' Pure Tone with Noise ','location','best');