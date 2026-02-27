function [] = labelPitch(x,s,pg,fs,wavfile,pA,p,k,fn,bpf)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
delt = 1/fs; N = length(x); t=1:N; %fn = linspace(0,0.5,N/2);
if (length(s ) > 1)
figure(2)
subplot(321); plot(t*delt*1000,x,'b');grid;
title([num2str(k) ' block voice '  wavfile],'interpreter','latex');
xticks([0 50 100 150]);
xticklabels({'0','50mS','100mS','150'});
ylabel(' Amplitude ', 'interpreter','latex');
%xlabel(' time in m Seconds ');
subplot(322); plot(fn*fs/1000,s,'-.k');grid; 
title(['Pitch Spectrum at block ' num2str(k)],'interpreter','latex');
xticks([bpf(1)/1000 0.5 bpf(2)/1000 2]);
xticklabels({'0.1','0.5kHz','1kHz','2kHz'});
end
fp = pg(:,2); pk = pg(:,3); fpn = (fp/(N-1))*fs/1000;
hold on;
subplot(322);stem(fpn(1:3),pk(1:3),'r'); hold off;

subplot(312); plot(t*delt*1000,p');grid;
ylabel(' Pitch Energy ','interpreter','latex');
xticks([0 20 40 60 80 100 120 140]);
xticklabels({'','20mS','','60mS','','100mS','','140mS'});

subplot(313);plot(t*delt*1000,pA,'.-r',N*delt*1000,0);grid;
title (['Pitch Variation over Block ' num2str(k)],'interpreter','latex');
ylabel(' Pitch in Hz ','interpreter','latex');
xticks([0 20 40 60 80 100 120 140]);
xticklabels({'','20mS','','60mS','','100mS','','140mS'});
end