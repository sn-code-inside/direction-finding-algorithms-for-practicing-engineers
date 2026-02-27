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
function [] = labelPhasors(str)
%[] = labelPhasors(str) Summary of this function goes here
%   Detailed explanation goes here
        phiPolarR = linspace(0,2*pi,64);
        R = ones(size(phiPolarR));
        w = str(1,:);
        polarplot(angle(w),abs(w),'.r',angle(w),abs(w),'sb',phiPolarR,R,'.-k');
        s1 = [ ' $\underbrace{' num2str(w(1),3) '}\atop w_1$' ' ' ...
               ' $\underbrace{' num2str(w(2),3) '}\atop w_2$' ' ' ...
               ' $\underbrace{' num2str(w(3),3) '}\atop w_3$' ' ' ...
               ' $\underbrace{' num2str(w(4),3) '}\atop w_4$'];
        s2 = ['weighting vector ${\bf{w}}$']; 
        s3 = ['\framebox{$b(z) = w_1 + w_2z^{-1} + w_3z^{-2} + w_4z^{-3}$}'];
        
        title(s1,"Position","HorizontalAlignment","center",'color','black','interpreter', 'latex');
        subtitle(s2,"Position",[270,1.25],"HorizontalAlignment",...
            "center",'color','black','interpreter', 'latex')
        text(200*pi/180,0.7,s3,'color','black','interpreter', 'latex');

        tha =[225 240]*pi/180; ra = [0.8 1];
        [xaf,yaf] = polarDS2nfu(tha,ra); % Convert to normalized figure units
        hT = annotation('textarrow',xaf,yaf,...
            'String','unit circle','color','blue','LineStyle','-.');
        hT.TextBackgroundColor = 'yellow';


        for j=1:length(w)
        tha =[0 angle(w(j))]; ra =[0 abs(w(j))];
        [xaf,yaf] = polarDS2nfu(tha,ra); % Convert to normalized figure units
        if (j == 1) hT = annotation('arrow',xaf,yaf,...
                'color','red','LineStyle','-.'); end;
        if (j == 2) hT = annotation('arrow',xaf,yaf,...
                'color','blue','LineStyle','-.'); end;
        if (j == 3) hT = annotation('arrow',xaf,yaf,...
                'color','black','LineStyle','-.'); end;
        if (j == 4) hT = annotation('arrow',xaf,yaf,...
                'color','green','LineStyle','-.'); end;
        end
end