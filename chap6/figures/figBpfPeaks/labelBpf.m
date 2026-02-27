function [] = labelBpf(wavfile,x,s,bpf,fs,pg,k)
%labelBpf(wavfile,x,s,bpf,fs,k) Summary of this function goes here
%   Detailed explanation goes here
delt = 1/fs; N = length(x); t=1:N;
fn = linspace(0,0.5,N/2);
if (length(s ) > 1)
figure(1)
subplot(311); plot(t*delt*1000,x,'b');grid;
title(['Decimated $\tilde{v}_k$(' num2str(N) ') ' num2str(k) ...
    ' block voice '  wavfile],'interpreter','latex');
xticks([0 25 50 75 100 128]);
xticklabels({'0','25mS','50mS','75mS','100mS','128mS'});
ylabel(' $\tilde{v}_k$ ', 'interpreter','latex');
%xlabel(' time in m Seconds ');
subplot(312); plot(fn*fs/1000,s,'-.k');grid; 
title(['Pitch Spectrum at block ' num2str(k)],'interpreter','latex');
xticks([bpf(1)/1000 0.5 bpf(2)/1000 2]);
xticklabels({'0.1','0.5kHz','1kHz','2kHz'});
ylabel(' $\tilde{V}_n$ ', 'interpreter','latex');
fp = pg(:,2); pk = pg(:,3); fpn = (fp/(N-1))*fs/1000;
hold on;
subplot(312);stem(fpn(1:3),pk(1:3),'r'); hold off;

% dominant peaks 1
xa(2) = fpn(1);   xa(1) = 0.8*xa(2);
ya(2) = pk(1);    ya(1) = 0.8*ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ['$p_a$'],...
    'Interpreter','latex','color','black','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';

% dominant peaks 2
xa(2) = fpn(2);   xa(1) = 0.8*xa(2);
ya(2) = pk(2);    ya(1) = 0.8*ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ['$p_b$'],...
    'Interpreter','latex','color','black','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';

% dominant peaks 3
xa(2) = fpn(3);   xa(1) = 0.8*xa(2);
ya(2) = pk(3);    ya(1) = 0.8*ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ['$p_c$'],...
    'Interpreter','latex','color','black','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';

end
end