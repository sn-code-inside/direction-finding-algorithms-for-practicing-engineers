% Author: Kaluri V. Ranga Rao
% Visiting Scholar, Department of Computer Science,
% The Ohio State University
%
% Copyright (c) 2025 Kaluri V. Ranga Rao
% All rights reserved.
%
% This code is part of the material for the book:
% "Direction Finding Algorithms for Practicing Engineers,"
% published by Springer Nature.
%
% This material is intended for academic and research purposes only.
function [] = wbSpk(fn,spk,pkX,pkY,bins)
%wbSpk(fn,spk,pkX,pkY,bins) Summary of this function goes here
%   Detailed explanation goes here
        subplot(211);plot(fn,spk,'.-b',pkX,pkY,'s-r');grid;
        title(' Wide Band Signal Spectrum of $s_k$','interpreter', 'latex');
        xlabel('Normalized Frequency','interpreter', 'latex');
        ylabel('Amplitude','interpreter', 'latex');
        %   peak index labeling
        pkIndx = bins(1)+1;
        xa =[fn(pkIndx)+0.2 fn(pkIndx)]; ya = [spk(pkIndx) spk(pkIndx)];
        [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
        hT = annotation('textarrow',xaf,yaf,'String',...
        ['Target at $f_i= $' num2str(xa(2))],'color','blue','LineStyle','-.','interpreter', 'latex');
        hT.TextBackgroundColor = 'yellow';
        axes('pos',[.065 .65 1.4 .27]); %lower left corner (0.065 0.65) and width and height (1.4,0.27)
        imshow('twoBot.jpg');
end