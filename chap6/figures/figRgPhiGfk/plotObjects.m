function rphi = plotObjects(clouds,k,annotation)
%plotObjects(clouds) Summary of this function goes here
%   Detailed explanation goes here
    sz = size(clouds); 
    rows = sz(1);
    figure(1);
    rphi(:,1) = clouds(:,7); rphi(:,2) = 90-clouds(:,8);
    delx = clouds(:,5); dely = clouds(:,3);
    delr = sqrt(delx.*delx + dely.*dely); delth = atan2(dely,delx)*180/pi;
    rphi(:,3) = delr; rphi(:,4) = delth;
    formatSpec = '%4.2f';
    rold = ['\bar{r} & \bar{\varphi} & \delta{r} & \delta\varphi'];
    for k=1:rows
    ri = [num2str(rphi(k,1),formatSpec) '&' num2str(rphi(k,2),formatSpec) '&' num2str(rphi(k,3),formatSpec) '&' num2str(rphi(k,4),formatSpec)];
    rnew = [rold '\cr' ri]; rold = rnew;
    end



    for i=1:rows
        sigx(i) = clouds(i,3); x(i) = clouds(i,4);
        sigy(i) = clouds(i,5); y(i) = clouds(i,6);
        [rCg,phiCg,r,phi,X,Y] = tgtpic(sigx(i),sigy(i),x(i),y(i));
        if (i==1)
            if ( k == 1 ) polarplot(phiCg,rCg,'.'); title(annotation);
            %xlabel('clustering of radar points');
            else polarplot(phi,r,'.'); grid; title(annotation); 
                %xlabel('clustering of radar points'); 
            end;
            hold on;
        else  
            if ( k == 1 ) polarplot(phiCg,rCg,'.');
            else polarplot(phi,r,'.'); grid; end;
        end
    end
        LightBlue = [0 0.4470 0.7410];
        text(210*pi/180,15,['${\bf{S}}(t)=\pmatrix{' rnew '}$'],...
            'color',LightBlue,'Interpreter','latex');
        thetaticks([0 30 60 120 150 180]);
        thetaticklabels({'90^o','60^o','30^o','-30^o','-60^o','-90^o'});
end
