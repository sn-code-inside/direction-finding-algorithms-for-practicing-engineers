function [] = labelFigDbyL(doaEst,dbyl)
%[] = labelFigDbyL(doaEst,dbyl) Summary of this function goes here
%   Detailed explanation goes here
  figure(1)
  subplot(313);plot(doaEst,dbyl,'.b');grid;
  xlabel(' DOA in Degrees ','interpreter','latex');  
  title('DOA and Pitch Variations','interpreter','latex');
  ylabel(' Pitch Freq in Hz ','interpreter','latex');
end
