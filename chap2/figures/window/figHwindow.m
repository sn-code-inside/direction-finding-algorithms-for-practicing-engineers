clc; clear all;
close all;
N=10;f=1/N;kmax=31; K=0:kmax;Mark=K*0+16;
x=cos(2*pi*f*K);
% hamming window
w=hamming(kmax+1); x=x.*w';
subplot(221)
plot(K,x,'o-b','MarkerSize',3,'MarkerFaceColor','b');grid;
xlabel(' samples ')
title(' $w_k=0.54 -0.46\cos\frac{2\pi k}{N-1}$ ','color','red','interpreter','latex');
xlabel(' samples $k$','interpreter','latex');
ylabel('$x_k\times w_k$ ','interpreter','latex')
hold; subplot(221); plot(K,w,'.r'); hold off;
% wk
bin = 25;
xa = [20 bin]; ya = [-0.5 w(bin)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['$w_k$'],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';


subplot(222)
sx=abs(fft(x));
stem(K,sx,'b');grid;title('Hamming Window DFT ','interpreter','latex');
xlabel(' Freq bin # ')
xlabel(' Freq bin \# $n$','interpreter','latex');
ylabel('$|s(\omega)|$ ','interpreter','latex');
yticks([0 5 10 16 20]);
yticklabels({'0','5','10','16','20'});
%bin 3
bin = 3;
xa = [10 bin]; ya = [5 3.5];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['bin ' num2str(bin)],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
% bin 29
bin = 29;
xa = [20 bin]; ya = [2 3.5];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['bin ' num2str(bin)],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

hold;plot(K,Mark,'.r');
