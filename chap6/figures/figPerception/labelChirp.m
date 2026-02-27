function [] = labelChirp(indx,indA,chp,scale)
%[] = labelChirp(indx,indA) Summary of this function goes here
%   Detailed explanation goes here
%%
% label Delta t
  xc = indx(2) + (indx(3)-indx(2))*0.6; yc = max(chp*0.2);
  xa = [xc indx(3)];
  ya = [yc  yc];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['$\Delta t$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';

% arrow left side
  xc = indx(2) + (indx(3)-indx(2))*0.4; 
  xa = [xc indx(2)];
  ya = [yc  yc];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('arrow',xaf,yaf,'color','black','LineStyle','-.'); 

%%

%%
% label tb
  xc = indx(1) + (indA(1)-indx(1))*0.6; yc = max(chp*0.3);
  xa = [xc indA(1)];
  ya = [yc  yc];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['$t_b$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';

% arrow left side
  xc = indx(1) + (indA(1)-indx(1))*0.4; 
  xa = [xc indx(1)];
  ya = [yc  yc];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('arrow',xaf,yaf,'color','black','LineStyle','-.'); 
%%
% N delta t and tChirp
  xc = indx(4) + (indA(4)-indx(3))*0.15; yc = max(chp*0.3);
  xa = [xc indx(4)];
  ya = [yc  yc];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['$N\delta t$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
% arrow right side
  xc = indA(3)*0.9; 
  xa = [xc indA(3)];
  ya = [yc  yc];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('arrow',xaf,yaf,'color','black','LineStyle','-.'); 
  text(xc*0.93,yc*0.93,['$t_{chirp}$'],'interpreter','latex','color','black');

% slope alpha
  indxA = 413;
  xc = indxA*0.9; yc = chp(indxA)*scale;
  xa = [xc indxA];
  ya = [yc  yc];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['slope $\alpha$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
% insert image
  bounds = axis;
  boxa = [480 1 150 bounds(4)*0.9]; %[xb yb xt yt] of box
  boxb = dsxy2figxy(boxa);
  axes('pos',boxb);
  imshow('scene.jpg');

end