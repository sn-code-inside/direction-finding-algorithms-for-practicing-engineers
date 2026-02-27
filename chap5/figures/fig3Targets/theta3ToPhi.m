function [] = theta3ToPhi(phiA, phiB, phiC)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
Y = [phiA phiB phiC];
thold = 4; theta=0; thetaA = 0; thetaB = 0;
for k = 1:length(Y)
    for m = k:length(Y)
        if ( k ~= m )
        xp = Y(m); yp = Y(k);
        X1 = sind(xp) - sind(yp); Y1 = cosd(xp) - cosd(yp);
        J1 = atan2(Y1,X1)*180/pi; 
        
        
        J2 = J1 - yp;
        
        s90 = abs(J1 + 90); 
		s180 = abs(J1 + 180); 
        s60 = abs(J1 + 60);
        s150 = abs(J1 - 150);
        S = [ii xp yp s90 s180 s60 s150]

% ... this is for negative angles ....        
            inc = 0;
            if ( (s90 < thold) || (s180 < thold) )
                display([num2str(ii) '  Negative Theta ']);
                if ( abs(xp+yp) < thold ) theta(n) = (abs(xp) + abs(yp))*0.5;
                else 
                    if ( xp < yp ) theta(n) = xp; else theta(n) = yp; end
                end
                theta(n) = (-1)*theta(n); inc = 1;
            else
 % ... let us work positve angles ... 
                display([num2str(ii) ' Positive Theta ']);
                pair(n,:) = [ii xp yp J1 J2 s60 s150] 
                thold
                if ( s150 < thold )
                    if ( xp > yp ) thetaA = xp; else thetaA = yp; end
                    inc = 1;
                end
                s150
                thetaA
                    if ( s60 < thold )
                        if ( xp < yp ) thetaB = xp; else thetaB = yp; end
                        inc = 1;
                    end
                        thetaB
                       
                        if ( abs(thetaA - thetaB) < thold ) theta(n) = (thetaA + thetaB)*0.5
                        else if ( abs(thetaA) > abs(thetaB) ) theta(n) = thetaA; else theta(n) = thetaB; end
                        end
             
 %               end
 %   .... 
            end
            n = n+inc 
            theta
        end
    end
end


end