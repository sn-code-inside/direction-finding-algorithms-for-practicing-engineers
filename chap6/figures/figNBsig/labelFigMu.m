function [] = labelFigMu(wavfile,doa1,doa,muSpk,dbyL,k,outDoa,inDoa,dbyl,kmax)
%[] = labelFig1(doa1,sz,doa,muSpk,dbyL) Summary of this function goes here
%   Detailed explanation goes here
  figure(1)
  %doaout = doa; 
  numberOfSamples = length(muSpk);
  phi = linspace(-180, 180, numberOfSamples);
 
  sth = phi/(360*dbyL);
  ind = find(abs(sth) < 1.0);
  vMuSpk = muSpk(ind);
  theta = -asind(phi(ind)/(360*dbyL));
  X =[-doa -doa]; Y =[0 max(vMuSpk)*1.1];  
  subplot(311);plot(theta,vMuSpk,'.-b',X,Y,'.-r');grid;
  xlabel(' DOA $\theta^o$ ','interpreter','latex'); 
  ylabel(' $J(\theta)$ ','interpreter','latex');
  title([wavfile ' Block ' num2str(k) '; Est ' ...
      num2str(-doa,3) '$^o$; True ' ... 
  num2str(-doa1,3) '$^o$; $\frac{d}{\lambda}=F_0\frac{d}{c}=$ ' ...
  num2str(dbyL,3)],'interpreter','latex');

  % MUSIC peak
  % [vMu ind] = max(vMuSpk);
  % xa(2) = theta(ind);   xa(1) = -2*abs(xa(2));
  % ya(2) = vMuSpk(ind);  ya(1) = 0.8*ya(2);
  % [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  % hT = annotation('textarrow',xaf,yaf,'String', ...
  %     ['$\theta_{MUSIC}$ ' num2str(theta(ind),3) '$^o$'],...
  %   'Interpreter','latex','color','black','LineStyle','-.');
  % hT.TextBackgroundColor = 'yellow';

  % gold MUSIC peak
  xa(2) = X(2);   xa(1) =2*abs(xa(2));
  ya(2) = Y(2);  ya(1) = 0.8*ya(2);
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String', ...
      ['$\theta_{gMUSIC}$ ' num2str(-doa,3) '$^o$'],...
    'Interpreter','latex','color','black','LineStyle','-.');
  hT.TextBackgroundColor = 'yellow';

% errors at an angle
i = find(dbyl < 0.1); ek = outDoa - inDoa;
j = find(dbyl > 0.1); 
sig=std(ek(j)); sige = std(ek(i));
subplot(312); plot(dbyl(i),ek(i),'.r',dbyl(j),ek(j),'.b');grid
title([wavfile ' ' num2str(kmax,3) ' blocks used for $\sigma$ estimate' ],'Interpreter','latex');
xlabel('$\frac{d}{\lambda}=F_0\frac{d}{c}$','Interpreter','latex');
ylabel('$e_k$','Interpreter','latex');

  % errors
  xa(2) = dbyl(150);   xa(1) =1.2*abs(xa(2));
  ya(2) = ek(150);     ya(1) = 0.8*ya(2);
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String', ...
      ['$\sigma_\theta$ ' num2str(sig,3) '$^o$'],...
    'Interpreter','latex','color','black','LineStyle','-.');
  hT.TextBackgroundColor = 'yellow';

  xa(2) = dbyl(20);   xa(1) =1.2*abs(xa(2));
  ya(2) = ek(20);     ya(1) = 0.8*ya(2);
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String', ...
      ['$\sigma_\theta$ ' num2str(sige,3) '$^o$'],...
    'Interpreter','latex','color','black','LineStyle','-.');
  hT.TextBackgroundColor = 'yellow';



end