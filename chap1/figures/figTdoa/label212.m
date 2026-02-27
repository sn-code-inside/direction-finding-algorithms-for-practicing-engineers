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
function [] = label212(f,T,y1,c,tou,N)
%[] = label212(f,T,y1) Summary of this function goes here
%  label subplot(212);
  %.... estimated coarse xB
  [x1m,ind] = max(f);
  %xa =[T(ind+20) T(ind+7)]; ya = [f(ind+7)+0.3 f(ind+7)+0.3];
  xa =[T(ind+20) T(ind+9)]; ya = [c(ind+9) c(ind+9)];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String','$\tilde{x}_B$','color','black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
  %... estimated fine xB
  [x1m,ind] = min(f);
  %xa =[T(ind+20) T(ind+7)]; ya = [f(ind+7)+0.3 f(ind+7)+0.3];
  xa =[T(ind+20) T(ind)]; ya = [f(ind) f(ind)];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String','$\hat{x}_B$','color','black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';

  %.... estimated delay
  [x1m,ind] = max(y1); [x2m,ind2] = max(f); offset = fix((ind2 - ind)/2);
  xa =[T(ind+offset-1) T(ind)]; ya = [x1m x1m]; tend = T(ind+offset+4);
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String','$\hat\tau$','color','black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
  % ....
  [x2m,ind] = max(f);
  xa =[tend T(ind)]; ya = [x1m x1m];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('arrow',xaf,yaf,'color','black','LineStyle','-.');
  % ....
  [x1m,ind] = max(f);
  text(T(ind+35),x1m*0.90,['Delay $\hat\tau$ = ' num2str(tou(1)) ' Cycles'],'color','black','interpreter', 'latex');
  text(T(ind+35),x1m*0.65,['Integer $n$ = ' num2str(tou(2)*N) ' Samples'],'color','black','interpreter', 'latex');
  text(T(ind+35),x1m*0.4,['Fine $\epsilon$ = ' num2str(tou(3)*N) ' Samples'],'color','black','interpreter', 'latex');
end