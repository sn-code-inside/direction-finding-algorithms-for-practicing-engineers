function [] = labelNB(k,wavfile,s,u,uwav,bpf,fs)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
%delt = 1/fs; N = length(x); t=1:N; 
  N = length(s);   ks = 1:N; %kw = 1:length(uwav);
  [sx phiu f] =Spk(s,1); [su phiu f] =Spk(u,1);
  [pk ind] = max(sx); fn = ind/N;
  X=[f(ind) f(ind)]*fs/1000; Y =[pk 0];
  if (length(s ) > 1)
  figure(1)
  subplot(311); plot(1000*ks/fs,s,'.-r');grid;
  title([wavfile ' ' num2str(k) ' NB Signal $x_k$ at $F_0$ ' ...
      num2str(fs*fn,4) ' Hz'],'interpreter','latex');
  xticks([0 25 50 75 100 128 150]);
  xticklabels({'0','25mS','50mS','75mS','100mS','128mS','150'});
  ylabel('$x_k$','interpreter','latex');

  subplot(312); plot(f*fs/1000,sx,'.-b',f*fs/1000,su,'-.r',X,Y,'o-k');grid;
  xticks([bpf(1)/1000 0.25 0.5 X(1) bpf(2)/1000 1.5 2]);
  xticklabels({'0.1','0.25kHz','0.5kHz','F_0','1kHz','1.5kHz','2kHz'});
  title(['NB Spectrum $X_n$ at $F_0$ ' num2str(fs*fn,4) ' Hz'],'interpreter','latex');
  ylabel('$|X_n|$ and $|\tilde{V}_n|$','interpreter','latex');

% Formant Spectrum
xa(2) = f(105)*fs/1000; xa(1) = 1.2*xa(2);
ya(2) = su(105);        ya(1) = 1.2*ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ['$|\tilde{V}_n|$'],...
    'Interpreter','latex','color','black','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';

% Narrow Band Spectrum
xa(2) = f(75)*fs/1000; xa(1) = 1.2*xa(2);
ya(2) = sx(75);        ya(1) = 1.2*ya(2);
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ['$|{X}_n|$'],...
    'Interpreter','latex','color','black','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';

end