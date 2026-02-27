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
function [] = labelgFKpeaks(bins,str,rgMat,rds,aspectRatio,fn,spk)
%[] = labelgFKpeaks(bins,str,rgMat,rds,aspectRatio,fn,spk) Summary of this function goes here
%   Detailed explanation goes here
        pkIndx = bins(1)+1;
        w = str(1,:);
        binsX(1,:) = rgMat(1,:); binsX(2,:) = rgMat(1,:);
        binsY(1,:) = abs(w)*0; binsY(2,:) = abs(w);

        cornX =[-1 0 1];
        s = pkIndx-3; e = pkIndx+3;
        phiPolar = linspace(0,360,rds);
        xk = cosd(phiPolar)*aspectRatio; yk = sind(phiPolar);

        plot(fn(s:e),spk(s:e),'.-b',binsX,binsY,'s-');grid;
        title(' Exact Peaks at 4 antenna elements ','interpreter', 'latex');
        xlabel('Normalized Frequency','interpreter', 'latex');
        ylabel('Amplitude','interpreter', 'latex');
        % labelling 4 antenna elements
        % First Phasor
        k = 1;
        s1 =['$w_1$ phasor ' num2str(angle(w(k))*180/pi,3) '$^o$'];
        xa =[rgMat(1,k)-0.001 rgMat(1,k)]; ya = [abs(w(k))-0.1 abs(w(k))];
        [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
        hT = annotation('textarrow',xaf,yaf,'String',s1,...
            'color','black','LineStyle','-.','interpreter', 'latex');
        hT.TextBackgroundColor = 'yellow';

        % Second Phasor
        k = 2;
        s1 =['$w_2$ phasor ' num2str(angle(w(k))*180/pi,3) '$^o$'];
        xa =[rgMat(1,k)+0.001 rgMat(1,k)]; ya = [abs(w(k)) abs(w(k))];
        [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
        hT = annotation('textarrow',xaf,yaf,'String',s1,...
            'color','black','LineStyle','-.','interpreter', 'latex');
        hT.TextBackgroundColor = 'yellow';

        % Third Phasor
        k = 3;
        s1 =['$w_3$ phasor ' num2str(angle(w(k))*180/pi,3) '$^o$'];
        xa =[rgMat(1,k)+0.002 rgMat(1,k)]; ya = [abs(w(k)) abs(w(k))];
        [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
        hT = annotation('textarrow',xaf,yaf,'String',s1,...
            'color','black','LineStyle','-.','interpreter', 'latex');
        hT.TextBackgroundColor = 'yellow';

        % Fourth Phasor
        k = 4;
        s1 =['$w_4$ phasor ' num2str(angle(w(k))*180/pi,3) '$^o$'];
        xa =[rgMat(1,k)-0.002 rgMat(1,k)]; ya = [abs(w(k))-0.1 abs(w(k))];
        [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
        hT = annotation('textarrow',xaf,yaf,'String',s1,...
            'color','black','LineStyle','-.','interpreter', 'latex');
        hT.TextBackgroundColor = 'yellow';

end