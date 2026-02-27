function [theta] = azimuth2doa(phi)
%[theta] = azimut2doa(phi) Summary of this function goes here
%   Detailed explanation goes here
kmax = length(phi);
for k=1:kmax
    if ( (phi(k) > -90  ) && (phi(k) < 90) )
        theta(k) = phi(k); 
    elseif ( (phi(k) < -90  )  )
        theta(k) = -phi(k)-180;
    else 
        theta(k) = -phi(k)+180;
    end;
end
end