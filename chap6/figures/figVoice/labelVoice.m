function [] = labelVoice(wavfile,uwav,fs,bpf,k)
%labelVoice(uwav,fs,bpf,k) Summary of this function goes here
%   Detailed explanation goes here
    figure(1); N = length(uwav);
    kw = 1:N;
    subplot(311); plot(1000*kw/(2*fs),uwav,'.-r');grid;
    title(['Voice $v_k$(' num2str(N) ') ' wavfile ' ' ... 
        num2str(k)],'interpreter','latex');
    xticks([0 25 50 75 100 128]);
    xticklabels({'0','25mS','50mS','75mS','100mS','128mS'});
    ylabel(' $v_k$ ','interpreter','latex');

    [sxw phiu fw] =Spk(uwav,1);
    subplot(312); plot(fw*fs*2/1000,sxw,'.-b');grid;
    title(' Voice Spectrum $|V_n|$ ','interpreter','latex');
    xticks([bpf(1)/1000 bpf(2)/1000 3 4])
    xticklabels({'0.1','1kHz','3kHz','4'})
    ylabel(' $|V_n|$ ','interpreter','latex');

% arrow for pitch band
    xa(2) = 1;   xa(1) = 0.77;
    ya(2) = 0.12; ya(1) = 0.12;
    [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
    hT = annotation('textarrow',xaf,yaf,'String', ['Formant'],...
    'Interpreter','latex','color','black','LineStyle','-.');
    hT.TextBackgroundColor = 'yellow';

    xa(2) = 0.1;   xa(1) = 0.3;
    ya(2) = 0.12; ya(1) = 0.12;
    [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
    hT = annotation('arrow',xaf,yaf,'color','black','LineStyle','-.');



end