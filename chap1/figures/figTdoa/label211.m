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
function [] = label211(x1,x2,T,t,SNR)
%[] = label211(inputArg1,inputArg2) Summary of this function goes here
% Labeling subplot(211);
  %.... xA
  [x1m,ind] = max(x1);
  xa =[t(ind-100) t(ind)]; ya = [x1m x1m];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String','$x_A$','color','red','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
  %.... xB
  [x1m,ind] = max(x2);
  xa =[t(ind+100) t(ind)]; ya = [x1m x1m];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String','$x_B$','color','blue','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
  %... SNR value
  %[x1m,ind] = max(f);
  text(t(ind+160),x1m,['SNR $=10\log(\frac{1}{\sigma^2})$ = ' num2str(SNR) ' dB'],'color','black','interpreter', 'latex');

  %.... Detection Window
  xa =[T(length(T))+10 T(length(T))]; ya = [0.25 0.25];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String','Detection Window','color','black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
end